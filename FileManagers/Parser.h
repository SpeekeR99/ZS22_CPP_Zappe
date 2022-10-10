#pragma once

#include <iostream>
#include <fstream>
#include "../Drawing/Canvas.h"

/**
 * Class for parsing command line arguments and input file
 */
class Parser {
private:
    /** Input file stream */
    std::ifstream mInputFile;
    /** Output file name */
    std::string mOutputFile;
    /** Output file format */
    std::string mOutputFormat;
    /** Canvas width */
    size_t mWidth{};
    /** Canvas height */
    size_t mHeight{};

public:
    /**
     * Default constructor
     */
    Parser() = default;

    /**
     * Default destructor
     */
    virtual ~Parser();

    /**
     * Get output file name
     * @return Output file name (path)
     */
    std::string GetOutputFile() const;

    /**
     * Get output file format
     * @return Output file format
     */
    std::string GetOutputFormat() const;

    /**
     * Get canvas width
     * @return Width of the canvas
     */
    size_t GetWidth() const;

    /**
     * Get canvas height
     * @return Height of the canvas
     */
    size_t GetHeight() const;

    /**
     * Parse command line arguments
     * @param argc Number of command line arguments
     * @param argv Command line arguments
     * @return True if parsing was successful, false otherwise
     */
    bool ParseCmdArgs(int argc, char *argv[]);

    /**
     * Parse input file
     * @return One line of the input file - one command to execute
     */
    std::string ParseInputFile();

    /**
     * Check if input file is EOF
     * @return True if input file is EOF, false otherwise
     */
    bool IsInputFileEOF();
};
