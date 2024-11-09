/***************************************************************************
 * @file    Project_1_update.c
 * @brief   Định nghĩa các hàm tìm kiếm dữ liệu trong danh sách.
 * @details File này chứa phần định nghĩa của các hàm tạo và thêm danh sách, tìm kiếm theo tên, tìm kiếm theo số điện thoại.
 * @version 1.0
 * @date    2024-11-10
 * @author  Tâm Devil
 ***************************************************************************/

#include "Project_1_update.h"   // file header chứa các khai báo liên quan
#include <stdio.h>              // Dùng để xuất, nhập dữ liệu.
#include <stdlib.h>             // Dùng để quản lý bộ nhớ động.
#include <string.h>             // Dùng để thao tác trên chuỗi.
#include <ctype.h>              // Dùng để kiểm tra ký tự khoảng trắng.

/**
 * @brief   Thêm node được sắp xếp theo tên
 * @param   **ar    địa chỉ của con trỏ trỏ tới danh sách.
 * @param   *name   tên người dùng.
 * @param   age     tuổi người dùng.
 * @param   *addr   địa chỉ người dùng.
 * @param   *num    số điên thoại người dùng.
 * @return  node    Trả về con trỏ node nếu thêm danh sách thành công, trả về con trỏ NULL nếu thêm thất bại.
 */
node *AddNodeByName(node **arr, char *name, int age, char *addr, char *num){
    node *temp = (node*)malloc(sizeof(node));    // cấp phát động bộ nhớ cho con trỏ node
    if (temp == NULL)
    {
        printf("Khong cap phat duoc bo nho!\n");
        return NULL;
    }
    strcpy(temp->name, name);       // Hàm gán dữ liệu biến name vào temp->name
    temp->age = age;                // gán dữ liệu biến age vào temp->age
    strcpy(temp->addr, addr);       // Hàm gán dữ liệu biến addr vào temp->addr
    strcpy(temp->Num, num);         // Hàm gán dữ liệu biến num vào temp->Num
    temp->next = NULL;              // gán con trỏ next bằng con trỏ NULL

    /**
     * Kiểm tra nếu danh sách rỗng
     * hoặc tên của node đầu tiên trong danh sách có thứ tự lớn hơn hoặc bằng tên cần chèn
    */
    if (*arr == NULL || strcmp((*arr)->name, name) >= 0)
    {
        temp->next = *arr;  // gán node mới trỏ đến node đầu tiên trong danh sách.
        *arr = temp;        // gán temp là node đầu tiên trong danh sách.
        return temp;        // trả về con trỏ node mới chèn
    }

    // Gán con trỏ `current` trỏ đến node đầu tiên trong danh sách
    node *current = *arr;
    /**
     * Duyệt qua danh sách liên kết cho đến khi `current->next` là NULL
     * hoặc cho đến khi tìm thấy vị trí chèn (tên của node tiếp theo lớn hơn hoặc bằng `name`
     */
    while (current->next != NULL && strcmp(current->next->name, name) < 0)
    {
        // Di chuyển con trỏ `current` đến node tiếp theo
        current = current->next;
    }
    // chèn node mới vào sau current
    temp->next = current->next;
    current->next = temp;
    return temp;    // trả về con trỏ temp mới chèn
}
/**
 * @brief   Thêm node được sắp xếp theo sô điện thoại.
 * @param   **ar    địa chỉ của con trỏ trỏ tới danh sách.
 * @param   *name   tên người dùng.
 * @param   age     tuổi người dùng.
 * @param   *addr   địa chỉ người dùng.
 * @param   *num    số điên thoại người dùng.
 * @return  node    Trả về con trỏ node nếu thêm danh sách thành công, trả về con trỏ NULL nếu thêm thất bại.
 */
