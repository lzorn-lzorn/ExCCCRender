#include "../../runtime/platform/FileParser.hpp"

namespace ExCCCRender::Platform {
void FileParser::_path_parser() {
    if (absolute_file_path != "") {
        size_t last_separator_pos = this->absolute_file_path.find_last_of("/\\");
        if (last_separator_pos != std::string::npos) {
            this->file_path = absolute_file_path.substr(0, last_separator_pos);
            this->file_name = absolute_file_path.substr(last_separator_pos + 1);
        } else {

            this->file_path = " ";
            this->file_name = absolute_file_path.substr(last_separator_pos + 1);
            std::cerr << "file: " << __FILE__ << "; \n";
            std::cerr << "line:" << __LINE__ << "; \n";
            std::cerr << "function " << __func__ << ": param error";
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
}  // namespace ExCCCRender::Platform