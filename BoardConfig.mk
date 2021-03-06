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

# Kernel
TARGET_KERNEL_CONFIG := lineageos_noblelte_defconfig

# Partitions
BOARD_HAS_NO_MISC_PARTITION:= true
TARGET_USERIMAGES_USE_F2FS := true
BOARD_BOOTIMAGE_PARTITION_SIZE := 29360128
BOARD_CACHEIMAGE_PARTITION_SIZE := 209715200
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 35651584
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 3124019200
#BOARD_USERDATAIMAGE_PARTITION_SIZE := 59183980544 #64GB
BOARD_FLASH_BLOCK_SIZE := 131072

# Properties
TARGET_SYSTEM_PROP += device/samsung/noblelte/system.prop

# Radio
BOARD_MODEM_TYPE := ss333
