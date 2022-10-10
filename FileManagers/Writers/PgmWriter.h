#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "IWritable.h"

/**
 * Class for writing data to a file in PGM format
 */
class PgmWriter : public IWritable {
private:
    /** File stream */
    std::ofstream mFile;
    /** Canvas width */
    size_t mWidth{};
    /** Canvas height */
    size_t mHeight{};
    /** Matrix of integers representing the raster image */
    std::vector<std::vector<int>> mRaster;

public:
    /**
     * Default constructor
     */
    PgmWriter() = default;

    /**
     * Opens a file for writing and sets the width and height of the canvas
     * @param filename Path to the file
     * @param width Width of the canvas
     * @param height Height of the canvas
     */
    PgmWriter(const std::string &filename, size_t width, size_t height);

    /**
     * Default destructor
     */
    ~PgmWriter() override;

    /**
     * Writes the initial magic number, width, height and maximum value to the file
     */
    void WriteInitMagic() override;

    /**
     * Writes the raster image to the file as a matrix of bytes
     * @param canvas Canvas which is to be written to the file
     */
    void WriteCanvas(const std::shared_ptr<Canvas> &canvas) override;

    /**
     * Writes the final magic number to the file
     * PGM format does not require a final magic number -> does nothing
     */
    void WriteEndMagic() override;
};
