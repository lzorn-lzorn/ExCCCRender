#include "../../runtime/tools/FileParser.hpp"
#include "../../runtime/stdheader.h"

namespace ExCCCRender::Tools {
namespace detail {
using _Value_Type  = std::variant<int, float, double, std::string, bool>;
using _Key_Type    = std::string;
using _Config_Type = std::string;

struct IniItem {
    _Config_Type config_name;
    _Key_Type    key;
    _Value_Type  value;
};
}  // namespace detail

class ConfigParser final : public FileParser {
public:
    ConfigParser() = delete;

    template <String _Ty>
    explicit ConfigParser(FilePath<_Ty> absolute_file_path) : FileParser(absolute_file_path) {
    }

    template <String _Ty>
    explicit ConfigParser(FilePath<_Ty> file_path, FilePath<_Ty> file_name) : FileParser(file_path, file_name) {
    }

    virtual ~ConfigParser() override {};
    virtual void Parser();
    virtual void PrintConfigInfo() const;

private:
    //  将配置文件的字符串解析为ConfigInfo的表项
    std::optional<detail::_Value_Type> parser_config_value(const std::string& config_item_value);

    template <typename... _Ts>
    void print_config_value(const std::variant<_Ts...>& val) const {
        std::visit(
            [](auto&& arg) {
                std::cout << arg;
            },
            val);
    }

    // 消除字符串中的所有空格
    void clear_space(std::string&) const;
    void clear_annotation(std::string&) const;

private:
    std::vector<detail::IniItem> ConfigInfo;
};
}  // namespace ExCCCRender::Tools