#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} node;

node *createNode(int value){
    node *temp = (node*)malloc(sizeof(node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

void push_back(node **array, int value){
    node* temp = createNode(value);
    if (*array == NULL)
    {
        *array = temp; 
        return;
    }
    node *p = *array;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = temp;
}
void push_front(node **arr,int value){
    node *temp = createNode(value);
    if (*arr == NULL)
    {
        *arr = temp;
        return;
    }
    temp->next = *arr;
    *arr = temp;
}

void pop_back(node **arr){
    if (*arr == NULL)
    {
        printf("mang rong\n");
        return;
    }
    node *p = *arr;
    if (p->next == NULL)
    {
        free(p);
        *arr = NULL;
        return;
    }
    
    while (p->next->next != NULL)
    {
        p = p->next;
    }
    node *temp = p->next;
    p->next = NULL;
    free(temp);
}
void pop_front(node **arr){
    if (*arr == NULL)
    {
        printf("mang rong\n");
        return;
    }
    node *temp = *arr;
    *arr = temp->next;
    free(temp);
}
int front(node *arr){
    if (arr == NULL)
    {
        return 0;
    }
    return arr->data;
}
int back(node *arr){
    if(arr == NULL){
        return 0;
    }
    while (arr->next != NULL)
    {
        arr = arr->next;
    }
    return arr->data;
}
void insert(node **arr,int value, int pos){
    node *temp = createNode(value);
    if (*arr == NULL || pos == 0)
    {
        push_front(arr,value);
        return;
    }
    int index = 1;
    
    node *p = *arr;
    while (p != NULL && index < pos)
    {
        p = p->next;
        index++;
    }
    if (p == NULL && index == pos)
    {
        push_back(arr,value);
        return;
    }else if(p == NULL && index < pos)
    {
        printf("mang khong du phan tu\n");
        free(temp);
        return;
    }
    temp->next = p->next;
    p->next = temp;
}

void delete_list(node **arr, int pos){
    if (*arr == NULL)
    {
            printf("mang khong\n");
            return;
    }
    if (pos == 0)
    {
        pop_front(arr);
        return;
    }
    int index = 0;
    node *p = *arr;
    while (p->next != NULL && index != (pos - 1))
    {
        p = p->next;
        index++;
    }
    if ((pos -1) != index)
    {
            printf("mang khong du phan tu\n");
            return;
    }
    
    node * temp = p->next;
    p->next = p->next->next;
    free(temp);
}
int size (node *arr){
    int index = 0;
    if (arr == NULL)
    {
        return index;
    }
    while(arr != NULL){
        arr = arr->next;
        index++;
    }
    return index;
}

int get (node *arr, int pos){
    if (pos == 0)
    {
        front(arr);
    }
    int index = 0;
    while (arr->next != NULL && index < pos)
    {
        arr = arr->next;
        index++;
    }
    if (arr->next == NULL && index == pos)
    {
        back(arr);
    }else if (arr->next == NULL && index != pos)
    {
        return 0;
    }
    return arr->data;
    
}
int isempty(node *arr){
    return arr == NULL;
}
void printList(node* arr){
    int index = 0;
    while(arr != NULL){
        printf("node %d, value %d\n", index, arr->data);
        index++;
        arr = arr->next;
    }
}
int main(int argc, char const *argv[])
{
    node *arr = NULL;
    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);
    push_back(&arr, 40);
    push_back(&arr, 200);
    push_front(&arr, 100);
    delete_list(&arr, 2);
    insert(&arr, 300,5);
    pop_back(&arr);
    pop_front(&arr);
    return 0;
}
