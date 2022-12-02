#include "Point2D.h"

Point2D::Point2D(double x, double y) : mX{x}, mY{y} {
    //
}

double Point2D::GetX() const {
    return mX;
}

double Point2D::GetY() const {
    return mY;
}

void Point2D::TranslateByOrigin(const Point2D &pt) {
    *this += pt;
}

void Point2D::TranslateByOrigin(double x, double y) {
    TranslateByOrigin({x, y});
}

void Point2D::RotateAroundOrigin(double angle) {
    angle = angle * std::numbers::pi / 180; // Convert angle in degrees to radians
    double s = sin(angle);
    double c = cos(angle);
    double newX = mX * c - mY * s;
    double newY = mX * s + mY * c;
    mX = newX;
    mY = newY;
}

void Point2D::ScaleByOrigin(double scale_factor) {
    *this *= scale_factor;
}

Point2D Point2D::operator+(const Point2D &other) const {
    return Point2D{mX + other.mX, mY + other.mY};
}

Point2D Point2D::operator-(const Point2D &other) const {
    return Point2D{mX - other.mX, mY - other.mY};
}

Point2D Point2D::operator*(double scale_factor) const {
    return Point2D{mX * scale_factor, mY * scale_factor};
}

Point2D Point2D::operator+=(const Point2D &other) {
    this->mX += other.mX;
    this->mY += other.mY;
    return *this;
}

Point2D Point2D::operator-=(const Point2D &other) {
    this->mX -= other.mX;
    this->mY -= other.mY;
    return *this;
}

Point2D Point2D::operator*=(const double scale_factor) {
    this->mX *= scale_factor;
    this->mY *= scale_factor;
    return *this;
}
