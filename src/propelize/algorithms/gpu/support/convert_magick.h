#ifdef _WIN32
# pragma once
#endif

#ifndef PROPELIZE_ALGORITHMS_GPU_SUPPORT_CONVERT_MAGICK_H
#define PROPELIZE_ALGORITHMS_GPU_SUPPORT_CONVERT_MAGICK_H

#include "propelize/platform/exports.h"

#include "Magick++.h"
#include <amp.h>

namespace propelize { namespace algorithms { namespace gpu { namespace support {

	PROPELIZE_API void ConvertFromMagickImage(const Magick::Image &source, concurrency::array<uint32_t, 2> &output);
	PROPELIZE_API Magick::Image ConvertToMagickImage(concurrency::array<uint32_t, 2> &image);

}
}
}
}

#endif