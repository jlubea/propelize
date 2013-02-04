#include "convert_magick.h"
#include <boost/shared_array.hpp>

namespace cn = concurrency;

namespace propelize { namespace algorithms { namespace gpu { namespace support {

	PROPELIZE_API void ConvertFromMagickImage(const Magick::Image &source, cn::array<uint32_t, 2> &output)
	{
		boost::shared_array<uint32_t> staging(new uint32_t[source.columns() * source.rows()]);
		const_cast<Magick::Image &>(source).write(0, 0, source.columns(), source.rows(), "RGBR", Magick::StorageType::CharPixel, staging.get());
		output = cn::array<uint32_t, 2>(static_cast<int>(source.rows()), static_cast<int>(source.columns()), staging.get(), output.accelerator_view);
	}

	PROPELIZE_API Magick::Image ConvertToMagickImage(cn::array<uint32_t, 2> &image)
	{
		boost::shared_array<uint32_t> staging(new uint32_t[image.extent[0] * image.extent[1]]);
		cn::copy(image, staging.get());
		Magick::Image output(image.extent[1], image.extent[0], "RGBR", Magick::StorageType::CharPixel, staging.get());
		return output;
	}

}
}
}
}