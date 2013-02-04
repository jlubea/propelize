#ifdef _WIN32
# pragma once
#endif

#ifndef PROPELIZE_ALGORITHMS_COLOR_CHANNELS_H
#define PROPELIZE_ALGORITHMS_COLOR_CHANNELS_H

#define GET_RED(pixel)						(static_cast<uint32_t>(pixel) & 0xff)
#define GET_GRN(pixel)						((static_cast<uint32_t>(pixel) >> 8) & 0xff)
#define GET_BLU(pixel)						((static_cast<uint32_t>(pixel) >> 16) & 0xff)
#define GET_ALPHA(pixel)					((static_cast<uint32_t>(pixel) >> 24) & 0xff)

#define BUILD_RED(red)						(static_cast<uint32_t>(red) & 0xff)
#define BUILD_GRN(grn)						((static_cast<uint32_t>(grn) & 0xff) << 8)
#define BUILD_BLU(blu)						((static_cast<uint32_t>(blu) & 0xff) << 16)
#define BUILD_ALPHA(alpha)					((static_cast<uint32_t>(alpha) & 0xff) << 24)
#define BUILD_RGBA(red, grn, blu, alpha)	(BUILD_RED(red) | BUILD_GRN(grn) | BUILD_BLU(blu) | BUILD_ALPHA(alpha))
#define BUILD_RGBR(red, grn, blu)			(BUILD_RED(red) | BUILD_GRN(grn) | BUILD_BLU(blu) | BUILD_ALPHA(red))

#define SET_RED(pixel, red)			((static_cast<uint32_t>(pixel) & 0xffffff00) | BUILD_RED(red))
#define SET_GRN(pixel, grn)			((static_cast<uint32_t>(pixel) & 0xffff00ff) | BUILD_GRN(grn))
#define SET_BLU(pixel, blu)			((static_cast<uint32_t>(pixel) & 0xff00ffff) | BUILD_BLU(blu))
#define SET_ALPHA(pixel, alpha)		((static_cast<uint32_t>(pixel) & 0x00ffffff) | BUILD_ALPHA(alpha))

#define GET_CHANNEL(pixel, channel)				((static_cast<uint32_t>(pixel) >> (8*channel)) & 0xff)
#define SET_CHANNEL(pixel, channel, component)	((static_cast<uint32_t>(pixel) & ~static_cast<uint32_t>(0xff << (8*channel))) | (static_cast<uint32_t>(component) & 0xff) << (8*channel))

#define IS_IN_IMAGE(y, x, rows, cols)			(static_cast<int32_t>(y) >= 0 && static_cast<int32_t>(y) < static_cast<int32_t>(rows) && static_cast<int32_t>(x) >= 0 && static_cast<int32_t>(x) < static_cast<int32_t>(cols))
#define IS_IN_IMAGE_NO_CAST(y, x, rows, cols)	((y) >= 0 && (y) < (rows) && (x) >= 0 && (x) < (cols))

#define IS_IN_RANGE(value, lower, upper)		((value) > (lower) && (value) <= (upper))

#endif
