#pragma once

#include <memory>
#include <fstream>
#include "IWritable.h"

/**
 * Class for writing data to a file in SVG format
 */
class SvgWriter : public IWritable {
private:
    /** File stream */
    std::ofstream mFile;
    /** Canvas width */
    size_t mWidth{};
    /** Canvas height */
    size_t mHeight{};

public:
    /**
     * Default constructor
     */
    SvgWriter() = default;

    /**
     * Opens a file for writing and sets the width and height of the canvas
     * @param filename Path to the file
     * @param width Width of the canvas
     * @param height Height of the canvas
     */
    SvgWriter(const std::string &filename, size_t width, size_t height);

    /**
     * Default destructor
     */
    ~SvgWriter() override;

    /**
     * Writes the initial magic constants to the file
     * For example <svg> element in SVG format
     */
    void WriteInitMagic() override;

    /**
     * Writes the canvas content to the file as SVG strings
     * @param canvas Canvas which is to be written to the file
     */
    void WriteCanvas(const std::shared_ptr<Canvas> &canvas) override;

    /**
     * Writes the final magic constants to the file
     * For example </svg> element in SVG format
     */
    void WriteEndMagic() override;
};
