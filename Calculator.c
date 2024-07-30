#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

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
    printf(" eq for linear equation (ax + b = 0)\n");
    printf(" qeq for quadratic equation (ax^2 + bx + c = 0)\n");
    printf(" Enter operation: ");
}

double evaluate_expression(const char* expr);
double parse_number(const char** expr);
double parse_parentheses(const char** expr);
double parse_factor(const char** expr);
double parse_term(const char** expr);
double parse_expression(const char** expr);
double solve_linear_equation(double a, double b);
void solve_quadratic_equation(double a, double b, double c);
double evaluate_trigonometric_function(const char* func, double x);

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
        } else {
            // Evaluate expression
            const char* p = input;
            result = evaluate_expression(p);
            printf("Result: %.2lf\n", result);
        }
    }

    return 0;
}
