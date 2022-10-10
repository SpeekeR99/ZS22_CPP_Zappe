#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "IDrawable.h"
#include "Geometry/Point2D.h"
#include "Geometry/Line.h"
#include "Geometry/Circle.h"
#include "Geometry/Rectangle.h"

/**
 * Class representing a canvas
 * Canvas is just a container for drawable shapes
 */
class Canvas {
private:
    /**
     * Vector of drawable shapes
     * Each shape is represented by a shared pointer to IDrawable
     */
    std::vector<std::shared_ptr<IDrawable>> mContent;

public:
    /**
     * Default constructor
     */
    Canvas() = default;

    /**
     * Default destructor
     */
    virtual ~Canvas() = default;

    /**
     * Get content of the canvas (vector of drawable shapes)
     * @return Vector of drawable shapes (shared pointers to IDrawable)
     */
    [[nodiscard]] std::vector<std::shared_ptr<IDrawable>> GetContent() const;

    /**
     * Add drawable shape to the canvas (add shared pointer to IDrawable to the vector of drawable shapes)
     * @param drawable Drawable shape (shared pointer to IDrawable)
     */
    void AddIDrawableShape(const std::shared_ptr<IDrawable> &drawable);

    /**
     * Add line to the canvas (add shared pointer to Line to the vector of drawable shapes)
     * @param x1 X coordinate of the first point (start point)
     * @param y1 Y coordinate of the first point (start point)
     * @param x2 X coordinate of the second point (end point)
     * @param y2 Y coordinate of the second point (end point)
     */
    void AddLine(double x1, double y1, double x2, double y2);

    /**
     * Add circle to the canvas (add shared pointer to Circle to the vector of drawable shapes)
     * @param x X coordinate of the center
     * @param y Y coordinate of the center
     * @param r Radius (should be positive)
     */
    void AddCircle(double x, double y, double r);

    /**
     * Add rectangle to the canvas (add shared pointer to Rectangle to the vector of drawable shapes)
     * @param x X coordinate of the top left corner
     * @param y Y coordinate of the top left corner
     * @param w Width (should be positive)
     * @param h Height (should be positive)
     */
    void AddRectangle(double x, double y, double w, double h);

    /**
     * Translate all drawable shapes on the canvas by given vector
     * @param x X coordinate of the translation vector
     * @param y Y coordinate of the translation vector
     */
    void Translate(double x, double y);

    /**
     * Rotate all drawable shapes on the canvas around given point by given angle
     * @param x X coordinate of the rotation point
     * @param y Y coordinate of the rotation point
     * @param a Angle of rotation (in degrees)
     */
    void Rotate(double x, double y, double a);

    /**
     * Scale all drawable shapes on the canvas around given point by given factor
     * @param x X coordinate of the scaling point
     * @param y Y coordinate of the scaling point
     * @param f Factor of scaling (should be non-zero)
     */
    void Scale(double x, double y, double f);
};
