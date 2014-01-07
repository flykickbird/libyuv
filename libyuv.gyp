# Copyright 2011 The LibYuv Project Authors. All rights reserved.
#
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file in the root of the source
# tree. An additional intellectual property rights grant can be found
# in the file PATENTS. All contributing project authors may
# be found in the AUTHORS file in the root of the source tree.

{
  'variables': {
    'use_system_libjpeg%': 0,
    'build_neon': 0,
    'conditions': [
       ['OS == "android" or OS == "ios"', {
         # TODO(noahric): Also check tool version for armv7
         'build_neon': 1,
       }],
    ],
  },
  'conditions': [
    [ 'build_neon != 0', {
      'targets': [
        # The NEON-specific components.
        {
          'target_name': 'libyuv_neon',
          'type': 'static_library',
          'standalone_static_library': 1,
          'defines': [
            'LIBYUV_NEON',
          ],
          # TODO(noahric): This should remove whatever mfpu is set, not
          # just vfpv3-d16.
          'cflags!': [
            '-mfpu=vfp',
            '-mfpu=vfpv3',
            '-mfpu=vfpv3-d16',
          ],
          'cflags': [
            '-mfpu=neon',
          ],
          'include_dirs': [
            'include',
            '.',
          ],
          'direct_dependent_settings': {
            'include_dirs': [
              'include',
              '.',
            ],
          },
          'sources': [
            # sources.
            'source/compare_neon.cc',
            'source/rotate_neon.cc',
            'source/row_neon.cc',
            'source/scale_neon.cc',
          ],
        },
      ],
    }],
  ],
  'targets': [
    {
      'target_name': 'libyuv',
      # Change type to 'shared_library' to build .so or .dll files.
      'type': 'static_library',
      # Allows libyuv.a redistributable library without external dependencies.
      'standalone_static_library': 1,
      'conditions': [
        # TODO(fbarchard): Use gyp define to enable jpeg.
        [ 'OS != "ios"', {
          'defines': [
            'HAVE_JPEG'
          ],
          'conditions': [
            # Android uses libjpeg for system jpeg support.
            [ 'OS == "android" and use_system_libjpeg == 1', {
              'dependencies': [
                 '<(DEPTH)/third_party/libjpeg/libjpeg.gyp:libjpeg',
              ],
            }, {
              'dependencies': [
                 '<(DEPTH)/third_party/libjpeg_turbo/libjpeg.gyp:libjpeg',
              ],
            }],
            [ 'use_system_libjpeg == 1', {
              'link_settings': {
                'libraries': [
                  '-ljpeg',
                ],
              }
            }],
          ],
        }],
        [ 'build_neon != 0', {
          'dependencies': [
            'libyuv_neon',
          ],
          'defines': [
            'LIBYUV_NEON',
          ]
        }],
      ],
      'defines': [
        # Enable the following 3 macros to turn off assembly for specified CPU.
        # 'LIBYUV_DISABLE_X86',
        # 'LIBYUV_DISABLE_NEON',
        # 'LIBYUV_DISABLE_MIPS',
        # Enable the following macro to build libyuv as a shared library (dll).
        # 'LIBYUV_USING_SHARED_LIBRARY',
      ],
      'include_dirs': [
        'include',
        '.',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          'include',
          '.',
        ],
      },
      'sources': [
        # includes.
        'include/libyuv.h',
        'include/libyuv/basic_types.h',
        'include/libyuv/compare.h',
        'include/libyuv/convert.h',
        'include/libyuv/convert_argb.h',
        'include/libyuv/convert_from.h',
        'include/libyuv/convert_from_argb.h',
        'include/libyuv/cpu_id.h',
        'include/libyuv/format_conversion.h',
        'include/libyuv/mjpeg_decoder.h',
        'include/libyuv/planar_functions.h',
        'include/libyuv/rotate.h',
        'include/libyuv/rotate_argb.h',
        'include/libyuv/row.h',
        'include/libyuv/scale.h',
        'include/libyuv/scale_argb.h',
        'include/libyuv/scale_row.h',
        'include/libyuv/version.h',
        'include/libyuv/video_common.h',

        # sources.
        'source/compare.cc',
        'source/compare_common.cc',
        'source/compare_posix.cc',
        'source/compare_win.cc',
        'source/convert.cc',
        'source/convert_argb.cc',
        'source/convert_from.cc',
        'source/convert_from_argb.cc',
        'source/convert_jpeg.cc',
        'source/convert_to_argb.cc',
        'source/convert_to_i420.cc',
        'source/cpu_id.cc',
        'source/format_conversion.cc',
        'source/mjpeg_decoder.cc',
        'source/mjpeg_validate.cc',
        'source/planar_functions.cc',
        'source/rotate.cc',
        'source/rotate_argb.cc',
        'source/rotate_mips.cc',
        'source/row_any.cc',
        'source/row_common.cc',
        'source/row_mips.cc',
        'source/row_posix.cc',
        'source/row_win.cc',
        'source/scale.cc',
        'source/scale_argb.cc',
        'source/scale_common.cc',
        'source/scale_mips.cc',
        'source/scale_posix.cc',
        'source/scale_win.cc',
        'source/video_common.cc',
      ],
    },
  ], # targets.
}

# Local Variables:
# tab-width:2
# indent-tabs-mode:nil
# End:
# vim: set expandtab tabstop=2 shiftwidth=2:
