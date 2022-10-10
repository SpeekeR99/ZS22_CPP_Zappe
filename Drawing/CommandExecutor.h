#pragma once

#include <regex>
#include <iostream>
#include "Canvas.h"

/**
 * Class for executing commands from input file to canvas
 */
class CommandExecutor {
public:
    /**
     * Executes given command onto canvas and returns true if command was executed successfully
     * @param canvas Canvas to execute command on
     * @param command Command to execute
     * @return True if command was executed successfully, false otherwise
     */
    static bool ExecuteCommand(const std::shared_ptr<Canvas> &canvas, const std::string &command);

    /**
     * Parses command and returns true if command was parsed successfully
     * @param command  Command to parse
     * @param cmd Command name (alternate return) (line, circle, rect, translate, rotate, scale)
     * @param params_vector Vector of number parameters (alternate return)
     * @return True if command was parsed successfully, false otherwise
     */
    static bool ParseCommand(std::string command, std::string &cmd, std::vector<double> &params_vector);

    /**
     * Executes drawing command (line, circle, rect) and returns true if command was executed successfully
     * @param canvas Canvas to execute command on
     * @param cmd Command name (line, circle, rect)
     * @param params_vector Vector of number parameters
     * @param command Original command (for error messages)
     * @return True if command was executed successfully, false otherwise
     */
    static bool ExecuteDrawingCommand(const std::shared_ptr<Canvas> &canvas, const std::string &cmd,
                                      const std::vector<double> &params_vector, const std::string &command);

    /**
     * Executes transformation command (translate, rotate, scale) and returns true if command was executed successfully
     * @param canvas Canvas to execute command on
     * @param cmd  Command name (translate, rotate, scale)
     * @param params_vector Vector of number parameters
     * @param command Original command (for error messages)
     * @return True if command was executed successfully, false otherwise
     */
    static bool ExecuteTransformationCommand(const std::shared_ptr<Canvas> &canvas, const std::string &cmd,
                                             const std::vector<double> &params_vector, const std::string &command);
};
