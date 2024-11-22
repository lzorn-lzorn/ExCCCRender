#include "../../runtime/tools/FileParser.hpp"
#include "../../runtime/tools/debug.hpp"

namespace ExCCCRender::Tools {
void FileParser::_path_parser() {
    if (absolute_file_path != "") {
        size_t last_separator_pos = this->absolute_file_path.find_last_of("/\\");

        if (last_separator_pos != std::string::npos) {
            this->file_path = this->absolute_file_path.substr(0, last_separator_pos);
            this->file_name = this->absolute_file_path.substr(last_separator_pos + 1);
        } else {
            std::cerr << "file: " << __FILE__ << "; \n";
            std::cerr << "line:" << __LINE__ << "; \n";
            std::cerr << "function " << __func__ << ": param error";
            // throw
            // print error
            // log error
        }
    } else {
        if (file_path != "" && file_name != "") {
            this->absolute_file_path = file_path + file_name;
        }
    }
}

void FileParser::_extension_parser() {
    if (this->file_name != "") {
        size_t last_dot_pos  = this->file_name.find_last_of('.');
        this->file_extension = this->file_name.substr(last_dot_pos + 1);
    } else {
        std::cerr << "file: " << __FILE__ << "; \n";
        std::cerr << "line:" << __LINE__ << "; \n";
        std::cerr << "function " << __func__ << ": param error";
    }
}

bool FileParser::Loader() {
    file_stream.open(absolute_file_path, std::ios::in);
    if (!file_stream.is_open()) {
        std::cerr << "open file fail\n";
        return false;
    }
    return true;
}

std::vector<std::string> FileParser::GetFileContents() {
    if (!file_stream.good()) {
        std::cerr << "file stream error" << std::endl;
    }
    std::vector<std::string> contents;
    std::string              line;
    while (std::getline(file_stream, line)) {
        if (!line.empty()) {
            contents.push_back(line);
        }
    }
    return contents;
}
}  // namespace ExCCCRender::Tools