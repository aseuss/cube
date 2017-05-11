//
// src/vulkan_debug.cc
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

#include "vulkan_debug.h"
#include <log.h>
//#include <iostream>

namespace c3 {

VKAPI_ATTR vk::Bool32 VKAPI_CALL VulkanDebug::DebugCallback(VkFlags message_flags,
    VkDebugReportObjectTypeEXT object_type, uint64_t source_object, size_t location,
    int32_t message_code, const char *layer_prefix, const char *message, void *user_data) {

  vk::DebugReportFlagsEXT flags(static_cast<vk::DebugReportFlagBitsEXT>(message_flags));
  vk::DebugReportObjectTypeEXT type = static_cast<vk::DebugReportObjectTypeEXT>(object_type);
  VulkanDebug *vulkan_debug = static_cast<VulkanDebug*>(user_data);

  return vulkan_debug->DebugCallback(flags, type, source_object,
      location, message_code, layer_prefix, message);
}
  
vk::Bool32 VulkanDebug::DebugCallback(vk::DebugReportFlagsEXT message_flags,
      vk::DebugReportObjectTypeEXT object_type, uint64_t source_object,
      size_t location, int32_t message_code, const char *layer_prefix,
      const char *message) {
  vk::Bool32 result = VK_TRUE;

  if (message_flags & vk::DebugReportFlagBitsEXT::eError) {
    Log::e("device_info") << layer_prefix << " code: " << message_code << ":" << message; 
    result = VK_FALSE;
  } else if (message_flags & vk::DebugReportFlagBitsEXT::eWarning) {
    Log::w("device_info") << layer_prefix << " code: " << message_code << ":" << message; 
  } else if (message_flags & vk::DebugReportFlagBitsEXT::eInformation) {
    Log::i("device_info") << layer_prefix << " code: " << message_code << ":" << message; 
  } else if (message_flags & vk::DebugReportFlagBitsEXT::ePerformanceWarning) {
    Log::w("device_info") << "[performance] " << layer_prefix << " code: " << message_code << ":" << message; 
  } else if (message_flags & vk::DebugReportFlagBitsEXT::eDebug) {
    Log::d("device_info") << layer_prefix << " code: " << message_code << ":" << message; 
  } else {
    result = VK_FALSE;
  }
  return result;
}

} // end of namespace c3