node *AddNodeByPhone(node **arr, char *name, int age, char *addr, char *num){
    node *temp = (node*)malloc(sizeof(node));   // cấp phát động bộ nhớ cho con trỏ node
    if (temp == NULL)
    {
        printf("Khong cap phat duoc bo nho!\n");
        return NULL;
    }
    strcpy(temp->name, name);       // Hàm gán dữ liệu biến name vào temp->name
    temp->age = age;                // gán dữ liệu biến age vào temp->age
    strcpy(temp->addr, addr);       // Hàm gán dữ liệu biến addr vào temp->addr
    strcpy(temp->Num, num);         // Hàm gán dữ liệu biến num vào temp->Num
    temp->next = NULL;              // Gán con trỏ next bằng con trỏ NULL.

     /**
     * Kiểm tra nếu danh sách rỗng
     * hoặc số điện thoại của node đầu tiên trong danh sách có thứ tự lớn hơn hoặc bằng số điện thoại cần chèn
    */
    if (*arr == NULL || strcmp((*arr)->Num, num) >= 0)
    {

        temp->next = *arr;      // gán node mới trỏ đến node đầu tiên trong danh sách.
        *arr = temp;            // gán temp là node đầu tiên trong danh sách.
        return temp;            // trả về con trỏ node mới chèn
    }
    // Gán con trỏ `current` trỏ đến node đầu tiên trong danh sách
    node *current = *arr;

    /**
     * Duyệt qua danh sách liên kết cho đến khi `current->next` là NULL
     * hoặc cho đến khi tìm thấy vị trí chèn số điện thoại của node tiếp theo lớn hơn hoặc bằng `num`
     */
    while (current->next != NULL && strcmp(current->next->Num, num) < 0)
    {
        // Di chuyển con trỏ `current` đến node tiếp theo
        current = current->next;
    }
    // chèn node mới vào sau current
    temp->next = current->next;
    current->next = temp;
    return temp;      // trả về con trỏ temp mới chèn
}

/**
 * @brief   Tạo và ghi đè lên file.
 * @param   *filename   tên file cần tạo.
 * @return  int         0 nếu file tạo không thành công, 1 nếu file tạo thành công.
 */
int CreateFile(char *filename){
    // Mở file với chế độ "append"
    FILE *file = fopen(filename, "a");

    // Kiểm tra nếu không thể mở file
    if (file == NULL)
    {
        printf("Khong the tao file!\n");
        return 0;       // trả về 0 nếu không thể tạo hoặc mở file
    }

    // di chuyển con trỏ file đến cuối file
    fseek(file, 0, SEEK_END);
    // Kiểm tra nếu file trống
    if (ftell(file) == 0)
    {
        fprintf(file, "Ho va ten, Tuoi, Dia chi, So dien thoai\n");
    }

    // Khai báo các biến để lưu thông tin người dùng.
    int n, age; char name[50]; char addr[100]; char num[15];
    // nhập số lượng người muốn thêm
    printf("Nhap so luong nguoi: ");
    scanf("%d", &n);
    getchar();  // xóa ký tự newline
    for (int i = 0; i < n; i++)
    {
        printf("Nhap ho va ten: ");
        fgets(name,sizeof(name),stdin);
        name[strcspn(name,"\n")] = '\0';    // xóa ký tự newline ở cuối tên
        fprintf(file,"%s, ",name);

        printf("Nhap tuoi: ");
        scanf("%d",&age);
        getchar();          // xóa ký tự newline ở cuối tuổi
        fprintf(file,"%d, ",age);

        printf("Nhap dia chi: ");
        fgets(addr,sizeof(addr),stdin);
        addr[strcspn(addr,"\n")] = '\0';    // xóa ký tự newline ở cuối địa chỉ
        fprintf(file,"%s, ",addr);  

        printf("Nhap so dien thoai: ");
        fgets(num,sizeof(num),stdin);
        num[strcspn(num,"\n")] = '\0';      // xóa ký tự newline ở cuối số điện thoại
        fprintf(file,"%s\n",num);
    }
    // đóng file sau khi ghi xong
    fclose(file);
    // trả về 1 khi hoàn tất
    return 1;
}

