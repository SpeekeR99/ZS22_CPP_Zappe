#include "CommandExecutor.h"

bool CommandExecutor::ExecuteCommand(const std::shared_ptr<Canvas> &canvas, const std::string &command) {
    std::string cmd;
    std::vector<double> params_vector;

    if (!ParseCommand(command, cmd, params_vector)) {
        return false;
    }

    if (cmd == "line" || cmd == "circle" || cmd == "rect") {
        if (!ExecuteDrawingCommand(canvas, cmd, params_vector, command)) {
            return false;
        }
    } else if (cmd == "translate" || cmd == "rotate" || cmd == "scale") {
        if (!ExecuteTransformationCommand(canvas, cmd, params_vector, command)) {
            return false;
        }
    } else {
        std::cerr << "Invalid command: " << cmd << std::endl;
        return false;
    }
    return true;
}

bool CommandExecutor::ParseCommand(std::string command, std::string &cmd, std::vector<double> &params_vector) {
    std::string params;
    command = command.substr(command.find_first_not_of(' '), command.size());

    std::regex regex("\\s+");
    std::sregex_token_iterator it{command.begin(), command.end(), regex, -1};
    std::sregex_token_iterator end;

    cmd = *it++;
    while (it != end) {
        try {
            params_vector.push_back(std::stod(*it++));
        }
        catch (const std::invalid_argument &e) {
            std::cerr << "Invalid command parameters: " << command << std::endl;
            return false;
        }
    }
    return true;
}

bool CommandExecutor::ExecuteDrawingCommand(const std::shared_ptr<Canvas> &canvas, const std::string &cmd,
                                            const std::vector<double> &params_vector, const std::string &command) {
    if (cmd == "line") {
        if (params_vector.size() != 4) {
            std::cerr << "Invalid number of parameters for line command: " << command << std::endl;
            return false;
        }
        double x1 = params_vector[0];
        double y1 = params_vector[1];
        double x2 = params_vector[2];
        double y2 = params_vector[3];
        if (x1 == x2 && y1 == y2) {
            std::cerr << "Invalid line: " << command << std::endl;
            return false;
        }
        canvas->AddIDrawableShape(std::make_shared<Line>(x1, y1, x2, y2));
    } else if (cmd == "circle") {
        if (params_vector.size() != 3) {
            std::cerr << "Invalid number of parameters for circle command: " << command << std::endl;
            return false;
        }
        double x = params_vector[0];
        double y = params_vector[1];
        double r = params_vector[2];
        if (r <= 0) {
            std::cerr << "Invalid circle: " << command << std::endl;
            return false;
        }
        canvas->AddIDrawableShape(std::make_shared<Circle>(x, y, r));
    } else if (cmd == "rect") {
        if (params_vector.size() != 4) {
            std::cerr << "Invalid number of parameters for rect command: " << command << std::endl;
            return false;
        }
        double x = params_vector[0];
        double y = params_vector[1];
        double width = params_vector[2];
        double height = params_vector[3];
        if (width <= 0 || height <= 0) {
            std::cerr << "Invalid rectangle: " << command << std::endl;
            return false;
        }
        canvas->AddIDrawableShape(std::make_shared<Rectangle>(x, y, width, height));
    }
    return true;
}

bool CommandExecutor::ExecuteTransformationCommand(const std::shared_ptr<Canvas> &canvas, const std::string &cmd,
                                                   const std::vector<double> &params_vector,
                                                   const std::string &command) {
    if (cmd == "translate") {
        if (params_vector.size() != 2) {
            std::cerr << "Invalid number of parameters for translate command: " << command << std::endl;
            return false;
        }
        double x = params_vector[0];
        double y = params_vector[1];
        canvas->Translate(x, y);
    } else if (cmd == "rotate") {
        if (params_vector.size() != 3) {
            std::cerr << "Invalid number of parameters for rotate command: " << command << std::endl;
            return false;
        }
        double x = params_vector[0];
        double y = params_vector[1];
        double a = params_vector[2];
        canvas->Rotate(x, y, a);
    } else if (cmd == "scale") {
        if (params_vector.size() != 3) {
            std::cerr << "Invalid number of parameters for scale command: " << command << std::endl;
            return false;
        }
        double x = params_vector[0];
        double y = params_vector[1];
        double f = params_vector[2];
        if (f == 0) {
            std::cerr << "Invalid scale: " << command << std::endl;
            return false;
        }
        canvas->Scale(x, y, f);
    }
    return true;
}
