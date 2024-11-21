#include "FileParser.hpp"
#include <map>
#include <variant>
#include <iostream>

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
    std::optional<detail::_Value_Type> parser_config_value(const std::string& config_item_value);

    template <typename... _Ts>
    void print_config_value(const std::variant<_Ts...>& val) const {
        std::visit(
            [](auto&& arg) {
                std::cout << arg;
            },
            val);
    }

private:
    std::vector<detail::IniItem> ConfigInfo;
};
}  // namespace ExCCCRender::Tools