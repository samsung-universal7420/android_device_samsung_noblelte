#
# Copyright (C) 2020 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Inherit from universal7420-common
include device/samsung/universal7420-common/BoardConfigCommon.mk

# Assert
TARGET_OTA_ASSERT_DEVICE := noblelte,nobleltecan,nobleltedd,nobleltedv,nobleltejv,nobleltektt,nobleltelgt,noblelteskt,nobleltespr,nobleltetmo,nobleltezt

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/samsung/noblelte/bluetooth

# Init
TARGET_INIT_VENDOR_LIB := libinit_noblelte
