#include <stdio.h>
#include <string.h>
#define READ_FILE_FAILED 1
typedef struct 
{
    char ho_va_ten[50];
    int Tuoi;
    char Dia_chi[50];
    char So_dien_thoai[15];
} Nguoi;

 
int main(int argc, char const *argv[])
{
    
 FILE *file = fopen("file.csv", "r");
 
 if (file == NULL)
 {
    printf("Doc file khong thanh cong!");
    return READ_FILE_FAILED;
 }
 char line[100];
 Nguoi nguoi;
 fgets(line,sizeof(line), file);
 while (fgets(line, sizeof(line), file) != NULL)
 {
    char *token = strtok(line, ",");
    if (token != NULL)
    {
        strcpy(nguoi.ho_va_ten, token);
    }
    token = strtok(NULL, ",");
    if (token != NULL)
    {
        nguoi.Tuoi = atoi(token);
    }
    token = strtok(NULL, ",");
    if (token != NULL)
    {
        strcpy(nguoi.Dia_chi, token);
    }
    token = strtok(NULL, ",");
    if (token != NULL)
    {
        strcpy(nguoi.So_dien_thoai, token);
    }
    
    printf("Ho va ten: %s\n", nguoi.ho_va_ten);
    printf("Tuoi: %d\n", nguoi.Tuoi);
    printf("Dia chi: %s\n", nguoi.Dia_chi);
    printf("So dien thoai: %s\n", nguoi.So_dien_thoai);
 }
 fclose(file);
    return 0;
}
