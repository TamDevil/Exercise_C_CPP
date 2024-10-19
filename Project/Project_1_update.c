#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum{
    Addperson = 1,
    SearchName,
    SearchNum,
    Exit
}choice;

typedef struct Node{
    char name[50];
    int age;
    char addr[100];
    char Num[15];
    struct Node *next;
}node;

typedef struct centerpoint
{
    char name[50];
    int age;
    char addr[100];
    char num[15];
    struct centerpoint *left;
    struct centerpoint *right;
}centerpoint;

node *AddNodeByName(node **arr, char *name, int age, char *addr, char *num){
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL)
    {
        printf("Khong cap phat duoc bo nho!\n");
        return NULL;
    }
    strcpy(temp->name, name);
    temp->age = age;
    strcpy(temp->addr, addr);
    strcpy(temp->Num, num);
    temp->next = NULL;

    if (*arr == NULL || strcmp((*arr)->name, name) >= 0)
    {
        temp->next = *arr;
        *arr = temp;
        return temp;
    }
    node *current = *arr;
    while (current->next != NULL && strcmp(current->next->name, name) < 0)
    {
        current = current->next;
    }
    temp->next = current->next;
    current->next = temp;
    return temp;
}


node *AddNodeByPhone(node **arr, char *name, int age, char *addr, char *num){
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL)
    {
        printf("Khong cap phat duoc bo nho!\n");
        return NULL;
    }
    strcpy(temp->name, name);
    temp->age = age;
    strcpy(temp->addr, addr);
    strcpy(temp->Num, num);
    temp->next = NULL;

    if (*arr == NULL || strcmp((*arr)->Num, num) >= 0)
    {
        temp->next = *arr;
        *arr = temp;
        return temp;
    }
    node *current = *arr;
    while (current->next != NULL && strcmp(current->next->Num, num) < 0)
    {
        current = current->next;
    }
    temp->next = current->next;
    current->next = temp;
    return temp;
}

int createfile(char *filename){
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Khong the tao file!\n");
        return 0;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fprintf(file, "Ho va ten, Tuoi, Dia chi, So dien thoai\n");
    }
    int n, age; char name[50]; char addr[100]; char num[15];
    printf("Nhap so luong nguoi: ");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        printf("Nhap ho va ten: ");
        fgets(name,sizeof(name),stdin);
        name[strcspn(name,"\n")] = '\0';
        fprintf(file,"%s, ",name);

        printf("Nhap tuoi: ");
        scanf("%d",&age);
        getchar();
        fprintf(file,"%d, ",age);

        printf("Nhap dia chi: ");
        fgets(addr,sizeof(addr),stdin);
        addr[strcspn(addr,"\n")] = '\0';
        fprintf(file,"%s, ",addr);

        printf("Nhap so dien thoai: ");
        fgets(num,sizeof(num),stdin);
        num[strcspn(num,"\n")] = '\0';
        fprintf(file,"%s\n",num);
    }
    fclose(file);
    return 1;
}

void removespace(char *str){
    int count = 0;
    for (int i = 0;str[i]; i++)
    {
        if (!isspace(str[i]))
        {
            str[count++] = str[i];
        }
    }
        str[count] = '\0';
}

void ReadFileByName(node** arr, char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Khong the doc file!\n");
        return;
    }
    char line[200]; char name[50]; char addr[100]; char num[15]; int age;
    fgets(line, sizeof(line), file); // bo qua tieu de
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        strcpy(name, token);
        removespace(name);

        token = strtok(NULL, ",");
        age = atoi(token);

        token = strtok(NULL, ",");
        strcpy(addr, token);

        token = strtok(NULL, ",");
        strcpy(num, token);
        removespace(num);

        AddNodeByName(arr, name, age, addr, num);
    }
}

void ReadFileByPhone(node** arr, char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Khong the doc file!\n");
        return;
    }
    char line[200]; char name[50]; char addr[100]; char num[15]; int age;
    fgets(line, sizeof(line), file); // bo qua tieu de
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        strcpy(name, token);
        removespace(name);

        token = strtok(NULL, ",");
        age = atoi(token);

        token = strtok(NULL, ",");
        strcpy(addr, token);

        token = strtok(NULL, ",");
        strcpy(num, token);
        removespace(num);

        AddNodeByPhone(arr, name, age, addr, num);
    }
}

void freelist(node **arr){
    while (*arr != NULL)
    {
        node *temp = *arr;
        *arr = (*arr)->next;
        free(temp);
    }
    
}

