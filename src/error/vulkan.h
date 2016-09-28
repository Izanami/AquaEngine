// AquaEngine
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

#ifndef AE_ERROR_H_
#define AE_ERROR_H8

#include <vulkan/vulkan.h>
#include <memory>
#include <string>
#include <utility>
#include "../error.h"
#include "../instance.h"

namespace ae::error {

/// \brief Handle vulkan errors.
/// \sa ae::Error
///
/// Example :
///
/// \code
///    auto instance = std::make_shared<ae::Instance>();
///    ae::Error::Vulkan error;
///    error.set_instance(instance);
///    error.set_result(instance->Create());
///
///    if(error.IsError())
///        throw error.DiagnosticAll().first;
/// \encode
class Vulkan final : public ae::Error {
   public:
    Vulkan();
    virtual ~Vulkan();

    Vulkan(const Vulkan &);
    Vulkan(Vulkan &&);
    Vulkan &operator=(const Vulkan &);
    Vulkan &operator=(Vulkan &&);

    explicit Vulkan(VkResult);
    explicit Vulkan(VkResult, std::shared_ptr<ae::Instance>);
    explicit Vulkan(std::shared_ptr<ae::Instance>);

    VkResult result() const noexcept;
    void set_result(const VkResult) noexcept;

    std::shared_ptr<ae::Instance> instance() const noexcept;
    void set_instance(std::shared_ptr<ae::Instance>) noexcept;

    /// \brief Analyse the errors for more details.
    /// \sa ae::Error::DiagnosticAll()
    std::pair<std::string, Flags> DiagnosticAll() noexcept override;

    /// \brief Analyse extensions vulkan.
    /// \sa ae::Error::DiagnisticAll()
    std::pair<std::string, Flags> DiagnosticExtensions() noexcept;

    /// \brief Returns message errors.
    const std::string ToString() const noexcept;

    /// \brief Returns the corresponding string of the code.
    static constexpr const char *ToString(const VkResult code) noexcept {
        switch (code) {
            case VK_SUCCESS:
                return u8"Vulkan : Command successfully completed";
                break;
            case VK_NOT_READY:
                return u8"Vulkan : A fence or query has not yet completed";
                break;
            case VK_TIMEOUT:
                return u8"Vulkan : A wait operation has not completed in the "
                       "specified time";
                break;
            case VK_EVENT_SET:
                return u8"Vulkan : An event is signaled";
                break;
            case VK_EVENT_RESET:
                return u8"Vulkan : An event is unsignaled";
                break;
            case VK_INCOMPLETE:
                return u8"Vulkan : A return array was too small for the result";
                break;

            case VK_ERROR_OUT_OF_HOST_MEMORY:
                return u8"Vulan : A host memory allocation has failed";
                break;
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                return u8"Vulkan : A device memory allocation has failed";
                break;
            case VK_ERROR_INITIALIZATION_FAILED:
                return u8"Vulkan : Initialization of an object could not be "
                       "completed";
                break;
            case VK_ERROR_DEVICE_LOST:
                return u8"Vulkan : The logical or physical device has been "
                       u8"lost";
                break;
            case VK_ERROR_MEMORY_MAP_FAILED:
                return u8"Vulkan : Mapping of a memory object has failed";
                break;
            case VK_ERROR_LAYER_NOT_PRESENT:
                return u8"Vulkan: A requested layer is not present or could "
                       u8"not "
                       "be loaded";
                break;
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                return u8"Vulkan : A requested extension is not supported";
                break;
            case VK_ERROR_FEATURE_NOT_PRESENT:
                return u8"Vulkan : A requested feature is not supported";
                break;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                return u8"Vulkan : The requested version of Vulkan is not "
                       "supported by the driver or is otherwise incompatible";
                break;
            case VK_ERROR_TOO_MANY_OBJECTS:
                return u8"Vulkan : Too many objects of the type have already "
                       "been created";
                break;
            case VK_ERROR_FORMAT_NOT_SUPPORTED:
                return u8"Vulkan : A requested format is not supported on this "
                       "device";
                break;
            case VK_ERROR_FRAGMENTED_POOL:
                return u8"Vulkan : A requested pool allocation has failed due "
                       u8"to "
                       "fragmentation of the pool’s memory";
                break;

            /* Extra */
            case VK_ERROR_VALIDATION_FAILED_EXT:
                return u8"Vulkan : VK_ERROR_VALIDATION_FAILED_EXT";
                break;

            case VK_RESULT_RANGE_SIZE:
                return u8"Vulkan : VK_RESULT_RANGE_SIZE";
                break;

            case VK_SUBOPTIMAL_KHR:
                return u8"Vulkan : VK_SUBOPTIMAL_KHR";
                break;

            case VK_RESULT_MAX_ENUM:
                return u8"Vulkan : VK_RESULT_MAX_ENUM";
                break;

            /* KHR */
            case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                return u8"Vulkan : VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
                break;
            case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                return u8"Vulkan : VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
                break;
            case VK_ERROR_SURFACE_LOST_KHR:
                return u8"Vulkan : VK_ERROR_SURFACE_LOST_KHR";
                break;
            case VK_ERROR_OUT_OF_DATE_KHR:
                return u8"Vulkan : VK_ERROR_OUT_OF_DATE_KHR";
                break;

            /* Nvidia */
            case VK_ERROR_INVALID_SHADER_NV:
                return u8"Vulkan : VK_ERROR_INVALID_SHADER_NV";
                break;
        }

        return u8"Vulkan : Unknow error";
    }

   private:
    /// \brief The code error.
    VkResult result_ = VK_SUCCESS;

    /// \brief Used to analyse errors.
    std::shared_ptr<ae::Instance> instance_ = std::make_shared<ae::Instance>();
};
} /* ae::error */

#endif /* AE_ERROR_H8 */
