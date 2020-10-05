#include "ctriskseg/transform.h"

#include <array>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream input("circle_in.bin", std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator(input), {});
    auto data = reinterpret_cast<double*>(buffer.data());
    std::vector<double> arr(data, data + buffer.size() * sizeof(unsigned char) / sizeof(double));

    std::array<double, 2> in_spacing { 1.0, 1.0 };
    std::array<std::size_t, 2> in_shape { 512, 512 };

    std::array<double, 2> out_spacing { 4.0, 4.0 };
    std::array<std::size_t, 2> out_shape { 256, 256 };



    Resample t;
    t.setOutputDimensions(out_shape);
    t.setOutputSpacing(out_spacing);
    auto samp = t(arr, in_shape, in_spacing);

    std::ofstream outfile("circle_out.bin", std::ios::out | std::ofstream::binary);
    
    std::ostream_iterator<char> osi { outfile };
    const char* beginByte = (char*)&samp[0];

    const char* endByte = (char*)&samp.back() + sizeof(double);
    std::copy(beginByte, endByte, osi);



}