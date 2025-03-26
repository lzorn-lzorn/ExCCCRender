#pragma once
#include "pch.hpp"

namespace ExCCCRender::Tools::RegexPattern {
using _RegexPattern = std::string;
template <typename _Ty>
concept _Regex_Pattern_Ty =
    std::convertible_to<_Ty, std::string> || std::is_same_v<std::remove_cv_t<std::remove_pointer_t<_Ty>>, char>;

class RegexHelper {
public:
    static RegexHelper& GetInstance() {
        static RegexHelper instance;
        return instance;
    }

    ~RegexHelper()                             = default;
    RegexHelper(const RegexHelper&)            = default;
    RegexHelper& operator=(const RegexHelper&) = default;

    template <_Regex_Pattern_Ty... Args>
    _RegexPattern connect_regex_with_char(char c, Args... args) {
        // A B C ... 其中A, B, C均是正则表达式,
        // 该函数将正则表达式用字符c连接

        return concatenate_with_char(c, {args...});
    }

    _RegexPattern bracket_of_(const char c, _RegexPattern regex = "") noexcept {
        std::string add_str, add_str_inv;
        switch (c) {
            case '(':
            case ')':
                add_str     = std::string(1, '(');
                add_str_inv = std::string(1, ')');
                break;
            case '[':
            case ']':
                add_str     = std::string(1, '[');
                add_str_inv = std::string(1, ']');
                break;
            case '{':
            case '}':
                add_str     = std::string(1, '{');
                add_str_inv = std::string(1, '}');
                break;
            case '<':
            case '>':
                add_str     = std::string(1, '<');
                add_str_inv = std::string(1, '>');
                break;
            default:
                add_str     = std::string(1, c);
                add_str_inv = std::string(1, c);
                break;
        }
        if (IsEscape(c)) {
            add_str     = "\\" + add_str;
            add_str_inv = "\\" + add_str_inv;
        }
        _RegexPattern pattern     = regex.empty() ? R"(.*)" : regex;
        std::string   ret_pattern = add_str + "(" + pattern + ")" + add_str_inv;
        return ret_pattern;
    }

    // 等号模式，支持多个正则表达式
    _RegexPattern equation(_RegexPattern A = "", _RegexPattern B = "") noexcept {
        _RegexPattern key_regex   = A.empty() ? ".*" : A;
        _RegexPattern value_regex = B.empty() ? ".*" : B;
        return "^(" + key_regex + ")=(" + value_regex + ")$";
    }

    template <_Regex_Pattern_Ty... Args>
    std::string regex_or(Args&&... patterns) {
        std::string ret_string = "";
        (..., (ret_string += std::string("(") + std::forward<Args>(patterns) + ")|"));  // 展开每个参数
        ret_string.pop_back();
        return "(" + ret_string + ")";
    }

    template <_Regex_Pattern_Ty... Args>
    std::string regex_and(Args&&... patterns) {
        std::string result = "(?=";
        (..., (result += std::string("(") + std::forward<Args>(patterns) + ")"));  // 展开每个参数
        result += ").*";  // 匹配任意字符串，同时满足所有断言
        return result;
    }

    std::unordered_map<std::string, _RegexPattern>& Get() {
        return regex_table;
    }

public:
    std::unordered_map<std::string, _RegexPattern> regex_table;

private:
    RegexHelper() {
        regex_table = {
            {"integer", R"(-?\d+)"},                   // 匹配整数
            {"float", R"(-?\d+\.\d+)"},                // 匹配浮点数
            {"string", R"(\"(.*?)\")"},                // 匹配双引号字符串
            {"character", R"(\'(.*?)\')"},             // 匹配单引号字符
            {"boolean", R"(true|false)"},              // 匹配布尔值
            {"variable", R"([a-zA-Z_][a-zA-Z0-9_]*)"}  // 匹配变量
        };
    }

private:
    bool IsEscape(const char c) const {
        static const std::string escape_chars = R"(\.,^$|()[]{}*+?)";
        return escape_chars.find(c) != std::string::npos;
    }

    std::string concatenate_with_char(char c, const std::vector<std::string>& parts) {
        std::ostringstream oss;
        bool               first = true;
        for (const auto& part : parts) {
            if (!first) {
                oss << (IsEscape(c) ? "\\" + std::string(1, c) : std::string(1, c));
                // "\\"用于 转义字符
            }
            oss << "(" << part << ")";
            first = false;
        }
        return oss.str();
    }
};

}  // namespace ExCCCRender::Tools::RegexPattern