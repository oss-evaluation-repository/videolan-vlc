/*****************************************************************************
 * libvlc_media_track.h:  libvlc external API
 *****************************************************************************
 * Copyright (C) 1998-2020 VLC authors and VideoLAN
 *
 * Authors: Clément Stenac <zorglub@videolan.org>
 *          Jean-Paul Saman <jpsaman@videolan.org>
 *          Pierre d'Herbemont <pdherbemont@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef VLC_LIBVLC_MEDIA_TRACK_H
#define VLC_LIBVLC_MEDIA_TRACK_H 1

# ifdef __cplusplus
extern "C" {
# else
#  include <stdbool.h>
# endif

/** \defgroup libvlc_media_track LibVLC media track
 * \ingroup libvlc
 * @ref libvlc_media_track_t is an abstract representation of a media track.
 * @{
 * \file
 * LibVLC media track
 */

typedef enum libvlc_track_type_t
{
    libvlc_track_unknown   = -1,
    libvlc_track_audio     = 0,
    libvlc_track_video     = 1,
    libvlc_track_text      = 2
} libvlc_track_type_t;

typedef struct libvlc_audio_track_t
{
    unsigned    i_channels;
    unsigned    i_rate;
} libvlc_audio_track_t;

typedef enum libvlc_video_orient_t
{
    libvlc_video_orient_top_left,       /**< Normal. Top line represents top, left column left. */
    libvlc_video_orient_top_right,      /**< Flipped horizontally */
    libvlc_video_orient_bottom_left,    /**< Flipped vertically */
    libvlc_video_orient_bottom_right,   /**< Rotated 180 degrees */
    libvlc_video_orient_left_top,       /**< Transposed */
    libvlc_video_orient_left_bottom,    /**< Rotated 90 degrees clockwise (or 270 anti-clockwise) */
    libvlc_video_orient_right_top,      /**< Rotated 90 degrees anti-clockwise */
    libvlc_video_orient_right_bottom    /**< Anti-transposed */
} libvlc_video_orient_t;

typedef enum libvlc_video_projection_t
{
    libvlc_video_projection_rectangular,
    libvlc_video_projection_equirectangular, /**< 360 spherical */

    libvlc_video_projection_cubemap_layout_standard = 0x100,
} libvlc_video_projection_t;

/**
 * Viewpoint
 *
 * \warning allocate using libvlc_video_new_viewpoint()
 */
typedef struct libvlc_video_viewpoint_t
{
    float f_yaw;           /**< view point yaw in degrees  ]-180;180] */
    float f_pitch;         /**< view point pitch in degrees  ]-90;90] */
    float f_roll;          /**< view point roll in degrees ]-180;180] */
    float f_field_of_view; /**< field of view in degrees ]0;180[ (default 80.)*/
} libvlc_video_viewpoint_t;

typedef enum libvlc_video_multiview_t
{
    libvlc_video_multiview_2d,                  /**< No stereoscopy: 2D picture. */
    libvlc_video_multiview_stereo_sbs,          /**< Side-by-side */
    libvlc_video_multiview_stereo_tb,           /**< Top-bottom */
    libvlc_video_multiview_stereo_row,          /**< Row sequential */
    libvlc_video_multiview_stereo_col,          /**< Column sequential */
    libvlc_video_multiview_stereo_frame,        /**< Frame sequential */
    libvlc_video_multiview_stereo_checkerboard, /**< Checkerboard pattern */
} libvlc_video_multiview_t;

typedef struct libvlc_video_track_t
{
    unsigned    i_height;
    unsigned    i_width;
    unsigned    i_sar_num;
    unsigned    i_sar_den;
    unsigned    i_frame_rate_num;
    unsigned    i_frame_rate_den;

    libvlc_video_orient_t       i_orientation;
    libvlc_video_projection_t   i_projection;
    libvlc_video_viewpoint_t    pose; /**< Initial view point */
    libvlc_video_multiview_t    i_multiview;
} libvlc_video_track_t;

typedef struct libvlc_subtitle_track_t
{
    char *psz_encoding;
} libvlc_subtitle_track_t;

typedef struct libvlc_media_track_t
{
    /* Codec fourcc */
    uint32_t    i_codec;
    uint32_t    i_original_fourcc;
    int         i_id;
    libvlc_track_type_t i_type;

    /* Codec specific */
    int         i_profile;
    int         i_level;

    union {
        libvlc_audio_track_t *audio;
        libvlc_video_track_t *video;
        libvlc_subtitle_track_t *subtitle;
    };

    unsigned int i_bitrate;
    char *psz_language;
    char *psz_description;

} libvlc_media_track_t;

/** @}*/

# ifdef __cplusplus
}
# endif

#endif /* VLC_LIBVLC_MEDIA_TRACK_H */
