/*
 *  Copyright (c) 2011 The LibYuv project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "source/row.h"

#include <string.h>  // For memcpy

#include "libyuv/basic_types.h"

#ifdef __cplusplus
namespace libyuv {
extern "C" {
#endif

void ABGRToARGBRow_C(const uint8* src_abgr, uint8* dst_argb, int width) {
  for (int x = 0; x < width; ++x) {
    // To support in-place conversion.
    uint8 r = src_abgr[0];
    uint8 g = src_abgr[1];
    uint8 b = src_abgr[2];
    uint8 a = src_abgr[3];
    dst_argb[0] = b;
    dst_argb[1] = g;
    dst_argb[2] = r;
    dst_argb[3] = a;
    dst_argb += 4;
    src_abgr += 4;
  }
}

void BGRAToARGBRow_C(const uint8* src_bgra, uint8* dst_argb, int width) {
  for (int x = 0; x < width; ++x) {
    // To support in-place conversion.
    uint8 a = src_bgra[0];
    uint8 r = src_bgra[1];
    uint8 g = src_bgra[2];
    uint8 b = src_bgra[3];
    dst_argb[0] = b;
    dst_argb[1] = g;
    dst_argb[2] = r;
    dst_argb[3] = a;
    dst_argb += 4;
    src_bgra += 4;
  }
}

void RGB24ToARGBRow_C(const uint8* src_rgb24, uint8* dst_argb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_rgb24[0];
    uint8 g = src_rgb24[1];
    uint8 r = src_rgb24[2];
    dst_argb[0] = b;
    dst_argb[1] = g;
    dst_argb[2] = r;
    dst_argb[3] = 255u;
    dst_argb += 4;
    src_rgb24 += 3;
  }
}

void RAWToARGBRow_C(const uint8* src_raw, uint8* dst_argb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 r = src_raw[0];
    uint8 g = src_raw[1];
    uint8 b = src_raw[2];
    dst_argb[0] = b;
    dst_argb[1] = g;
    dst_argb[2] = r;
    dst_argb[3] = 255u;
    dst_argb += 4;
    src_raw += 3;
  }
}

void RGB565ToARGBRow_C(const uint8* src_rgb, uint8* dst_argb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_rgb[0] & 0x1f;
    uint8 g = (src_rgb[0] >> 5) | ((src_rgb[1] & 0x07) << 3);
    uint8 r = src_rgb[1] >> 3;
    dst_argb[0] = (b << 3) | (b >> 2);
    dst_argb[1] = (g << 2) | (g >> 4);
    dst_argb[2] = (r << 3) | (r >> 2);
    dst_argb[3] = 255u;
    dst_argb += 4;
    src_rgb += 2;
  }
}

void ARGB1555ToARGBRow_C(const uint8* src_rgb, uint8* dst_argb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_rgb[0] & 0x1f;
    uint8 g = (src_rgb[0] >> 5) | ((src_rgb[1] & 0x03) << 3);
    uint8 r = (src_rgb[1] & 0x7c) >> 2;
    uint8 a = src_rgb[1] >> 7;
    dst_argb[0] = (b << 3) | (b >> 2);
    dst_argb[1] = (g << 3) | (g >> 2);
    dst_argb[2] = (r << 3) | (r >> 2);
    dst_argb[3] = -a;
    dst_argb += 4;
    src_rgb += 2;
  }
}

void ARGB4444ToARGBRow_C(const uint8* src_rgb, uint8* dst_argb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 a = src_rgb[1] >> 4;
    uint8 r = src_rgb[1] & 0x0f;
    uint8 g = src_rgb[0] >> 4;
    uint8 b = src_rgb[0] & 0x0f;
    dst_argb[0] = (b << 4) | b;
    dst_argb[1] = (g << 4) | g;
    dst_argb[2] = (r << 4) | r;
    dst_argb[3] = (a << 4) | a;
    dst_argb += 4;
    src_rgb += 2;
  }
}

void ARGBToRGB24Row_C(const uint8* src_argb, uint8* dst_rgb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_argb[0];
    uint8 g = src_argb[1];
    uint8 r = src_argb[2];
    dst_rgb[0] = b;
    dst_rgb[1] = g;
    dst_rgb[2] = r;
    dst_rgb += 3;
    src_argb += 4;
  }
}

void ARGBToRAWRow_C(const uint8* src_argb, uint8* dst_rgb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_argb[0];
    uint8 g = src_argb[1];
    uint8 r = src_argb[2];
    dst_rgb[0] = r;
    dst_rgb[1] = g;
    dst_rgb[2] = b;
    dst_rgb += 3;
    src_argb += 4;
  }
}

// TODO(fbarchard): support big endian CPU
void ARGBToRGB565Row_C(const uint8* src_argb, uint8* dst_rgb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_argb[0] >> 3;
    uint8 g = src_argb[1] >> 2;
    uint8 r = src_argb[2] >> 3;
    *reinterpret_cast<uint16*>(dst_rgb) = (r << 11) | (g << 5) | b;
    dst_rgb += 2;
    src_argb += 4;
  }
}

void ARGBToARGB1555Row_C(const uint8* src_argb, uint8* dst_rgb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_argb[0] >> 3;
    uint8 g = src_argb[1] >> 3;
    uint8 r = src_argb[2] >> 3;
    uint8 a = src_argb[2] >> 7;
    *reinterpret_cast<uint16*>(dst_rgb) = (a << 15) | (r << 10) | (g << 5) | b;
    dst_rgb += 2;
    src_argb += 4;
  }
}

void ARGBToARGB4444Row_C(const uint8* src_argb, uint8* dst_rgb, int width) {
  for (int x = 0; x < width; ++x) {
    uint8 b = src_argb[0] >> 4;
    uint8 g = src_argb[1] >> 4;
    uint8 r = src_argb[2] >> 4;
    uint8 a = src_argb[2] >> 4;
    *reinterpret_cast<uint16*>(dst_rgb) = (a << 12) | (r << 8) | (g << 4) | b;
    dst_rgb += 2;
    src_argb += 4;
  }
}

static __inline int RGBToY(uint8 r, uint8 g, uint8 b) {
  return (( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16;
}

static __inline int RGBToU(uint8 r, uint8 g, uint8 b) {
  return ((-38 * r -  74 * g + 112 * b + 128) >> 8) + 128;
}
static __inline int RGBToV(uint8 r, uint8 g, uint8 b) {
  return ((112 * r -  94 * g -  18 * b + 128) >> 8) + 128;
}

#define MAKEROWY(NAME, R, G, B) \
void NAME ## ToYRow_C(const uint8* src_argb0, uint8* dst_y, int width) {       \
  for (int x = 0; x < width; ++x) {                                            \
    dst_y[0] = RGBToY(src_argb0[R], src_argb0[G], src_argb0[B]);               \
    src_argb0 += 4;                                                            \
    dst_y += 1;                                                                \
  }                                                                            \
}                                                                              \
void NAME ## ToUVRow_C(const uint8* src_rgb0, int src_stride_rgb,              \
                       uint8* dst_u, uint8* dst_v, int width) {                \
  const uint8* src_rgb1 = src_rgb0 + src_stride_rgb;                           \
  for (int x = 0; x < width - 1; x += 2) {                                     \
    uint8 ab = (src_rgb0[B] + src_rgb0[B + 4] +                                \
               src_rgb1[B] + src_rgb1[B + 4]) >> 2;                            \
    uint8 ag = (src_rgb0[G] + src_rgb0[G + 4] +                                \
               src_rgb1[G] + src_rgb1[G + 4]) >> 2;                            \
    uint8 ar = (src_rgb0[R] + src_rgb0[R + 4] +                                \
               src_rgb1[R] + src_rgb1[R + 4]) >> 2;                            \
    dst_u[0] = RGBToU(ar, ag, ab);                                             \
    dst_v[0] = RGBToV(ar, ag, ab);                                             \
    src_rgb0 += 8;                                                             \
    src_rgb1 += 8;                                                             \
    dst_u += 1;                                                                \
    dst_v += 1;                                                                \
  }                                                                            \
  if (width & 1) {                                                             \
    uint8 ab = (src_rgb0[B] + src_rgb1[B]) >> 1;                               \
    uint8 ag = (src_rgb0[G] + src_rgb1[G]) >> 1;                               \
    uint8 ar = (src_rgb0[R] + src_rgb1[R]) >> 1;                               \
    dst_u[0] = RGBToU(ar, ag, ab);                                             \
    dst_v[0] = RGBToV(ar, ag, ab);                                             \
  }                                                                            \
}

MAKEROWY(ARGB, 2, 1, 0)
MAKEROWY(BGRA, 1, 2, 3)
MAKEROWY(ABGR, 0, 1, 2)

void I400ToARGBRow_C(const uint8* src_y, uint8* dst_argb, int width) {
  // Copy a Y to RGB.
  for (int x = 0; x < width; ++x) {
    uint8 y = src_y[0];
    dst_argb[2] = dst_argb[1] = dst_argb[0] = y;
    dst_argb[3] = 255u;
    dst_argb += 4;
    ++src_y;
  }
}

// C reference code that mimics the YUV assembly.

#define YG 74 /* static_cast<int8>(1.164 * 64 + 0.5) */

