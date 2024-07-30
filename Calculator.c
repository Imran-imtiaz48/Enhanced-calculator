#include <stdio.h>
#include <math.h>

void print_menu() {
    printf("Select operation:\n");
    printf(" + for addition\n");
    printf(" - for subtraction\n");
    printf(" * for multiplication\n");
    printf(" / for division\n");
    printf(" ^ for exponentiation (power)\n");
    printf(" sqrt for square root\n");
    printf(" Enter operation: ");
}

int main() {
    char operation[10];
    double num1, num2, result;

    // Display menu
    print_menu();
    scanf("%s", operation);

    if (operation[0] == 's' && operation[1] == 'q' && operation[2] == 'r' && operation[3] == 't') {
        // Square root calculation
        printf("Enter a number: ");
        scanf("%lf", &num1);
        if (num1 < 0) {
            printf("Error! Negative number for square root.\n");
        } else {
            result = sqrt(num1);
            printf("Result: %.2lf\n", result);
        }
    } else if (operation[0] == '^') {
        // Exponentiation
        printf("Enter base and exponent: ");
        scanf("%lf %lf", &num1, &num2);
        result = pow(num1, num2);
        printf("Result: %.2lf\n", result);
    } else {
        // Get two numbers from user
        printf("Enter two numbers: ");
        scanf("%lf %lf", &num1, &num2);

        // Perform calculation based on operator
        switch (operation[0]) {
            case '+':
                result = num1 + num2;
                printf("Result: %.2lf\n", result);
                break;
            case '-':
                result = num1 - num2;
                printf("Result: %.2lf\n", result);
                break;
            case '*':
                result = num1 * num2;
                printf("Result: %.2lf\n", result);
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error! Division by zero.\n");
                }
                break;
            default:
                printf("Error! Invalid operation.\n");
                break;
        }
    }

    return 0;
}
