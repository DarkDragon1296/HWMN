#include <chrono>
#include "io.hpp"

using namespace mat;
using namespace buffers;
using namespace io;

int main(void) {
    std::optional<Input> opt_input = read_input(std::cin);
    if (!opt_input.has_value())
        return EXIT_FAILURE;

    Input &input = opt_input.value();

    auto start = std::chrono::steady_clock::now();

    for (auto &mat : input.bfs) {
        std::cout << mat << "\t \\delta = " 
                  << mat.det_bareiss() << std::endl;
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "( time = " << duration.count() << " ms )" << std::endl;

    return EXIT_SUCCESS;
}
