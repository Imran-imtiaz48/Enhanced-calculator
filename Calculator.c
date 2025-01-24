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
    printf("Select an operation:\n");
    printf(" +, -, *, /, ^ for basic arithmetic\n");
    printf(" sqrt for square root\n");
    printf(" sin, cos, tan for trigonometric functions\n");
    printf(" log, log10 for logarithmic functions\n");
    printf(" factorial for factorial calculation\n");
    printf(" eq for linear equations (ax + b = 0)\n");
    printf(" qeq for quadratic equations (ax^2 + bx + c = 0)\n");
    printf(" deg2rad or rad2deg for angle conversions\n");
    printf(" mean, median for statistics\n");
    printf(" matrix for matrix operations\n");
    printf(" mem for memory operations\n");
    printf(" exit to quit\n");
}

double parse_number(const char** expr) {
    while (isspace(**expr)) (*expr)++;
    char* end;
    double result = strtod(*expr, &end);
    if (*expr == end) {
        printf("Error! Invalid number format.\n");
        exit(EXIT_FAILURE);
    }
    *expr = end;
    return result;
}

// Other parsing functions remain similar with improved error handling...

void matrix_operations() {
    printf("Matrix operations are currently under development.\n");
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

    // Calculate mean
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    printf("Mean: %.2lf\n", sum / n);

    // Other statistics (median, mode, etc.) go here...

    free(arr);
}

int main() {
    char input[256];
    char operation[10];
    double num1, num2, result;

    while (1) {
        print_menu();
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input.\n");
            break;
        }

        input[strcspn(input, "\n")] = 0; // Remove newline
        sscanf(input, "%s", operation);

        if (strcmp(operation, "exit") == 0) {
            printf("Exiting... Goodbye!\n");
            break;
        }

        // Add cases for operations (sqrt, eq, qeq, sin, etc.)...
        printf("Feature is currently under review. Please enter valid input.\n");
    }

    return 0;
}
