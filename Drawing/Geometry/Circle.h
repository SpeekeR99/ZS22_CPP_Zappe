#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "../IDrawable.h"
#include "Point2D.h"

/**
 * Class representing a circle primitive
 */
class Circle : public IDrawable {
private:
    /** Center of the circle */
    Point2D mCenter;
    /** Radius of the circle */
    double mRadius{};

public:
    /**
     * Default constructor
     */
    Circle() = default;

    /**
     * Constructor with Point2D center and radius
     * @param center Center of the circle
     * @param radius Radius of the circle (should be positive)
     */
    Circle(const Point2D &center, double radius);

    /**
     * Constructor with x and y coordinates of the center and radius
     * @param x X coordinate of the center
     * @param y Y coordinate of the center
     * @param radius Radius of the circle (should be positive)
     */
    Circle(double x, double y, double radius);

    /**
     * Default destructor
     */
    ~Circle() override = default;

    /**
     * Get the center of the circle as a Point2D object
     * @return Center of the circle
     */
    [[nodiscard]] Point2D GetCenter() const;

    /**
     * Get the radius of the circle
     * @return Radius of the circle
     */
    [[nodiscard]] double GetRadius() const;

    /**
     * "Draw" the circle as an SVG string
     * Transforms the circle object into an SVG string
     * @return SVG string representing the circle
     */
    std::string DrawSvg() override;

    /**
     * Draw the circle on a raster
     * @param raster Matrix of integers representing the raster
     */
    void DrawRaster(std::vector<std::vector<int>> &raster) override;

    /**
     * Translate the circle by a given vector
     * @param x X coordinate of the translation vector
     * @param y Y coordinate of the translation vector
     */
    void Translate(double x, double y) override;

    /**
     * Rotate the circle around a given point by a given angle
     * @param x X coordinate of the rotation point
     * @param y Y coordinate of the rotation point
     * @param a Angle of rotation in degrees
     */
    void Rotate(double x, double y, double a) override;

    /**
     * Scale the circle around a given point by a given factor
     * @param x X coordinate of the scaling point
     * @param y Y coordinate of the scaling point
     * @param f Factor of scaling (should be non-zero)
     */
    void Scale(double x, double y, double f) override;
};
