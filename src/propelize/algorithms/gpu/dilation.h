#ifdef _WIN32
# pragma once
#endif

#ifndef PROPELIZE_ALGORITHMS_GPU_DILATION_H
#define PROPELIZE_ALGORITHMS_GPU_DILATION_H

#include "propelize/platform/exports.h"

#ifdef _WIN32
# include <amp.h>
#endif

namespace propelize { namespace algorithms { namespace gpu {

	class PROPELIZE_API Dilation
	{
	public:
		Dilation(concurrency::array<uint32_t, 2> &kernel) :
			_kernel(kernel)
		{
		}

		void operator()(concurrency::array<uint32_t, 2> &image, concurrency::array<uint32_t, 2> &output);

	private:
		concurrency::array<uint32_t, 2> &_kernel;
	};

}
}
}

#endif