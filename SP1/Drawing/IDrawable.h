#pragma once

#include <string>
#include <vector>

/**
 * Interface representing a drawable object
 */
class IDrawable {
public:
    /**
     * Default constructor
     */
    virtual ~IDrawable() = default;

    /**
     * "Draw" the object as an SVG string
     * Transforms the object into an SVG string
     * @return SVG string representing the object
     */
    virtual std::string DrawSvg() = 0;

    /**
     * Draw the object onto a raster
     * @param raster Matrix of integers representing the raster
     */
    virtual void DrawRaster(std::vector<std::vector<int>> &raster) = 0;

    /**
     * Translate the object by a given vector
     * @param x X coordinate of the translation vector
     * @param y Y coordinate of the translation vector
     */
    virtual void Translate(double x, double y) = 0;

    /**
     * Rotate the object around a given point by a given angle
     * @param x X coordinate of the rotation point
     * @param y Y coordinate of the rotation point
     * @param a Angle of rotation in degrees
     */
    virtual void Rotate(double x, double y, double a) = 0;

    /**
     * Scale the object around a given point by a given factor
     * @param x X coordinate of the scaling point
     * @param y Y coordinate of the scaling point
     * @param f Factor of scaling (should be non-zero)
     */
    virtual void Scale(double x, double y, double f) = 0;
};
