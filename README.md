## Enhanced Calculator Program Documentation

### Overview
The calculator program supports a wide range of mathematical operations, including basic arithmetic, trigonometric functions, logarithmic functions, statistical calculations, and more. It also supports solving linear and quadratic equations, converting between degrees and radians, and matrix operations.

### Features
- **Basic Arithmetic**: Addition, subtraction, multiplication, division, and exponentiation.
- **Square Root Calculation**: `sqrt` for square root.
- **Trigonometric Functions**: `sin`, `cos`, `tan`, `asin`, `acos`, `atan`.
- **Logarithmic Functions**: `log` for natural logarithm, `log10` for base-10 logarithm.
- **Factorial Calculation**: `factorial` for calculating the factorial of an integer.
- **Modulo Operation**: `mod` for modulo operation.
- **Prime Check**: `prime` for checking if a number is prime.
- **Linear Equation Solving**: `eq` for solving linear equations of the form `ax + b = 0`.
- **Quadratic Equation Solving**: `qeq` for solving quadratic equations of the form `ax^2 + bx + c = 0`.
- **Degree-Radian Conversion**: `deg2rad` and `rad2deg`.
- **Statistical Calculations**: Mean (`mean`), median (`median`), mode (`mode`), standard deviation (`stddev`).
- **Matrix Operations**: `matrix` (not implemented yet).
- **Memory Operations**: `mem` for saving and recalling values from memory.

### Usage
#### Main Menu
- The program displays a menu with available operations.
- Enter the corresponding operation keyword or symbol to perform a specific operation.
- To exit the program, type `exit`.

#### Basic Arithmetic and Expressions
- Supports expressions involving addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), and exponentiation (`^`).
- Expressions can be entered directly and will be evaluated.

#### Square Root
- Operation: `sqrt`
- Enter a number to calculate its square root.

#### Trigonometric Functions
- Operations: `sin`, `cos`, `tan`, `asin`, `acos`, `atan`
- Enter the angle in radians to calculate the corresponding trigonometric value.

#### Logarithmic Functions
- Operations: `log` (natural logarithm), `log10` (base-10 logarithm)
- Enter a number to calculate its logarithm.

#### Factorial Calculation
- Operation: `factorial`
- Enter an integer to calculate its factorial.

#### Modulo Operation
- Operation: `mod`
- Enter two integers to calculate the modulo (remainder) of their division.

#### Prime Check
- Operation: `prime`
- Enter an integer to check if it is a prime number.

#### Linear Equation Solving
- Operation: `eq`
- Enter the coefficients `a` and `b` for the linear equation `ax + b = 0` to find the value of `x`.

#### Quadratic Equation Solving
- Operation: `qeq`
- Enter the coefficients `a`, `b`, and `c` for the quadratic equation `ax^2 + bx + c = 0` to find the roots.

#### Degree-Radian Conversion
- Operations: `deg2rad`, `rad2deg`
- Convert degrees to radians or radians to degrees by entering the value.

#### Statistical Calculations
- Operations: `mean`, `median`, `mode`, `stddev`
- Enter the number of elements and their values to calculate the respective statistical measure.

#### Matrix Operations
- Operation: `matrix`
- Matrix operations are not yet implemented.

#### Memory Operations
- Operation: `mem`
- Save a value to memory or recall a value from memory.

### Example Usage
#### Basic Arithmetic
```
> 3 + 4 * 2 / (1 - 5) ^ 2
Result: 3.50
```

#### Trigonometric Function
```
> sin
Enter the angle (in radians): 1.5708
Result: 1.00
```

#### Logarithmic Function
```
> log
Enter a number: 2.7183
Result: 1.00
```

#### Factorial
```
> factorial
Enter an integer: 5
Result: 120.00
```

#### Modulo Operation
```
> mod
Enter two integers: 10 3
Result: 1.00
```

#### Prime Check
```
> prime
Enter an integer: 7
Result: 7 is a prime number.
```

#### Linear Equation
```
> eq
Enter coefficients a and b for ax + b = 0: 2 -4
Result: 2.00
```

#### Quadratic Equation
```
> qeq
Enter coefficients a, b, and c for ax^2 + bx + c = 0: 1 -3 2
Roots: 2.00 and 1.00
```

#### Degree-Radian Conversion
```
> deg2rad
Enter degrees: 180
Radians: 3.14
```

### Notes
- The program handles both floating-point and integer inputs.
- Error messages are displayed for invalid operations or inputs, such as division by zero or invalid function names.
- Memory operations allow for saving and recalling values for later use.

This documentation covers all features and usage scenarios for the enhanced calculator program. Feel free to modify and expand it as needed!
