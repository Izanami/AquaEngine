#include "instance.h"
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

    if (result != VK_SUCCESS) {
	throw std::runtime_error(error::Vulkan::to_str(result));
    }

    return vk_instance_;
}

void Instance::Application(std::shared_ptr<ae::Application> application) {
    application_ = application;

    // Get information from Application class
    vk_instance_informations_->pApplicationInfo =
	application->Informations().get();
}

void Instance::AddExtensions(std::vector<const char*> extension) {
    extensions_.insert(std::end(extensions_), std::begin(extension),
		       std::end(extension));
}

std::vector<const char*> Instance::Extensions() { return extensions_; }

} /* ae */