// hàm xóa khoảng trắng chuỗi
void RemoveSpace(char *str){
    int count = 0;
    for (int i = 0;str[i]; i++)
    {
        if (!isspace(str[i]))       // kiểm tra chuỗi nếu có khoảng trắng 
        {
            str[count++] = str[i];  // dịch con trỏ sang vị trí tiếp theo
        }
    }
        str[count] = '\0';  //gán ký tự kết thúc chuỗi cho vị trí cuối cùng.
}

/**
 * @brief   Đọc file theo tên.
 * @param   **arr       con trỏ cấp 2 để lưu dữ liệu.
 * @param   *filename   tên file cần đọc.
 * @return  void
 */
void ReadFileByName(node** arr, char *filename){
    // mở file với chế độ đọc "read"
    FILE *file = fopen(filename, "r");
    // Kiểm tra nếu file trống
    if (file == NULL)
    {
        printf("Khong the doc file!\n");
        return;
    }
    // khai báo các biến tạm để lưu dữ liệu đọc được
    char line[200]; char name[50]; char addr[100]; char num[15]; int age;
    fgets(line, sizeof(line), file); // đọc và bỏ qua tiêu đề
    while (fgets(line, sizeof(line), file)) // đọc các dòng còn lại của file
    {
        char *token = strtok(line, ",");    // hàm tách ký tự đến "," lấy tên
        strcpy(name, token);    // lưu tên
        RemoveSpace(name);      // xóa khoảng trắng của tên

        token = strtok(NULL, ",");      // tách lấy tuổi
        age = atoi(token);          // chuyển từ chuỗi sang số

        token = strtok(NULL, ",");  // tách lấy địa chỉ
        strcpy(addr, token);        // lưu địa chỉ

        token = strtok(NULL, ",");  // tách lấy số điện thoại
        strcpy(num, token);         // lưu số điện thoại
        RemoveSpace(num);           // xóa khoảng trắng của số điện thoại

        AddNodeByName(arr, name, age, addr, num);   // thêm node vào danh sách liên kết theo tên
    }
    // đống file sau khi đọc xong
    fclose(file);
}

void ReadFileByPhone(node** arr, char *filename){
    // mở file với chế độ đọc "read"
    FILE *file = fopen(filename, "r");
    if (file == NULL)       // Kiểm tra nếu file trống
    {
        printf("Khong the doc file!\n");
        return;
    }
    // khai báo các biến tạm để lưu dữ liệu đọc được
    char line[200]; char name[50]; char addr[100]; char num[15]; int age;
    fgets(line, sizeof(line), file); // đọc và bỏ qua tiêu đề
    while (fgets(line, sizeof(line), file))     // đọc các dòng còn lại của file
    {
        char *token = strtok(line, ",");    // hàm tách ký tự đến "," lấy tên
        strcpy(name, token);                // lưu tên
        RemoveSpace(name);                  // xóa khoảng trắng của tên

        token = strtok(NULL, ",");          // tách lấy tuổi
        age = atoi(token);                  // chuyển từ chuỗi sang số

        token = strtok(NULL, ",");          // tách lấy địa chỉ
        strcpy(addr, token);                // lưu địa chỉ

        token = strtok(NULL, ",");          // tách lấy số điện thoại
        strcpy(num, token);                 // lưu số điện thoại
        RemoveSpace(num);                   // xóa khoảng trắng của số điện thoại

        AddNodeByPhone(arr, name, age, addr, num);      //// thêm node vào danh sách liên kết theo số diện thoại
    }
    // đóng file sau khi đọc xong.
    fclose(file); 
}

/**
 * @brief   Hàm giải phóng bộ nhớ lưu danh sách.
 * @param   **arr con trỏ cấp 2 lưu danh sách.
 * @return  void
 */
void FreeList(node **arr){
    while (*arr != NULL)      // hàm lặp lại cho đến khi *arr bằng NULL
    {
        node *temp = *arr;      // gán node đầu tiên cho con trỏ temp
        *arr = (*arr)->next;    // trỏ con trỏ arr đến node tiếp theo    
        free(temp);             // giải phóng bộ nhớ con trỏ temp
    }
    
}

