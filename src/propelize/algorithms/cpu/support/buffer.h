#ifdef _WIN32
# pragma once
#endif

#ifndef PROPELIZE_ALGORITHMS_CPU_SUPPORT_BUFFER_H
#define PROPELIZE_ALGORITHMS_CPU_SUPPORT_BUFFER_H

#include "propelize/platform/exports.h"

#include <stdint.h>
#include <boost/shared_array.hpp>

namespace propelize { namespace algorithms { namespace cpu { namespace support {

	class PROPELIZE_API buffer
	{
	public:
		buffer(int rows, int cols);
		buffer(int rows, int cols, boost::shared_array<uint32_t> &toOwn);
		buffer(const buffer &that);

		void reset(int rows, int cols);
		void reset(int rows, int cols, boost::shared_array<uint32_t> &toOwn);

		boost::shared_array<uint32_t> &get();
		const boost::shared_array<uint32_t> &get() const;
		int rows() const;
		int cols() const;

		uint32_t &operator()(int row, int col);
		const uint32_t operator()(int row, int col) const;

	private:
		boost::shared_array<uint32_t> _buffer;
		int _rows;
		int _cols;
	};

}
}
}
}

#endif