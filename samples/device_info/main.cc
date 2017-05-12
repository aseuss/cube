//
// samples/device_info/device_info.cc
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

#include <cube.h>
//#include <vulkan_application.h>
//#include <vulkan_instance.h>
#include <iostream>

int main(int argc, char **argv) {
  std::vector<const char*> layer_names = {
    "VK_LAYER_LUNARG_api_dump"
  };
  std::vector<const char*> extension_names = {
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME
  };

  c3::VulkanApplication application("DeviceInfo", 42);
  application.set_requested_layers(layer_names);
  application.set_requested_extensions(extension_names);

  c3::VulkanInstance instance(application);
  //instance.EnumerateLayerProperties();
  instance.EnumerateProperties();
  auto instance_extensions = instance.extension_properties();
  std::cout << "Instance extensions:" << std::endl;
  for (auto const &extension : instance_extensions) {
    std::cout << "  - " << extension.extensionName << std::endl;
  }

  auto layer_properties = instance.layer_properties();
  std::cout << "Instance layer properties:" << std::endl;
  for (auto const &property : layer_properties) {
    std::cout << "  - " << property.layer.layerName << " : " << property.layer.description << std::endl;
    for (auto const &extension : property.extensions) {
      std::cout << "    - " << extension.extensionName << std::endl;
    }
  }
  auto physical_devices = instance.physical_devices();
  auto physical_device = physical_devices[0];
  auto device_properties = physical_device.getProperties();

  // device properties could be checked

  uint32_t api_version = device_properties.apiVersion;

  std::cout << "vulkan API version: " << VK_VERSION_MAJOR(api_version) << ".";
  std::cout << VK_VERSION_MINOR(api_version) << "." << VK_VERSION_PATCH(api_version) << std::endl;
  std::cout << "hardware: " << device_properties.vendorID << " " << device_properties.deviceName << std::endl;

  auto device_memory_properties = physical_device.getMemoryProperties();

  std::vector<vk::QueueFamilyProperties> queue_family_properties = physical_device.getQueueFamilyProperties();

  // check device que families for family supporting graphics
  uint32_t graphics_queue_family_index = 0;
  for (;graphics_queue_family_index < queue_family_properties.size(); ++graphics_queue_family_index) {
    if (queue_family_properties[graphics_queue_family_index].queueFlags & vk::QueueFlagBits::eGraphics) {
        std::cout << "graphics queue index: " << graphics_queue_family_index << std::endl;
        break;
    }
  }
 
  std::vector<float> priorities = {0.0};
  // TODO: put into vector to make it more generic in case multiple queues should be created?
  std::vector<vk::DeviceQueueCreateInfo> device_queue_create_infos;
  vk::DeviceQueueCreateInfo device_queue_create_info;
  device_queue_create_info.queueFamilyIndex = graphics_queue_family_index;
  device_queue_create_info.queueCount = 1;
  device_queue_create_info.pQueuePriorities = priorities.data();
  device_queue_create_infos.push_back(device_queue_create_info);


  vk::DeviceCreateInfo device_create_info;
  device_create_info.queueCreateInfoCount = device_queue_create_infos.size();
  device_create_info.pQueueCreateInfos = device_queue_create_infos.data();
  // device layers are deprecated

  auto logical_device = physical_device.createDevice(device_create_info);

  logical_device.destroy();
}