/**
 * @brief   Hàm cập nhật danh sách.
 * @param   **arr       con trỏ cấp 2 lưu danh sách.
 * @param   *filename   file lấy dữ liệu.
 * @return  void
 */
void UpdateFile(node **arr, char *filename){
    if (CreateFile(filename))      // kiểm tra nếu file được tạo
    {
        // giải phóng danh sách
        FreeList(arr);
        ReadFileByName(arr, filename);      // đọc file theo tên
        ReadFileByPhone(arr, filename);     // đọc file theo số điện thoại
        printf("Cap nhat file thanh cong!\n");
    }else
    printf("Cap nhat file khong thanh cong!\n"); 
}

/**
 * @brief   Hàm tạo cây nhị phân.
 * @param   *arr        con trỏ lưu danh sách.
 * @param   start       chỉ số bắt đầu.
 * @param   end         chỉ số kết thúc.
 * @return  centerpoint Trả về con trỏ centerpoint nếu tạo cây nhị phân thành công, trả về con trỏ NULL nếu tạo không thành công.
 */
centerpoint *BuildTree(node *arr, int start, int end){
    if (arr == NULL || start > end)     // kiểm tra nếu arr bằng NULL hoặc start lớn hơn end
    {
        return NULL;
    }
    centerpoint *root = (centerpoint*)malloc(sizeof(centerpoint));  // cấp phát động bộ nhớ cho con trỏ root
    if (root == NULL)
    {
        printf("Khong the cap phat bo nho!\n");
        return NULL;
    }
    int mid = start + (end - start) / 2;        // tính chỉ số chính giữa 
    node *current = arr;        // gán node đầu tiên cho con trỏ current
    for (int i = start; i < mid; i++)   // vòng lặp chạy từ start đến vị trí chính giữa (mid)
    {
        if (current->next == NULL)      // kiểm tra nếu node tiếp theo của con trỏ current là NULL
        {
            break;          // thoát vòng lặp
        }
        current = current->next;        // di chuyển con trỏ current tới node tiếp theo
    }
    
    strcpy(root->name, current->name);  // gán tên của con trỏ current sang con trỏ root
    root->age = current->age;           // gán tuổi của con trỏ current sang con trỏ root   
    strcpy(root->addr, current->addr);  // gán địa chỉ của con trỏ current sang con trỏ root
    strcpy(root->num, current->Num);    // gán số điện thoại của con trỏ current sang con trỏ root
    root->left = BuildTree(arr, start, mid -1); // tạo cây nhị phân con bên trái của node hiện tại.
    root->right = BuildTree(current->next, mid + 1, end);   // tạo cây nhị phân con bên phải của node hiện tại.
    return root; // trả về con trỏ root vừa tạo
}

/**
 * @brief   Hàm giải phóng bộ nhớ cây nhị phân
 * @param   *root con trỏ trỏ tới cây nhị phân
 * @return  void
 */
void FreeTree(centerpoint *root){
    if (root == NULL)   // kiểm tra nếu root bằng NULL
    {
        return;
    }
    free(root->left);   // giải phóng cây nhị phân con bên trái root.
    free(root->right);  // giải phóng cây nhị phân con bên phải root.
    free(root);         // giải phóng cây nhị phân chính root.
}

/**
 * @brief   Hàm tìm số lượng phần tử trong danh sách và gọi hàm buildtree để tạo cây nhị phân
 * @param   *arr con trỏ lưu danh sách liên kết
 * @return  con trỏ centerpoint
 */
centerpoint *CreateBiraryTree(node *arr){
    if (arr == NULL)        // kiểm tra nếu arr bằng NULL
    {
        printf("Mang rong!\n");
        return NULL;
    }
    int count = 0;
    node *current = arr;        // gán node đầu tiên cho con trỏ current
    while (current != NULL)     // lặp lại cho đến khi current bằng NULL
    {
        count++;
        current = current->next;        // di chuyển con trỏ current tới node tiếp theo
    }
    return BuildTree(arr, 0, count -1); // gọi hàm để tạo cây nhị phân
}

