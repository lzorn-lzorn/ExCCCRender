#include <../../runtime/platform/GraphicsAPI.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_handles.hpp>

namespace ExCCCRender::Platform {
// 所有图形学API的虚接口
class VulkanGraphicsAPI final : public GraphicsAPI {
public:
    virtual ~VulkanGraphicsAPI();

    virtual void Initialize();
    virtual void Destroy();

    static VulkanGraphicsAPI& CreateInstance() {
        assert(instance_ == nullptr);
        return *instance_;
    }

public:
    struct QueueFamilyIndices final {
        std::optional<uint32_t> graphics_queue;
    };

    vk::Instance       instance;
    vk::PhysicalDevice physical_device;
    vk::Device         device;
    QueueFamilyIndices queues_family_indices;
    vk::Queue          graphics_queue;

private:
    VulkanGraphicsAPI();

    void _create_instance();
    void _pickup_physical_device();
    void _create_device();
    void _query_queue_family_indices();
    void _get_queue();

private:
    static std::unique_ptr<VulkanGraphicsAPI> instance_;
};

}  // namespace ExCCCRender::Platform