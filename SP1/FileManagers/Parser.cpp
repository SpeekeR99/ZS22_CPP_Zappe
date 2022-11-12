#include "Parser.h"

/* magic numbers */
constexpr int expected_number_of_cmd_args = 4;
constexpr const char *supported_formats[] = {"svg", "pgm"};

Parser::~Parser() {
    mInputFile.close();
}

std::string Parser::GetOutputFile() const {
    return mOutputFile;
}

std::string Parser::GetOutputFormat() const {
    return mOutputFormat;
}

size_t Parser::GetWidth() const {
    return mWidth;
}

size_t Parser::GetHeight() const {
    return mHeight;
}

bool Parser::ParseCmdArgs(int argc, char **argv) {
    if (argc != expected_number_of_cmd_args) { // check if the number of arguments is correct
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file> <size>" << std::endl;
        return false;
    }
    mInputFile.open(argv[1]);
    if (!mInputFile.is_open()) { // check if the input file is valid
        std::cerr << "Failed to open input file: " << argv[1] << std::endl;
        return false;
    }
    mOutputFile = argv[2];
    mOutputFormat = mOutputFile.substr(mOutputFile.find_last_of('.') + 1, mOutputFile.size());
    bool supported = false;
    for (const auto &format: supported_formats) {
        if (mOutputFormat == format) { // check if the output format is supported
            supported = true;
        }
    }
    if (!supported) {
        std::cerr << "Unsupported output format: " << mOutputFormat << std::endl;
        std::cerr << "Supported formats: svg, pgm" << std::endl;
        return false;
    }
    std::string size = argv[3];
    int width = std::stoi(size.substr(0, size.find('x')));
    int height = std::stoi(size.substr(size.find('x') + 1, size.size()));
    if (width <= 0 || height <= 0) { // check if the size is valid
        std::cerr << "Invalid size: " << size << std::endl;
        return false;
    }
    mWidth = static_cast<size_t>(width);
    mHeight = static_cast<size_t>(height);
    return true;
}

std::string Parser::ParseInputFile() {
    std::string line;
    std::getline(mInputFile, line);
    line = line.substr(0, line.find_first_of('#')); // remove comments
    return line;
}

bool Parser::IsInputFileEOF() {
    return mInputFile.eof();
}
