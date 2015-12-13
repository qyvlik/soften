#include "vector2d.h"

#include <cmath>
#include <iostream>

vector2d::vector2d():
    m_x(0),
    m_y(0)
{

}

vector2d::vector2d(double x, double y):
    m_x(x),
    m_y(y)
{
}

double vector2d::x() const
{
    return m_x;
}

void vector2d::setX(double x)
{
    m_x = x;
}

double vector2d::y() const
{
    return m_y;
}

void vector2d::setY(double y)
{
    m_y = y;
}

double vector2d::dotProduct(const vector2d &other) const
{
    return this->m_x*other.m_x + this->m_y*other.m_y;
}

vector2d vector2d::times(const vector2d &other) const
{
    return vector2d(this->m_x*other.m_x, this->m_y*other.m_y);
}

vector2d vector2d::times(double factor) const
{
    return vector2d(this->m_x*factor, this->m_y*factor);
}

vector2d vector2d::plus(const vector2d &other) const
{
    return vector2d(this->m_x+other.m_x, this->m_y+other.m_y);
}

vector2d vector2d::minus(const vector2d &other) const
{
    return vector2d(this->m_x-other.m_x, this->m_y-other.m_y);
}

double vector2d::length() const
{
    return sqrt(pow(this->m_x, 2) + pow(this->m_y, 2));
}

bool vector2d::fuzzyEquals(const vector2d &other, double epsilon) const
{
    return abs(this->m_x-other.m_x)+abs(this->m_y-other.m_y) < epsilon;
}

vector2d vector2d::normalized() const
{
    double length = this->length();

#ifdef QBS_DEBUG
    std::cout << "double equal zero mean equal 1e-7" << std::endl;
#endif

    return length != 1e-7 ?
                vector2d(this->m_x / length, this->m_y / length)
              : vector2d();
}

