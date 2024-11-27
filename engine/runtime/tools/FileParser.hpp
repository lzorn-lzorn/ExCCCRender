#include "../../runtime/stdheader.h"

namespace ExCCCRender::Tools {
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
    explicit FileParser(FilePath<_Ty> absolute_file_path) : m_absolute_file_path(std::string(absolute_file_path)) {
        init();
    }

    template <String _Ty>
    explicit FileParser(FilePath<_Ty> file_path, FilePath<_Ty> file_name)
        : m_file_path(std::string(file_path)), m_file_name(std::string(file_name)) {
        init();
    }

    virtual ~FileParser() {
        m_file_stream.close();
    };

    virtual bool                     Loader();
    virtual std::vector<std::string> GetFileContents();

    virtual std::string GetFilePath() const {
        return m_file_path;
    }

    virtual std::string GetFileName() const {
        return m_file_name;
    }

    virtual std::string GetFileExtension() const {
        return m_file_extension;
    }

    virtual std::string GetFullFilePath() const {
        return m_absolute_file_path;
    }

private:
    void init() {
        path_parser();
        extension_parser();
    }

    void path_parser();       // 路径解析
    void extension_parser();  // 扩展名解析
private:
    std::vector<char> m_buffer;
    std::fstream      m_file_stream{};
    std::string       m_file_path{""};
    std::string       m_file_name{""};
    std::string       m_file_extension{""};
    std::string       m_absolute_file_path{""};  // absolute_file_path = file_path + file_name
};

}  // namespace ExCCCRender::Tools