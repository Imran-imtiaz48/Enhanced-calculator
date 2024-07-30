Here’s an updated `README.md` file that includes the new features and improvements for your enhanced calculator program:

```markdown
# Enhanced Calculator Program

## Overview

This is an enhanced calculator program written in C. It supports a wide range of mathematical operations, including basic arithmetic, advanced mathematical functions, and statistical calculations. The program provides error handling for invalid operations and division by zero.

## Features

- **Basic Arithmetic**:
  - **Addition (`+`)**: Adds two numbers.
  - **Subtraction (`-`)**: Subtracts the second number from the first.
  - **Multiplication (`*`)**: Multiplies two numbers.
  - **Division (`/`)**: Divides the first number by the second. Handles division by zero.
  - **Exponentiation (`^`)**: Calculates the power of a number (base raised to exponent).
  - **Square Root (`sqrt`)**: Calculates the square root of a non-negative number.

- **Advanced Mathematical Functions**:
  - **Trigonometric Functions**:
    - `sin`, `cos`, `tan`: Sine, cosine, and tangent.
    - `asin`, `acos`, `atan`: Arcsine, arccosine, and arctangent.
  - **Linear Equation Solver (`eq`)**: Solves linear equations of the form `ax + b = 0`.
  - **Quadratic Equation Solver (`qeq`)**: Solves quadratic equations of the form `ax^2 + bx + c = 0`.

- **Additional Features**:
  - **Degree/Radian Conversion (`deg2rad`, `rad2deg`)**: Converts between degrees and radians.
  - **Constants Handling (`const`)**: Handles mathematical constants like π and e.
  - **Statistics**:
    - `mean`: Calculates the mean of a set of numbers.
    - `median`: Calculates the median of a set of numbers.
    - `mode`: Calculates the mode of a set of numbers.
    - `stddev`: Calculates the standard deviation of a set of numbers.
  - **Matrix Operations (`matrix`)**: Performs matrix operations (e.g., addition, multiplication). (Implementation needed)
  - **Memory Operations (`mem`)**: Saves and recalls values to/from memory.

## Prerequisites

To compile and run this program, you need:

- A C compiler (e.g., GCC)
- The `math.h` library for mathematical functions

## Compilation

To compile the program using GCC, run the following command in your terminal:

```bash
gcc -o calculator calculator.c -lm
```

This command compiles `calculator.c` into an executable named `calculator`, linking the `math` library (`-lm`) required for mathematical operations.

## Execution

After compilation, run the executable with:

### On Windows:
```bash
calculator.exe
```

### On macOS or Linux:
```bash
./calculator
```

## Usage

1. **Start the Program**: Execute the compiled program.
2. **Select Operation**: Choose an operation by entering the corresponding symbol or keyword:
   - `+` for addition
   - `-` for subtraction
   - `*` for multiplication
   - `/` for division
   - `^` for exponentiation
   - `sqrt` for square root
   - `sin` for sine
   - `cos` for cosine
   - `tan` for tangent
   - `asin` for arcsine
   - `acos` for arccosine
   - `atan` for arctangent
   - `eq` for linear equation (ax + b = 0)
   - `qeq` for quadratic equation (ax^2 + bx + c = 0)
   - `deg2rad` for degrees to radians conversion
   - `rad2deg` for radians to degrees conversion
   - `const` for constants (π or e)
   - `mean` for mean calculation
   - `median` for median calculation
   - `mode` for mode calculation
   - `stddev` for standard deviation calculation
   - `matrix` for matrix operations
   - `mem` for memory operations
3. **Input Numbers**: Follow the prompts to enter the numbers required for the selected operation.
4. **View Result**: The program will display the result of the operation.

## Example

```
Select operation:
 + for addition
 - for subtraction
 * for multiplication
 / for division
 ^ for exponentiation (power)
 sqrt for square root
 Enter operation: +
Enter two numbers: 10 5
Result: 15.00
```

## Error Handling

- **Division by Zero**: If the operation is division and the second number is zero, the program will output an error message.
- **Invalid Operations**: If an unsupported operation is entered, the program will notify the user of an invalid operation.
- **Negative Square Root**: If a negative number is provided for the square root operation, an error message will be displayed.

## License

This program is provided as-is, free for personal or educational use. No warranties or guarantees are provided.

```

Feel free to adjust or expand on any sections based on additional features or changes!
