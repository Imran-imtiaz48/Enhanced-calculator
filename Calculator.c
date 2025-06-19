#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Uncomment for Visual Studio compilation
// #define _CRT_SECURE_NO_WARNINGS

#define MAX_INPUT_LEN 256
#define MAX_CMD_LEN   20

// Function prototypes
void print_menu(void);
void handle_basic_arithmetic(const char* op);
void handle_square_root(void);
void handle_trig(const char* func);
void handle_log(const char* func);
void handle_factorial(void);
void handle_linear_eq(void);
void handle_quadratic_eq(void);
void handle_deg_rad(const char* op);
void calculate_statistics(const char* mode);
void matrix_operations(void);
void memory_operations(void);
int get_double(const char *prompt, double *out);
int get_int(const char *prompt, int *out);

double memory = 0.0;

// Helper to get a double from the user (returns 1 if successful)
int get_double(const char *prompt, double *out) {
    char buf[MAX_INPUT_LEN];
    printf("%s", prompt);
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 0;
    }
    char *endptr;
    double val = strtod(buf, &endptr);
    while (isspace(*endptr)) endptr++;
    if (endptr == buf || *endptr != '\0' && *endptr != '\n') {
        printf("Invalid number.\n");
        return 0;
    }
    *out = val;
    return 1;
}

// Helper to get an int from the user (returns 1 if successful)
int get_int(const char *prompt, int *out) {
    char buf[MAX_INPUT_LEN];
    printf("%s", prompt);
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    char *endptr;
    long val = strtol(buf, &endptr, 10);
    while (isspace(*endptr)) endptr++;
    if (endptr == buf || *endptr != '\0' && *endptr != '\n') {
        printf("Invalid integer.\n");
        return 0;
    }
    *out = (int)val;
    return 1;
}

void print_menu(void) {
    printf("\n=== Enhanced Calculator ===\n");
    printf("Select an operation:\n"
           " +, -, *, /, ^      : Basic arithmetic\n"
           " sqrt               : Square root\n"
           " sin, cos, tan      : Trigonometric functions\n"
           " log, log10         : Logarithmic functions\n"
           " factorial          : Factorial calculation\n"
           " eq                 : Linear equation (ax + b = 0)\n"
           " qeq                : Quadratic equation (ax^2 + bx + c = 0)\n"
           " deg2rad, rad2deg   : Degree/radian conversions\n"
           " mean, median       : Statistics\n"
           " matrix             : Matrix operations\n"
           " mem                : Memory operations\n"
           " exit               : Quit\n"
    );
}

void handle_basic_arithmetic(const char* op) {
    double a, b, result;

    if (!get_double("Enter first number: ", &a) || !get_double("Enter second number: ", &b)) return;

    if (strcmp(op, "+") == 0)       result = a + b;
    else if (strcmp(op, "-") == 0)  result = a - b;
    else if (strcmp(op, "*") == 0)  result = a * b;
    else if (strcmp(op, "/") == 0) {
        if (b == 0) { printf("Error: Division by zero.\n"); return; }
        result = a / b;
    }
    else if (strcmp(op, "^") == 0)  result = pow(a, b);
    else { printf("Unknown operator.\n"); return; }

    printf("Result: %.6lf\n", result);
    memory = result;
}

void handle_square_root(void) {
    double x;
    if (!get_double("Enter number: ", &x) || x < 0) {
        printf("Invalid input or negative number.\n");
        return;
    }
    double result = sqrt(x);
    printf("sqrt(%.6lf) = %.6lf\n", x, result);
    memory = result;
}

void handle_trig(const char* func) {
    double x;
    if (!get_double("Enter value in degrees: ", &x)) return;
    double rad = x * M_PI / 180.0, result;

    if      (strcmp(func, "sin") == 0) result = sin(rad);
    else if (strcmp(func, "cos") == 0) result = cos(rad);
    else if (strcmp(func, "tan") == 0) result = tan(rad);
    else { printf("Unknown trig function.\n"); return; }

    printf("%s(%.2lf degrees) = %.6lf\n", func, x, result);
    memory = result;
}

void handle_log(const char* func) {
    double x, result;
    if (!get_double("Enter positive number: ", &x) || x <= 0) {
        printf("Invalid or non-positive input.\n");
        return;
    }
    if      (strcmp(func, "log") == 0)   result = log(x);
    else if (strcmp(func, "log10") == 0) result = log10(x);
    else { printf("Unknown log function.\n"); return; }
    printf("%s(%.6lf) = %.6lf\n", func, x, result);
    memory = result;
}

void handle_factorial(void) {
    int n;
    if (!get_int("Enter a non-negative integer: ", &n) || n < 0) {
        printf("Invalid input.\n");
        return;
    }
    unsigned long long fact = 1;
    for (int i = 2; i <= n; ++i) fact *= i;
    printf("%d! = %llu\n", n, fact);
    memory = (double)fact;
}

void handle_linear_eq(void) {
    double a, b;
    printf("Equation ax + b = 0\n");
    if (!get_double("Enter a: ", &a) || !get_double("Enter b: ", &b)) return;
    if (a == 0) { printf("No solution (a=0).\n"); return; }
    double x = -b / a;
    printf("Solution: x = %.6lf\n", x);
    memory = x;
}

