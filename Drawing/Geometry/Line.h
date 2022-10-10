#pragma once

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "../IDrawable.h"
#include "Point2D.h"

/**
 * Class representing a line primitive
 */
class Line : public IDrawable {
private:
    /** Start point of the line */
    Point2D mP1;
    /** End point of the line */
    Point2D mP2;

public:
    /**
     * Default constructor
     */
    Line() = default;

    /**
     * Constructor with Point2D start and end points
     * @param p1 Point2D start point (should not be equal to p2)
     * @param p2 Point2D end point (should not be equal to p1)
     */
    Line(const Point2D &p1, const Point2D &p2);

    /**
     * Constructor with x and y coordinates of the start and end points
     * @param x1 X coordinate of the start point (should not be equal to x2)
     * @param y1 Y coordinate of the start point (should not be equal to y2)
     * @param x2 X coordinate of the end point (should not be equal to x1)
     * @param y2 Y coordinate of the end point (should not be equal to y1)
     */
    Line(double x1, double y1, double x2, double y2);

    /**
     * Default destructor
     */
    ~Line() override = default;

    /**
     * Get the start point of the line as a Point2D object
     * @return Start point of the line
     */
    [[nodiscard]] Point2D GetPoint1() const;

    /**
     * Get the end point of the line as a Point2D object
     * @return End point of the line
     */
    [[nodiscard]] Point2D GetPoint2() const;

    /**
     * "Draw" the line as an SVG string
     * Transforms the line object into an SVG string
     * @return SVG string representing the line
     */
    std::string DrawSvg() override;

    /**
     * Draw the line on a raster
     * @param raster Matrix of integers representing the raster
     */
    void DrawRaster(std::vector<std::vector<int>> &raster) override;

    /**
     * Translate the line by a given vector
     * @param x X coordinate of the translation vector
     * @param y Y coordinate of the translation vector
     */
    void Translate(double x, double y) override;

    /**
     * Rotate the line around the origin by a given angle
     * @param x X coordinate of the rotation center
     * @param y Y coordinate of the rotation center
     * @param a Angle of rotation in degrees
     */
    void Rotate(double x, double y, double a) override;

    /**
     * Scale the line around the origin by a given factor
     * @param x X coordinate of the scaling center
     * @param y Y coordinate of the scaling center
     * @param f Factor of scaling (should be non-zero)
     */
    void Scale(double x, double y, double f) override;
};
