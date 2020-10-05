#include "ctriskseg/transform.h"

#include <array>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream input("\python\circle_in.bin", std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator(input), {});
    auto data = reinterpret_cast<double*>(buffer.data());
    std::vector<double> arr(data, data + buffer.size() * sizeof(unsigned char) / sizeof(double));

    std::array<double, 2> spacing { 1.0, 1.0 };
    std::array<std::size_t, 2> shape { 512, 512 };

    Resample t;

}