#include <concepts>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace ExCCCRender::Tools::RegexPattern {
using _RegexPattern = const std::string&;
template <typename _Ty>
concept _Regex_Pattern_Ty = std::same_as<_Ty, _RegexPattern>;

static inline _RegexPattern variable() noexcept {
    return R"(^[a-zA-Z_][a-zA-Z0-9_]*$)";
}

static inline _RegexPattern color() noexcept {
    return R"(#[a-fA-F0-9]{6}\b)";
}

static inline _RegexPattern word() noexcept {
    return R"([a-zA-Z]+)";
}

static inline _RegexPattern square_bracket(_RegexPattern regex = "") noexcept {
    // 匹配方括号中的内容, regex 也是一个正则表达式
    _RegexPattern pattern = regex == "" ? R"(\[(.*?)\])" : R"(\[()" + regex + R"()\])";
    return pattern;
}

static inline _RegexPattern equation(_RegexPattern A = "", _RegexPattern B = "") noexcept {
    _RegexPattern key_regex   = A.empty() ? ".*" : A;
    _RegexPattern value_regex = B.empty() ? ".*" : B;
    return "^(" + key_regex + ")=(" + value_regex + ")$";
}

template <_Regex_Pattern_Ty... Args>
static inline _RegexPattern connect_regex_with_char(char c, Args... args) {
    // A B C ... 其中A, B, C均是正则表达式,
    // 该函数将正则表达式用字符c连接
    return detail::concatenate_with_char(c, {args...});
}

namespace detail {
static std::string concatenate_with_char(char c, const std::vector<std::string>& parts) {
    std::ostringstream oss;
    bool               first = true;
    for (const auto& part : parts) {
        if (!first) {
            oss << (std::isalnum(c) ? std::string(1, c) : "\\" + std::string(1, c));
            // "\\"用于 转义字符
        }
        oss << "(" << part << ")";
        first = false;
    }
    return oss.str();
}
}  // namespace detail
}  // namespace ExCCCRender::Tools::RegexPattern