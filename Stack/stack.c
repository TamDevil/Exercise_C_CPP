#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *arr;
    int size;
    int top;
} stack;

void init(stack *stack, int size){
    stack->arr = (int*)malloc(sizeof(int)*size);
    stack->top = -1;
    stack->size = size;
}
int isfull(stack stack){
    return stack.top == stack.size - 1;
}
int isempty(stack stack){
    return stack.top == -1;
}
void push(stack *stack, int value){
    if (!isfull(*stack))
    {       
        stack->arr[++stack->top] = value;
    }else
    printf("stack is full\n");
}
int pop (stack *stack){
    if (!isempty(*stack))
    {
        return stack->arr[stack->top--];
    }else
    return -1;
}
int top(stack stack){
    if (!isempty(stack))
    {
    return stack.arr[stack.top];
    }else
    return -1;
    
}
int main(int argc, char const *argv[])
{
    stack stack;
    init(&stack,5);
    push(&stack, 50);
    printf("%d\n", stack.arr[0]);
    return 0;
}