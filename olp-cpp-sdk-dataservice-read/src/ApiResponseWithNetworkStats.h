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

#pragma once

#include <olp/core/client/ApiResponse.h>
#include <olp/core/client/HttpResponse.h>

namespace olp {
namespace dataservice {
namespace read {

template <typename Result, typename Error>
class ApiResponseWithNetworkStats : public client::ApiResponse<Result, Error> {
 public:
  ApiResponseWithNetworkStats() = default;

  // Implicit constructor by desing, same as in ApiResponse
  ApiResponseWithNetworkStats(Result result)
      : client::ApiResponse<Result, Error>(std::move(result)), statistics_{} {}

  // Implicit constructor by desing, same as in ApiResponse
  ApiResponseWithNetworkStats(const Error& error)
      : client::ApiResponse<Result, Error>(error), statistics_{} {}

  ApiResponseWithNetworkStats(Result result,
                              client::NetworkStatistics statistics)
      : client::ApiResponse<Result, Error>(std::move(result)),
        statistics_(statistics) {}

  ApiResponseWithNetworkStats(const Error& error,
                              client::NetworkStatistics statistics)
      : client::ApiResponse<Result, Error>(error), statistics_(statistics) {}

  client::NetworkStatistics GetNetworkStatistics() const { return statistics_; }

 private:
  client::NetworkStatistics statistics_;
};

}  // namespace read
}  // namespace dataservice
}  // namespace olp
