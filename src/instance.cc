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

void Instance::AddExtensions(std::vector<const char *> extension) {
    extensions_.insert(std::end(extensions_), std::begin(extension),
		       std::end(extension));
}

std::vector<const char *> Instance::Extensions() { return extensions_; }

std::vector<VkExtensionProperties> Instance::AvailableExtensions() {
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
					   extensions.data());
    return extensions;
}

std::vector<const char *> Instance::MissingExtensions() {
    /* Keep only name from AvailableExtensions() */
    auto available_extensions = AvailableExtensions();
    std::vector<const char *> available_extensions_name(
	available_extensions.size());

    for (const auto &extension : available_extensions) {
	available_extensions_name.push_back(std::move(extension.extensionName));
    }

    /* Dismatch between AvailableExtensions and Extensions */
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

std::vector<VkLayerProperties> Instance::AvailableValidations() {
    uint32_t validations_count = 0;
    vkEnumerateInstanceLayerProperties(&validations_count, nullptr);

    std::vector<VkLayerProperties> validations(validations_count);
    vkEnumerateInstanceLayerProperties(&validations_count, validations.data());

    return validations;
}

} /* ae */
