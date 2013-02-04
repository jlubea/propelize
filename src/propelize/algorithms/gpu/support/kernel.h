#ifdef _WIN32
# pragma once
#endif

#ifndef PROPELIZE_ALGORITHMS_GPU_SUPPORT_KERNEL_H
#define PROPELIZE_ALGORITHMS_GPU_SUPPORT_KERNEL_H

#include "propelize/platform/exports.h"
#include "propelize/algorithms/cpu/support/kernel.h"

#ifdef _WIN32
# include <amp.h>
#endif

namespace propelize { namespace algorithms { namespace gpu { namespace support {

	PROPELIZE_API void convert_kernel(const propelize::algorithms::cpu::support::kernel &k, concurrency::accelerator_view av, concurrency::array<uint32_t, 2> &out);

}
}
}
}

#endif