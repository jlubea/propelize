#include "propelize/algorithms/gpu/erosion.h"
#include "propelize/algorithms/color_channels.h"
#include "substasics/platform/exceptions.h"

namespace cn = concurrency;
namespace sp = substasics::platform;

namespace propelize { namespace algorithms { namespace gpu {

	void Erosion::operator()(concurrency::array<uint32_t, 2> &image, concurrency::array<uint32_t, 2> &output)
	{
		static const char *func = "Erosion::()";

		int filterYMid = _kernel.extent[0] / 2;
		int filterXMid = _kernel.extent[1] / 2;
		int maxY = image.extent[0] - filterYMid;
		int maxX = image.extent[1] - filterXMid;

		// these can be negative for very small images.
		if (maxX < 0 || maxY < 0)
		{
			throw sp::exception(func, "Image is too small for erosion with kernel dimensions: (%d, %d)", _kernel.extent[0], _kernel.extent[1]);
		}
		else
		{
			cn::array<uint32_t, 2> &kernel = _kernel;

			cn::parallel_for_each(
				image.accelerator_view,
				image.extent,
				[=, &image, &kernel, &output](cn::index<2> idx) restrict(amp)
				{
					int r = static_cast<int>(idx[0]);
					int c = static_cast<int>(idx[1]);

					// if the erosion kernel doesn't fit in the image at the current position
					if ((r - filterYMid) < 0
						|| (c - filterXMid) < 0
						|| (r + filterYMid) >= image.extent[0]
						|| (c + filterXMid) >= image.extent[1])
					{
						output[idx] = 0;
					}
					// apply the erosion kernel
					else
					{
						uint32_t minRed = MAXBYTE, minGrn = MAXBYTE, minBlu = MAXBYTE, minAlpha = MAXBYTE;

						// apply the filter to a local region
						for (int y = 0; y < kernel.extent[0]; ++y)
						for (int x = 0; x < kernel.extent[1]; ++x)
						{
							if (kernel(y, x) == 0) continue;

							int dx = -filterXMid + x;
							int dy = -filterYMid + y;

							uint32_t sourceP = image(r + dy, c + dx);
							uint32_t red = GET_RED(sourceP);
							uint32_t grn = GET_GRN(sourceP);
							uint32_t blu = GET_BLU(sourceP);
							uint32_t alpha = GET_ALPHA(sourceP);

							minRed = min(red, minRed);
							minGrn = min(grn, minGrn);
							minBlu = min(blu, minBlu);
							minAlpha = min(alpha, minAlpha);
						}

						if (minRed > 0 || minGrn > 0 || minBlu > 0 || minAlpha > 0)
						{
							int a = 3;
							a++;
						}

						output[idx] = BUILD_RGBA(minRed, minGrn, minBlu, minAlpha);
					}
				}
			);

			// Extend border.  We don't want to fill with black in case we do something like edge detection in a later algorithm.
			// In the future this fill policy will be configurable.

			// replace the left and right borders
			cn::extent<2> lrExt(image.extent[0], filterXMid);
			cn::parallel_for_each(
				image.accelerator_view,
				lrExt,
				[=, &image, &output](cn::index<2> idx) restrict(amp)
				{
					uint32_t leftSourceP = output(idx[0], filterXMid);
					uint32_t rightSourceP = output(idx[0], image.extent[1]-1 - filterXMid);

					output(idx[0], filterXMid - (idx[1] + 1)) = leftSourceP;
					output(idx[0], (image.extent[1]-1 - filterXMid) + (idx[1] + 1)) = rightSourceP;
				}
			);

			// replace the top and bottom borders
			cn::extent<2> tbExt(image.extent[1], filterYMid);
			cn::parallel_for_each(
				image.accelerator_view,
				tbExt,
				[=, &image, &output](cn::index<2> idx) restrict(amp)
				{
					uint32_t topSourceP = output(filterYMid, idx[0]);
					uint32_t bottomSourceP = output(image.extent[0]-1 - filterYMid, idx[0]);

					output(filterYMid - (idx[1] + 1), idx[0]) = topSourceP;
					output((image.extent[0]-1 - filterYMid) + (idx[1] + 1), idx[0]) = bottomSourceP;
				}
			);
		}
	}

}
}
}