#define UB 127 /* min(63,static_cast<int8>(2.018 * 64)) */
#define UG -25 /* static_cast<int8>(-0.391 * 64 - 0.5) */
#define UR 0

#define VB 0
#define VG -52 /* static_cast<int8>(-0.813 * 64 - 0.5) */
#define VR 102 /* static_cast<int8>(1.596 * 64 + 0.5) */

// Bias
#define BB UB * 128 + VB * 128
#define BG UG * 128 + VG * 128
#define BR UR * 128 + VR * 128

static __inline uint32 Clip(int32 val) {
  if (val < 0) {
    return static_cast<uint32>(0);
  } else if (val > 255) {
    return static_cast<uint32>(255);
  }
  return static_cast<uint32>(val);
}

static __inline void YuvPixel(uint8 y, uint8 u, uint8 v, uint8* rgb_buf,
                              int ashift, int rshift, int gshift, int bshift) {
  int32 y1 = (static_cast<int32>(y) - 16) * YG;
  uint32 b = Clip(static_cast<int32>((u * UB + v * VB) - (BB) + y1) >> 6);
  uint32 g = Clip(static_cast<int32>((u * UG + v * VG) - (BG) + y1) >> 6);
  uint32 r = Clip(static_cast<int32>((u * UR + v * VR) - (BR) + y1) >> 6);
  *reinterpret_cast<uint32*>(rgb_buf) = (b << bshift) |
                                        (g << gshift) |
                                        (r << rshift) |
                                        (255u << ashift);
}

