#include <iostream>

#include "../../runtime/platform/FileParser.hpp"

int main() {
    ExCCCRender::Platform::FileParser parser("include/test.txt");
    std::cout << parser.GetFileName() << std::endl;
    return 0;
}