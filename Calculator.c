#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
double evaluate_expression(const char* expr);
double parse_number(const char** expr);
double parse_parentheses(const char** expr);
double parse_factor(const char** expr);
double parse_term(const char** expr);
double parse_expression(const char** expr);

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

int main() {
    char input[256];

    printf("Enter a mathematical expression (or type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input.\n");
            break;
        }

        // Remove newline character if present
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Evaluate the expression
        double result;
        const char* p = input;

        if (*p) {
            result = evaluate_expression(p);
            printf("Result: %.2lf\n", result);
        } else {
            printf("Error! Empty input.\n");
        }
    }

    return 0;
}
