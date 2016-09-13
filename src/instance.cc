#include "instance.h"
#include <string.h>
#include <algorithm>
#include "error.h"

namespace ae {
Instance::Instance() {
    vk_instance_ = std::make_shared<VkInstance>();
    vk_instance_informations_ = std::make_shared<VkInstanceCreateInfo>();

    vk_instance_informations_->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
}
Instance::~Instance() {}

std::shared_ptr<VkInstance> Instance::Create() {
    if (application_ == nullptr) {
	Application(std::make_shared<ae::Application>());
    }

    auto result = vkCreateInstance(vk_instance_informations_.get(), nullptr,
				   vk_instance_.get());

    vk_instance_informations_->enabledExtensionCount =
	static_cast<uint32_t>(extensions_.size());
    vk_instance_informations_->ppEnabledExtensionNames = extensions_.data();

    if (result == VK_ERROR_EXTENSION_NOT_PRESENT) {
	std::string error_message = error::Vulkan::to_str(result);
	error_message += " :";
	for (const auto &extension : MissingExtensions()) {
	    error_message += " ";
	    error_message += extension;
	}
	throw std::runtime_error(error_message);
    }

    else if (result != VK_SUCCESS) {
	throw std::runtime_error(error::Vulkan::to_str(result));
    }

    return vk_instance_;
}

void Instance::Application(std::shared_ptr<ae::Application> application) {
    application_ = application;

    // Get information from Application class
    vk_instance_informations_->pApplicationInfo =
	application->informations().get();
}

void Instance::AddExtensions(std::vector<const char *> extension) noexcept {
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
    const std::vector<const char *> validations) noexcept {
    validations_.insert(std::end(validations_), std::begin(validations),
			std::end(validations));
}

std::vector<VkLayerProperties> Instance::AvailableValidations() const noexcept {
    uint32_t validations_count = 0;
    vkEnumerateInstanceLayerProperties(&validations_count, nullptr);

    std::vector<VkLayerProperties> validations(validations_count);
    vkEnumerateInstanceLayerProperties(&validations_count, validations.data());

    return validations;
}

std::vector<const char *> Instance::AvailableValidationsName() const noexcept {
    auto available_validations = AvailableValidations();
    std::vector<const char *> available_validations_name;
    available_validations_name.reserve(available_validations.size());

    for (const auto &valisation : available_validations) {
	available_validations_name.push_back(std::move(valisation.layerName));
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
