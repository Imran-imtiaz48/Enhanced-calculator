# Enhanced Calculator Program

## Overview

This is an enhanced calculator program written in C. It supports a range of mathematical operations including addition, subtraction, multiplication, division, exponentiation, and square root calculations. The program also handles basic input validation and provides error messages for invalid operations and division by zero.

## Features

- **Addition (`+`)**: Adds two numbers.
- **Subtraction (`-`)**: Subtracts the second number from the first.
- **Multiplication (`*`)**: Multiplies two numbers.
- **Division (`/`)**: Divides the first number by the second. Handles division by zero.
- **Exponentiation (`^`)**: Calculates the power of a number (base raised to exponent).
- **Square Root (`sqrt`)**: Calculates the square root of a non-negative number.

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
