#include "ctriskseg/transform.h"


Resample::Resample()
{

}

void Resample::setInputSpacing(const std::array<double, 2>& spacing)
{
    m_inSpacing[0] = spacing[0] > 0 ? spacing[0] : 0.01;
    m_inSpacing[1] = spacing[1] > 0 ? spacing[1] : 0.01;
}

void Resample::setOutputSpacing(const std::array<double, 2>& spacing)
{
    m_outSpacing[0] = spacing[0] > 0 ? spacing[0] : 0.01;
    m_outSpacing[1] = spacing[1] > 0 ? spacing[1] : 0.01;
}


