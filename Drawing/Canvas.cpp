#include "Canvas.h"

std::vector<std::shared_ptr<IDrawable>> Canvas::GetContent() const {
    return mContent;
}

void Canvas::AddIDrawableShape(const std::shared_ptr<IDrawable> &drawable) {
    mContent.push_back(drawable);
}

void Canvas::AddLine(double x1, double y1, double x2, double y2) {
    std::shared_ptr<IDrawable> line = std::make_shared<Line>(x1, y1, x2, y2);
    mContent.push_back(line);
}

void Canvas::AddCircle(double x, double y, double r) {
    std::shared_ptr<IDrawable> circle = std::make_shared<Circle>(x, y, r);
    mContent.push_back(circle);
}

void Canvas::AddRectangle(double x, double y, double w, double h) {
    std::shared_ptr<IDrawable> rect = std::make_shared<Rectangle>(x, y, w, h);
    mContent.push_back(rect);
}

void Canvas::Translate(double x, double y) {
    std::for_each(mContent.begin(), mContent.end(), [x, y](const auto &shape) {
        shape->Translate(x, y);
    });
}

void Canvas::Rotate(double x, double y, double a) {
    std::for_each(mContent.begin(), mContent.end(), [x, y, a](const auto &shape) {
        shape->Rotate(x, y, a);
    });
}

void Canvas::Scale(double x, double y, double f) {
    std::for_each(mContent.begin(), mContent.end(), [x, y, f](const auto &shape) {
        shape->Scale(x, y, f);
    });
}
