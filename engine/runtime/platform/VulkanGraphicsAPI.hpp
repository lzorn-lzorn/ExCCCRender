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
        assert(instance == nullptr);
        return *instance;
    }

public:
    struct QueueFamilyIndices final {
        std::optional<uint32_t> graphics_queue;
    };

    vk::Instance       vk_instance;
    vk::PhysicalDevice vk_physical_device;
    vk::Device         vk_device;
    QueueFamilyIndices vk_queues_family_indices;
    vk::Queue          vk_graphics_queue;

private:
    VulkanGraphicsAPI();

    void create_instance();
    void pickup_physical_device();
    void create_device();
    void query_queue_family_indices();
    void get_queue();

private:
    static std::unique_ptr<VulkanGraphicsAPI> instance;
};

}  // namespace ExCCCRender::Platform