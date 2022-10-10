#pragma once

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "../IDrawable.h"
#include "Point2D.h"
#include "Line.h"

constexpr size_t number_of_lines = 4;

/**
 * Class representing a rectangle primitive
 */
class Rectangle : public IDrawable {
private:
    /** Array of lines representing the rectangle (Rectangle is just four lines) */
    std::array<std::shared_ptr<Line>, number_of_lines> mLines;

public:
    /**
     * Default constructor
     */
    Rectangle() = default;

    /**
     * Constructor with Point2D start (top left), width and height
     * @param p1 Point2D start point (top left)
     * @param width Width of the rectangle (should be positive)
     * @param height Height of the rectangle (should be positive)
     */
    Rectangle(const Point2D &p1, double width, double height);

    /**
     * Constructor with x and y coordinates of the start (top left), width and height
     * @param x X coordinate of the start point (top left)
     * @param y Y coordinate of the start point (top left)
     * @param width Width of the rectangle (should be positive)
     * @param height Height of the rectangle (should be positive)
     */
    Rectangle(double x, double y, double width, double height);

    /**
     * Default destructor
     */
    ~Rectangle() override = default;

    /**
     * Get the four lines of the rectangle as an array of shared pointers to Line objects
     * @return Array of shared pointers to Line objects
     */
    [[nodiscard]] std::array<std::shared_ptr<Line>, number_of_lines> GetLines() const;

    /**
     * "Draw" the rectangle as an SVG string
     * Transforms the rectangle object into an SVG string
     * @return SVG string representing the rectangle
     */
    std::string DrawSvg() override;

    /**
     * Draw the rectangle onto a raster
     * @param raster Matrix of integers representing the raster
     */
    void DrawRaster(std::vector<std::vector<int>> &raster) override;

    /**
     * Translate the rectangle by a given vector
     * @param x X coordinate of the translation vector
     * @param y Y coordinate of the translation vector
     */
    void Translate(double x, double y) override;

    /**
     * Rotate the rectangle around a given point by a given angle
     * @param x X coordinate of the rotation point
     * @param y Y coordinate of the rotation point
     * @param a Angle of rotation in degrees
     */
    void Rotate(double x, double y, double a) override;

    /**
     * Scale the rectangle around a given point by a given factor
     * @param x X coordinate of the scaling point
     * @param y Y coordinate of the scaling point
     * @param f Factor of scaling (should be non-zero)
     */
    void Scale(double x, double y, double f) override;
};
