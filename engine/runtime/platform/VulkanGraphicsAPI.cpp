#include <../../runtime/platform/VulkanGraphicsAPI.hpp>
#include <memory>
#include <vulkan/vulkan_funcs.hpp>
#include <vulkan/vulkan_structs.hpp>

namespace ExCCCRender::Platform {

std::unique_ptr<VulkanGraphicsAPI> VulkanGraphicsAPI::instance_ = nullptr;

void VulkanGraphicsAPI::Initialize() {
    instance_.reset();
}

void VulkanGraphicsAPI::Destroy() {
    instance_.reset();
}

VulkanGraphicsAPI::VulkanGraphicsAPI() {
    CreateInstance();
}

VulkanGraphicsAPI::~VulkanGraphicsAPI() {
    instance.destroy();
}

void VulkanGraphicsAPI::_internal_create_instance() {
    vk::InstanceCreateInfo createInfo{};
    vk::ApplicationInfo    appInfo{};
    appInfo.setApiVersion(VK_API_VERSION_1_3).setPEngineName("imugi");
    createInfo.setPApplicationInfo(&appInfo);

    instance = vk::createInstance(createInfo);

    std::vector<const char*> layers = {"VK_LAYER_KHRONOS_validation"};
    createInfo.setPEnabledLayerNames(layers);
    instance = vk::createInstance(createInfo);
}  // namespace ExCCCRender::Platform

}  // namespace ExCCCRender::Platform