

namespace ExCCCRender::Platform {
// 所有图形学API的虚接口
class AbstractGraphicsAPI {
public:
    AbstractGraphicsAPI();
    virtual ~AbstractGraphicsAPI() = 0;
    virtual void Initialize()      = 0;
    virtual void Destroy()         = 0;
};

}  // namespace ExCCCRender::Platform