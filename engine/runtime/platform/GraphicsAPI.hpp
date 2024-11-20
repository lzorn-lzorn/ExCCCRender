
#include <../../runtime/platform/AbstractGraphicsAPI.hpp>

namespace ExCCCRender::Platform {
// 所有图形学API的虚接口
class GraphicsAPI : public AbstractGraphicsAPI {
public:
    GraphicsAPI()          = default;
    virtual ~GraphicsAPI() = default;

    virtual void Init() {
    }

    virtual void Destroy() {
    }
};

}  // namespace ExCCCRender::Platform