void UpdateFile(node **arr, char *filename){
    if (createfile(filename))
    {
        printf("Cap nhan file thanh cong!\n");
        freelist(arr);
        ReadFileByName(arr, filename);
        ReadFileByPhone(arr, filename);
    }else
    printf("Cap nhat file khong thanh cong!\n"); 
}

centerpoint *buildtree(node *arr, int start, int end){
    if (arr == NULL || start > end)
    {
        return NULL;
    }
    centerpoint *root = (centerpoint*)malloc(sizeof(centerpoint));
    if (root == NULL)
    {
        printf("Khong the cap phat bo nho!\n");
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
    
    strcpy(root->name, current->name);
    root->age = current->age;
    strcpy(root->addr, current->addr);
    strcpy(root->num, current->Num);
    root->left = buildtree(arr, start, mid -1);
    root->right = buildtree(current->next, mid + 1, end);
    return root;
}

void freetree(centerpoint *root){
    if (root == NULL)
    {
        return;
    }
    free(root->left);
    free(root->right);
    free(root);
}

centerpoint *Centerpoint(node *arr){
    if (arr == NULL)
    {
        printf(" mang rong!\n");
        return NULL;
    }
    int count = 0;
    node *current = arr;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return buildtree(arr, 0, count -1);
}

centerpoint *SearchByName(centerpoint *root, char *name){
    if (root == NULL)
    {
        printf("Khong co cay nhi phan!\n");
        return NULL;
    }
    int cmp = strcasecmp(root->name, name);
    if (cmp == 0)
    {
        printf("Ho va ten: %s\n", root->name);
        printf("Tuoi: %d\n", root->age);
        printf("Dia chi: %s\n", root->addr);
        printf("So dien thoai: %s\n", root->num);
        return root;
    }else if (cmp > 0)
    {
        return SearchByName(root->left, name);
    }else
        return SearchByName(root->right, name);
}

centerpoint *SearchByPhone(centerpoint *root, char *num){
    if (root == NULL)
    {
        printf("Khong co cay nhi phan!\n");
        return NULL;
    }
    int cmp = strcasecmp(root->num, num);
    if (cmp == 0)
    {
        printf("Ho va ten: %s\n", root->name);
        printf("Tuoi: %d\n", root->age);
        printf("Dia chi: %s\n", root->addr);
        printf("So dien thoai: %s\n", root->num);
        return root;
    }else if (cmp > 0)
    {
        return SearchByPhone(root->left, num);
    }else
        return SearchByPhone(root->right, num);
}

void printlist(node *arr){
    if (arr == NULL)
    {
        printf("Mang rong!\n");
        return;
    }
    while (arr != NULL)
    {
        printf("Ho va ten: %s\n", arr->name);
        printf("Tuoi: %d\n", arr->age);
        printf("Dia chi: %s\n", arr->addr);
        printf("So dien thoai: %s\n", arr->Num);
        arr = arr->next;
    }
    return;
}


int main(int argc, char const *argv[])
{
    int choice;
    node *arr = NULL;
    centerpoint *root = NULL;
    do
    {
        printf("Menu\n");
        printf("1. Them du lieu.\n");
        printf("2. Tim kiem bang Ten.\n");
        printf("3. Tim kiem bang So dien thoai.\n");
        printf("4. Thoat.\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case Addperson:
            UpdateFile(&arr, "createfile.csv");
            break;

        case SearchName:
            char name[50];
            freelist(&arr);
            ReadFileByName(&arr,"createfile.csv");
            printlist(arr);
            printf("Nhap ten can tim: ");
            //scanf("%s", name);
            getchar();
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            root = Centerpoint(arr);
            SearchByName(root, name);
            break;

        case SearchNum:
            char num[15];
            freelist(&arr);
            ReadFileByPhone(&arr,"createfile.csv");
            printlist(arr);
            printf("Nhap so dien thoai can tim: ");
            //scanf("%s", num);
            getchar();
            fgets(num, sizeof(num), stdin);
            num[strcspn(num, "\n")] = '\0';
            root = Centerpoint(arr);
            SearchByPhone(root, num);
            break;

        case Exit:
        printf("Thoat chuong trinh!\n");
        break;
        default:
        printf("Lua chon khong hop le!\n");
            break;
        }

    } while (choice != Exit);
    freelist(&arr);  // Giải phóng bộ nhớ
    freetree(root);
    return 0;
}
