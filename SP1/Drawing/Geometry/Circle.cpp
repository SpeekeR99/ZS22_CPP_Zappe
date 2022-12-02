#include "Circle.h"

Circle::Circle(const Point2D &center, double radius) : mCenter{center}, mRadius{radius} {
    //
}

Circle::Circle(double x, double y, double radius) : mCenter{x, y}, mRadius{radius} {
    //
}

Point2D Circle::GetCenter() const {
    return mCenter;
}

double Circle::GetRadius() const {
    return mRadius;
}

std::string Circle::DrawSvg() {
    // Standard SVG circle element (using black color and 2px stroke width and no fill)
    return "<circle cx=\"" + std::to_string(mCenter.GetX()) + "\" cy=\"" + std::to_string(mCenter.GetY()) +
           "\" r=\"" + std::to_string(mRadius) + R"(" stroke="black" stroke-width="2" fill="none" />)";
}

void Circle::DrawRaster(std::vector<std::vector<int>> &raster) {
    // Copied algorithm from: http://members.chello.at/~easyfilter/bresenham.html
    int x = static_cast<int>(mCenter.GetX());
    int y = static_cast<int>(mCenter.GetY());
    int r = static_cast<int>(mRadius);

    if (x < 0 || y < 0 || x >= raster[0].size() || y >= raster.size()) {
        std::cerr << "ERROR: Circle is out of bounds." << std::endl;
        return; // Simple check to avoid out of bounds errors
    }

    int x2 = -r;
    int y2 = 0;
    int err = 2 - 2 * r;

    do {
        raster[y + y2][x - x2] = 0;
        raster[y - x2][x - y2] = 0;
        raster[y - y2][x + x2] = 0;
        raster[y + x2][x + y2] = 0;
        // Add pixel to the right if possible, if not add to the left
        // Add pixel to the top if possible, if not add to the bottom
        y + y2 + 1 < raster.size() ? raster[y + y2 + 1][x - x2] = 0 : raster[y + y2 - 1][x - x2] = 0;
        y - x2 + 1 < raster.size() ? raster[y - x2 + 1][x - y2] = 0 : raster[y - x2 - 1][x - y2] = 0;
        y - y2 + 1 < raster.size() ? raster[y - y2 + 1][x + x2] = 0 : raster[y - y2 - 1][x + x2] = 0;
        y + x2 + 1 < raster.size() ? raster[y + x2 + 1][x + y2] = 0 : raster[y + x2 - 1][x + y2] = 0;
        x - x2 + 1 < raster[0].size() ? raster[y + y2][x - x2 + 1] = 0 : raster[y + y2][x - x2 - 1] = 0;
        x - y2 + 1 < raster[0].size() ? raster[y - x2][x - y2 + 1] = 0 : raster[y - x2][x - y2 - 1] = 0;
        x + x2 + 1 < raster[0].size() ? raster[y - y2][x + x2 + 1] = 0 : raster[y - y2][x + x2 - 1] = 0;
        x + y2 + 1 < raster[0].size() ? raster[y + x2][x + y2 + 1] = 0 : raster[y + x2][x + y2 - 1] = 0;

        r = err;
        if (r <= y2) {
            err += ++y2 * 2 + 1;
        }
        if (r > x2 || err > y2) {
            err += ++x2 * 2 + 1;
        }
    } while (x2 < 0);
}

void Circle::Translate(double x, double y) {
    mCenter.TranslateByOrigin(x, y);
}

void Circle::Rotate(double x, double y, double a) {
    Translate(-x, -y);
    mCenter.RotateAroundOrigin(a);
    Translate(x, y);
}

void Circle::Scale(double x, double y, double f) {
    Translate(-x, -y);
    mCenter.ScaleByOrigin(f);
    mRadius *= f;
    Translate(x, y);
}
