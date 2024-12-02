#include "imgui.h"
#include "../../imgui/backends/imgui_impl_glfw.h"
#include "../../imgui/backends/imgui_impl_vulkan.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace ExCCCRender::Editor {
namespace Detail {

struct ImGuiWithGLFW {};
}  // namespace Detail

class Editor {

public:
    void SetUp();
    bool ShouldWindowClose();
};
}  // namespace ExCCCRender::Editor