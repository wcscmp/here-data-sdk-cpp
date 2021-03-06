/*
 * Copyright (C) 2019 HERE Europe B.V.
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

#include "olp/core/logging/Configuration.h"

#include <memory>

#include "olp/core/logging/ConsoleAppender.h"
#include "olp/core/logging/DebugAppender.h"

namespace olp {
namespace logging {

Configuration Configuration::createDefault() {
  Configuration configuration;

  configuration.addAppender(
      std::make_shared<ConsoleAppender>(MessageFormatter::createDefault()));

  if (DebugAppender::isImplemented()) {
    configuration.addAppender(std::make_shared<DebugAppender>());
  }

  return configuration;
}

}  // namespace logging
}  // namespace olp