void I420ToARGBRow_C(const uint8* y_buf,
                     const uint8* u_buf,
                     const uint8* v_buf,
                     uint8* rgb_buf,
                     int width) {
  for (int x = 0; x < width - 1; x += 2) {
    YuvPixel(y_buf[0], u_buf[0], v_buf[0], rgb_buf + 0, 24, 16, 8, 0);
    YuvPixel(y_buf[1], u_buf[0], v_buf[0], rgb_buf + 4, 24, 16, 8, 0);
    y_buf += 2;
    u_buf += 1;
    v_buf += 1;
    rgb_buf += 8;  // Advance 2 pixels.
  }
  if (width & 1) {
    YuvPixel(y_buf[0], u_buf[0], v_buf[0], rgb_buf + 0, 24, 16, 8, 0);
  }
}

void I420ToBGRARow_C(const uint8* y_buf,
                     const uint8* u_buf,
                     const uint8* v_buf,
                     uint8* rgb_buf,
                     int width) {
  for (int x = 0; x < width - 1; x += 2) {
    YuvPixel(y_buf[0], u_buf[0], v_buf[0], rgb_buf + 0, 0, 8, 16, 24);
    YuvPixel(y_buf[1], u_buf[0], v_buf[0], rgb_buf + 4, 0, 8, 16, 24);
    y_buf += 2;
    u_buf += 1;
    v_buf += 1;
    rgb_buf += 8;  // Advance 2 pixels.
  }
  if (width & 1) {
    YuvPixel(y_buf[0], u_buf[0], v_buf[0], rgb_buf, 0, 8, 16, 24);
  }
}

