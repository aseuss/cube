//
// src/include/vulkan_debug.h
//
// Copyright 2017 Andreas Seuss
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CUBE_VULKAN_DEBUG_H
#define CUBE_VULKAN_DEBUG_H

#include <vulkan/vulkan.hpp>

namespace c3 {

class VulkanDebug {
 public:
  static VKAPI_ATTR vk::Bool32 VKAPI_CALL DebugCallback(VkFlags message_flags,
      VkDebugReportObjectTypeEXT object_type, uint64_t source_object, size_t location,
      int32_t message_code, const char *layer_prefix, const char *message, void *user_data);

  vk::Bool32 DebugCallback(vk::DebugReportFlagsEXT message_flags,
      vk::DebugReportObjectTypeEXT object_type, uint64_t source_object,
      size_t location, int32_t message_code, const char *layer_prefix,
      const char *message);
};

} // end of namespace c3

#endif // CUBE_VULKAN_DEBUG_H

