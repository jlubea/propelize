#ifdef _WIN32
# pragma once
#endif

#ifndef PROPELIZE_ALGORITHMS_CPU_SUPPORT_KERNEL_H
#define PROPELIZE_ALGORITHMS_CPU_SUPPORT_KERNEL_H

#include "propelize/platform/exports.h"
#include "propelize/algorithms/cpu/support/buffer.h"

#include <stdint.h>
#include <boost/shared_array.hpp>

namespace propelize { namespace algorithms { namespace cpu { namespace support {

	class PROPELIZE_API kernel
	{
	public:
		kernel(const buffer &k);

		boost::shared_array<uint32_t> &get();
		const boost::shared_array<uint32_t> get() const;

		int rows() const;
		int cols() const;

		uint32_t &operator()(int row, int col);
		const uint32_t operator()(int row, int col) const;

	private:
		buffer _kernel;
	};

}
}
}
}

#endif