void I420ToABGRRow_C(const uint8* y_buf,
                     const uint8* u_buf,
                     const uint8* v_buf,
                     uint8* rgb_buf,
                     int width) {
  for (int x = 0; x < width - 1; x += 2) {
    YuvPixel(y_buf[0], u_buf[0], v_buf[0], rgb_buf + 0, 24, 0, 8, 16);
    YuvPixel(y_buf[1], u_buf[0], v_buf[0], rgb_buf + 4, 24, 0, 8, 16);
    y_buf += 2;
    u_buf += 1;
    v_buf += 1;
    rgb_buf += 8;  // Advance 2 pixels.
  }
  if (width & 1) {
    YuvPixel(y_buf[0], u_buf[0], v_buf[0], rgb_buf + 0, 24, 0, 8, 16);
  }
}

void I444ToARGBRow_C(const uint8* y_buf,
                     const uint8* u_buf,
                     const uint8* v_buf,
                     uint8* rgb_buf,
                     int width) {
  for (int x = 0; x < width; ++x) {
    YuvPixel(y_buf[0], u_buf[0], v_buf[0], rgb_buf, 24, 16, 8, 0);
    y_buf += 1;
    u_buf += 1;
    v_buf += 1;
    rgb_buf += 4;  // Advance 1 pixel.
  }
}

void YToARGBRow_C(const uint8* y_buf, uint8* rgb_buf, int width) {
  for (int x = 0; x < width; ++x) {
    YuvPixel(y_buf[0], 128, 128, rgb_buf, 24, 16, 8, 0);
    y_buf += 1;
    rgb_buf += 4;  // Advance 1 pixel.
  }
}

void MirrorRow_C(const uint8* src, uint8* dst, int width) {
  src += width - 1;
  for (int x = 0; x < width - 1; x += 2) {
    dst[x] = src[0];
    dst[x + 1] = src[-1];
    src -= 2;
  }
  if (width & 1) {
    dst[width - 1] = src[0];
  }
}

void MirrorRowUV_C(const uint8* src_uv, uint8* dst_u, uint8* dst_v, int width) {
  src_uv += (width - 1) << 1;
  for (int x = 0; x < width - 1; x += 2) {
    dst_u[x] = src_uv[0];
    dst_u[x + 1] = src_uv[-2];
    dst_v[x] = src_uv[1];
    dst_v[x + 1] = src_uv[-2 + 1];
    src_uv -= 4;
  }
  if (width & 1) {
    dst_u[width - 1] = src_uv[0];
    dst_v[width - 1] = src_uv[1];
  }
}

void SplitUV_C(const uint8* src_uv, uint8* dst_u, uint8* dst_v, int width) {
  for (int x = 0; x < width - 1; x += 2) {
    dst_u[x] = src_uv[0];
    dst_u[x + 1] = src_uv[2];
    dst_v[x] = src_uv[1];
    dst_v[x + 1] = src_uv[3];
    src_uv += 4;
  }
  if (width & 1) {
    dst_u[width - 1] = src_uv[0];
    dst_v[width - 1] = src_uv[1];
  }
}

void CopyRow_C(const uint8* src, uint8* dst, int count) {
  memcpy(dst, src, count);
}

// Filter 2 rows of YUY2 UV's (422) into U and V (420)
void YUY2ToUVRow_C(const uint8* src_yuy2, int src_stride_yuy2,
                   uint8* dst_u, uint8* dst_v, int width) {
  // Output a row of UV values, filtering 2 rows of YUY2
  for (int x = 0; x < width; x += 2) {
    dst_u[0] = (src_yuy2[1] + src_yuy2[src_stride_yuy2 + 1] + 1) >> 1;
    dst_v[0] = (src_yuy2[3] + src_yuy2[src_stride_yuy2 + 3] + 1) >> 1;
    src_yuy2 += 4;
    dst_u += 1;
    dst_v += 1;
  }
}

void YUY2ToYRow_C(const uint8* src_yuy2, uint8* dst_y, int width) {
  // Copy a row of yuy2 Y values
  for (int x = 0; x < width - 1; x += 2) {
    dst_y[x] = src_yuy2[0];
    dst_y[x + 1] = src_yuy2[2];
    src_yuy2 += 4;
  }
  if (width & 1) {
    dst_y[width - 1] = src_yuy2[0];
  }
}

