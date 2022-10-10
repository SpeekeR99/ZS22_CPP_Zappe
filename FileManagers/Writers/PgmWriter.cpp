#include "PgmWriter.h"

/* Magic numbers for PGM file format */
constexpr const char *pgmHeader = "P2";
constexpr const char *pgmMaxVal = "255";

PgmWriter::PgmWriter(const std::string &filename, size_t width, size_t height) : mWidth{width}, mHeight{height} {
    mFile.open(filename);
    mWidth = width;
    mHeight = height;
    mRaster.resize(mHeight);
    for (size_t i = 0; i < mHeight; ++i) {
        mRaster[i].resize(mWidth);
        std::fill(mRaster[i].begin(), mRaster[i].end(), 255);
    }
}

PgmWriter::~PgmWriter() {
    mFile.close();
}

void PgmWriter::WriteInitMagic() {
    mFile << pgmHeader << std::endl;
    mFile << mWidth << " " << mHeight << std::endl;
    mFile << pgmMaxVal << std::endl;
}

void PgmWriter::WriteCanvas(const std::shared_ptr<Canvas> &canvas) {
    auto content = canvas->GetContent();
    for (const auto &shape: content) {
        shape->DrawRaster(mRaster);
    }
    for (size_t i = 0; i < mHeight; ++i) {
        for (size_t j = 0; j < mWidth; ++j) {
            mFile << mRaster[i][j] << " ";
        }
        mFile << std::endl;
    }
}

void PgmWriter::WriteEndMagic() {
    // For PGM this function does nothing at all :)
}
