#include "FileParser.hpp"
#include <map>
#include <variant>
#include <iostream>

namespace ExCCCRender::Platform {
class ConfigParser : public FileParser {
public:
    ConfigParser() = delete;

    template <String _Ty>
    ConfigParser(FilePath<_Ty> absolute_file_path) : FileParser(absolute_file_path) {
    }

    template <String _Ty>
    ConfigParser(FilePath<_Ty> file_path, FilePath<_Ty> file_name) : FileParser(file_path, file_name) {
    }

    virtual ~ConfigParser() override {};
    virtual void Loader() override {};
    virtual void Parser() override {};

public:
    using _Value_Type = std::variant<int, float, double, std::string, bool>;
    using _Key_Type   = std::string;

private:
    std::map<std::string, std::pair<_Key_Type, _Value_Type>> config_data;
};
}  // namespace ExCCCRender::Platform