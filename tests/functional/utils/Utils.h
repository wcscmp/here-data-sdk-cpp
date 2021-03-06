/*
 * Copyright (C) 2019-2020 HERE Europe B.V.
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
 *
 * SPDX-License-Identifier: Apache-2.0
 * License-Filename: LICENSE
 */

#pragma once

#include <gtest/gtest.h>
#include <sstream>
#include "olp/core/client/ApiError.h"

namespace {

#define EXPECT_SUCCESS(response)                                   \
  EXPECT_TRUE((response).IsSuccessful())                           \
      << "ERROR: code: "                                           \
      << static_cast<int>((response).GetError().GetErrorCode())    \
      << ", status: " << (response).GetError().GetHttpStatusCode() \
      << ", message: " << (response).GetError().GetMessage();

}  // namespace
