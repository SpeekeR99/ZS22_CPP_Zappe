#pragma once

#include <cmath>
#include <numbers>

/**
 * Class representing 2D point
 */
class Point2D {
private:
    /** X coordinate */
    double mX{};
    /** Y coordinate */
    double mY{};

public:
    /**
     * Default constructor
     */
    Point2D() = default;

    /**
     * Constructor with coordinates
     * @param x X coordinate
     * @param y Y coordinate
     */
    Point2D(double x, double y);

    /**
     * Default destructor
     */
    virtual ~Point2D() = default;

    /**
     * Get X coordinate
     * @return X coordinate
     */
    [[nodiscard]] double GetX() const;

    /**
     * Get Y coordinate
     * @return Y coordinate
     */
    [[nodiscard]] double GetY() const;

    /**
     * Translate the point by the given vector (Point2D works as a vector)
     * @param pt Vector to translate by
     */
    void TranslateByOrigin(const Point2D &pt);

    /**
     * Translate the point by the given vector (two doubles work as a vector)
     * @param x X coordinate of the translation vector
     * @param y Y coordinate of the translation vector
     */
    void TranslateByOrigin(double x, double y);

    /**
     * Rotate the point around the origin by the given angle
     * @param angle Angle to rotate by (in degrees)
     */
    void RotateAroundOrigin(double angle);

    /**
     * Scale the point around the origin by the given factor
     * @param scale_factor Factor to scale by (should be non-zero)
     */
    void ScaleByOrigin(double scale_factor);

    /**
     * Adding two points is basically translating the first point by the second one (Point2D works as a vector)
     * @param other Other point to translate by
     * @return Translated point
     */
    Point2D operator+(const Point2D &other) const;

    /**
     * Subtracting two points is basically translating the first point by the negative of the second one (Point2D works as a vector)
     * @param other Other point to translate by
     * @return Translated point
     */
    Point2D operator-(const Point2D &other) const;

    /**
     * Multiplying a point by a number is basically scaling the point by the number
     * @param scale_factor Scale factor to scale by
     * @return Scaled point
     */
    Point2D operator*(double scale_factor) const;

    /**
     * Uses the same logic as the + operator
     * @param other Other point to add (translate) to this one
     * @return Updated point (translated by the other point)
     */
    Point2D operator+=(const Point2D &other);

    /**
     * Uses the same logic as the - operator
     * @param other Other point to subtract (translate) from this one
     * @return Updated point (translated by the negative of the other point)
     */
    Point2D operator-=(const Point2D &other);

    /**
     * Uses the same logic as the * operator
     * @param scale_factor Scale factor to scale by
     * @return Updated point (scaled by the given factor)
     */
    Point2D operator*=(double scale_factor);
};
