#include "propelize/algorithms/cpu/support/kernel.h"

namespace propelize { namespace algorithms { namespace cpu { namespace support {

	kernel::kernel(const buffer &k) :
		_kernel(k)
	{
	}

	boost::shared_array<uint32_t> &kernel::get()
	{
		return _kernel.get();
	}

	const boost::shared_array<uint32_t> kernel::get() const
	{
		return _kernel.get();
	}

	int kernel::rows() const
	{
		return _kernel.rows();
	}

	int kernel::cols() const
	{
		return _kernel.cols();
	}

	uint32_t &kernel::operator()(int row, int col)
	{
		return _kernel(row, col);
	}

	const uint32_t kernel::operator()(int row, int col) const
	{
		return _kernel(row, col);
	}

}
}
}
}
