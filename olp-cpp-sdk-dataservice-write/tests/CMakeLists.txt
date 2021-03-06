# Copyright (C) 2019 HERE Europe B.V.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0
# License-Filename: LICENSE

set(OLP_SDK_DATASERVICE_WRITE_TEST_SOURCES
    ApiClientLookupTest.cpp
    CancellationTokenListTest.cpp
    ParserTest.cpp
    SerializerTest.cpp
    StartBatchRequestTest.cpp
    StreamLayerClientImplTest.cpp
    TimeUtilsTest.cpp
    VersionedLayerClientImplTest.cpp
    )


find_package(OpenSSL)

if (ANDROID OR IOS)
    set(OLP_SDK_DASERVICE_WRITE_TESTS_LIB olp-cpp-sdk-dataservice-write-tests-lib)

    add_library(${OLP_SDK_DASERVICE_WRITE_TESTS_LIB}
        ${OLP_SDK_DATASERVICE_WRITE_TEST_SOURCES}
    )

    target_link_libraries(${OLP_SDK_DASERVICE_WRITE_TESTS_LIB}
    PRIVATE
        custom-params
        gmock
        gtest
        olp-cpp-sdk-authentication
        olp-cpp-sdk-dataservice-write
        olp-cpp-sdk-tests-common
    )

    # For internal testing
    target_include_directories(${OLP_SDK_DASERVICE_WRITE_TESTS_LIB}
    PRIVATE
        ${${PROJECT_NAME}_SOURCE_DIR}/src
    )

    # For checksum testing
    if(OPENSSL_FOUND)
        target_include_directories(${OLP_SDK_DASERVICE_WRITE_TESTS_LIB}
        PRIVATE
            ${OPENSSL_INCLUDE_DIR}
        )

        target_link_libraries(${OLP_SDK_DASERVICE_WRITE_TESTS_LIB}
        PRIVATE
            ${OPENSSL_CRYPTO_LIBRARY}
        )

        target_compile_definitions(${OLP_SDK_DASERVICE_WRITE_TESTS_LIB}
        PRIVATE
            DATASERVICE_WRITE_HAS_OPENSSL
        )
    endif()

    if (ANDROID)
        include(${CMAKE_SOURCE_DIR}/cmake/android/gen_android_test.cmake)
        gen_android_test_runner(olp-cpp-sdk-dataservice-write-tests
            ${OLP_SDK_DASERVICE_WRITE_TESTS_LIB})
        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/android
            ${CMAKE_CURRENT_BINARY_DIR}/android)

    else()
        include(${CMAKE_SOURCE_DIR}/cmake/ios/gen_ios_test.cmake)
        gen_ios_test_runner(olp-cpp-sdk-dataservice-write-tests
            ${OLP_SDK_DASERVICE_WRITE_TESTS_LIB})
        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/ios
            ${CMAKE_CURRENT_BINARY_DIR}/ios)

    endif()

else()
    add_executable(olp-cpp-sdk-dataservice-write-tests
        ${OLP_SDK_DATASERVICE_WRITE_TEST_SOURCES}
    )

    target_link_libraries(olp-cpp-sdk-dataservice-write-tests
        PRIVATE
            custom-params
            gmock
            gtest
            gtest_main
            olp-cpp-sdk-authentication
            olp-cpp-sdk-dataservice-write
            olp-cpp-sdk-tests-common
    )

    # For internal testing
    target_include_directories(olp-cpp-sdk-dataservice-write-tests
    PRIVATE
        ${${PROJECT_NAME}_SOURCE_DIR}/src
    )

    # For checksum testing
    if(OPENSSL_FOUND)
        target_include_directories(olp-cpp-sdk-dataservice-write-tests
        PRIVATE
            ${OPENSSL_INCLUDE_DIR}
        )

        target_link_libraries(olp-cpp-sdk-dataservice-write-tests
        PRIVATE
            ${OPENSSL_CRYPTO_LIBRARY}
        )

        target_compile_definitions(olp-cpp-sdk-dataservice-write-tests
        PRIVATE
            DATASERVICE_WRITE_HAS_OPENSSL
        )
    endif()
endif()
