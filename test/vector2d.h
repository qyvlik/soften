#ifndef VECTOR2D_H
#define VECTOR2D_H


class vector2d
{
public:
    static constexpr double Epsilon = 0.001;

    vector2d();

    vector2d(double x, double y);

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    double dotProduct(const vector2d& other) const;

    vector2d times(const vector2d& other) const;

    vector2d times(double factor) const;

    vector2d plus(const vector2d& other) const;

    vector2d minus(const vector2d& other) const;

    double length() const;

    vector2d normalized() const;

    bool fuzzyEquals(const vector2d& other, double epsilon = vector2d::Epsilon) const;

private:
    double m_x;
    double m_y;
};

#endif // VECTOR2D_H
