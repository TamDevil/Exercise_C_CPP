/***************************************************************************
 * @file    Project_1_update.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến tạo và tìm kiếm danh sách
 * @details File này cung cấp giao diện cho việc tạo danh sách, tìm kiếm theo tên, tìm kiếm theo số điện thoại.
 * @version 1.0
 * @date    2024-11-10
 * @author  Tâm Devil
 ***************************************************************************/



#ifndef PROJECT_1_UPDATE_H_
#define  PROJECT_1_UPDATE_H_

#include <stdint.h> // Thư viện chuẩn cho kiểu dữ liệu cố định.

/**************************************************************************
 * Định nghĩa hằng số cho giới hạn ký tự cho tên, địa chỉ, số điện thoại.
 * MAX_NAME_LENGTH: số ký tự tên tôi đa (30 ký tự).
 * MAX_ADDR_LENGTH: số ký tự địa chỉ tối đa (70).
 * MAX_NUM_LENGTH:  số ký tự số điện thoại tối đa (15).
 **************************************************************************/

#define MAX_NAME_LENGTH 30
#define MAX_ADDR_LENGTH 70
#define MAX_NUM_LENGTH 15

/**************************************************************************
 * Định nghĩa kiểu dữ liệu enum cho lựa chọn.
 * Addperson: Thêm danh sách.
 * SearchName: Tìm kiếm theo tên.
 * SearchNum: Tìm kiếm theo số điện thoại.
 * Exit: Thoát.
 **************************************************************************/
typedef enum{
    AddPerson = 1,                          
    SearchName,
    SearchNum,
    Exit
}choice;

/**************************************************************************
 * Định nghĩa cấu trúc node chứa thông tin về người dùng
 * name:    Tên người dùng.
 * age:     Tuổi người dùng.
 * addr:    Địa chỉ người dùng.
 * Num:     Số điện thoại người dùng.
 * *next:   con trỏ next.
 **************************************************************************/
typedef struct Node{
    char name[MAX_NAME_LENGTH];     
    int age;                        
    char addr[MAX_ADDR_LENGTH];     
    char Num[MAX_NUM_LENGTH];       
    struct Node *next;             
}node;

/***********************************************************************************
 * cấu trúc centerpoint chứa thông tin người dùng và con trỏ trỏ tới cây nhị phân
 *  * name:    Tên người dùng.
 * age:     Tuổi người dùng.
 * addr:    Địa chỉ người dùng.
 * Num:     Số điện thoại người dùng.
 * *left:   con trỏ left.
 * *right:  con trỏ right.
 ***********************************************************************************/
typedef struct centerpoint
{
    char name[MAX_NAME_LENGTH];     
    int age;                        
    char addr[MAX_ADDR_LENGTH];     
    char num[MAX_NUM_LENGTH];       
    struct centerpoint *left;       
    struct centerpoint *right;      
}centerpoint;
// Thêm node theo tên.
node *AddNodeByName(node **arr, char *name, int age, char *addr, char *num);

// Thêm node theo số điện thoại.
node *AddNodeByPhone(node **arr, char *name, int age, char *addr, char *num);

// Tạo và ghi đè lên file
int CreateFile(char *filename);

// xóa khoảng trắng của chuỗi
void RemoveSpace(char *str);

// Đọc file theo tên
void ReadFileByName(node** arr, char *filename);

// Đọc file theo số điện thoại
void ReadFileByPhone(node** arr, char *filename);

// Giải phóng danh sách
void FreeList(node **arr);

// Cập nhật danh sách
void UpdateFile(node **arr, char *filename);

// Hàm tạo cây nhị phân
centerpoint *BuildTree(node *arr, int start, int end);

// Giải phóng bộ nhớ cây nhị phân
void FreeTree(centerpoint *root);

// Tìm số lượng phần tử trong danh sách và gọi hàm BuildTree
centerpoint *CreateBiraryTree(node *arr);

// Tìm kiếm theo tên
centerpoint *SearchByName(centerpoint *root, char *name);

// Tìm kiếm theo số điện thoại
centerpoint *SearchByPhone(centerpoint *root, char *num);

// In danh sách
void PrintList(node *arr);
#endif  // PROJECT_1_UPDATE_H_