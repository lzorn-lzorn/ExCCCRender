#include <iostream>

#include "../../runtime/tools/FileParser.hpp"

int main() {
    ExCCCRender::Tools::FileParser parser("include/test.txt");
    std::cout << parser.GetFileName() << std::endl;
    return 0;
}