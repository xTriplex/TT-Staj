#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    OPERATION_COUNT
} Operation;

typedef struct
{
    int result;
    bool error;
} OperationResult;

// Arithmetic functions
OperationResult Add(int a, int b)
{
    return (OperationResult){ a + b, false };
}

OperationResult Subtract(int a, int b)
{
    return (OperationResult){ a - b, false };
}

OperationResult Multiply(int a, int b)
{
    return (OperationResult){ a * b, false };
}

OperationResult Divide(int a, int b)
{
    if (b != 0)
    {
        printf("Remainder: %d\n", a % b);
        return (OperationResult){ a / b, false };
    } 
    else
    {
        return (OperationResult){ 0, true }; // Set error flag to true for division by zero
    }
}

// Function pointer
typedef OperationResult (*ArithmeticFunction)(int, int);

// Array of function pointers
ArithmeticFunction operations[OPERATION_COUNT] = { Add, Subtract, Multiply, Divide };

void PerformOperation(int a, int b, Operation op)
{
    const char *operationNames[] = { "Addition", "Subtraction", "Multiplication", "Division" };
    if (op >= 0 && op < OPERATION_COUNT)
    {
        OperationResult opResult = operations[op](a, b);
        if (opResult.error)
        {
            printf("%s: Division by zero is not allowed!\n", operationNames[op]);
            return;
        } 
        else
        {
            printf("%s: %d\n", operationNames[op], opResult.result);
        }
    } 
    else
    {
        printf("Invalid operation\n"); // Redundant until implementing user input for choosing an operation
    }
}

int main()
{
    int x, y;
    printf("Enter the first number: ");
    scanf("%d", &x);
    printf("Enter the second number: ");
    scanf("%d", &y);

    PerformOperation(x, y, 0);    // Addition
    PerformOperation(x, y, 1);    // Subtraction
    PerformOperation(x, y, 2);    // Multiplication
    PerformOperation(x, y, 3);    // Division

    return 0;
}
