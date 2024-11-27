#include <../../runtime/platform/VulkanGraphicsAPI.hpp>
#include <memory>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_funcs.hpp>
#include <vulkan/vulkan_structs.hpp>

namespace ExCCCRender::Platform {

std::unique_ptr<VulkanGraphicsAPI> VulkanGraphicsAPI::instance = nullptr;

}  // namespace ExCCCRender::Platform