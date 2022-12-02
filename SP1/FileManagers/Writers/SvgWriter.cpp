#include "SvgWriter.h"

/* Magic constants for SVG file format */
constexpr const char *xmlHeader = R"(<?xml version="1.0" standalone="no"?>)";
constexpr const char *svgHeader1 = "<svg";
constexpr const char *svgHeader2 = R"(version="1.1" xmlns="http://www.w3.org/2000/svg">)";
constexpr const char *svgBackground = R"(<rect x="0" y="0" width="100%" height="100%" fill="white" />)";
constexpr const char *svgFooter = "</svg>";

SvgWriter::SvgWriter(const std::string &filename, size_t width, size_t height) : mWidth{width}, mHeight{height} {
    mFile.open(filename);
}

SvgWriter::~SvgWriter() {
    mFile.close();
}

void SvgWriter::WriteInitMagic() {
    mFile << xmlHeader << std::endl;
    mFile << svgHeader1 << " width=\"" << mWidth << "\" height=\"" << mHeight << "\" " << svgHeader2 << std::endl;
    mFile << svgBackground << std::endl;
}

void SvgWriter::WriteCanvas(const std::shared_ptr<Canvas> &canvas) {
    auto content = canvas->GetContent();
    for (const auto &shape: content) {
        mFile << shape->DrawSvg() << std::endl;
    }
}

void SvgWriter::WriteEndMagic() {
    mFile << svgFooter << std::endl;
}
