// AquaEngineV
// Copyright © 2016 Adrien Jeser <adrien@jeser.me>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "instance.h"
#include <string.h>
#include <algorithm>
#include "error.h"

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define DISCARD
#endif
#endif

namespace ae {
Instance::Instance() {
    vk_instance_informations_->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
}
Instance::~Instance() { vkDestroyInstance(*vk_instance_.get(), nullptr); }

Instance::Instance(const Instance &instance)
    : vk_instance_(instance.vk_instance_),
      vk_instance_informations_(instance.vk_instance_informations_),
      extensions_(instance.extensions_),
      validations_(instance.validations_) {}

Instance::Instance(Instance &&instance)
    : vk_instance_(std::move(instance.vk_instance_)),
      vk_instance_informations_(std::move(instance.vk_instance_informations_)),
      extensions_(std::move(instance.extensions_)),
      validations_(std::move(instance.validations_)) {}

Instance &Instance::operator=(const Instance &instance) {
    vk_instance_ = instance.vk_instance_;
    vk_instance_informations_ = instance.vk_instance_informations_;
    extensions_ = instance.extensions_;
    validations_ = instance.validations_;
    return *this;
}

Instance &Instance::operator=(Instance &&instance) {
    vk_instance_ = std::move(instance.vk_instance_);
    vk_instance_informations_ = std::move(instance.vk_instance_informations_);
    extensions_ = std::move(instance.extensions_);
    validations_ = std::move(instance.validations_);
    return *this;
}

VkResult Instance::Create() noexcept {
    if (enable_default_validations) {
	AddDefaultValidations();
    }

    if (validations_.size() > 0) {
	std::vector<const char *> extensions_validations = {
	    VK_EXT_DEBUG_REPORT_EXTENSION_NAME};
	AddExtensions(extensions_validations);
    }

#ifndef DISCARD
    vk_instance_informations_->enabledLayerCount =
	static_cast<uint32_t>(validations_.size());
    vk_instance_informations_->ppEnabledLayerNames = validations_.data();
#else
#pragma message("Disable validation layer. #22")
#endif

    auto result = vkCreateInstance(vk_instance_informations_.get(), nullptr,
				   vk_instance_.get());

    return result;
}

void Instance::AddExtensions(
    const std::vector<const char *> &extension) noexcept {
    extensions_.insert(std::end(extensions_), std::begin(extension),
		       std::end(extension));
}

std::vector<const char *> Instance::extensions() const noexcept {
    return extensions_;
}

std::vector<VkExtensionProperties> Instance::AvailableExtensions() const
    noexcept {
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
					   extensions.data());
    return extensions;
}

std::vector<const char *> Instance::AvailableExtensionsName() const noexcept {
    auto available_extensions = AvailableExtensions();
    std::vector<const char *> available_extensions_name;
    available_extensions_name.reserve(available_extensions.size());

    for (const auto &extension : available_extensions) {
	available_extensions_name.push_back(std::move(extension.extensionName));
    }

    return available_extensions_name;
}

std::vector<const char *> Instance::MissingExtensions() const noexcept {
    auto available_extensions_name = AvailableExtensionsName();

    /* Dismatch between AvailableExtensionsName and Extensions */
    std::vector<const char *> missing_extensions;
    for (const auto &extension : extensions_) {
	auto result = std::find(std::begin(available_extensions_name),
				std::end(available_extensions_name), extension);

	if (result == std::end(available_extensions_name)) {
	    missing_extensions.push_back(extension);
	}
    }

    return missing_extensions;
}

std::vector<const char *> Instance::validations() const noexcept {
    return validations_;
}

void Instance::AddValidations(
    const std::vector<const char *> &validations) noexcept {
    validations_.insert(std::end(validations_), std::begin(validations),
			std::end(validations));
}

std::vector<VkLayerProperties> Instance::AvailableValidations() const noexcept {
#ifdef DISCARD
    std::vector<VkLayerProperties> validations;
    return validations;
#else
    uint32_t validations_count = 0;
    vkEnumerateInstanceLayerProperties(&validations_count, nullptr);

    std::vector<VkLayerProperties> validations(validations_count);
    vkEnumerateInstanceLayerProperties(&validations_count, validations.data());
    return validations;
#endif
}

void Instance::AddDefaultValidations() noexcept {
    AddValidations(kDefaultValidations);
}

std::vector<const char *> Instance::AvailableValidationsName() const noexcept {
    auto available_validations = AvailableValidations();
    std::vector<const char *> available_validations_name;
    available_validations_name.reserve(available_validations.size());

    for (const auto &validation : available_validations) {
	available_validations_name.push_back(std::move(validation.layerName));
    }

    return available_validations_name;
}

std::vector<const char *> Instance::MissingValidations() const noexcept {
    auto available_validations_name = AvailableValidationsName();

    std::vector<const char *> missing_validations;

    for (const auto &validation : validations_) {
	auto result =
	    std::find(std::begin(available_validations_name),
		      std::end(available_validations_name), validation);

	if (result == std::end(available_validations_name)) {
	    missing_validations.push_back(validation);
	}
    }

    return missing_validations;
}

} /* ae */
