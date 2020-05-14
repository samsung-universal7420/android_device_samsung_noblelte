/*
   Copyright (c) 2020, The CyanogenMod Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <string.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;

void property_override(char const prop[], char const value[])
{	
	prop_info *pi;

	pi = (prop_info*) __system_property_find(prop);
	if (pi)
		__system_property_update(pi, value, strlen(value));
	else
		__system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[],
		char const vendor_prop[], char const value[])
{
	property_override(system_prop, value);
	property_override(vendor_prop, value);
}

void set_sim_info()
{
	const char *simslot_count_path = "/proc/simslot_count";
	std::string simslot_count;
	
	if (ReadFileToString(simslot_count_path, &simslot_count)) {
		simslot_count = Trim(simslot_count); // strip newline
		property_override("ro.multisim.simslotcount", simslot_count.c_str());
		if (simslot_count.compare("2") == 0) {
			property_override("rild.libpath2", "/system/vendor/lib64/libsec-ril-dsds.so");
			property_override("persist.radio.multisim.config", "dsds");
		}
	}
	else {
		LOG(ERROR) << "Could not open '" << simslot_count_path << "'\n";
	}
}

void vendor_load_properties()
{
	std::string bootloader = GetProperty("ro.bootloader", "");
	std::string device;

	if (bootloader.find("N9208") != std::string::npos) {
		/* SM-N9208 */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltezt/noblelte:7.0/NRD90M/N9208ZTS5CRH3:user/release-keys");
		property_override("ro.build.description", "nobleltezt-user 7.0 NRD90M N9208ZTS5CRH3 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N9208");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "noblelte");
		property_override("ro.product.name", "nobleltezt");
	}
	else if (bootloader.find("N920C") != std::string::npos) {
		/* SM-N920C */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltejv/noblelte:7.0/NRD90M/N920CXXU5CRL3:user/release-keys");
		property_override("ro.build.description", "nobleltejv-user 7.0 NRD90M N920CXXU5CRL3 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920C");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "noblelte");
		property_override("ro.product.name", "nobleltejv");
	}
	else if (bootloader.find("N920G") != std::string::npos) {
		/* SM-N920G */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltedd/noblelte:7.0/NRD90M/N920GUBU5CSJ1:user/release-keys");
		property_override("ro.build.description", "nobleltedd-user 7.0 NRD90M N920GUBU5CSJ1 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920G");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "noblelte");
		property_override("ro.product.name", "nobleltedd");
	}
	else if (bootloader.find("N920I") != std::string::npos) {
		/* SM-N920I */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltedv/noblelte:7.0/NRD90M/N920IDVU5CRK2:user/release-keys");
		property_override("ro.build.description", "nobleltedv-user 7.0 NRD90M N920IDVU5CRK2 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920I");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "noblelte");
		property_override("ro.product.name", "nobleltedv");
	}
	else if (bootloader.find("N920K") != std::string::npos) {
		/* SM-N920K */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltektt/nobleltektt:7.0/NRD90M/N920KKKU2DRG3:user/release-keys");
		property_override("ro.build.description", "nobleltektt-user 7.0 NRD90M N920KKKU2DRG3 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920K");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "nobleltektt");
		property_override("ro.product.name", "nobleltektt");
	}
	else if (bootloader.find("N920L") != std::string::npos) {
		/* SM-N920L */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltelgt/nobleltelgt:7.0/NRD90M/N920LKLU2DRH1:user/release-keys");
		property_override("ro.build.description", "nobleltelgt-user 7.0 NRD90M N920LKLU2DRH1 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920L");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "nobleltelgt");
		property_override("ro.product.name", "nobleltelgt");
	}
	else if (bootloader.find("N920P") != std::string::npos) {
		/* SM-N920P */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltespr/nobleltespr:7.0/NRD90M/N920PVPS3DRH1:user/release-keys");
		property_override("ro.build.description", "nobleltespr-user 7.0 NRD90M N920PVPS3DRH1 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920P");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "nobleltespr");
		property_override("ro.product.name", "nobleltespr");
	}
	else if (bootloader.find("N920S") != std::string::npos) {
		/* SM-N920S */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/noblelteskt/noblelteskt:7.0/NRD90M/N920SKSU2DRG3:user/test-keys");
		property_override("ro.build.description", "noblelteskt-user 7.0 NRD90M N920SKSU2DRG3 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920S");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "noblelteskt");
		property_override("ro.product.name", "noblelteskt");
	}
	else if (bootloader.find("N920T") != std::string::npos) {
		/* SM-N920T */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltetmo/nobleltetmo:7.0/NRD90M/N920TUVS6ERH1:user/test-keys");
		property_override("ro.build.description", "nobleltetmo-user 7.0 NRD90M N920TUVS6ERH1 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920T");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "nobleltetmo");
		property_override("ro.product.name", "nobleltetmo");
	}
	else if (bootloader.find("N920W8") != std::string::npos) {
		/* SM-N920W8 */
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/nobleltecan/nobleltecan:7.0/NRD90M/N920W8VLS6CRH1:user/test-keys");
		property_override("ro.build.description", "nobleltecan-user 7.0 NRD90M N920W8VLS6CRH1 release-keys");
		property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-N920W8");
		property_override_dual("ro.product.device", "ro.product.vendor.device", "nobleltecan");
		property_override("ro.product.name", "nobleltecan");
	}

	set_sim_info();

	device = GetProperty("ro.product.device", "");
	LOG(ERROR) << "Found bootloader id '" << bootloader.c_str() << "' setting build properties for '" << device.c_str() << "' device\n";
}