void UYVYToUVRow_C(const uint8* src_uyvy, int src_stride_uyvy,
                   uint8* dst_u, uint8* dst_v, int width) {
  // Copy a row of uyvy UV values
  for (int x = 0; x < width; x += 2) {
    dst_u[0] = (src_uyvy[0] + src_uyvy[src_stride_uyvy + 0] + 1) >> 1;
    dst_v[0] = (src_uyvy[2] + src_uyvy[src_stride_uyvy + 2] + 1) >> 1;
    src_uyvy += 4;
    dst_u += 1;
    dst_v += 1;
  }
}

void UYVYToYRow_C(const uint8* src_yuy2, uint8* dst_y, int width) {
  // Copy a row of uyvy Y values
  for (int x = 0; x < width - 1; x += 2) {
    dst_y[x] = src_yuy2[1];
    dst_y[x + 1] = src_yuy2[3];
    src_yuy2 += 4;
  }
  if (width & 1) {
    dst_y[width - 1] = src_yuy2[1];
  }
}

#define BLENDER(f, b, a) (((256 - a) * b) >> 8) + f
void ARGBBlendRow_C(const uint8* src_argb, uint8* dst_argb, int width) {
  for (int x = 0; x < width - 1; x += 2) {
    uint32 a = src_argb[3];
    if (a) {
      if (a < 255) {
        const uint32 fb = src_argb[0];
        const uint32 fg = src_argb[1];
        const uint32 fr = src_argb[2];
        const uint32 bb = dst_argb[0];
        const uint32 bg = dst_argb[1];
        const uint32 br = dst_argb[2];
        dst_argb[0] = BLENDER(fb, bb, a);
        dst_argb[1] = BLENDER(fg, bg, a);
        dst_argb[2] = BLENDER(fr, br, a);
        dst_argb[3] = 255u;
      } else {
        *reinterpret_cast<uint32*>(dst_argb) =
            *reinterpret_cast<const uint32*>(src_argb);
      }
    }
    a = src_argb[4 + 3];
    if (a) {
      if (a < 255) {
        const uint32 fb = src_argb[4 + 0];
        const uint32 fg = src_argb[4 + 1];
        const uint32 fr = src_argb[4 + 2];
        const uint32 bb = dst_argb[4 + 0];
        const uint32 bg = dst_argb[4 + 1];
        const uint32 br = dst_argb[4 + 2];
        dst_argb[4 + 0] = BLENDER(fb, bb, a);
        dst_argb[4 + 1] = BLENDER(fg, bg, a);
        dst_argb[4 + 2] = BLENDER(fr, br, a);
        dst_argb[4 + 3] = 255u;
      } else {
        *reinterpret_cast<uint32*>(dst_argb + 4) =
            *reinterpret_cast<const uint32*>(src_argb + 4);
      }
    }
    src_argb += 8;
    dst_argb += 8;
  }

  if (width & 1) {
    const uint32 a = src_argb[3];
    if (a) {
      if (a < 255) {
        const uint32 fb = src_argb[0];
        const uint32 fg = src_argb[1];
        const uint32 fr = src_argb[2];
        const uint32 bb = dst_argb[0];
        const uint32 bg = dst_argb[1];
        const uint32 br = dst_argb[2];
        dst_argb[0] = BLENDER(fb, bb, a);
        dst_argb[1] = BLENDER(fg, bg, a);
        dst_argb[2] = BLENDER(fr, br, a);
        dst_argb[3] = 255u;
      } else {
        *reinterpret_cast<uint32*>(dst_argb) =
            *reinterpret_cast<const uint32*>(src_argb);
      }
    }
  }
}

