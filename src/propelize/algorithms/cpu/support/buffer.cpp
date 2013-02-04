#include "propelize/algorithms/cpu/support/buffer.h"

namespace propelize { namespace algorithms { namespace cpu { namespace support {

	buffer::buffer(int rows, int cols) :
		_rows(rows),
		_cols(cols),
		_buffer(new uint32_t[rows * cols])
	{
	}

	buffer::buffer(int rows, int cols, boost::shared_array<uint32_t> &toOwn) :
		_rows(rows),
		_cols(cols),
		_buffer(toOwn)
	{
	}

	buffer::buffer(const buffer &that) :
		_rows(that._rows),
		_cols(that._cols),
		_buffer(new uint32_t[that._rows * that._cols])
	{
		memcpy(_buffer.get(), that._buffer.get(), _rows * _cols * sizeof(uint32_t));
	}

	void buffer::reset(int rows, int cols)
	{
		_buffer.reset(new uint32_t[rows * cols]);
		_rows = rows;
		_cols = cols;
	}

	void buffer::reset(int rows, int cols, boost::shared_array<uint32_t> &toOwn)
	{
		_buffer = toOwn;
		_rows = rows;
		_cols = cols;
	}

	boost::shared_array<uint32_t> &buffer::get()
	{
		return _buffer;
	}

	const boost::shared_array<uint32_t> &buffer::get() const
	{
		return _buffer;
	}

	int buffer::rows() const
	{
		return _rows;
	}

	int buffer::cols() const
	{
		return _cols;
	}

	uint32_t &buffer::operator()(int row, int col)
	{
		return _buffer[row * _cols + col];
	}

	const uint32_t buffer::operator()(int row, int col) const
	{
		return _buffer[row * _cols + col];
	}

}
}
}
}
