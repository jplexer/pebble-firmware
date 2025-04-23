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

#include "layout_layer.h"

// layout implementations
#include "alarm_layout.h"
#include "calendar_layout.h"
#include "generic_layout.h"
#include "health_layout.h"
#include "notification_layout.h"
#include "sports_layout.h"
#include "weather_layout.h"

#include "system/passert.h"
#include "applib/ui/status_bar_layer.h"

static const LayoutLayerConstructor s_layout_constructors[NumLayoutIds] = {
  [LayoutIdGeneric] = generic_layout_create,
  [LayoutIdCalendar] = calendar_layout_create,
  [LayoutIdReminder] = notification_layout_create,
  [LayoutIdNotification] = notification_layout_create,
  [LayoutIdWeather] = weather_layout_create,
  [LayoutIdSports] = sports_layout_create,
  [LayoutIdAlarm] = alarm_layout_create,
  [LayoutIdHealth] = health_layout_create,
};

static const LayoutVerifier s_layout_verifiers[NumLayoutIds] = {
  [LayoutIdGeneric] = generic_layout_verify,
  [LayoutIdCalendar] = calendar_layout_verify,
  [LayoutIdReminder] = notification_layout_verify,
  [LayoutIdNotification] = notification_layout_verify,
  [LayoutIdWeather] = weather_layout_verify,
  [LayoutIdSports] = sports_layout_verify,
  [LayoutIdAlarm] = alarm_layout_verify,
  [LayoutIdHealth] = health_layout_verify,
};

static const LayoutColors s_default_colors = {
  .primary_color = { .argb = GColorBlackARGB8 },
  .secondary_color = { .argb = GColorBlackARGB8 },
  .bg_color = { .argb = PBL_IF_COLOR_ELSE(GColorLightGrayARGB8, GColorWhiteARGB8) },
};

static const LayoutColors s_default_notification_colors = {
    .primary_color = {.argb = GColorWhiteARGB8},
    .secondary_color = {.argb = GColorBlackARGB8},
    .bg_color = {.argb = GColorBlackARGB8},
};

LayoutLayer *layout_create(LayoutId id, const LayoutLayerConfig *config) {
  // pretend tests are generics for testing
  PBL_ASSERTN(id != LayoutIdUnknown);
  if (id == LayoutIdTest) {
    id = LayoutIdGeneric;
  }
  return s_layout_constructors[id](config);
}

bool layout_verify(bool existing_attributes[], LayoutId id) {
  if (id == LayoutIdTest) {
    return true;
  } else if (id == LayoutIdUnknown || id >= NumLayoutIds) {
    return false; // out of range
  } else if (id == LayoutIdCommNotification) {
    return false; // NYI
  } else {
    return s_layout_verifiers[id](existing_attributes);
  }
}

GSize layout_get_size(GContext *ctx, LayoutLayer *layout) {
  return layout->impl->size_getter(ctx, layout);
}

const LayoutColors *layout_get_colors(const LayoutLayer *layout) {
#if PBL_COLOR
  if (layout->impl->color_getter) {
    return layout->impl->color_getter(layout);
  }
#endif
  return &s_default_colors;
}

const LayoutColors *layout_get_notification_colors(const LayoutLayer *layout) {
  return PBL_IF_COLOR_ELSE(layout_get_colors(layout), &s_default_notification_colors);
}

void layout_set_mode(LayoutLayer *layout, LayoutLayerMode final_mode) {
  layout->impl->mode_setter(layout, final_mode);
}

void *layout_get_context(LayoutLayer *layout) {
  if (layout->impl->context_getter) {
    return layout->impl->context_getter(layout);
  } else {
    return NULL;
  }
}

void layout_destroy(LayoutLayer *layout) {
  layout->impl->destructor(layout);
}
