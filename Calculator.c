#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void print_menu();
double evaluate_expression(const char* expr);
double parse_number(const char** expr);
double parse_parentheses(const char** expr);
double parse_factor(const char** expr);
double parse_term(const char** expr);
double parse_expression(const char** expr);
double solve_linear_equation(double a, double b);
void solve_quadratic_equation(double a, double b, double c);
double evaluate_trigonometric_function(const char* func, double x);
void convert_degrees_radians();
void handle_constants(double* num1);
void calculate_statistics();
void matrix_operations();
void memory_operations();
double factorial(int n);
double evaluate_logarithmic_function(const char* func, double x);
int is_prime(int num);

double memory = 0; // Memory variable

void print_menu() {
    printf("Select operation:\n");
    printf(" + for addition\n");
    printf(" - for subtraction\n");
    printf(" * for multiplication\n");
    printf(" / for division\n");
    printf(" ^ for exponentiation (power)\n");
    printf(" sqrt for square root\n");
    printf(" sin for sine\n");
    printf(" cos for cosine\n");
    printf(" tan for tangent\n");
    printf(" asin for arcsine\n");
    printf(" acos for arccosine\n");
    printf(" atan for arctangent\n");
    printf(" log for natural logarithm\n");
    printf(" log10 for base-10 logarithm\n");
    printf(" factorial for factorial\n");
    printf(" mod for modulo\n");
    printf(" prime for prime check\n");
    printf(" eq for linear equation (ax + b = 0)\n");
    printf(" qeq for quadratic equation (ax^2 + bx + c = 0)\n");
    printf(" deg2rad for degrees to radians conversion\n");
    printf(" rad2deg for radians to degrees conversion\n");
    printf(" mean for mean calculation\n");
    printf(" median for median calculation\n");
    printf(" mode for mode calculation\n");
    printf(" stddev for standard deviation calculation\n");
    printf(" matrix for matrix operations\n");
    printf(" mem for memory operations\n");
    printf(" Enter operation: ");
}

double evaluate_expression(const char* expr) {
    const char* p = expr;
    return parse_expression(&p);
}

double parse_number(const char** expr) {
    while (isspace(**expr)) (*expr)++;
    double result = strtod(*expr, (char**)expr);
    return result;
}

double parse_parentheses(const char** expr) {
    if (**expr == '(') {
        (*expr)++;
        double result = parse_expression(expr);
        if (**expr == ')') {
            (*expr)++;
        } else {
            printf("Error! Unmatched parentheses.\n");
            exit(EXIT_FAILURE);
        }
        return result;
    }
    return parse_number(expr);
}

double parse_factor(const char** expr) {
    double result = parse_parentheses(expr);
    while (**expr == '^') {
        (*expr)++;
        double exponent = parse_parentheses(expr);
        result = pow(result, exponent);
    }
    return result;
}

