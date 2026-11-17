#include "io.hpp"

using namespace mat;
using namespace buffers;

namespace io {

std::optional<Input> read_input(std::istream &source) {
    size_t matrix_count = 0;
    if (!(source >> matrix_count)) {
        std::cerr << "Invalid matrix count\n";
        return std::nullopt;
    }

    Input input = {
        .bfs = Bfs::create(matrix_count),
        .jgs = Jgs::create(matrix_count),
    };

    for (size_t i = 0; i < matrix_count; ++i) {
        size_t matrix_size = 0;
        if (!(source >> matrix_size)) {
            std::cerr << "Invalid matrix size\n";
            return std::nullopt;
        }

        auto vla = VLA<double>::create(matrix_size * matrix_size);
        if (!(source >> vla)) {
            std::cerr << "Missing data for matrix " 
                      << i + 1 << "." << std::endl;
            return std::nullopt;
        }
        input.bfs[i] = SqMatrixBf<double>(matrix_size, vla.cbegin(), vla.cend());
        input.jgs[i] = SqMatrixJg<double>(matrix_size, vla.cbegin(), vla.cend());
    }

    return input;
}

std::istream &operator>>(std::istream &source, VLA<double> &vla) {
    if (!read_vla(source, vla))
        source.setstate(std::ios::failbit);
    return source;
}

bool read_vla(std::istream &source, VLA<double> &vla) {
    for (double &it : vla) {
        double dbl = 0.0f;
        if (!(source >> dbl) || 
            !std::isfinite(dbl)) {
            return false;
        }
        it = dbl;
    }
    return true;
}

}
