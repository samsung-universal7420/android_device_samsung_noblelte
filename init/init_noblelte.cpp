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

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add=false)
{
	auto pi = (prop_info *) __system_property_find(prop);
	if (pi != nullptr) {
	
		__system_property_update(pi, value, strlen(value));
	} else if (add) {
		__system_property_add(prop, strlen(prop), value, strlen(value));
	}
}

void set_ro_product_prop(char const prop[], char const value[])
{
	for (const auto &source : ro_product_props_default_source_order) {
		auto prop_name = "ro.product." + source + prop;
		property_override(prop_name.c_str(), value, false);
	}
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
		property_override("ro.build.description", "nobleltezt-user 7.0 NRD90M N9208ZTS5CRH3 release-keys");
		set_ro_product_prop("device", "noblelte");
		set_ro_product_prop("fingerprint", "samsung/nobleltezt/noblelte:7.0/NRD90M/N9208ZTS5CRH3:user/release-keys");
		set_ro_product_prop("model", "SM-N9208");
		set_ro_product_prop("name", "nobleltezt");
	}
	else if (bootloader.find("N920C") != std::string::npos) {
		/* SM-N920C */
		property_override("ro.build.description", "nobleltejv-user 7.0 NRD90M N920CXXU5CRL3 release-keys");
		set_ro_product_prop("device", "noblelte");
		set_ro_product_prop("fingerprint", "samsung/nobleltejv/noblelte:7.0/NRD90M/N920CXXU5CRL3:user/release-keys");
		set_ro_product_prop("model", "SM-N920C");
		set_ro_product_prop("name", "nobleltejv");
	}
	else if (bootloader.find("N920G") != std::string::npos) {
		/* SM-N920G */
		property_override("ro.build.description", "nobleltedd-user 7.0 NRD90M N920GUBU5CSJ1 release-keys");
		set_ro_product_prop("device", "noblelte");
		set_ro_product_prop("fingerprint", "samsung/nobleltedd/noblelte:7.0/NRD90M/N920GUBU5CSJ1:user/release-keys");
		set_ro_product_prop("model", "SM-N920G");
		set_ro_product_prop("name", "nobleltedd");
	}
	else if (bootloader.find("N920I") != std::string::npos) {
		/* SM-N920I */
		property_override("ro.build.description", "nobleltedv-user 7.0 NRD90M N920IDVU5CRK2 release-keys");
		set_ro_product_prop("device", "noblelte");
		set_ro_product_prop("fingerprint", "samsung/nobleltedv/noblelte:7.0/NRD90M/N920IDVU5CRK2:user/release-keys");
		set_ro_product_prop("model", "SM-N920I");
		set_ro_product_prop("name", "nobleltedv");
	}
	else if (bootloader.find("N920K") != std::string::npos) {
		/* SM-N920K */
		property_override("ro.build.description", "nobleltektt-user 7.0 NRD90M N920KKKU2DRG3 release-keys");
		set_ro_product_prop("device", "nobleltektt");
		set_ro_product_prop("fingerprint", "samsung/nobleltektt/nobleltektt:7.0/NRD90M/N920KKKU2DRG3:user/release-keys");
		set_ro_product_prop("model", "SM-N920K");
		set_ro_product_prop("name", "nobleltektt");
	}
	else if (bootloader.find("N920L") != std::string::npos) {
		/* SM-N920L */
		property_override("ro.build.description", "nobleltelgt-user 7.0 NRD90M N920LKLU2DRH1 release-keys");
		set_ro_product_prop("device", "nobleltelgt");
		set_ro_product_prop("fingerprint", "samsung/nobleltelgt/nobleltelgt:7.0/NRD90M/N920LKLU2DRH1:user/release-keys");
		set_ro_product_prop("model", "SM-N920L");
		set_ro_product_prop("name", "nobleltelgt");
	}
	else if (bootloader.find("N920P") != std::string::npos) {
		/* SM-N920P */
		property_override("ro.build.description", "nobleltespr-user 7.0 NRD90M N920PVPS3DRH1 release-keys");
		set_ro_product_prop("device", "nobleltespr");
		set_ro_product_prop("fingerprint", "samsung/nobleltespr/nobleltespr:7.0/NRD90M/N920PVPS3DRH1:user/release-keys");
		set_ro_product_prop("model", "SM-N920P");
		set_ro_product_prop("name", "nobleltespr");
	}
	else if (bootloader.find("N920S") != std::string::npos) {
		/* SM-N920S */
		property_override("ro.build.description", "noblelteskt-user 7.0 NRD90M N920SKSU2DRG3 release-keys");
		set_ro_product_prop("device", "noblelteskt");
		set_ro_product_prop("fingerprint", "samsung/noblelteskt/noblelteskt:7.0/NRD90M/N920SKSU2DRG3:user/test-keys");
		set_ro_product_prop("model", "SM-N920S");
		set_ro_product_prop("name", "noblelteskt");
	}
	else if (bootloader.find("N920T") != std::string::npos) {
		/* SM-N920T */
		property_override("ro.build.description", "nobleltetmo-user 7.0 NRD90M N920TUVS6ERH1 release-keys");
		set_ro_product_prop("device", "nobleltetmo");
		set_ro_product_prop("fingerprint", "samsung/nobleltetmo/nobleltetmo:7.0/NRD90M/N920TUVS6ERH1:user/test-keys");
		set_ro_product_prop("model", "SM-N920T");
		set_ro_product_prop("name", "nobleltetmo");
	}
	else if (bootloader.find("N920W8") != std::string::npos) {
		/* SM-N920W8 */
		property_override("ro.build.description", "nobleltecan-user 7.0 NRD90M N920W8VLS6CRH1 release-keys");
		set_ro_product_prop("device", "nobleltecan");
		set_ro_product_prop("fingerprint", "samsung/nobleltecan/nobleltecan:7.0/NRD90M/N920W8VLS6CRH1:user/test-keys");
		set_ro_product_prop("model", "SM-N920W8");
		set_ro_product_prop("name", "nobleltecan");
	}

	set_sim_info();

	device = GetProperty("ro.product.device", "");
	LOG(ERROR) << "Found bootloader id '" << bootloader.c_str() << "' setting build properties for '" << device.c_str() << "' device\n";
}
