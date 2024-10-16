#include <stdio.h>

#define CREATE_FILE_FAILED 1
typedef struct
{
    char Ho_va_ten[50];
    int Tuoi;
    char Dia_chi[50];
    char So_dien_thoai[15];
} Nguoi;

Nguoi nguoi[] = {
    {"Anh", 23, "TP.HCM", "0920158302"},
    {"Ngoc", 20, "Ha Noi", "0123539291"},
    {"An", 18, "Da Nang", "0373512236"},
    {"Tu", 22, "Binh Dinh", "0898232163"},
    {"Binh", 25, "Can Tho", "0232163820"},
    {"Nhung", 22, "Dak Lak", "0829472934"}
};
int main(int argc, char const *argv[])
{
    
FILE *file = fopen("file.csv", "w");
if (file == NULL)
{
    printf("Tao file khong thanh cong!");
    return CREATE_FILE_FAILED;
}
fprintf(file, "Ho va ten, Tuoi, Dia chi, So dien thoai\n");
for (int i = 0; i < sizeof(nguoi) / sizeof(nguoi[0]); i++)
{
fprintf(file, "%s, %d, %s,%s\n", nguoi[i].Ho_va_ten, nguoi[i].Tuoi, nguoi[i].Dia_chi, nguoi[i].So_dien_thoai);
}
fclose(file);
printf("Tao file thanh cong!");
    return 0;
}


