#include <../../runtime/platform/GraphicsAPI.hpp>
#include <memory>
#include <vulkan/vulkan.hpp>

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
    vk::Instance instance;

private:
    VulkanGraphicsAPI();

    void _internal_create_instance();
    void _internal_pickup_physical_device();

private:
    static std::unique_ptr<VulkanGraphicsAPI> instance_;
};

}  // namespace ExCCCRender::Platform