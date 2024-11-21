#include <../../runtime/platform/VulkanGraphicsAPI.hpp>
#include <memory>
#include <vulkan/vulkan_enums.hpp>
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
    _pickup_physical_device();
    _query_queue_family_indices();
    _create_device();
    _get_queue();
}

VulkanGraphicsAPI::~VulkanGraphicsAPI() {
    instance.destroy();
    device.destroy();
}

void VulkanGraphicsAPI::_create_instance() {
    vk::InstanceCreateInfo createInfo{};
    vk::ApplicationInfo    appInfo{};
    appInfo.setApiVersion(VK_API_VERSION_1_3).setPEngineName("imugi");
    createInfo.setPApplicationInfo(&appInfo);

    instance = vk::createInstance(createInfo);

    std::vector<const char*> layers = {"VK_LAYER_KHRONOS_validation"};
    createInfo.setPEnabledLayerNames(layers);
    instance = vk::createInstance(createInfo);
}  // namespace ExCCCRender::Platform

void VulkanGraphicsAPI::_pickup_physical_device() {
    auto device     = instance.enumeratePhysicalDevices();
    physical_device = device[0];  // ! 这里可以选择 GPU，通过GPU支持的特性
}

void VulkanGraphicsAPI::_create_device() {
    vk::DeviceCreateInfo      create_info{};
    vk::DeviceQueueCreateInfo queue_create_info{};
    float                     queue_priorities = 1.0f;
    queue_create_info.setPQueuePriorities(&queue_priorities)
        .setQueueCount(1)
        .setQueueFamilyIndex(queues_family_indices.graphics_queue.value());
    create_info.setQueueCreateInfos(queue_create_info);

    device = physical_device.createDevice(create_info);
}

void VulkanGraphicsAPI::_query_queue_family_indices() {
    auto properties = physical_device.getQueueFamilyProperties();
    for (int i = 0; i < properties.size(); i++) {
        const auto& property = properties[i];
        if (property.queueFlags | vk::QueueFlagBits::eGraphics) {
            queues_family_indices.graphics_queue = i;
            break;
        }
    }
}

void VulkanGraphicsAPI::_get_queue() {
    graphics_queue = device.getQueue(queues_family_indices.graphics_queue.value(), 0);
}
}  // namespace ExCCCRender::Platform