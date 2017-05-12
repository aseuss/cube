//
// src/vendor_ids.h
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

#ifndef CUBE_VENDOR_IDS_H
#define CUBE_VENDOR_IDS_H

#include <map>

namespace c3 {

static const std::map<uint32_t, const char * const> kVendorIds = {
  {0xFFFFFFFF, "UNKNOWN"},
  {0x00001002, "AMD"},
  {0x00001010, "ImgTec"},
  {0x000010DE, "NVIDIA"},
  {0x000013B5, "ARM"},
  {0x00005143, "Qualcomm"},
  {0x00008086, "INTEL"},
};

} // end of namespace c3

#endif // CUBE_VENDOR_IDS_H

