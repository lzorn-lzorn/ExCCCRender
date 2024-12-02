#include <iostream>
#include "../../runtime/tools/ConfigParser.hpp"

int main() {
    ExCCCRender::Tools::ConfigParser parser(
        "C:\\Program User\\code\\ExCCCRender\\engine\\configs\\GrapicsAPIConfig.ini");
    std::cout << parser.GetFullFilePath() << std::endl;
    try {
        parser.Loader();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    parser.Parser();
    std::cout << "Parser Over" << std::endl;
    parser.PrintConfigInfo();
    return 0;
}