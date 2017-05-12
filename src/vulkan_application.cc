//
// src/vulkan_application.cc
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

#include "vulkan_application.h"
#include "cube_config.h"
#include "vendor_ids.h"

namespace c3 {

VulkanApplication::VulkanApplication(const char *application_name, uint32_t application_version)
    : info_(application_name, application_version, CUBE_ENGINE_NAME,
            CUBE_ENGINE_VERSION, VK_MAKE_VERSION(1, 0, 0)) {

}

VulkanApplication::~VulkanApplication() {
  requested_layers_.clear();
  requested_extensions_.clear();
}

} // end of namespace c3

