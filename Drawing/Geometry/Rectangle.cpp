#include "Rectangle.h"

Rectangle::Rectangle(const Point2D &p1, double width, double height) {
    mLines[0] = std::make_shared<Line>(p1.GetX(), p1.GetY(), p1.GetX() + width, p1.GetY());
    mLines[1] = std::make_shared<Line>(p1.GetX(), p1.GetY() + height, p1.GetX() + width, p1.GetY() + height);
    mLines[2] = std::make_shared<Line>(p1.GetX(), p1.GetY(), p1.GetX(), p1.GetY() + height);
    mLines[3] = std::make_shared<Line>(p1.GetX() + width, p1.GetY(), p1.GetX() + width, p1.GetY() + height);
}

Rectangle::Rectangle(double x, double y, double width, double height) {
    mLines[0] = std::make_shared<Line>(x, y, x + width, y);
    mLines[1] = std::make_shared<Line>(x, y + height, x + width, y + height);
    mLines[2] = std::make_shared<Line>(x, y, x, y + height);
    mLines[3] = std::make_shared<Line>(x + width, y, x + width, y + height);
}

std::array<std::shared_ptr<Line>, number_of_lines> Rectangle::GetLines() const {
    return mLines;
}

std::string Rectangle::DrawSvg() {
    std::string result;
    for (const auto &line: mLines) {
        result += line->DrawSvg() + "\n"; // Using the Line object to draw the rectangle
    }
    return result;
}

void Rectangle::DrawRaster(std::vector<std::vector<int>> &raster) {
    std::for_each(mLines.begin(), mLines.end(), [&raster](const std::shared_ptr<Line> &line) {
        line->DrawRaster(raster); // Using the Line object to draw the rectangle
    });
}

void Rectangle::Translate(double x, double y) {
    std::for_each(mLines.begin(), mLines.end(), [x, y](const std::shared_ptr<Line> &line) {
        line->Translate(x, y); // Using the Line object to translate the rectangle
    });
}

void Rectangle::Rotate(double x, double y, double a) {
    std::for_each(mLines.begin(), mLines.end(), [x, y, a](const std::shared_ptr<Line> &line) {
        line->Rotate(x, y, a); // Using the Line object to rotate the rectangle
    });
}

void Rectangle::Scale(double x, double y, double f) {
    std::for_each(mLines.begin(), mLines.end(), [x, y, f](const std::shared_ptr<Line> &line) {
        line->Scale(x, y, f); // Using the Line object to scale the rectangle
    });
}
