/*
 * Copyright 2024 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "item.h"
#include "layout_layer.h"
#include "timeline_layout.h"

#include "applib/graphics/graphics.h"
#include "applib/graphics/text.h"
#include "applib/graphics/perimeter.h"
#include "applib/ui/bitmap_layer.h"
#include "applib/ui/kino/kino_layer.h"
#include "applib/ui/text_layer.h"
#include "services/normal/timeline/attribute.h"
#include "services/normal/timeline/timeline_resources.h"

//! Banner height of notification and reminder layouts (excluding status bar)
//! Rectangular banner is the same size on both the top and bottom
#define LAYOUT_BANNER_HEIGHT_RECT                                  \
    PREFERRED_CONTENT_SIZE_SWITCH(PreferredContentSizeDefault,     \
      /* This is the same as Medium until Small is designed */     \
      /* small */ 36,                                              \
      /* medium */ 36,                                             \
      /* large */ 29,                                              \
      /* This is the same as Large until ExtraLarge is designed */ \
      /* extralarge */ 29                                          \
    )
//! Round banner is different between the top and bottom
#define LAYOUT_TOP_BANNER_HEIGHT_ROUND 60
#define LAYOUT_BOTTOM_BANNER_HEIGHT_ROUND 40
#define LAYOUT_TOP_BANNER_HEIGHT \
    PBL_IF_RECT_ELSE(LAYOUT_BANNER_HEIGHT_RECT, \
                     LAYOUT_TOP_BANNER_HEIGHT_ROUND - STATUS_BAR_LAYER_HEIGHT)
//! Height of the white arrow layer
#define LAYOUT_ARROW_HEIGHT PBL_IF_RECT_ELSE(19, 16)
//! Display height of the layout, which removes the arrow_height from the text layout region
//! PBL-23103 Remove hard-coded layout_height used for S4 paging notification and swap_layer
#define LAYOUT_HEIGHT (DISP_ROWS - STATUS_BAR_LAYER_HEIGHT - LAYOUT_ARROW_HEIGHT)
//! The y-offset before the text begins
#define LAYOUT_BEFORE_TEXT_SPACING_Y 40
//! Radius of the (round) banner
#define BANNER_CIRCLE_RADIUS 140
//! The starting y-position of the top banner
#define LAYOUT_TOP_BANNER_ORIGIN_Y (LAYOUT_TOP_BANNER_HEIGHT_ROUND - \
                                    (BANNER_CIRCLE_RADIUS + STATUS_BAR_LAYER_HEIGHT) - 1)

#define TEXT_VISIBLE_UPPER_THRESHOLD (STATUS_BAR_LAYER_HEIGHT - INTERPOLATE_MOOOK_BOUNCE_BACK - 1)
#define TEXT_VISIBLE_LOWER_THRESHOLD(h) \
    (-(h) + DISP_ROWS - STATUS_BAR_LAYER_HEIGHT - INTERPOLATE_MOOOK_BOUNCE_BACK - 1)

//! Offset and margin refer to the GTextNode definition where offset is the internal position delta
//! to be applied not affecting neighboring elements and margin is the size delta to be applied not
//! affecting internal positioning of the owning element. Padding is the amount of additional
//! spacing needed to be added between the owning element and the lower subsequent element. Upper
//! padding is the same except between the owning element and the upper previous element. Newer
//! positional or sizing fields should generally be either offset or margin instead of padding.
//! @see \ref GTextNode
typedef struct {
  const char *header_font_key;
  const char *title_font_key;
  const char *subtitle_font_key;
  const char *body_font_key;
  const char *footer_font_key;
  int8_t header_padding;
  int8_t title_offset_if_body_icon; //!< Conditional title delta offset if body icon exists
  int8_t title_padding;
  int8_t title_line_delta;
  int8_t subtitle_upper_padding;
  int8_t subtitle_lower_padding;
  int8_t subtitle_line_delta;
  int8_t location_offset;
  int8_t location_margin;
  int8_t body_padding;
  int8_t body_line_delta;
  int8_t body_icon_offset; //!< Body icon refers to a large body icon, currently used by Jumboji
  int8_t body_icon_margin;
  int8_t timestamp_upper_padding;
  int8_t timestamp_lower_padding;
} NotificationStyle;

typedef struct {
  TimelineItem *item;
#if !PLATFORM_TINTIN
  bool show_notification_timestamp;
#endif
} NotificationLayoutInfo;

typedef struct BannerScrollState BannerScrollState;

typedef struct {
  LayoutLayer layout;
  KinoLayer icon_layer;
  AppResourceInfo icon_res_info;
  LayoutColors colors;
  NotificationLayoutInfo info;
#if !PLATFORM_TINTIN
  KinoLayer *detail_icon_layer; //!< Not common, so not inline with the layout
#endif
  const NotificationStyle *style;
  GTextNode *view_node;
  GSize view_size;
  TextLayer *banner_title_layer;
  int banner_scroll_cycle;           // Track scroll cycle count
  AppTimer *banner_scroll_timer;     // Timer for scrolling
  int16_t banner_title_scroll_distance; // Distance to scroll
  bool destroyed;
  uint8_t banner_scroll_state;
} NotificationLayout;


//! Default notification color
#define DEFAULT_NOTIFICATION_COLOR (GColorFolly)
#define DEFAULT_REMINDER_COLOR (GColorRed)
//! Generic notification icon
static const TimelineResourceId NOTIF_FALLBACK_ICON = TIMELINE_RESOURCE_NOTIFICATION_GENERIC;
static const TimelineResourceId REMINDER_FALLBACK_ICON = TIMELINE_RESOURCE_NOTIFICATION_REMINDER;
//! Height of tiny resource icons used in the top banner of notifications.
#define NOTIFICATION_TINY_RESOURCE_HEIGHT (ATTRIBUTE_ICON_TINY_SIZE_PX)
//! Used because some notification icons are 30 px wide.
#define NOTIFICATION_TINY_RESOURCE_SIZE (GSize(30, NOTIFICATION_TINY_RESOURCE_HEIGHT))
//! Adjusts the vertical position of the tiny resource icon on notifications to account for the
//! whitespace inside the status bar but below the status bar text. Note that this depends on the
//! font used in the status bar.
#define NOTIFICATION_TINY_RESOURCE_VERTICAL_OFFSET                 \
    PREFERRED_CONTENT_SIZE_SWITCH(PreferredContentSizeDefault,     \
      /* This is the same as Medium until Small is designed */     \
      /* small */ -1,                                              \
      /* medium */ -1,                                             \
      /* large */ -2,                                              \
      /* This is the same as Large until ExtraLarge is designed */ \
      /* extralarge */ -2                                          \
    )
//! Used to know where the icon is within the layout.
#define CARD_ICON_UPPER_PADDING                                            \
    ((LAYOUT_TOP_BANNER_HEIGHT - NOTIFICATION_TINY_RESOURCE_HEIGHT) / 2) + \
      NOTIFICATION_TINY_RESOURCE_VERTICAL_OFFSET

LayoutLayer *notification_layout_create(const LayoutLayerConfig *config);

bool notification_layout_verify(bool existing_attributes[]);

TimelineResourceId notification_layout_get_fallback_icon_id(TimelineItemType item_type);
