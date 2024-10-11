#include <stdio.h>
#include <setjmp.h>
enum ErrorCodes { NO_ERROR, FILE_ERROR, NETWORK_ERROR, CALCULATION_ERROR };
jmp_buf check;
int error_check;
char *error_message;
#define TRY if((error_check =setjmp(check)) == NO_ERROR)
#define CATCH(error) else if (error_check == error)
#define THROW(error,cmd)\
do{\
    error_message = cmd;\
    longjmp(check, error);\
}while(0)

void readFile() {
    printf("Doc file...\n");
    THROW(FILE_ERROR, "Loi doc FILE: FILE khong ton tai.");
}

void networkOperation() {
    printf("Loading...\n");
    THROW(NETWORK_ERROR, "Loi mang: Khong the ket noi voi may chu.");
}

void calculateData() {
    printf("calculating...\n");
    THROW(CALCULATION_ERROR, "Loi tinh toan: Phep tinh khong hop le.");
}
int main(int argc, char const *argv[])
{
     TRY {
        readFile();
        networkOperation();
        calculateData();
    }CATCH(FILE_ERROR) {
        printf("%s\n", error_message);}
    CATCH(NETWORK_ERROR) {
        printf("%s\n", error_message);}
    CATCH(CALCULATION_ERROR) {
        printf("%s\n", error_message);}
    return 0;
}