double parse_term(const char** expr) {
    double result = parse_factor(expr);
    while (**expr == '*' || **expr == '/') {
        char op = **expr;
        (*expr)++;
        double operand = parse_factor(expr);
        if (op == '*') {
            result *= operand;
        } else if (op == '/') {
            if (operand != 0) {
                result /= operand;
            } else {
                printf("Error! Division by zero.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return result;
}

double parse_expression(const char** expr) {
    double result = parse_term(expr);
    while (**expr == '+' || **expr == '-') {
        char op = **expr;
        (*expr)++;
        double operand = parse_term(expr);
        if (op == '+') {
            result += operand;
        } else if (op == '-') {
            result -= operand;
        }
    }
    return result;
}

double solve_linear_equation(double a, double b) {
    if (a != 0) {
        return -b / a;
    } else {
        printf("Error! No solution for a = 0.\n");
        exit(EXIT_FAILURE);
    }
}

void solve_quadratic_equation(double a, double b, double c) {
    if (a == 0) {
        printf("Error! Coefficient a cannot be zero.\n");
        return;
    }

    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Roots: %.2lf and %.2lf\n", root1, root2);
    } else if (discriminant == 0) {
        double root = -b / (2 * a);
        printf("Root: %.2lf\n", root);
    } else {
        printf("Error! Complex roots.\n");
    }
}

double evaluate_trigonometric_function(const char* func, double x) {
    if (strcmp(func, "sin") == 0) return sin(x);
    if (strcmp(func, "cos") == 0) return cos(x);
    if (strcmp(func, "tan") == 0) return tan(x);
    if (strcmp(func, "asin") == 0) return asin(x);
    if (strcmp(func, "acos") == 0) return acos(x);
    if (strcmp(func, "atan") == 0) return atan(x);

    printf("Error! Invalid trigonometric function.\n");
    exit(EXIT_FAILURE);
}

double evaluate_logarithmic_function(const char* func, double x) {
    if (strcmp(func, "log") == 0) return log(x);
    if (strcmp(func, "log10") == 0) return log10(x);

    printf("Error! Invalid logarithmic function.\n");
    exit(EXIT_FAILURE);
}

void convert_degrees_radians() {
    char choice;
    double value;
    printf("Convert from (d)egrees to radians or (r)adians to degrees? ");
    scanf(" %c", &choice);
    if (choice == 'd') {
        printf("Enter degrees: ");
        scanf("%lf", &value);
        printf("Radians: %.2lf\n", value * M_PI / 180);
    } else if (choice == 'r') {
        printf("Enter radians: ");
        scanf("%lf", &value);
        printf("Degrees: %.2lf\n", value * 180 / M_PI);
    } else {
        printf("Invalid choice.\n");
    }
}

void handle_constants(double* num1) {
    char choice;
    printf("Enter (p)i for pi or (e) for e: ");
    scanf(" %c", &choice);
    if (choice == 'p') {
        *num1 = M_PI;
    } else if (choice == 'e') {
        *num1 = M_E;
    } else {
        printf("Invalid choice.\n");
    }
}

void calculate_statistics() {
    int n, i;
    double sum = 0, mean, median;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    double* arr = (double*)malloc(n * sizeof(double));
    if (!arr) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
        sum += arr[i];
    }
    
    // Compute mean
    mean = sum / n;
    printf("Mean: %.2lf\n", mean);

    // Compute median
    qsort(arr, n, sizeof(double), (int(*)(const void*, const void*))strcmp);
    if (n % 2 == 0) {
        median = (arr[n / 2 - 1] + arr[n / 2]) / 2;
    } else {
        median = arr[n / 2];
    }
    printf("Median: %.2lf\n", median);

    free(arr);
}

void matrix_operations() {
    // Implement matrix operations here
    printf("Matrix operations not implemented yet.\n");
}

void memory_operations() {
    char choice;
    double value;
    printf("Enter (s)ave to memory or (r)ecall from memory: ");
    scanf(" %c", &choice);
    if (choice == 's') {
        printf("Enter value to save: ");
        scanf("%lf", &value);
        memory = value;
        printf("Value saved to memory.\n");
    } else if (choice == 'r') {
        printf("Value from memory: %.2lf\n", memory);
    } else {
        printf("Invalid choice.\n");
    }
}

double factorial(int n) {
    if (n < 0) {
        printf("Error! Factorial of negative number.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    char input[256];
    char operation[10];
    double num1, num2, result;

    print_menu();

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input.\n");
            break;
        }

        // Remove newline character if present
        input[strcspn(input, "\n")] = 0;

        // Parse operation
        sscanf(input, "%s", operation);

        if (strcmp(operation, "exit") == 0) {
            break;
        } else if (strcmp(operation, "sqrt") == 0) {
            printf("Enter a number: ");
            scanf("%lf", &num1);
            if (num1 < 0) {
                printf("Error! Negative number for square root.\n");
            } else {
                result = sqrt(num1);
                printf("Result: %.2lf\n", result);
            }
        } else if (strcmp(operation, "eq") == 0) {
            printf("Enter coefficients a and b for ax + b = 0: ");
            scanf("%lf %lf", &num1, &num2);
            result = solve_linear_equation(num1, num2);
            printf("Result: %.2lf\n", result);
        } else if (strcmp(operation, "qeq") == 0) {
            printf("Enter coefficients a, b, and c for ax^2 + bx + c = 0: ");
            scanf("%lf %lf %lf", &num1, &num2, &result);
            solve_quadratic_equation(num1, num2, result);
        } else if (strcmp(operation, "sin") == 0 ||
                   strcmp(operation, "cos") == 0 ||
                   strcmp(operation, "tan") == 0 ||
                   strcmp(operation, "asin") == 0 ||
                   strcmp(operation, "acos") == 0 ||
                   strcmp(operation, "atan") == 0) {
            printf("Enter the angle (in radians): ");
            scanf("%lf", &num1);
            result = evaluate_trigonometric_function(operation, num1);
            printf("Result: %.2lf\n", result);
        } else if (strcmp(operation, "deg2rad") == 0 ||
                   strcmp(operation, "rad2deg") == 0) {
            convert_degrees_radians();
        } else if (strcmp(operation, "const") == 0) {
            handle_constants(&num1);
            printf("Constant value: %.2lf\n", num1);
        } else if (strcmp(operation, "mean") == 0 ||
                   strcmp(operation, "median") == 0 ||
                   strcmp(operation, "mode") == 0 ||
                   strcmp(operation, "stddev") == 0) {
            calculate_statistics();
        } else if (strcmp(operation, "matrix") == 0) {
            matrix_operations();
        } else if (strcmp(operation, "mem") == 0) {
            memory_operations();
        } else if (strcmp(operation, "log") == 0 ||
                   strcmp(operation, "log10") == 0) {
            printf("Enter a number: ");
            scanf("%lf", &num1);
            result = evaluate_logarithmic_function(operation, num1);
            printf("Result: %.2lf\n", result);
        } else if (strcmp(operation, "factorial") == 0) {
            printf("Enter an integer: ");
            scanf("%lf", &num1);
            result = factorial((int)num1);
            printf("Result: %.2lf\n", result);
        } else if (strcmp(operation, "mod") == 0) {
            printf("Enter two integers: ");
            scanf("%lf %lf", &num1, &num2);
            result = (int)num1 % (int)num2;
            printf("Result: %.2lf\n", result);
        } else if (strcmp(operation, "prime") == 0) {
            printf("Enter an integer: ");
            scanf("%lf", &num1);
            int isPrime = is_prime((int)num1);
            if (isPrime) {
                printf("Result: %.0lf is a prime number.\n", num1);
            } else {
                printf("Result: %.0lf is not a prime number.\n", num1);
            }
        } else {
            // Evaluate expression
            const char* p = input;
            result = evaluate_expression(p);
            printf("Result: %.2lf\n", result);
        }

        // Clear the input buffer
        while (getchar() != '\n');
    }

    return 0;
}