// Blend src_argb0 over src_argb1 and store to dst_argb.
// dst_argb may be src_argb0 or src_argb1.
void ARGBBlend2Row_C(const uint8* src_argb0, const uint8* src_argb1,
                     uint8* dst_argb, int width) {
  for (int x = 0; x < width - 1; x += 2) {
    uint32 a = src_argb0[3];
    if (a == 0) {
      *reinterpret_cast<uint32*>(dst_argb) =
          *reinterpret_cast<const uint32*>(src_argb1);
    } else if (a == 255) {
      *reinterpret_cast<uint32*>(dst_argb) =
          *reinterpret_cast<const uint32*>(src_argb0);
    } else {
      const uint32 fb = src_argb0[0];
      const uint32 fg = src_argb0[1];
      const uint32 fr = src_argb0[2];
      const uint32 bb = src_argb1[0];
      const uint32 bg = src_argb1[1];
      const uint32 br = src_argb1[2];
      dst_argb[0] = BLENDER(fb, bb, a);
      dst_argb[1] = BLENDER(fg, bg, a);
      dst_argb[2] = BLENDER(fr, br, a);
      dst_argb[3] = 255u;
    }
    a = src_argb0[4 + 3];
    if (a == 0) {
      *reinterpret_cast<uint32*>(dst_argb + 4) =
          *reinterpret_cast<const uint32*>(src_argb1 + 4);
    } else if (a == 255) {
      *reinterpret_cast<uint32*>(dst_argb + 4) =
          *reinterpret_cast<const uint32*>(src_argb0 + 4);
    } else {
      const uint32 fb = src_argb0[4 + 0];
      const uint32 fg = src_argb0[4 + 1];
      const uint32 fr = src_argb0[4 + 2];
      const uint32 bb = src_argb1[4 + 0];
      const uint32 bg = src_argb1[4 + 1];
      const uint32 br = src_argb1[4 + 2];
      dst_argb[4 + 0] = BLENDER(fb, bb, a);
      dst_argb[4 + 1] = BLENDER(fg, bg, a);
      dst_argb[4 + 2] = BLENDER(fr, br, a);
      dst_argb[4 + 3] = 255u;
    }
    src_argb0 += 8;
    src_argb1 += 8;
    dst_argb += 8;
  }

  if (width & 1) {
    uint32 a = src_argb0[3];
    if (a == 0) {
      *reinterpret_cast<uint32*>(dst_argb) =
          *reinterpret_cast<const uint32*>(src_argb1);
    } else if (a == 255) {
      *reinterpret_cast<uint32*>(dst_argb) =
          *reinterpret_cast<const uint32*>(src_argb0);
    } else {
      const uint32 fb = src_argb0[0];
      const uint32 fg = src_argb0[1];
      const uint32 fr = src_argb0[2];
      const uint32 bb = src_argb1[0];
      const uint32 bg = src_argb1[1];
      const uint32 br = src_argb1[2];
      dst_argb[0] = BLENDER(fb, bb, a);
      dst_argb[1] = BLENDER(fg, bg, a);
      dst_argb[2] = BLENDER(fr, br, a);
      dst_argb[3] = 255u;
    }
  }
}

// Wrappers to handle odd sizes/alignments
#define YUVANY(NAMEANY, I420TORGB_SSE, I420TORGB_C)                            \
    void NAMEANY(const uint8* y_buf,                                           \
                 const uint8* u_buf,                                           \
                 const uint8* v_buf,                                           \
                 uint8* rgb_buf,                                               \
                 int width) {                                                  \
      int n = width & ~7;                                                      \
      I420TORGB_SSE(y_buf, u_buf, v_buf, rgb_buf, n);                          \
      I420TORGB_C(y_buf + n,                                                   \
                   u_buf + (n >> 1),                                           \
                   v_buf + (n >> 1),                                           \
                   rgb_buf + n * 4, width & 7);                                \
    }

#if defined(HAS_I420TOARGBROW_SSSE3)
YUVANY(I420ToARGBRow_Any_SSSE3, I420ToARGBRow_Unaligned_SSSE3, I420ToARGBRow_C)
YUVANY(I420ToBGRARow_Any_SSSE3, I420ToBGRARow_Unaligned_SSSE3, I420ToBGRARow_C)
YUVANY(I420ToABGRRow_Any_SSSE3, I420ToABGRRow_Unaligned_SSSE3, I420ToABGRRow_C)
#endif
#if defined(HAS_I420TOARGBROW_NEON)
YUVANY(I420ToARGBRow_Any_NEON, I420ToARGBRow_NEON, I420ToARGBRow_C)
YUVANY(I420ToBGRARow_Any_NEON, I420ToBGRARow_NEON, I420ToBGRARow_C)
YUVANY(I420ToABGRRow_Any_NEON, I420ToABGRRow_NEON, I420ToABGRRow_C)
#endif
#undef YUVANY

