#include "io.hpp"

using namespace mat;
using namespace buffers;
using namespace io;

int main(void) {
    std::optional<Input> opt_input = read_input(std::cin);
    if (!opt_input.has_value())
        return EXIT_FAILURE;

    Input &input = opt_input.value();
    for (auto &mat : input.bfs) {
        std::cout << mat << "\t \\delta = " 
                  << mat.det_recursion() << std::endl;
    }
        
    return EXIT_SUCCESS;
}
