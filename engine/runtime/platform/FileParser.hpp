#include <string>
#include <iostream>
#include <concepts>

namespace ExCCCRender::Platform {
template <typename _Ty>
concept String = requires(_Ty type) {
    { std::string(type) } -> std::convertible_to<std::string>;
};
template <String _Ty>
using FilePath = _Ty const&;

class FileParser {
public:
    FileParser() = delete;

    template <String _Ty>
    FileParser(FilePath<_Ty> absolute_file_path) : absolute_file_path(std::string(absolute_file_path)) {
        _init();
    }

    template <String _Ty>
    FileParser(FilePath<_Ty> file_path, FilePath<_Ty> file_name)
        : file_path(std::string(file_path)), file_name(std::string(file_name)) {
        _init();
    }

    virtual ~FileParser() = default;

    virtual void Loader() {};
    virtual void Parser() {};

    virtual std::string GetFilePath() const {
        return file_path;
    }

    virtual std::string GetFileName() const {
        return file_name;
    }

    virtual std::string GetFileExtension() const {
        return file_extension;
    }

private:
    void _init() {
        _path_parser();
        _extension_parser();
    }

    void _path_parser();
    void _extension_parser();

private:
    std::string file_path{""};
    std::string file_name{""};
    std::string file_extension{""};
    std::string absolute_file_path{""};  // absolute_file_path = file_path + file_name
};

}  // namespace ExCCCRender::Platform