#define RGBANY(NAMEANY, ARGBTORGB, BPP)                                        \
    void NAMEANY(const uint8* argb_buf,                                        \
                 uint8* rgb_buf,                                               \
                 int width) {                                                  \
      SIMD_ALIGNED(uint8 row[kMaxStride]);                                     \
      ARGBTORGB(argb_buf, row, width);                                         \
      memcpy(rgb_buf, row, width * BPP);                                       \
    }

#if defined(HAS_ARGBTORGB24ROW_SSSE3)
RGBANY(ARGBToRGB24Row_Any_SSSE3, ARGBToRGB24Row_SSSE3, 3)
RGBANY(ARGBToRAWRow_Any_SSSE3, ARGBToRAWRow_SSSE3, 3)
RGBANY(ARGBToRGB565Row_Any_SSE2, ARGBToRGB565Row_SSE2, 2)
RGBANY(ARGBToARGB1555Row_Any_SSE2, ARGBToARGB1555Row_SSE2, 2)
RGBANY(ARGBToARGB4444Row_Any_SSE2, ARGBToARGB4444Row_SSE2, 2)
#endif
#undef RGBANY

#ifdef HAS_ARGBTOYROW_SSSE3
#define YANY(NAMEANY, ARGBTOY_SSE, BPP)                                        \
    void NAMEANY(const uint8* src_argb, uint8* dst_y, int width) {             \
      ARGBTOY_SSE(src_argb, dst_y, width - 16);                                \
      ARGBTOY_SSE(src_argb + (width - 16) * BPP, dst_y + (width - 16), 16);    \
    }

YANY(ARGBToYRow_Any_SSSE3, ARGBToYRow_Unaligned_SSSE3, 4)
YANY(BGRAToYRow_Any_SSSE3, BGRAToYRow_Unaligned_SSSE3, 4)
YANY(ABGRToYRow_Any_SSSE3, ABGRToYRow_Unaligned_SSSE3, 4)
YANY(YUY2ToYRow_Any_SSE2, YUY2ToYRow_Unaligned_SSE2, 2)
YANY(UYVYToYRow_Any_SSE2, UYVYToYRow_Unaligned_SSE2, 2)
#undef YANY

#define UVANY(NAMEANY, ARGBTOUV_SSE, ARGBTOUV_C, BPP)                          \
    void NAMEANY(const uint8* src_argb, int src_stride_argb,                   \
                 uint8* dst_u, uint8* dst_v, int width) {                      \
      int n = width & ~15;                                                     \
      ARGBTOUV_SSE(src_argb, src_stride_argb, dst_u, dst_v, n);                \
      ARGBTOUV_C(src_argb  + n * BPP, src_stride_argb,                         \
                 dst_u + (n >> 1),                                             \
                 dst_v + (n >> 1),                                             \
                 width & 15);                                                  \
    }

UVANY(ARGBToUVRow_Any_SSSE3, ARGBToUVRow_Unaligned_SSSE3, ARGBToUVRow_C, 4)
UVANY(BGRAToUVRow_Any_SSSE3, BGRAToUVRow_Unaligned_SSSE3, BGRAToUVRow_C, 4)
UVANY(ABGRToUVRow_Any_SSSE3, ABGRToUVRow_Unaligned_SSSE3, ABGRToUVRow_C, 4)
UVANY(YUY2ToUVRow_Any_SSE2, YUY2ToUVRow_Unaligned_SSE2, YUY2ToUVRow_C, 2)
UVANY(UYVYToUVRow_Any_SSE2, UYVYToUVRow_Unaligned_SSE2, UYVYToUVRow_C, 2)
#undef UVANY
#endif

#ifdef __cplusplus
}  // extern "C"
}  // namespace libyuv
#endif
