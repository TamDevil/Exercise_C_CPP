#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    int *arr;
    int size;
    int front;
    int rear;
} queue;

int isfull(queue queue){
    return ((queue.rear +1) % queue.size ) == queue.front; 
}
int isempty(queue queue){
    return queue.front == -1;
}
void initqueue(queue *queue, int size){
    queue->arr = (int*)malloc(size * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
}
void enqueue(queue *queue, int value){
    if (!isfull(*queue))
    {
        if (isempty(*queue))
        {
            queue->front = 0;
        }
        queue->rear = (queue->rear + 1) % queue->size;
        queue->arr[queue->rear] = value;
    }else{
    printf("queue is full\n");}
}
int dequeue(queue *queue){
    if (!isempty(*queue))
    {
       int value = queue->arr[queue->front];
       if (queue->front == queue->rear)
       {
        queue->front = queue->rear = -1;
       }else
       queue->front = (queue->front + 1) % queue->size;
       return value;
    }else
    return -1;
}
int front(queue queue){
    if (!isempty(queue))
    {
    return queue.arr[queue.front];
    }else
    printf("queue is empty");
}
int rear(queue queue){
     if (!isempty(queue))
    {
    return queue.arr[queue.rear];
    }else
    printf("queue is empty");
}
int main(int argc, char const *argv[])
{
    queue queue;
    initqueue(&queue, 5);
    enqueue(&queue, 50);
    printf("%d\n", dequeue(&queue));
    printf("%d\n", queue.front);
    printf("%d\n", queue.rear);
    return 0;
}
