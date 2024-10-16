#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{
    NameSearch = 1,
    PhNumSearch,
    Thoat
} choice;

typedef struct node{
    char Hovaten[50];
    int Tuoi;
    char Diachi[100];
    char Sodienthoai[15];
    struct node *next;
} node;

node *AddNodeByName(node **arr, char *name, int age, char *addr, char *PhNum){
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL)
    {
        printf("Cap phat bo nho khong thanh cong!\n");
        return NULL;
    }
    strcpy(temp->Hovaten, name);
    temp->Tuoi = age;
    strcpy(temp->Diachi, addr);
    strcpy(temp->Sodienthoai, PhNum);
    temp->next = NULL;
    
    if (*arr == NULL || strcmp((*arr)->Hovaten,name) >= 0)
    {
        temp->next = *arr;
        *arr = temp;
        return temp;
    }
    node *current = *arr;
    while (current->next != NULL && strcmp(current->next->Hovaten, name) <0)
    {
        current = current->next;
    }
    temp->next = current->next;
    current->next = temp;
    return temp;
}

node *AddNodeByPhone(node **arr, char *name, int age, char *addr, char *PhNum){
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL)
    {
        printf("Cap phat bo nho khong thanh cong!\n");
        return NULL;
    }
    strcpy(temp->Hovaten, name);
    temp->Tuoi = age;
    strcpy(temp->Diachi, addr);
    strcpy(temp->Sodienthoai, PhNum);
    temp->next = NULL;
    
    if (*arr == NULL || strcmp((*arr)->Sodienthoai,PhNum) >= 0)
    {
        temp->next = *arr;
        *arr = temp;
        return temp;
    }
    node *current = *arr;
    while (current->next != NULL && strcmp(current->next->Sodienthoai, PhNum) <0)
    {
        current = current->next;
    }
    temp->next = current->next;
    current->next = temp;
    return temp;
}

void ReadFileByName(node **arr, char *filename){
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Khong doc duoc file!\n");
        return;
    }
    char line[200];
    char name[50];
    int age;
    char addr[100];
    char PhNum[15];
    // Bo dong header
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = 0; // xóa ký tự xuống dòng
        char *token = strtok(line, ",");
        if(token != NULL) strcpy(name, token);
        token = strtok(NULL, ",");
        if(token != NULL) age = atoi(token);
        token = strtok(NULL, ",");
        if(token != NULL) strcpy(addr, token);
        token = strtok(NULL, ",");
        if(token != NULL) strcpy(PhNum, token);
        AddNodeByName(arr, name, age, addr, PhNum);
    }
    fclose(file);
}

void ReadFileByPhone(node **arr, char *filename){
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Khong doc duoc file!\n");
        return;
    }
    char line[200];
    char name[50];
    int age;
    char addr[100];
    char PhNum[15];
    // Bo dong header
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if(token != NULL) strcpy(name, token);
        token = strtok(NULL, ",");
        if(token != NULL) age = atoi(token);
        token = strtok(NULL, ",");
        if(token != NULL) strcpy(addr, token);
        token = strtok(NULL, ",");
        if(token != NULL) strcpy(PhNum, token);
        AddNodeByPhone(arr, name, age, addr, PhNum);
    }
    fclose(file);
}

typedef struct centerpoint{
    char name[50];
    int age;
    char addr[100];
    char PhNum[15];
    struct centerpoint *left;
    struct centerpoint *right;
} centerpoint;

centerpoint *buildtree(node *arr, int start, int end){
    if(arr == NULL || start > end){
    return NULL;
    }
    int mid = start + (end - start) / 2;
    node *current = arr;
    for (int i = start; i < mid; i++)
    {
        if (current->next == NULL)
        {
            break;
        }
        current = current->next;
    }
    centerpoint *root = (centerpoint*)malloc(sizeof(centerpoint));
    if(root == NULL){
    printf("Khong the cap phat bo nho!");
    return NULL;
    }
    strcpy(root->name, current->Hovaten);
    root->age = current->Tuoi;
    strcpy(root->addr, current->Diachi);
    strcpy(root->PhNum, current->Sodienthoai);

    // Đệ quy xây dựng cây nhị phân cho hai nửa của danh sách liên kết
    root->left = buildtree(arr, start, mid - 1);
    root->right = buildtree(current->next, mid + 1, end);
    return root;
}

