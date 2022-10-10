#pragma once

#include <memory>
#include "../../Drawing/Canvas.h"

/**
 * Interface for writing a canvas to a file
 */
class IWritable {
public:
    /**
     * Default destructor
     */
    virtual ~IWritable() = default;

    /**
     * Write the initial magical constants to the file (depends on the file format)
     */
    virtual void WriteInitMagic() = 0;

    /**
     * Write the content of the canvas to the file (depends on the file format)
     * @param canvas The canvas that is to be written to the file
     */
    virtual void WriteCanvas(const std::shared_ptr<Canvas> &canvas) = 0;

    /**
     * Write the final magical constants to the file (depends on the file format)
     */
    virtual void WriteEndMagic() = 0;
};
