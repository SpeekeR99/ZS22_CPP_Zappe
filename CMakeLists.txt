cmake_minimum_required(VERSION 3.23)
project(SP1)

set(CMAKE_CXX_STANDARD 20)

add_executable(SP1 main.cpp Drawing/IDrawable.h Drawing/Geometry/Line.cpp Drawing/Geometry/Line.h Drawing/Geometry/Circle.cpp Drawing/Geometry/Circle.h Drawing/Geometry/Rectangle.cpp Drawing/Geometry/Rectangle.h Drawing/Geometry/Point2D.cpp Drawing/Geometry/Point2D.h Drawing/Canvas.cpp Drawing/Canvas.h FileManagers/Writers/IWritable.h FileManagers/Writers/SvgWriter.cpp FileManagers/Writers/SvgWriter.h FileManagers/Writers/PgmWriter.cpp FileManagers/Writers/PgmWriter.h FileManagers/Parser.cpp FileManagers/Parser.h Drawing/CommandExecutor.cpp Drawing/CommandExecutor.h)