centerpoint *Centerpoint(node *arr){
    if (arr == NULL)
    {
        printf("Mang khong co node!\n");
        return NULL;
    }
    int length = 0;
    node *current = arr;
    while (current != NULL)
    {
        length++;
        current = current->next;
    }
    return buildtree(arr, 0, length - 1);
}

centerpoint *BinaryByName(centerpoint *root, char *name){
    if (root == NULL)
    {
        printf("Khong co cay nhi phan!\n");
        return NULL;
    }
    int cmp = strcasecmp(root->name, name);
    if (cmp == 0)
    {
        printf("Hovaten: %s\n", root->name);
        printf("Tuoi: %d\n", root->age);
        printf("DiaChi: %s\n", root->addr);
        printf("SodienThoai: %s\n", root->PhNum);
        return root;
    }else if(cmp > 0){
        return BinaryByName(root->left, name);
    }else
    return BinaryByName(root->right, name);
}
centerpoint *BinaryByPhone(centerpoint *root, char *PhNum){
    if (root == NULL)
    {
        printf("Khong tim thay!\n");
        return NULL;
    }
    int cmp = strcasecmp(root->PhNum, PhNum);
    if (cmp == 0)
    {
        printf("Hovaten: %s\n", root->name);
        printf("Tuoi: %d\n", root->age);
        printf("DiaChi: %s\n", root->addr);
        printf("SodienThoai: %s\n", root->PhNum);
        return root;
    }else if(cmp > 0){
        return BinaryByPhone(root->left, PhNum);
    }else
    return BinaryByPhone(root->right, PhNum);
}

void freelist(node **arr){
    while(*arr != NULL){
    node *temp = *arr;
    *arr = (*arr)->next;
    free(temp);
}
}

void freetree(centerpoint *root){
    if(root == NULL) return;
    free(root->left);
    free(root->right);
    free(root);
}

void printlist(node *arr){
    if (arr == NULL)
    {
        printf("Danh sach rong!\n");
        return;
    }
    node *current = arr;
    while(current != NULL){
    printf("Ho va ten: %s\n",current->Hovaten);
    printf("Tuoi: %d\n",current->Tuoi);
    printf("Dia chi: %s\n",current->Diachi);
    printf("So dien thoai: %s\n",current->Sodienthoai);
    current = current->next;
    }
}
int main(int argc, char const *argv[])
{
    node *arr = NULL;
    centerpoint *root = NULL;
    int choice;
do{
    printf("Menu:\n");
    printf("1. Tim kiem bang ten.\n");
    printf("2. Tim kiem bang SDT.\n");
    printf("3. Thoat!\n");
    printf("nhap lua chon cua ban: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case NameSearch:
        char name[50];
        freelist(&arr);
        ReadFileByName(&arr,"D:\\Exercise_C_CPP\\File\\file.csv");
       // printlist(arr);
        printf("Nhap ten can tim: ");
        scanf("%s", name);
        root = Centerpoint(arr);
        BinaryByName(root,name);
        break;
    case PhNumSearch:
        char PhNum[15];
        freelist(&arr);
        ReadFileByPhone(&arr,"D:\\Exercise_C_CPP\\File\\file.csv");
       // printlist(arr);
        printf("Nhap Sdt can tim: ");
        scanf("%s", PhNum);
        root = Centerpoint(arr);
        BinaryByPhone(root,PhNum);
        break;
    case Thoat:
        printf("Thoat chuong trinh!\n");
        break;
    default:
        printf("Lua chon khong hop le, chon lai\n");
        break;
    }
}while(choice != 3);
    return 0;
}