/**
 * @brief   Hàm tìm kiếm kết quả trên cây nhị phân bằng tên
 * @param   *root           con trỏ trỏ đến cây nhị phân
 * @param   *name           tên cần tìm
 * @return  centerpoint     Trả về con trỏ centerpoint nếu tìm kiếm thành công, trả về con trỏ NULL nếu tìm kiếm thất bại.
 */
centerpoint *SearchByName(centerpoint *root, char *name){
    if (root == NULL)       // kiểm tra nếu root bằng NULL
    {
        printf("Khong co cay nhi phan!\n");
        return NULL;
    }
    int cmp = strcasecmp(root->name, name);     // so sánh tên của con trỏ root và tên cần tìm
    if (cmp == 0)   // nếu giống nhau thì cmp bằng 0
    {
        printf("Ket qua\n");
        printf("Ho va ten: %s\n", root->name);
        printf("Tuoi: %d\n", root->age);
        printf("Dia chi: %s\n", root->addr);
        printf("So dien thoai: %s\n", root->num);
        return root;
    }else if (cmp > 0)  // nếu tên của con trỏ root lớn hơn
    {
        return SearchByName(root->left, name);     // đệ quy tìm bên trái con trỏ root
    }else
        return SearchByName(root->right, name);     // đệ quy tìm bên phải con trỏ root
}

/**
 * @brief   Hàm tìm kiếm kết quả trên cây nhị phân bằng số điện thoại
 * @param   *root           con trỏ trỏ đến cây nhị phân
 * @param   *name           tên cần tìm
 * @return  centerpoint     Trả về con trỏ centerpoint nếu tìm kiếm thành công, trả về con trỏ NULL nếu tìm kiếm thất bại.
 */
centerpoint *SearchByPhone(centerpoint *root, char *num){
    if (root == NULL)       // kiểm tra nếu con trỏ root bằng NULL
    {
        printf("Khong co cay nhi phan!\n");
        return NULL;
    }
    int cmp = strcasecmp(root->num, num); // so sánh số diện thoại của con trỏ root và số điện thoại cần tìm
    if (cmp == 0)  // bằng nhau thì cmp bằng 0
    {
        printf("Ket qua\n");
        printf("Ho va ten: %s\n", root->name);
        printf("Tuoi: %d\n", root->age);
        printf("Dia chi: %s\n", root->addr);
        printf("So dien thoai: %s\n", root->num);
        return root;
    }else if (cmp > 0)      // nếu số điện thoại của con trỏ root lớn hơn số điện thoại cần tìm 
    {
        return SearchByPhone(root->left, num);  // đệ quy tìm bên trái con trỏ root
    }else
        return SearchByPhone(root->right, num);     // đệ quy tìm bên trái con trỏ root
}

void PrintList(node *arr){
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
        case AddPerson:
            UpdateFile(&arr, "createfile.csv");
            break;

        case SearchName:
            char name[50];
            FreeList(&arr);
            ReadFileByName(&arr,"createfile.csv");
            PrintList(arr);
            printf("Nhap ten can tim: ");
            //scanf("%s", name);
            getchar();
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            root = CreateBiraryTree(arr);
            SearchByName(root, name);
            break;

        case SearchNum:
            char num[15];
            FreeList(&arr);
            ReadFileByPhone(&arr,"createfile.csv");
            PrintList(arr);
            printf("Nhap so dien thoai can tim: ");
            //scanf("%s", num);
            getchar();
            fgets(num, sizeof(num), stdin);
            num[strcspn(num, "\n")] = '\0';
            root = CreateBiraryTree(arr);
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
    
    FreeList(&arr);  // Giải phóng bộ nhớ
    FreeTree(root);
    return 0;
}
