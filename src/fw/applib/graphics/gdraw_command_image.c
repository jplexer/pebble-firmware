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

#include "gdraw_command_image.h"
#include "gdraw_command_private.h"

#include "applib/applib_malloc.auto.h"
#include "applib/applib_resource_private.h"
#include "syscall/syscall.h"

GDrawCommandImage *gdraw_command_image_create_with_resource(uint32_t resource_id) {
  ResAppNum app_num = sys_get_current_resource_num();

  return gdraw_command_image_create_with_resource_system(app_num, resource_id);
}

GDrawCommandImage *gdraw_command_image_create_with_resource_system(ResAppNum app_num,
                                                                   uint32_t resource_id) {
  uint32_t data_size;
  if (!gdraw_command_resource_is_valid(app_num, resource_id, PDCI_SIGNATURE, &data_size)) {
    return NULL;
  }

  GDrawCommandImage *draw_command_image = applib_resource_mmap_or_load(app_num, resource_id,
                                                                       PDCI_DATA_OFFSET, data_size,
                                                                       false);

  // Validate the loaded command image
  if (!gdraw_command_image_validate(draw_command_image, data_size)) {
    gdraw_command_image_destroy(draw_command_image);
    return NULL;
  }

  return draw_command_image;
}

bool gdraw_command_image_copy(void *buffer, size_t buffer_length, GDrawCommandImage *src) {
  size_t src_size = gdraw_command_image_get_data_size(src);
  if (buffer_length < src_size) {
    return false;
  }

  memcpy(buffer, src, src_size);
  return true;
}

GDrawCommandImage *gdraw_command_image_clone(GDrawCommandImage *image) {
  if (!image) {
    return NULL;
  }

  // potentially extracting into a generic task_ptrdup(void *, size_t)
  size_t size = gdraw_command_image_get_data_size(image);
  GDrawCommandImage *result = applib_malloc(size);
  if (result) {
    memcpy(result, image, size);
  }

  return result;
}

void gdraw_command_image_destroy(GDrawCommandImage *image) {
  applib_resource_munmap_or_free(image);
}

bool gdraw_command_image_validate(GDrawCommandImage *image, size_t size) {
  if (!image ||
      (size < sizeof(GDrawCommandImage)) ||
      (image->version > GDRAW_COMMAND_VERSION) ||
      !gdraw_command_list_validate(&image->command_list, size - (sizeof(GDrawCommandImage) -
          sizeof(GDrawCommandList)))) {
    return false;
  }
  uint8_t *end = (uint8_t *)image + size;

  return (end == gdraw_command_list_iterate_private(&image->command_list, NULL, NULL));
}

void gdraw_command_image_draw(GContext *ctx, GDrawCommandImage *image, GPoint offset) {
  gdraw_command_image_draw_processed(ctx, image, offset, NULL);
}

void gdraw_command_image_draw_processed(GContext *ctx, GDrawCommandImage *image, GPoint offset,
                                        GDrawCommandProcessor *processor) {
  if (!ctx || !image) {
    return;
  }

  // Offset graphics context drawing box origin by specified amount
  graphics_context_move_draw_box(ctx, offset);

  gdraw_command_list_draw_processed(ctx, &image->command_list, processor);

  // Offset graphics context drawing box back to previous origin
  graphics_context_move_draw_box(ctx, GPoint(-offset.x, -offset.y));
}

size_t gdraw_command_image_get_data_size(GDrawCommandImage *image) {
  if (!image) {
    return 0;
  }

  return sizeof(GDrawCommandImage) - sizeof(GDrawCommandList)
      + gdraw_command_list_get_data_size(&image->command_list);
}

GSize gdraw_command_image_get_bounds_size(GDrawCommandImage *image) {
  if (!image) {
    return GSizeZero;
  }

  return image->size;
}

void gdraw_command_image_set_bounds_size(GDrawCommandImage *image, GSize size) {
  if (!image) {
    return;
  }

  image->size = size;
}

GDrawCommandList *gdraw_command_image_get_command_list(GDrawCommandImage *image) {
  if (!image) {
    return NULL;
  }

  return &image->command_list;
}

#if PBL_BW
// These functions are only needed for B&W platforms due to the new notification system
void gdraw_command_image_set_stroke_color(GDrawCommandImage *image, GColor stroke_color) {
  if (!image) {
    return;
  }

  GDrawCommandList *command_list = gdraw_command_image_get_command_list(image);
  if (command_list) {
    GDrawCommand *command = command_list->commands;
    for (uint32_t j = 0; j < command_list->num_commands; j++) {
      gdraw_command_set_stroke_color(command, stroke_color);
      command = (GDrawCommand *) (command->points + command->num_points);
    }
  }
}

void gdraw_command_image_set_fill_color(GDrawCommandImage *image, GColor fill_color) {
  if (!image) {
    return;
  }

  GDrawCommandList *command_list = gdraw_command_image_get_command_list(image);
  if (command_list) {
    GDrawCommand *command = command_list->commands;
    for (uint32_t j = 0; j < command_list->num_commands; j++) {
      gdraw_command_set_fill_color(command, fill_color);
      command = (GDrawCommand *) (command->points + command->num_points);
    }
  }
}
#endif