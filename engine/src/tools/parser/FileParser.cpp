#include "pch.hpp"
#include "tools/RegexHelper.hpp"
#include "tools/debug.hpp"
#include "tools/parser/FileParser.hpp"

namespace ExCCCRender::Tools {
FileParser::FileParser(FileParser&& other) noexcept
    : m_buffer(std::move(other.m_buffer)),
      m_file_stream(),  // 不直接移动 std::fstream
      m_file_path(std::move(other.m_file_path)),
      m_file_name(std::move(other.m_file_name)),
      m_file_extension(std::move(other.m_file_extension)),
      m_absolute_file_path(std::move(other.m_absolute_file_path)) {
    if (other.m_file_stream.is_open()) {
        // 如果源对象的文件流是打开的，将其转移到当前对象
        m_file_stream.open(other.m_absolute_file_path, std::ios::in | std::ios::out);
        other.m_file_stream.close();  // 关闭源对象的文件流
    }
}

FileParser& FileParser::operator=(FileParser&& other) noexcept {
    if (this != &other) {  // 防止自赋值
        // 释放当前对象的文件流
        if (m_file_stream.is_open()) {
            m_file_stream.close();
        }

        // 转移成员变量
        m_buffer             = std::move(other.m_buffer);
        m_file_path          = std::move(other.m_file_path);
        m_file_name          = std::move(other.m_file_name);
        m_file_extension     = std::move(other.m_file_extension);
        m_absolute_file_path = std::move(other.m_absolute_file_path);

        // 转移文件流
        if (other.m_file_stream.is_open()) {
            m_file_stream.open(other.m_absolute_file_path, std::ios::in | std::ios::out);
            other.m_file_stream.close();
        }
    }
    return *this;
}

void FileParser::path_parser() {
    if (m_absolute_file_path != "") {
        size_t last_separator_pos = this->m_absolute_file_path.find_last_of("/\\");

        if (last_separator_pos != std::string::npos) {
            this->m_file_path = this->m_absolute_file_path.substr(0, last_separator_pos);
            this->m_file_name = this->m_absolute_file_path.substr(last_separator_pos + 1);
        } else {
            std::cerr << "file: " << __FILE__ << "; \n";
            std::cerr << "line:" << __LINE__ << "; \n";
            std::cerr << "function " << __func__ << ": param error";
            // throw
            // print error
            // log error
        }
    } else {
        if (m_file_path != "" && m_file_name != "") {
            this->m_absolute_file_path = m_file_path + m_file_name;
        }
    }
}

void FileParser::extension_parser() {
    if (this->m_file_name != "") {
        size_t last_dot_pos    = this->m_file_name.find_last_of('.');
        this->m_file_extension = this->m_file_name.substr(last_dot_pos + 1);
    } else {
        std::cerr << "file: " << __FILE__ << "; \n";
        std::cerr << "line:" << __LINE__ << "; \n";
        std::cerr << "function " << __func__ << ": param error";
    }
}

bool FileParser::Loader() {
    m_file_stream.open(m_absolute_file_path, std::ios::in);
    if (!m_file_stream.is_open()) {
        std::cerr << "open file fail\n";
        return false;
    }
    return true;
}

std::vector<std::string> FileParser::GetFileContents() {
    if (!m_file_stream.good()) {
        std::cerr << "file stream error" << std::endl;
    }
    std::vector<std::string> contents;
    std::string              line;
    while (std::getline(m_file_stream, line)) {
        if (!line.empty()) {
            contents.push_back(line);
        }
    }
    return contents;
}
}  // namespace ExCCCRender::Tools