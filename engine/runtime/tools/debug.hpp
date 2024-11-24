#include "../../runtime/stdheader.h"

namespace ExCCCRender::Tools {  // 定义 debug 宏
#ifdef NDEBUG                   // release
    #define LOG(...)
#else  // debug
    // LOG 宏
    #define LOG(...) log_impl(std::cout, __VA_ARGS__)
#endif

template <typename... Args>
void log_impl(std::ostream& os, Args&&... args) {
    ((os << std::forward<Args>(args) << " "), ...) << '\n';  // 折叠表达式打印每个参数
}

#if defined(_MSC_VER)
    #define NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
    #define NOINLINE __attribute__((noinline))
#else
    #define NOINLINE
#endif
}  // namespace ExCCCRender::Tools
