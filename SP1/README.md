# Drawing based on text input

## Description

Application takes three command line arguments:
    
      input_file  - path to input file
      output_file - path to output file
      size        - specifier of size of output image

Program detects the format based on the extension of the output file.

Valid extensions are:

      pgm - Portable Gray Map
      svg - Scalable Vector Graphics

Size is a pair of integers separated by a symbol 'x', where the first integer is the width 
and the second is the height of the output image.

If anything goes wrong during the execution of the program, it prints an error message
and exits with a non-zero exit code.

If the program finishes successfully, it exits with a zero exit code, prints 'OK' and the number 
of commands executed to the standard output.

## Usage

    ./drawing.exe <input_file> <output_file> <size>

### Build

Project is built using CMake. To build the project, run the following commands:

#### Windows

    mkdir build
    cd build
    cmake ..
    cmake --build .

#### Linux

    mkdir build
    cd build
    cmake ..
    make

## Input file format

Input file consists of a sequence of commands. Each command is a single line of text.

Input file can contain empty lines and comments. Empty lines are ignored. Comments start 
with the symbol '#' and end with the end of the line.

### Line command

    line <x1> <y1> <x2> <y2>

Draws a line from the point (x1, y1) to the point (x2, y2).

### Circle command

    circle <x> <y> <r>

Draws a circle with center in the point (x, y) and radius r.

### Rectangle command

    rectangle <x> <y> <w> <h>

Draws a rectangle with left top corner in the point (x, y), width w and height h.

### Translate command

    translate <x> <y>

Moves the origin of the coordinate system by the vector (x, y).

### Rotate command

    rotate <x> <y> <a>

Rotates the coordinate system around the point (x, y) by the angle a.

### Scale command

    scale <x> <y> <s>

Scales the coordinate system around the point (x, y) by the factor s.

## Output file format

Line is black and has a width of 2 pixels.

Circle is black and has a width of 2 pixels and is filled with no color.

Rectangle is black and has a width of 2 pixels and is filled with no color.

## Example

Execute the following command:

    ./drawing.exe input.txt output.svg 160x160

Input file:

    circle 50 50 10
    line 50 50 100 50
    circle 100 50 15
    rotate 75 50 45
    translate 20 20
    rect 10 10 40 30
    scale 0 0 2
    line 20 20 100 80
    scale 0 0 0.25
    line 5 20 25 5
    rotate 80 80 180
    circle 40 40 30
    rotate 80 80 90
    circle 40 40 30
    rotate 80 80 -180
    rect 10 10 60 60

Output file:

![alt text](https://github.com/SpeekeR99/CPP_22ZS_Zappe/blob/master/SP1/output.svg)
