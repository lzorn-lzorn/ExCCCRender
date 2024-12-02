#include "../../runtime/stdheader.h"

namespace ExCCCRender::Platform {

class Shader {
public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~Shader() = 0;
};
}  // namespace ExCCCRender::Platform