
#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <vector>

class Resample {
public:
    Resample();
    void setInputDimensions(const std::array<std::size_t, 2>& dimensions) { m_inDimension = dimensions; }
    void setOutputDimensions(const std::array<std::size_t, 2>& dimensions) { m_outDimension = dimensions; }
    void setInputSpacing(const std::array<double, 2>& spacing);
    void setOutputSpacing(const std::array<double, 2>& spacing);

    template <typename T>
    std::vector<T> operator()(const std::vector<T>& in) // transform by call method of class
    {
        std::vector<T> out(in.size());

        const std::array<double, 2> forward_scaling { m_outSpacing[0] / m_inSpacing[0], m_outSpacing[1] / m_inSpacing[1] };
        const std::array<double, 2> backward_scaling { 1.0 / forward_scaling[0], 1.0 / forward_scaling[1] };

        // creating offset to preserve image sentering
        const std::array<double, 2> offset { 0.5 * (m_inDimension[0] * m_inSpacing[0] / m_outSpacing[0] - m_outDimension[0]),
            0.5 * (m_inDimension[1] * m_inSpacing[1] / m_outSpacing[1] - m_outDimension[1]) };

        //naive single threaded implenentation
        for (std::size_t j = 0; j < m_outDimension[1]; ++j) {
            // we clamp the values to make a shortcut to nearest interpolation mode if out of bounds
            const double y = std::clamp((j - offset[1]) * backward_scaling[1], 0.0, static_cast<double>(m_inDimension[1] - 1));

            // y-direction
            const auto y1_idx = y < 0.0 ? 0 : y > m_inDimension[1] - 1 ? m_inDimension[1] - 2 : static_cast<std::size_t>(std::floor(y));
            const auto y2_idx = y1_idx + 1;

            for (std::size_t i = 0; i < m_outDimension[0]; ++i) {
                // we clamp the values to make a shortcut to nearest interpolation mode if out of bounds
                const double x = std::clamp((i - offset[0]) * backward_scaling[0], 0.0, static_cast<double>(m_inDimension[0] - 1));

                // x-direction
                const auto x1_idx = x < 0.0 ? 0 : x > m_inDimension[0] - 1 ? m_inDimension[0] - 2 : static_cast<std::size_t>(std::floor(x));
                const auto x2_idx = x1_idx + 1;

                // image interpolation values
                const auto ind_start = x1_idx + y1_idx * m_inDimension[0];
                const auto q11 = in[ind_start];
                const auto q21 = in[ind_start + 1];
                const auto q12 = in[ind_start + m_inDimension[0]];
                const auto q22 = in[ind_start + m_inDimension[0] + 1];

                const auto fx1 = (x2_idx - x) * q11 + (x - x1_idx) * q21;
                const auto fx2 = (x2_idx - x) * q12 + (x - x1_idx) * q22;

                const auto f = static_cast<T>((y2_idx - y) * fx1 + (y - y1_idx) * fx2);
                out[i + j * m_outDimension[0]] = f;
            }
        }
    }

protected:
    static std::array<double, 4> inverse2x2(const std::array<double, 4>& mat)
    {
        const auto det = mat[0] * mat[3] - mat[1] * mat[2];
        std::array<double, 4> inv;
        inv[0] = mat[3] / det;
        inv[3] = mat[0] / det;
        inv[1] = -mat[1] / det;
        inv[2] = -mat[2] / det;
        return inv;
    }

    std::array<double, 2> m_inSpacing;
    std::array<double, 2> m_outSpacing;
    std::array<std::size_t, 2> m_inDimension;
    std::array<std::size_t, 2> m_outDimension;
};
