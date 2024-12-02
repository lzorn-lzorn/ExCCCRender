#include <vulkan/vulkan_core.h>
#include <../../runtime/platform/GraphicsAPI.hpp>
#include <../../runtime/tools/ConfigParser.hpp>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>
#include <vulkan/vulkan_core.h>

namespace ExCCCRender::Platform {
// 所有图形学API的虚接口
namespace detail {
struct VulkanPhysicalDevice {
public:
    VulkanPhysicalDevice() = default;
    VulkanPhysicalDevice(vk::Instance&, vk::InstanceCreateInfo&);

    ~VulkanPhysicalDevice() {
        vk_physical_device = nullptr;
    }

    VulkanPhysicalDevice(const VulkanPhysicalDevice&) = delete;

    VulkanPhysicalDevice(VulkanPhysicalDevice&& that) {
        this->vk_physical_device = std::move(that.vk_physical_device);
        this->extensions         = std::move(that.extensions);
        this->layers             = std::move(that.layers);
    }

    VulkanPhysicalDevice& operator=(VulkanPhysicalDevice&& that) {
        this->vk_physical_device = std::move(that.vk_physical_device);
        this->extensions         = std::move(that.extensions);
        this->layers             = std::move(that.layers);
        return *this;
    }

    vk::PhysicalDevice GetPhysicalDevice() const {
        return vk_physical_device;
    }

    bool IsDeviceSuitable() const {
        return true;
    }

private:
    void enumerate_extensions();
    void enumerate_layers();
    void enable_extensions(vk::InstanceCreateInfo&);
    void enable_layers(vk::InstanceCreateInfo&);
    void pickup_best_physical_device(vk::Instance&);

private:
    vk::PhysicalDevice       vk_physical_device;
    std::vector<const char*> extensions;
    std::vector<const char*> layers;
};

class VulkanContext final : public GraphicsAPI {
public:
    void Initialize(int weight, int height, std::function<void(int, int)>) override;
    void Destroy() override;

    static VulkanContext& GetInstance() {
        assert(instance == nullptr);
        return *instance;
    }

public:
    struct QueueFamilyIndices final {
        std::optional<uint32_t> graphics_queue;
    };

    ~VulkanContext() {
        Destroy();
    }

    vk::Instance         vk_instance;
    VulkanPhysicalDevice physical_device;
    vk::PhysicalDevice   vk_physical_device;
    vk::Device           vk_device;
    QueueFamilyIndices   vk_queues_family_indices;
    vk::Queue            vk_graphics_queue;
    vk::SurfaceKHR       vk_surface;  // 窗口句柄

private:
    static std::unique_ptr<VulkanContext> instance;

private:
    void create_instance();
    void create_surface(int weight, int height, std::function<void(int, int)>);
    void pickup_physical_device();
    void create_device();
    void query_queue_family_indices();
    void get_queue();
    void create_swapchain(int weight, int height);

private:  // 功能性检测
    bool is_device_suitable(vk::PhysicalDevice);
};

struct SwapChain final {
public:
    vk::SwapchainKHR swapchain;

    SwapChain(int weight, int height);
    ~SwapChain();

private:
    struct SwapChainInfo {
        vk::Extent2D                 image_extent;
        uint32_t                     image_count;
        vk::SurfaceFormatKHR         surface_format;
        vk::SurfaceTransformFlagsKHR transform;
        vk::PresentModeKHR           present_mode;
    };

public:
    SwapChainInfo swapchain_info;
};
}  // namespace detail

class VulkanContextBuilder {
public:
    VulkanContextBuilder();
    ~VulkanContextBuilder();
    VulkanContextBuilder(const VulkanContextBuilder&) = delete;
    VulkanContextBuilder(VulkanContextBuilder&&)      = delete;

    detail::VulkanContext& Build() {
        return detail::VulkanContext::GetInstance();
    }

    void LoadConfigFile(std::string&);

public:
private:
    ExCCCRender::Tools::ConfigParser config_parser;
};

}  // namespace ExCCCRender::Platform