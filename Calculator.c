#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Function prototypes
void print_menu();
void handle_basic_arithmetic(const char* op);
void handle_square_root();
void handle_trig(const char* func);
void handle_log(const char* func);
void handle_factorial();
void handle_linear_eq();
void handle_quadratic_eq();
void handle_deg_rad(const char* op);
void calculate_statistics();
void matrix_operations();
void memory_operations();

double memory = 0; // Memory variable

void print_menu() {
    printf("\n=== Enhanced Calculator ===\n");
    printf("Select an operation:\n");
    printf(" +, -, *, /, ^      : Basic arithmetic\n");
    printf(" sqrt               : Square root\n");
    printf(" sin, cos, tan      : Trigonometric functions\n");
    printf(" log, log10         : Logarithmic functions\n");
    printf(" factorial          : Factorial calculation\n");
    printf(" eq                 : Linear equation (ax + b = 0)\n");
    printf(" qeq                : Quadratic equation (ax^2 + bx + c = 0)\n");
    printf(" deg2rad, rad2deg   : Degree/radian conversions\n");
    printf(" mean, median       : Statistics\n");
    printf(" matrix             : Matrix operations\n");
    printf(" mem                : Memory operations\n");
    printf(" exit               : Quit\n");
}

void handle_basic_arithmetic(const char* op) {
    double a, b;
    printf("Enter first number: ");
    if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); return; }
    printf("Enter second number: ");
    if (scanf("%lf", &b) != 1) { printf("Invalid input.\n"); return; }

    double result;
    if (strcmp(op, "+") == 0) result = a + b;
    else if (strcmp(op, "-") == 0) result = a - b;
    else if (strcmp(op, "*") == 0) result = a * b;
    else if (strcmp(op, "/") == 0) {
        if (b == 0) { printf("Error: Division by zero.\n"); return; }
        result = a / b;
    } else if (strcmp(op, "^") == 0) result = pow(a, b);
    else { printf("Unknown operator.\n"); return; }
    printf("Result: %.6lf\n", result);
    memory = result;
}

void handle_square_root() {
    double x;
    printf("Enter number: ");
    if (scanf("%lf", &x) != 1 || x < 0) {
        printf("Invalid input or negative number.\n"); return;
    }
    double result = sqrt(x);
    printf("sqrt(%.6lf) = %.6lf\n", x, result);
    memory = result;
}

void handle_trig(const char* func) {
    double x;
    printf("Enter value in degrees: ");
    if (scanf("%lf", &x) != 1) { printf("Invalid input.\n"); return; }
    double rad = x * M_PI / 180.0;
    double result;
    if (strcmp(func, "sin") == 0) result = sin(rad);
    else if (strcmp(func, "cos") == 0) result = cos(rad);
    else if (strcmp(func, "tan") == 0) result = tan(rad);
    else { printf("Unknown trig function.\n"); return; }
    printf("%s(%.2lf degrees) = %.6lf\n", func, x, result);
    memory = result;
}

void handle_log(const char* func) {
    double x;
    printf("Enter positive number: ");
    if (scanf("%lf", &x) != 1 || x <= 0) {
        printf("Invalid or non-positive input.\n"); return;
    }
    double result;
    if (strcmp(func, "log") == 0) result = log(x);
    else if (strcmp(func, "log10") == 0) result = log10(x);
    else { printf("Unknown log function.\n"); return; }
    printf("%s(%.6lf) = %.6lf\n", func, x, result);
    memory = result;
}

void handle_factorial() {
    int n;
    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1 || n < 0) { printf("Invalid input.\n"); return; }
    unsigned long long fact = 1;
    for (int i = 2; i <= n; ++i) fact *= i;
    printf("%d! = %llu\n", n, fact);
    memory = (double)fact;
}

void handle_linear_eq() {
    double a, b;
    printf("Equation ax + b = 0\n");
    printf("Enter a: ");
    if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); return; }
    printf("Enter b: ");
    if (scanf("%lf", &b) != 1) { printf("Invalid input.\n"); return; }
    if (a == 0) { printf("No solution (a=0).\n"); return; }
    double x = -b / a;
    printf("Solution: x = %.6lf\n", x);
    memory = x;
}

void handle_quadratic_eq() {
    double a, b, c;
    printf("Equation ax^2 + bx + c = 0\n");
    printf("Enter a: ");
    if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); return; }
    printf("Enter b: ");
    if (scanf("%lf", &b) != 1) { printf("Invalid input.\n"); return; }
    printf("Enter c: ");
    if (scanf("%lf", &c) != 1) { printf("Invalid input.\n"); return; }
    double d = b * b - 4 * a * c;
    if (a == 0) { printf("Not a quadratic equation.\n"); return; }
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
        printf("Enter degrees: ");
        if (scanf("%lf", &val) != 1) { printf("Invalid input.\n"); return; }
        printf("%.2lf degrees = %.6lf radians\n", val, val * M_PI / 180.0);
    } else {
        printf("Enter radians: ");
        if (scanf("%lf", &val) != 1) { printf("Invalid input.\n"); return; }
        printf("%.6lf radians = %.2lf degrees\n", val, val * 180.0 / M_PI);
    }
}

void calculate_statistics() {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error! Invalid input for number of elements.\n");
        return;
    }

    double* arr = (double*)malloc(n * sizeof(double));
    if (!arr) {
        printf("Error! Memory allocation failed.\n");
        return;
    }

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &arr[i]) != 1) {
            printf("Error! Invalid input.\n");
            free(arr);
            return;
        }
    }

    // Mean
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    printf("Mean: %.2lf\n", sum / n);

    // Median
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                double tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
    double median = n%2 ? arr[n/2] : (arr[n/2-1]+arr[n/2])/2.0;
    printf("Median: %.2lf\n", median);

    free(arr);
}

void matrix_operations() {
    printf("Matrix operations are currently under development.\n");
}

void memory_operations() {
    printf("Memory value: %.6lf\n", memory);
    printf("Commands: store, recall, clear\n");
    char cmd[10];
    printf("Enter command: ");
    scanf("%s", cmd);
    if (strcmp(cmd, "store") == 0) {
        printf("Enter value to store: ");
        if (scanf("%lf", &memory) != 1) printf("Invalid input.\n");
        else printf("Stored %.6lf to memory.\n", memory);
    } else if (strcmp(cmd, "recall") == 0) {
        printf("Memory: %.6lf\n", memory);
    } else if (strcmp(cmd, "clear") == 0) {
        memory = 0;
        printf("Memory cleared.\n");
    } else {
        printf("Invalid memory command.\n");
    }
}

int main() {
    char input[256];
    char operation[20];

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
        } else if (
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
        else if (
            strcmp(operation, "mean") == 0 || strcmp(operation, "median") == 0
        ) calculate_statistics();
        else if (strcmp(operation, "matrix") == 0) matrix_operations();
        else if (strcmp(operation, "mem") == 0) memory_operations();
        else printf("Unknown command. Please try again.\n");

        // Flush stdin in case there is leftover input
        int c; while ((c = getchar()) != '\n' && c != EOF);
    }
    return 0;
}
