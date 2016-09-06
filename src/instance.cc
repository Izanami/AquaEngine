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

} /* ae */
