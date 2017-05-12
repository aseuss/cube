//
// src/vulkan_instance.cc
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

#include "vulkan_instance.h"

#include <iostream>
#include "vendor_ids.h"
#include "vulkan_debug.h"

namespace c3 {

VulkanInstance::VulkanInstance(const VulkanApplication &application,
                               vk::AllocationCallbacks *allocator)
    : allocator_(allocator), create_debug_report_callback_(nullptr),
    destroy_debug_report_callback_(nullptr), debug_report_callback_(nullptr) {
  vk::InstanceCreateInfo instance_create_info;

  auto layer_names = application.requested_layers();
  auto extension_names = application.requested_extensions();

  // TODO: the requested layers should be checked

  instance_create_info.pApplicationInfo = &application.info();
  instance_create_info.enabledLayerCount = (uint32_t) layer_names.size();
  instance_create_info.ppEnabledLayerNames = layer_names.size() ? layer_names.data() : nullptr;
  instance_create_info.enabledExtensionCount = (uint32_t) extension_names.size();
  instance_create_info.ppEnabledExtensionNames = extension_names.size() ? extension_names.data() : nullptr;

  instance_ = vk::createInstance(instance_create_info, allocator_);

  // TODO: create only if flags are != 0. flags should be obtained from application.
  create_debug_report_callback_ = (PFN_vkCreateDebugReportCallbackEXT)
      instance_.getProcAddr("vkCreateDebugReportCallbackEXT");
  destroy_debug_report_callback_ = (PFN_vkDestroyDebugReportCallbackEXT)
      instance_.getProcAddr("vkDestroyDebugReportCallbackEXT");

  // TODO: move to application? only create debug callback if flags are != 0
  vk::DebugReportCallbackCreateInfoEXT debug_callback_info;
  debug_callback_info.pfnCallback = VulkanDebug::DebugCallback;
  debug_callback_info.pUserData = new VulkanDebug();
  debug_callback_info.flags = vk::DebugReportFlagBitsEXT::eWarning |
      vk::DebugReportFlagBitsEXT::ePerformanceWarning |
      vk::DebugReportFlagBitsEXT::eError |
      vk::DebugReportFlagBitsEXT::eDebug |
      vk::DebugReportFlagBitsEXT::eInformation;
 
  //CreateDebugReportCallback(debug_callback_info), 

  physical_devices_ = EnumeratePhysicalDevices();
}

VulkanInstance::~VulkanInstance() {
  if (debug_report_callback_) {
    destroy_debug_report_callback_(static_cast<VkInstance>(instance_),
                                   debug_report_callback_, nullptr);
  }

  extension_properties_.clear();
  layer_properties_.clear();
  instance_.destroy();
}

std::vector<vk::LayerProperties> VulkanInstance::EnumerateLayerProperties() const {
  std::vector<vk::LayerProperties> layer_properties;
  uint32_t layer_count;
  vk::Result result;

  result = vk::enumerateInstanceLayerProperties(&layer_count, nullptr);
  layer_properties.resize(layer_count);

  result = vk::enumerateInstanceLayerProperties(&layer_count, layer_properties.data());

  return layer_properties;
}

std::vector<vk::ExtensionProperties> VulkanInstance::EnumerateExtensionProperties(const char* layer_name) const {
  std::vector<vk::ExtensionProperties> extension_properties;
  uint32_t extension_count;
  vk::Result result;

  result = vk::enumerateInstanceExtensionProperties(layer_name, &extension_count, nullptr);
  extension_properties.resize(extension_count);

  result = vk::enumerateInstanceExtensionProperties(layer_name, &extension_count, extension_properties.data());
  return extension_properties;
}

vk::Result VulkanInstance::EnumerateProperties() {
  extension_properties_ = EnumerateExtensionProperties(nullptr);
  std::vector<vk::LayerProperties> layer_properties = EnumerateLayerProperties();

  for (const auto& layer_property : layer_properties) {
    InstanceProperties properties;
    properties.layer = layer_property;
    properties.extensions = EnumerateExtensionProperties(properties.layer.layerName);

    layer_properties_.push_back(properties);
  }

  return vk::Result::eSuccess;
}

std::vector<vk::PhysicalDevice> VulkanInstance::EnumeratePhysicalDevices() const {
  std::vector<vk::PhysicalDevice> physical_devices;
  uint32_t physical_device_count;
  vk::Result result;

  result = instance_.enumeratePhysicalDevices(&physical_device_count, nullptr);
  physical_devices.resize(physical_device_count);

  result = instance_.enumeratePhysicalDevices(&physical_device_count, physical_devices.data());

  return physical_devices;
}

void VulkanInstance::CreateDebugReportCallback(const vk::DebugReportCallbackCreateInfoEXT &createInfo) {
  VkDebugReportCallbackCreateInfoEXT debug_create_info =
      static_cast<VkDebugReportCallbackCreateInfoEXT>(createInfo);

  create_debug_report_callback_(static_cast<VkInstance>(instance_), &debug_create_info, nullptr,
          &debug_report_callback_);
}

} // end of namespace c3

