#include <iostream>
#include "FileManagers/Parser.h"
#include "Drawing/Canvas.h"
#include "Drawing/CommandExecutor.h"
#include "FileManagers/Writers/SvgWriter.h"
#include "FileManagers/Writers/PgmWriter.h"

/**
 * Main function of the program
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return Exit code (0 - success, 1 - error)
 */
int main(int argc, char **argv) {
    std::unique_ptr<Parser> parser = std::make_unique<Parser>();
    if (!parser->ParseCmdArgs(argc, argv)) {
        return EXIT_FAILURE;
    }

    std::shared_ptr<Canvas> canvas = std::make_shared<Canvas>();
    int num_of_commands = 0;
    do {
        std::string command = parser->ParseInputFile();
        if (command.empty()) {
            continue;
        }
        if (!CommandExecutor::ExecuteCommand(canvas, command)) {
            return EXIT_FAILURE;
        }
        num_of_commands++;
    } while (!parser->IsInputFileEOF());

    std::string output_file = parser->GetOutputFile();
    std::string output_format = parser->GetOutputFormat();
    size_t width = parser->GetWidth();
    size_t height = parser->GetHeight();

    if (output_format == "svg") {
        SvgWriter writer{output_file, width, height};
        writer.WriteInitMagic();
        writer.WriteCanvas(canvas);
        writer.WriteEndMagic();
    } else if (output_format == "pgm") {
        PgmWriter writer{output_file, width, height};
        writer.WriteInitMagic();
        writer.WriteCanvas(canvas);
        writer.WriteEndMagic();
    }

    std::cout << "OK" << std::endl;
    std::cout << num_of_commands << std::endl;

    return EXIT_SUCCESS;
}
