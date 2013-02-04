#include "propelize/algorithms/gpu/support/kernel.h"

namespace propelize { namespace algorithms { namespace gpu { namespace support {

	PROPELIZE_API void convert_kernel(const propelize::algorithms::cpu::support::kernel &k, concurrency::accelerator_view av, concurrency::array<uint32_t, 2> &out)
	{
		out = concurrency::array<uint32_t, 2>(k.rows(), k.cols(), k.get().get(), av);
	}

}
}
}
}
