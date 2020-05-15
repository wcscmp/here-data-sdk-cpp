#!/bin/bash -ex
#
# Copyright (C) 2020 HERE Europe B.V.
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


mkdir -p build && cd build

echo ""
echo ""
echo "*************** $VARIANT Build ********** Start ***************"
CMAKE_COMMAND="cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=android-21 -DANDROID_STL=c++_static -DANDROID_ABI=armeabi-v7a"
NINJA_COMMAND="ninja -j$(nproc)"

echo ""
echo " ---- Calling $CMAKE_COMMAND"
${CMAKE_COMMAND}

# Run CMake. Warnings and errors are saved to build/CMakeFiles/CMakeOutput.log and
# build/CMakeFiles/CMakeError.log.
# -- We link Edge SDK as shared libraries in order to use shadowing for unit tests.
# -- We build the examples.
echo ""
echo " ---- Calling ${NINJA_COMMAND}"
${NINJA_COMMAND}

#cmake .. -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
#	-DANDROID_PLATFORM=android-25 \
#	-DANDROID_ABI=arm64-v8a \
#	-DOLP_SDK_ENABLE_TESTING=NO \
#	-DOLP_SDK_BUILD_EXAMPLES=ON

#cmake --build . # this is alternative option for build
#sudo make install -j$(nproc)
cd -

#ls -la $ANDROID_HOME
#export PATH=$PATH:$ANDROID_HOME/tools/bin/
sdkmanager --list
sdkmanager "platform-tools" "platforms;android-21" "emulator"
sdkmanager "system-images;android-21;google_apis;armeabi-v7a"
echo no | avdmanager create avd -n android-21 -k "system-images;android-21;google_apis;armeabi-v7a"
ls $ANDROID_HOME/tools/emulator
$ANDROID_HOME/tools/emulator -avd android-21 -no-snapshot -noaudio -no-boot-anim -gpu off -no-accel -no-window -camera-back none -camera-front none -selinux permissive -qemu -m 2048 &
./scripts/android/android-wait-for-emulator.sh
adb shell input keyevent 82 &