void handle_quadratic_eq(void) {
    double a, b, c;
    printf("Equation ax^2 + bx + c = 0\n");
    if (!get_double("Enter a: ", &a) || !get_double("Enter b: ", &b) || !get_double("Enter c: ", &c)) return;
    if (a == 0) { printf("Not a quadratic equation.\n"); return; }
    double d = b * b - 4 * a * c;
    if (d > 0) {
        printf("Roots: %.6lf and %.6lf\n", (-b + sqrt(d)) / (2*a), (-b - sqrt(d)) / (2*a));
    } else if (d == 0) {
        printf("Root: %.6lf\n", -b / (2*a));
    } else {
        printf("Complex roots: %.6lf + %.6lfi and %.6lf - %.6lfi\n",
            -b/(2*a), sqrt(-d)/(2*a), -b/(2*a), sqrt(-d)/(2*a));
    }
}

void handle_deg_rad(const char* op) {
    double val;
    if (strcmp(op, "deg2rad") == 0) {
        if (!get_double("Enter degrees: ", &val)) return;
        printf("%.2lf degrees = %.6lf radians\n", val, val * M_PI / 180.0);
    } else if (strcmp(op, "rad2deg") == 0) {
        if (!get_double("Enter radians: ", &val)) return;
        printf("%.6lf radians = %.2lf degrees\n", val, val * 180.0 / M_PI);
    } else {
        printf("Unknown conversion operation.\n");
    }
}

int compare_double(const void *a, const void *b) {
    double da = *(const double *)a;
    double db = *(const double *)b;
    return (da > db) - (da < db);
}

// Statistics: mean or median, depending on mode
void calculate_statistics(const char* mode) {
    int n;
    if (!get_int("Enter number of elements: ", &n) || n <= 0) {
        printf("Error! Invalid input for number of elements.\n");
        return;
    }
    double* arr = (double*)malloc(n * sizeof(double));
    if (!arr) {
        printf("Error! Memory allocation failed.\n");
        return;
    }
    printf("Enter %d numbers (one per line):\n", n);
    for (int i = 0; i < n; i++) {
        if (!get_double("", &arr[i])) {
            printf("Error! Invalid input.\n");
            free(arr);
            return;
        }
    }
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    if (strcmp(mode, "mean") == 0)
        printf("Mean: %.6lf\n", sum / n);

    qsort(arr, n, sizeof(double), compare_double);
    double median = (n % 2) ? arr[n/2] : (arr[n/2-1] + arr[n/2]) / 2.0;
    if (strcmp(mode, "median") == 0)
        printf("Median: %.6lf\n", median);

    free(arr);
}

void matrix_operations(void) {
    printf("Matrix operations are currently under development.\n");
    // Future implementation: Add, multiply, transpose, etc.
}

void memory_operations(void) {
    printf("Memory value: %.6lf\n", memory);
    printf("Commands: store, recall, clear\n");
    char cmd[MAX_CMD_LEN];
    printf("Enter command: ");
    if (!fgets(cmd, sizeof(cmd), stdin)) {
        printf("Error reading command.\n");
        return;
    }
    cmd[strcspn(cmd, "\n")] = 0;
    if (strcmp(cmd, "store") == 0) {
        if (!get_double("Enter value to store: ", &memory))
            printf("Invalid input.\n");
        else
            printf("Stored %.6lf to memory.\n", memory);
    } else if (strcmp(cmd, "recall") == 0) {
        printf("Memory: %.6lf\n", memory);
    } else if (strcmp(cmd, "clear") == 0) {
        memory = 0.0;
        printf("Memory cleared.\n");
    } else {
        printf("Invalid memory command.\n");
    }
}

int main(void) {
    char input[MAX_INPUT_LEN], operation[MAX_CMD_LEN];

    while (1) {
        print_menu();
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input.\n");
            break;
        }
        input[strcspn(input, "\n")] = 0; // Remove newline
        if (sscanf(input, "%19s", operation) != 1) continue;

        if (strcmp(operation, "exit") == 0) {
            printf("Exiting... Goodbye!\n");
            break;
        }
        else if (
            strcmp(operation, "+") == 0 || strcmp(operation, "-") == 0 ||
            strcmp(operation, "*") == 0 || strcmp(operation, "/") == 0 ||
            strcmp(operation, "^") == 0
        ) handle_basic_arithmetic(operation);
        else if (strcmp(operation, "sqrt") == 0) handle_square_root();
        else if (
            strcmp(operation, "sin") == 0 ||
            strcmp(operation, "cos") == 0 ||
            strcmp(operation, "tan") == 0
        ) handle_trig(operation);
        else if (
            strcmp(operation, "log") == 0 || strcmp(operation, "log10") == 0
        ) handle_log(operation);
        else if (strcmp(operation, "factorial") == 0) handle_factorial();
        else if (strcmp(operation, "eq") == 0) handle_linear_eq();
        else if (strcmp(operation, "qeq") == 0) handle_quadratic_eq();
        else if (
            strcmp(operation, "deg2rad") == 0 || strcmp(operation, "rad2deg") == 0
        ) handle_deg_rad(operation);
        else if (strcmp(operation, "mean") == 0) calculate_statistics("mean");
        else if (strcmp(operation, "median") == 0) calculate_statistics("median");
        else if (strcmp(operation, "matrix") == 0) matrix_operations();
        else if (strcmp(operation, "mem") == 0) memory_operations();
        else printf("Unknown command. Please try again.\n");
    }
    return 0;
}
