#include "Line.h"

Line::Line(const Point2D &p1, const Point2D &p2) : mP1{p1}, mP2{p2} {
    //
}

Line::Line(double x1, double y1, double x2, double y2) : mP1{x1, y1}, mP2{x2, y2} {
    //
}

Point2D Line::GetPoint1() const {
    return mP1;
}

Point2D Line::GetPoint2() const {
    return mP2;
}

std::string Line::DrawSvg() {
    // Standard SVG line format (using black color and 2px width)
    return "<line x1=\"" + std::to_string(mP1.GetX()) + "\" y1=\"" + std::to_string(mP1.GetY()) + "\" x2=\"" +
           std::to_string(mP2.GetX()) + "\" y2=\"" + std::to_string(mP2.GetY()) +
           R"(" stroke="black" stroke-width="2" />)";
}

void Line::DrawRaster(std::vector<std::vector<int>> &raster) {
    // Copied algorithm from: http://members.chello.at/~easyfilter/bresenham.html
    int x0 = static_cast<int>(mP1.GetX());
    int y0 = static_cast<int>(mP1.GetY());
    int x1 = static_cast<int>(mP2.GetX());
    int y1 = static_cast<int>(mP2.GetY());

    if (x0 < 0 || x0 >= raster[0].size() || y0 < 0 || y0 >= raster.size() ||
        x1 < 0 || x1 >= raster[0].size() || y1 < 0 || y1 >= raster.size()) {
        std::cerr << "ERROR: Line is out of bounds." << std::endl;
        return; // Simple check to avoid out of bounds errors
    }

    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        raster[y0][x0] = 0;
        // Add pixel to the right if possible, if not add to the left
        // Add pixel to the top if possible, if not add to the bottom
        x0 + 1 < raster[0].size() ? raster[y0][x0 + 1] = 0 : raster[y0][x0 - 1] = 0;
        y0 + 1 < raster.size() ? raster[y0 + 1][x0] = 0 : raster[y0 - 1][x0] = 0;
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void Line::Translate(double x, double y) {
    mP1.TranslateByOrigin(x, y); // Translate point 1
    mP2.TranslateByOrigin(x, y); // Translate point 2
}

void Line::Rotate(double x, double y, double a) {
    Translate(-x, -y); // Translate to origin
    mP1.RotateAroundOrigin(a); // Rotate point 1
    mP2.RotateAroundOrigin(a); // Rotate point 2
    Translate(x, y); // Translate back
}

void Line::Scale(double x, double y, double f) {
    Translate(-x, -y); // Translate to origin
    mP1.ScaleByOrigin(f); // Scale point 1
    mP2.ScaleByOrigin(f); // Scale point 2
    Translate(x, y); // Translate back
}
