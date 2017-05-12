//
// src/include/vulkan_instance.h
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

#ifndef CUBE_VULKAN_INSTANCE_H
#define CUBE_VULKAN_INSTANCE_H

#include <vulkan/vulkan.hpp>
#include <vector>

#include "vulkan_application.h"

namespace c3 {

struct InstanceProperties {
  vk::LayerProperties layer;   
  std::vector<vk::ExtensionProperties> extensions;
};

class VulkanInstance {
 public:
  VulkanInstance(const VulkanApplication &application) : VulkanInstance(application, nullptr) {}
  VulkanInstance(const VulkanApplication &application, vk::AllocationCallbacks *allocator);
  ~VulkanInstance();

  vk::Result EnumerateProperties();

  std::vector<vk::LayerProperties> EnumerateLayerProperties() const;

  std::vector<vk::ExtensionProperties> EnumerateExtensionProperties(const char* layer_name) const;

  std::vector<vk::PhysicalDevice> EnumeratePhysicalDevices() const;

  const std::vector<vk::ExtensionProperties>& extension_properties() const {
    return extension_properties_;
  }

  const std::vector<InstanceProperties>& layer_properties() const {
    return layer_properties_;
  }

  const std::vector<vk::PhysicalDevice>& physical_devices() const {
    return physical_devices_;
  }

  void CreateDebugReportCallback(const vk::DebugReportCallbackCreateInfoEXT &createInfo);

  const vk::Instance& instance() const {
    return instance_;
  }

 private:
  vk::AllocationCallbacks *allocator_;
  vk::Instance instance_;
  std::vector<vk::PhysicalDevice> physical_devices_;
  std::vector<vk::ExtensionProperties> extension_properties_;
  std::vector<InstanceProperties> layer_properties_;

  PFN_vkCreateDebugReportCallbackEXT create_debug_report_callback_;
  PFN_vkDestroyDebugReportCallbackEXT destroy_debug_report_callback_;
  VkDebugReportCallbackEXT debug_report_callback_;
};

} // end of namespace c3

#endif // CUBE_VULKAN_INSTANCE_H

