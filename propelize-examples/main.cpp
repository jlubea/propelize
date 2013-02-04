#include "Magick++.h"
#include "propelize/algorithms/gpu/support/convert_magick.h"
#include "propelize/algorithms/gpu/dilation.h"
#include "propelize/algorithms/gpu/erosion.h"

namespace pag = propelize::algorithms::gpu;
namespace pags = propelize::algorithms::gpu::support;
namespace cn = concurrency;

int main(int argc, char **argv)
{
	Magick::Image image("test.bmp");
	image.write("test_images/test.png");
	
	cn::array<uint32_t, 2> amp_buffer(1, 1);
	pags::ConvertFromMagickImage(image, amp_buffer);
	cn::array<uint32_t, 2> amp_output(amp_buffer.extent, amp_buffer.accelerator_view);

	uint32_t square3x3[9];
	uint32_t square5x5[25];
	uint32_t square11x11[121];

	for (int i = 0; i < 9; ++i) square3x3[i] = 1;
	for (int i = 0; i < 25; ++i) square5x5[i] = 1;
	for (int i = 0; i < 121; ++i) square11x11[i] = 1;

	cn::array<uint32_t, 2> kernel(3, 3, square3x3);
	//cn::array<uint32_t, 2> kernel(5, 5, square5x5);
	//cn::array<uint32_t, 2> kernel(11, 11, square11x11);
	pag::Dilation dilation(kernel);
	pag::Erosion erosion(kernel);

	Magick::Image output;

	erosion(amp_buffer, amp_output);
	dilation(amp_output, amp_buffer);
	output = pags::ConvertToMagickImage(amp_buffer);
	output.write("test_images/test.output.opening.png");

	
	pags::ConvertFromMagickImage(image, amp_buffer);
	dilation(amp_buffer, amp_output);
	erosion(amp_output, amp_buffer);
	output = pags::ConvertToMagickImage(amp_buffer);
	output.write("test_images/test.output.closing.png");


	pags::ConvertFromMagickImage(image, amp_buffer);
	erosion(amp_buffer, amp_output);
	output = pags::ConvertToMagickImage(amp_output);
	output.write("test_images/test.output.erosion.png");


	pags::ConvertFromMagickImage(image, amp_buffer);
	dilation(amp_buffer, amp_output);
	output = pags::ConvertToMagickImage(amp_output);
	output.write("test_images/test.output.dilation.png");

	return 0;
}