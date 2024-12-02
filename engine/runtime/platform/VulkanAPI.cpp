#include <vulkan/vulkan_core.h>
#include <../../runtime/platform/VulkanAPI.hpp>
#include <memory>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_funcs.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

namespace ExCCCRender::Platform {

std::unique_ptr<detail::VulkanContext> detail::VulkanContext::instance = nullptr;

namespace detail {
void VulkanContext::Initialize(int weight, int height, std::function<void(int, int)> op) {
    create_instance();
    create_surface(weight, height, op);
    pickup_physical_device();
    create_device();
    query_queue_family_indices();
    get_queue();
}

void VulkanContext::Destroy() {
    if (vk_device) {
        vk_device.destroy();
    }

    if (vk_instance) {
        vk_instance.destroy();
    }
}

void VulkanContext::create_instance() {
    vk::ApplicationInfo app_info{
        "ExCCCRender", VK_MAKE_VERSION(1, 3, 0), "No Engine", VK_MAKE_VERSION(1, 3, 0), VK_API_VERSION_1_3};
    vk::InstanceCreateInfo instance_create_info{};
    instance_create_info.setPApplicationInfo(&app_info);
    physical_device    = VulkanPhysicalDevice(vk_instance, instance_create_info);
    vk_physical_device = physical_device.GetPhysicalDevice();
    vk_instance        = vk::createInstance(instance_create_info);
}

void VulkanContext::create_surface(int weight, int height, std::function<void(int, int)> op) {
    vk::SurfaceKHR surface;
    // 需要基于具体的窗口系统
    op(weight, height);

    // 将其设置为一个hook, 暂时不实现通过, 在窗口系统初始化时调用这里的钩子函数
    vk_surface = vk::SurfaceKHR(surface);
}

void VulkanContext::create_device() {
    if (!vk_queues_family_indices.graphics_queue.has_value()) {
        throw std::runtime_error("Graphics queue family index not found.");
    }

    auto     queue_families         = vk_physical_device.getQueueFamilyProperties();
    uint32_t queue_family_max_count = 0;
    for (const auto& queue_family : queue_families) {
        if (queue_family.queueFlags & vk::QueueFlagBits::eGraphics) {
            queue_family_max_count = std::max(queue_family_max_count, queue_family.queueCount);
        }
    }

    if (queue_family_max_count == 0) {
        throw std::runtime_error("No graphics queue family found.");
    }

    vk::DeviceQueueCreateInfo queue_create_info{};
    const float               queue_priorities = 1.0f;
    queue_create_info.setQueueFamilyIndex(vk_queues_family_indices.graphics_queue.value())
        .setQueueCount(queue_family_max_count)  // 一般直接拉满
        .setPQueuePriorities(&queue_priorities);

    vk::DeviceCreateInfo create_info{};
    // 只关心图形队列
    create_info.setQueueCreateInfoCount(1).setPQueueCreateInfos(&queue_create_info);
}

void VulkanContext::query_queue_family_indices() {
    auto queue_families = vk_physical_device.getQueueFamilyProperties();
    auto size           = queue_families.size();
    for (uint32_t i = 0; i < size; ++i) {
        if (queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics) {
            vk_queues_family_indices.graphics_queue = i;
            break;
        }
    }

    if (!vk_queues_family_indices.graphics_queue.has_value()) {
        throw std::runtime_error("Graphics queue family index not found.");
    }
}

void VulkanContext::get_queue() {
    auto index        = vk_queues_family_indices.graphics_queue.value();
    vk_graphics_queue = vk_device.getQueue(index, 0);
}

// VulkanPhysicalDevice =====================================================
VulkanPhysicalDevice::VulkanPhysicalDevice(vk::Instance&           vk_instance,
                                           vk::InstanceCreateInfo& vk_instance_create_info) try {
    pickup_best_physical_device(vk_instance);
    enumerate_extensions();
    enumerate_layers();
    enable_extensions(vk_instance_create_info);
    enable_layers(vk_instance_create_info);
} catch (const std::exception& e) {

    std::cerr << e.what() << std::endl;
    // 打 LOG
}

void VulkanPhysicalDevice::enumerate_extensions() {
    auto available_extensions = vk_physical_device.enumerateDeviceExtensionProperties();
    for (const auto& extension : available_extensions) {
        extensions.push_back(extension.extensionName);
    }
}

void VulkanPhysicalDevice::enumerate_layers() {
    auto available_layers = vk::enumerateInstanceLayerProperties();
    for (const auto& layer : available_layers) {
        layers.push_back(layer.layerName);
    }
}

void VulkanPhysicalDevice::enable_extensions(vk::InstanceCreateInfo& create_info) {
    create_info.setEnabledExtensionCount(static_cast<uint32_t>(extensions.size()))
        .setPpEnabledExtensionNames(extensions.data());
}

void VulkanPhysicalDevice::enable_layers(vk::InstanceCreateInfo& create_info) {
    create_info.setEnabledLayerCount(static_cast<uint32_t>(extensions.size()))
        .setPpEnabledLayerNames(extensions.data());
}

void VulkanPhysicalDevice::pickup_best_physical_device(vk::Instance& vk_instance) {
    uint32_t max_extension_count = 0;
    uint32_t max_layer_count     = 0;

    if (vk_instance.enumeratePhysicalDevices().empty()) {
        throw std::runtime_error("No physical device found.");
    }

    for (const auto& device : vk_instance.enumeratePhysicalDevices()) {
        auto     extensions_     = device.enumerateDeviceExtensionProperties();
        uint32_t extension_count = extensions_.size();

        auto     layers_     = vk::enumerateInstanceLayerProperties();
        uint32_t layer_count = layers_.size();

        if (extension_count > max_extension_count
            || (extension_count == max_extension_count && layer_count > max_layer_count)) {
            max_extension_count = extension_count;
            max_layer_count     = layer_count;
            vk_physical_device  = device;
        }
    }
    if (!vk_physical_device) {
        throw std::runtime_error("No suitable physical device found.");
    }
}
}  // namespace detail

// @param path: absolute path
void VulkanContextBuilder::LoadConfigFile(std::string& path) {
    config_parser = ExCCCRender::Tools::ConfigParser(path);
}
}  // namespace ExCCCRender::Platform