//
// src/include/vulkan_application.h
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

#ifndef CUBE_VULKAN_APPLICATION_H
#define CUBE_VULKAN_APPLICATION_H

#include <vulkan/vulkan.hpp>
#include <vector>

namespace c3 {

class VulkanApplication {
 public:
  VulkanApplication(const char *application_name, uint32_t application_version = 1);
  ~VulkanApplication();

  void set_requested_layers(const std::vector<const char*> &layers) {
    requested_layers_ = layers;
  }

  const std::vector<const char*>& requested_layers() const {
    return requested_layers_;
  }
  
  void set_requested_extensions(const std::vector<const char*> &extensions) {
    requested_extensions_ = extensions;
  }

  const std::vector<const char*>& requested_extensions() const {
    return requested_extensions_;
  }

  const vk::ApplicationInfo& info() const {
      return info_;
  }

 private:
  vk::ApplicationInfo info_;
  std::vector<const char *> requested_layers_;
  std::vector<const char *> requested_extensions_;
};

} // end of namespace c3

#endif // CUBE_VULKAN_APPLICATION_H

