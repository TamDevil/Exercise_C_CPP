# Quá trình biên dịch chương trình của Compiler
![alt text](image.png)
## Tiền xử lý (Preprocessing)
**Chức năng**: Xử lý các chỉ thị tiền xử lý như #include (nhúng tệp header), #define (định nghĩa macro), và loại bỏ chú thích.
**Kết quả**: Mã nguồn đã được mở rộng và chuẩn bị cho bước tiếp theo.
**Tiền xử lý**
```
gcc -E main.c -o main.i
```
## Biên dịch (Compilation)
**Chức năng**: Chuyển đổi mã nguồn đã qua tiền xử lý thành mã assembly.
**Kết quả**: Tệp mã assembly, thường có phần mở rộng .s.
**Biên dịch**
```
gcc -S main.i -o main.s
```
## Dịch hợp ngữ (Assembly)
**Chức năng**: Chuyển đổi mã assembly thành mã máy (mã đối tượng).
**Kết quả**: Tệp mã đối tượng, thường có phần mở rộng .o (trên Linux) hoặc .obj (trên Windows).
**Dịch hợp ngữ**
```
gcc -c main.s -o main.o
```
## Liên kết (Linking)
**Chức năng**: Kết hợp các mã đối tượng và thư viện để tạo ra tệp thực thi.
**Kết quả**: Tệp thực thi hoàn chỉnh, có thể chạy trên hệ thống.
**Liên kết**
```
gcc main.o -o main
```
# Các loại Macro
## Macro Hằng số
Macro hằng số được sử dụng để định nghĩa một giá trị cố định (hằng số) mà không cần phải khai báo biến.
**Ví dụ**:
```c
#define PI 3.14159
#include <stdio.h>
int main() {
    printf("Giá trị của PI là: %f\n", PI);
    return 0;
}
```

## Macro Hàm
Macro hàm cho phép bạn định nghĩa các đoạn mã có tham số. Chúng hoạt động giống như các hàm nhưng không cần phải khai báo kiểu dữ liệu.
**Ví dụ**:
```c
#define SQUARE(x) ((x) * (x))
#include <stdio.h>
int main() {
    int num = 5;
    printf("Bình phương của %d là: %d\n", num, SQUARE(num));
    return 0;
}
```
## Macro điều kiện
**#ifdef**: Kiểm tra xem macro đã được định nghĩa hay chưa. Nếu có, mã trong khối này sẽ được biên dịch.
```c
#ifdef DEBUG
    printf("Chương trình đang chạy ở chế độ gỡ lỗi.\n");
#endif
```
**#ifndef**: Kiểm tra xem macro chưa được định nghĩa. Nếu chưa, mã trong khối này sẽ được biên dịch.
```c
#ifndef NDEBUG
    printf("Chương trình không đang ở chế độ gỡ lỗi.\n");
#endif
```
**#if**: Kiểm tra một biểu thức điều kiện. Nếu biểu thức này đánh giá thành true (khác 0), mã trong khối sẽ được biên dịch.
```c
#define VERSION 2
#if VERSION >= 2
    printf("Phiên bản 2 hoặc cao hơn.\n");
#endif
```
**#else**: Cung cấp một nhánh khác nếu điều kiện trong #ifdef, #ifndef, hoặc #if không đúng.
```c
#ifdef DEBUG
    printf("Chương trình đang chạy ở chế độ gỡ lỗi.\n");
#else
    printf("Chương trình không đang ở chế độ gỡ lỗi.\n");
#endif
```
**#elif**: Tương tự như else if trong cấu trúc điều kiện thông thường. Nó cho phép bạn kiểm tra nhiều điều kiện liên tiếp.
```c
#define DEBUG_LEVEL 2
#if DEBUG_LEVEL == 1
    printf("Chế độ gỡ lỗi mức 1.\n");
#elif DEBUG_LEVEL == 2
    printf("Chế độ gỡ lỗi mức 2.\n");
#else
    printf("Không có chế độ gỡ lỗi.\n");
#endif
```
**#endif**: Đánh dấu kết thúc của một khối điều kiện bắt đầu bằng #if, #ifdef, hoặc #ifndef.
## Variadic Macro
Variadic Macro được dùng khi không xác định rõ số lượng tham số được truyền vào macro.
**Cú pháp**
Cú pháp để định nghĩa một variadic macro trong C là sử dụng dấu ... để chỉ định rằng macro có thể nhận nhiều tham số, cùng với __VA_ARGS__ để tham chiếu đến các tham số đó.
**Ví dụ**
```c
#include <stdio.h>
// Định nghĩa variadic macro
#define PRINT(...) printf(__VA_ARGS__)
int main() {
    // Sử dụng macro với các tham số khác nhau
    PRINT("Hello, %s!\n", "world");  // In ra: Hello, world!
    PRINT("Number: %d, Pi: %.2f\n", 42, 3.14); // In ra: Number: 42, Pi: 3.14
    return 0;
}
```
# STDARG
stdarg là một thư viện trong ngôn ngữ lập trình C cho phép bạn tạo hàm nhận số lượng đối số không xác định. Điều này hữu ích khi bạn không biết trước số lượng đối số mà một hàm sẽ nhận.
## Các macro chính trong stdarg
**va_start**: Khởi tạo con trỏ va_list để truy cập các đối số không xác định.
**va_arg**: Lấy giá trị của đối số tiếp theo từ danh sách các đối số.
**va_copy**: sao chép giá trị mà con trỏ va_list đang trỏ tới
**va_end**: Dọn dẹp con trỏ va_list khi không còn cần truy cập các đối số nữa.
**Ví dụ**
```c
#include <stdio.h>
#include <stdarg.h>
void printNumbers(int count, ...) {
    va_list args;
    va_start(args, count); // Khởi tạo con trỏ args
    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int); // Lấy từng số
        printf("%d ", num);
    }
    va_end(args); // Dọn dẹp con trỏ args
    printf("\n");
}
int main() {
    printNumbers(5, 1, 2, 3, 4, 5); // Gọi hàm với 5 số
    return 0;
}
```
**Giải thích**
Hàm printNumbers: Nhận một số nguyên count và một danh sách các số nguyên.
va_start(args, count): Khởi tạo args để bắt đầu lấy các đối số.
va_arg(args, int): Lấy từng đối số trong danh sách.
va_end(args): Giải phóng tài nguyên mà args đã chiếm dụng.
# Assert
Assert trong C là một công cụ kiểm tra điều kiện. Nếu điều kiện sai, chương trình dừng lại và báo lỗi; nếu đúng, chương trình tiếp tục chạy. Nó thường dùng để phát hiện lỗi trong quá trình phát triển.
**Ví dụ**
```c
#include <stdio.h>
#include <assert.h>
int main() {
    int x = 5;
    assert(x == 5);  // Điều kiện đúng, chương trình tiếp tục chạy
    printf("X is 5\n");
    assert(x == 10); // Điều kiện sai, chương trình sẽ bị dừng
    printf("This line will not be printed\n");
    return 0;
}
```
Khi điều kiện sai, chương trình sẽ in ra thông báo giống như sau:
```c
Assertion failed: (x == 10), function main, file example.c, line 10.
```
Có thể ghi chú thêm lỗi cụ thể như:
```c
assert(x == 5 && "loi: x phai bang 5");
```
# Bitmask
- Bitmask là một kỹ thuật sử dụng các toán tử bitwise để thao tác các bit cụ thể của một số.
- Bitwise là các toán tử thao tác trực tiếp trên các bit của số.
**Các toán tử gồm:**
- **AND (&)**: Thực hiện phép AND logic trên mỗi cặp bit tương ứng của hai số. Kết quả sẽ là 1 chỉ khi cả hai bit là 1.
```c
5 & 3   // 0101 & 0011 => 0001 (1)
```
- **OR (|)**: Thực hiện phép OR logic trên mỗi cặp bit. Kết quả là 1 nếu ít nhất một trong hai bit là 1.
```c
5 | 3   // 0101 | 0011 => 0111 (7)
```
- **XOR (^)**: Thực hiện phép XOR (Exclusive OR) logic trên mỗi cặp bit. Kết quả là 1 nếu hai bit khác nhau.
```c
5 ^ 3   // 0101 ^ 0011 => 0110 (6)
```
- **NOT (~)**: Thực hiện phép đảo bit, tất cả các bit 1 trở thành 0 và ngược lại.
```c
~5   // ~0101 => 1010 
```
- **Dịch trái (<<)**: Dịch các bit sang trái một số lượng chỉ định. Các bit ở bên phải bằng 0.
```c
5 << 1   // 0101 << 1 => 1010 (10)
```
- **Dịch phải (>>)**: Dịch các bit sang phải. Các bit ở bên trái có thể được lấp đầy bằng 0 (nếu là số không dấu) hoặc 1 (nếu là số dấu).
```c
5 >> 1   // 0101 >> 1 => 0010 (2)
```
**Các thao tác với bitmask**
**Kiểm tra một bit**: Dùng phép AND (&) để kiểm tra xem bit tại một vị trí có phải là 1 không.
```c
int number = 5;  // 0101
int check = 1 << 2;  // check: 0100
if (number & check) {
    // Bit thứ 2 là 1
}
```
**Thiết lập một bit (Set a bit)**: Dùng phép OR (|) để đặt một bit cụ thể thành 1.
```c
int number = 5;  // 0101
int set = 1 << 1;  // set: 0010
number = number | set;  // Kết quả: 0111 (7)
```
**Xóa một bit (Clear a bit)**: Dùng phép AND với mặt nạ đảo (~) để đặt một bit cụ thể thành 0.
```c
int number = 7;  // 0111
int clear = 1 << 1;  // clear: 1101
number = number & ~clear;  // Kết quả: 0101 (5)
```
**Đảo một bit (Toggle a bit)**: Dùng phép XOR (^) để chuyển đổi một bit (từ 0 thành 1 hoặc ngược lại).
```c
int number = 5;  // 0101
int toggle = 1 << 1;  // toggle: 0010
number = number ^ toggle;  // Kết quả: 0111 (7)
```
**Bit field** 
Bit field giúp chỉ định số bit cần sử dụng mà không cần dùng hết số lượng bit của 1 kiểu dữ liệu.
```c
struct {
    unsigned int is_on : 1;  // Chỉ dùng 1 bit cho is_on
    unsigned int value : 4;  // Dùng 4 bit cho value
} status;
```
**Chú ý**: Thông thường khi dùng bit field cần đi chung với struct hoặc union để nhóm các biến lại với nhau với cùng không gian bộ nhớ.
Nếu không có struct hoặc union, không có cách nào để bảo đảm rằng các trường này sẽ chia sẻ chung 1 byte và sử dụng chỉ một phần của byte đó.
# Con trỏ (Pointer)
Con trỏ là một biến lưu địa chỉ của một đối tượng bất kỳ (biến, hàm, con trỏ,...).
Kích thước của con trỏ phụ thuộc vào trình biên dịch hoặc cấu trúc của máy tính.
**Ví dụ**
Trên hệ thống 32-bit, con trỏ có kích thước là 4 byte.
Trên hệ thống 64-bit, con trỏ có kích thước là 8 byte.
## Con trỏ cơ bản
Con trỏ cơ bản là con trỏ có 1 kiểu dữ liệu nào đó (int, float, char,...).
**Ví dụ**
```c
#include <stdio.h>
int main() {
    int x = 10;       // Biến thông thường
    int *ptr = &x;    // Con trỏ lưu địa chỉ của biến x
    float y = 3.5;
    float *ptr1 = &y;
    return 0;
}
```
**Chú ý** không nên khai báo mà không gán giá trị cho con trỏ sẽ làm nó trỏ tới địa chỉ không mong muốn.
**tác dụng**:
Truyền tham chiếu tới biến để thay đổi giá trị của biến bên trong một hàm mà không cần trả về.
Truy cập và thay đổi dữ liệu của các biến toàn cục hoặc ngoài phạm vi của hàm.
## Con trỏ void
Con trỏ void có thể lưu trữ địa chỉ của nhiều kiểu dữ liệu nhưng muốn lấy giá trị thì phải ép kiểu.
```c
#include <stdio.h>
int main() {
    int a = 10;
    float b = 20.5;
    void *ptr;      // Con trỏ void có thể trỏ tới bất kỳ kiểu dữ liệu nào
    ptr = &a;
    printf("Giá trị của a: %d\n", *(int *)ptr);  // Ép kiểu thành int*
    ptr = &b;
    printf("Giá trị của b: %.2f\n", *(float *)ptr);  // Ép kiểu thành float*
    return 0;
}
```
**Tác dụng**:
Con trỏ void thường được sử dụng trong các hàm xử lý bộ nhớ như malloc, calloc, vì hàm này cần trả về con trỏ mà có thể được ép kiểu để trỏ tới bất kỳ loại dữ liệu nào.
## Con trỏ mảng
Con trỏ có thể trỏ tới mảng, và con trỏ tới mảng chứa địa chỉ của phần tử đầu tiên của mảng.
```c
#include <stdio.h>
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;    // Con trỏ trỏ tới mảng
    for (int i = 0; i < 5; i++) {
        printf("Giá trị của arr[%d]: %d\n", i, *(ptr + i));
    }
    return 0;
}
```
**Tác dung**:
Duyệt qua các phần tử của mảng bằng cách sử dụng con trỏ thay vì chỉ số
## Con trỏ hàm
Con trỏ hàm là con trỏ trỏ tới một hàm và có thể được dùng để gọi hàm đó.
```c
#include <stdio.h>
void say_hello() {
    printf("Hello, world!\n");
}
int main() {
    void (*ptr)();    // Con trỏ hàm
    ptr = say_hello;  // Gán địa chỉ của hàm cho con trỏ
    ptr();            // Gọi hàm thông qua con trỏ
    return 0;
}
```
**Tác dung**:
Con trỏ hàm cho phép gọi các hàm thông qua địa chỉ của chúng, giúp tối ưu hóa các thao tác với hàm và triển khai tính năng callback.
Nó rất hữu ích trong các thiết kế hệ thống plugin, thư viện, hoặc API, nơi mà hàm được truyền vào dưới dạng đối số.
## Con trỏ đến con trỏ
Con trỏ đến con trỏ là con trỏ chứa địa chỉ của một con trỏ khác.
```c
#include <stdio.h>
int main() {
    int x = 10;
    int *ptr1 = &x;    // Con trỏ trỏ tới x
    int **ptr2 = &ptr1; // Con trỏ trỏ tới ptr1
    return 0;
}
```
**Tác dụng**:
Con trỏ đến con trỏ được sử dụng khi bạn cần quản lý một cấp độ trừu tượng cao hơn, chẳng hạn như quản lý mảng con trỏ, mảng động hai chiều, hoặc các cấu trúc phức tạp liên quan tới con trỏ.
## Con trỏ hằng (constant pointer)
Con trỏ hằng là con trỏ mà bạn không thể thay đổi giá trị mà nó trỏ tới.
```c
#include <stdio.h>
int main() {
    int x = 10;
    const int *ptr = &x; // Không thể thay đổi giá trị của x thông qua con trỏ
    *ptr = 20;  // Lỗi, không thể thay đổi giá trị của x qua con trỏ
    return 0;
}
```
**Tác dụng**:
Con trỏ hằng là con trỏ mà địa chỉ của nó không thể thay đổi sau khi được gán, điều này giúp bảo vệ địa chỉ mà nó trỏ tới, tránh việc thay đổi ngẫu nhiên địa chỉ đó trong chương trình.
## Con trỏ tới hằng (Pointer to constant)
Hằng con trỏ là con trỏ mà địa chỉ mà nó lưu trữ không thể thay đổi, nhưng giá trị mà nó trỏ tới thì có thể thay đổi.
```c
#include <stdio.h>
int main() {
    int x = 10;
    int y = 20;
    int *const ptr = &x;  // ptr là hằng con trỏ trỏ tới x
    ptr = &y;  // Lỗi: Không thể thay đổi địa chỉ của ptr
    *ptr = 30;    // Có thể thay đổi giá trị mà ptr trỏ tới (thay đổi giá trị của x)
    return 0;
}
```
**Tác dung**:
Con trỏ tới hằng bảo vệ giá trị mà con trỏ trỏ tới, đảm bảo rằng giá trị không thể bị thay đổi thông qua con trỏ. Điều này rất hữu ích trong các chương trình mà dữ liệu cần được bảo vệ khỏi việc sửa đổi ngoài ý muốn.
## Con trỏ NULL
Con trỏ NULL là con trỏ không trỏ tới địa chỉ hợp lệ nào, được khởi tạo bằng hằng số NULL.
```c
#include <stdio.h>

int main() {
    int *ptr = NULL;  // Con trỏ NULL

    if (ptr == NULL) {
        printf("Con trỏ không trỏ tới địa chỉ hợp lệ.\n");
    }

    return 0;
}
```
**Tác dụng**:
Kiểm tra xem một con trỏ có trỏ tới vùng nhớ hợp lệ hay không trước khi truy cập giá trị tại địa chỉ đó.
# Goto
Goto là lệnh làm chương trình nhảy đến nhãn đã được định nghĩa. Nó thường được dùng để thoát nhiều vòng lặp mà không cần dùng lệnh break nhiều lần. Để sử dụng goto cần đặt nó trong cục bộ.
**Ví dụ**
```c
#include <stdio.h>
int main() {
    while(1){
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 5;j++){
                goto thoat; // nhảy tới nhãn
            }
        }
    }
    thoat:  // định nghĩa nhãn
    return 0;
}
```
# Thư viện setjmp.h
Thư viện setjmp.h cung cấp 2 hàm chính setjmp() và longjmp(). Thư viện này giúp thực hiện việc nhảy qua các phần của mã code.
setjmp(jmp_buf env): Hàm truyền vào biến kiểu jmp_buf và khi gọi lần đầu trong chương trình sẽ có giá trị bằng 0.
longjmp(jmp_buf env, int val): Hàm truyền vào biến kiểu jmp_buf và biến số nguyên, hàm nhảy vào setjmp và và gán giá trị cho nó dựa vào giá trị của val.
Có thể định nghĩa 3 từ khóa TRY, CATCH THROW để xử lý ngoại lệ
TRY dùng để bao đoạn mã có khả năng gây ra lỗi.
CATCH là nơi định nghĩa cách xử lý khi đoạn code gây ra lỗi
THROW khi được đọc sẽ dừng ngày đoạn mã đang chạy và nhảy vào CATCH để xử lý lỗi.
**Ví dụ**
```c
#include <stdio.h>
#include <setjmp.h> //thêm thư viện setjmp
jmp_buf buffer; // khai báo biến kiểu jmp_buf
void function() {
    printf("Trong hàm function\n");
    longjmp(buffer, 1); // Nhảy vào vị trí của setjmp và thay đổi giá trị của nó bằng 1
}

int main() {
    if (setjmp(buffer) == 0) {  // setjmp gọi lần đầu sẽ
        printf("Gọi hàm function\n");
        function(); 
    } else {
        printf("Quay lại từ longjmp\n");
    }
    return 0;
}
```
# Extern
Extern dùng với biến và hàm để cho trình biên dịch biết là chúng được định nghĩa ở một file khác và sẽ liên kết khi ở thời điểm liên kết **(Linker)** thay vì trong thời gian biên dịch **(Compiler)**.
## Khai báo biến với extern
```c
// file1.c
#include <stdio.h>
int a = 10; // Định nghĩa biến a
// file2.c
#include <stdio.h>
extern int a; // Khai báo biến a
int main() {
    printf("%d\n", a); // In ra giá trị của a
    return 0;
}
```
## Khai báo hàm với extern
```c
// file1.c
#include <stdio.h>
void myFunction() {
    printf("Hello from myFunction!\n");
}
// file2.c
#include <stdio.h>
extern void myFunction(); // Khai báo hàm
int main() {
    myFunction(); // Gọi hàm
    return 0;
}
```
# Static
static có hai loại static toàn cục và static cục bộ
- static cục bộ khi bạn khai báo biến trong hàm với từ khóa static.Khi bạn khai báo biến trong hàm với từ khóa static, biến đó sẽ giữ giá trị suốt thời gian chạy chương trình mà không bị mất đi khi hàm kết thúc.
**ví dụ**
```c
#include <stdio.h>
void myFunction() {
    static int count = 0; // Biến count sẽ được khởi tạo chỉ một lần
    count++;
    printf("Count: %d\n", count);
}
int main() {
    myFunction(); // In ra Count: 1
    myFunction(); // In ra Count: 2
    myFunction(); // In ra Count: 3
    return 0;
}
```
- static toàn cục khi bạn khai báo biến toàn cục hoặc khai báo hàm với từ khóa static. Hàm hoặc biến đó chỉ có thể gọi ở file mà nó định nghĩa. Điều này giúp tránh xung đột tên biến hoặc hàm khi có nhiều tệp nguồn trong chương trình.
**ví dụ**
```c
#include <stdio.h>
static void myStaticFunction() { // Hàm này chỉ có thể được gọi trong tệp này
    printf("Hello from static function!\n");
}
static int a = 10; // biến này chỉ có thể được gọi trong tệp này
int main() {
    myStaticFunction(); // Gọi hàm
    printf("%d\n", a); In giá trị a
    return 0;
}
```
# Register
Register là từ khóa giúp lưu trữ dữ liệu sang thanh ghi mà không thông qua RAM, giúp tăng tốc độ xử lý dữ liệu.
Register chỉ được dùng cho biến cục bộ.
Register thường dùng với vòng lặp để tăng tốc độ xử lý.
**Ví dụ**
```c
#include <stdio.h>

int main() {
    register int i;
    for (i = 0; i < 1000000; i++) {
        // Code thực hiện vòng lặp
    }
    printf("i = %d\n", i);
    return 0;
}
```
# Volatile
từ khóa volatile được sử dụng để khai báo rằng giá trị của một biến có thể thay đổi bất ngờ mà không phải do chương trình trực tiếp thay đổi. Điều này khiến trình biên dịch không được phép tối ưu hóa việc đọc hoặc ghi biến đó (xóa biến khỏi trình biên dịch).
**Ví dụ**
```c
#include <stdio.h>
volatile int flag = 0;
void interruptHandler() {
    flag = 1; // Hàm xử lý ngắt thay đổi giá trị của flag
}
int main() {
    while (flag == 0) {
        // Chờ flag thay đổi
    }
    printf("Flag changed!\n");
    return 0;
}
```
Nếu không dùng Volatile trình biên dịch sẽ tối ưu hóa biến flag và không thay đổi giá trị của nó khiến chương trình bị treo ở vòng lặp while.
# Struct
Struct là kiểu dữ liệu do người dùng định nghĩa, cho phép nhóm nhiều kiểu dữ liệu khác nhau thành một đối tượng.
Kích thước của struct bằng tổng kích thước các thành viên cộng với padding.
**Ví dụ**
```c
#include <stdio.h>
#include <string.h>
// Định nghĩa struct "SinhVien"
struct SinhVien {
    char ten[50];
    int tuoi;
    float diem_trung_binh;
};
int main() {
    // Khai báo một biến kiểu SinhVien
    struct SinhVien sv1;
    // Gán giá trị cho các thành phần của struct
    strcpy(sv1.ten, "Nguyen Van A");
    sv1.tuoi = 20;
    sv1.diem_trung_binh = 8.5;
    return 0;
}
```
Sự sắp xếp các thành viên có thể ảnh hưởng đến kích thước của struct.
**Ví dụ**
```c
struct C1 {
    char c;    // 1 byte
    int i;     // 4 bytes
    uint16_t u;  // 2 bytes
};
```
Kích thước có thể là 12 bytes do có thêm 3 byte đệm giữa char và int và 2 byte đệm sau khi lưu biến u.
```c
struct C2 {
    int i;  // 4 bytes
    char c;     // 1 bytes
    uint16_t u;    // 2 byte2
};
```
Kích thước có thể là 8 bytes, vì có 1 byte đệm giữa char và uint16_t
# Union
Union là kiểu dữ liệu giống với struct nhưng có 1 điểm đặc biệt là các thành viên trong union dùng chung vùng nhớ, tức là trong một thời điểm chỉ có một thành viên được lưu dữ liệu.
**Ví dụ**
```c
#include <stdio.h>
union DuLieu {
    int i;
    float f;
    char c;
};
int main() {
    union DuLieu dl;
    // Gán giá trị cho thành viên int
    dl.i = 10;
    // Gán giá trị cho thành viên float (sẽ ghi đè lên giá trị trước)
    dl.f = 3.14;
    // Gán giá trị cho thành viên char (sẽ ghi đè lên giá trị trước)
    dl.c = 'A';
    return 0;
}
```
Kích thước của Union bằng kích thước của phần tử lớn nhất.
```c
#include <stdio.h>
union DuLieu {
    int i;        // 4 bytes
    float f;      // 4 bytes
    char c;       // 1 byte
};
int main() {
    printf("Kích thước của union DuLieu: %lu bytes\n", sizeof(union DuLieu));
    return 0;
}
```
Kết quả sẽ là 4 bytes (do thành viên lớn nhất là int và float, đều chiếm 4 bytes).
# Kết hợp struct và union
Sự kết hợp giữa struct và union là một ứng dụng để truyền dữ liệu cho các vi xử lý.
**ví dụ**
```c
typedef union {
    struct {
        uint8_t id[2];
        uint8_t data[4];
        uint8_t check_sum[2];
    } data;
    uint8_t frame[8];
} Data_Frame;
```
Lúc này những thay đổi member của struct sẽ cập nhật vào biến frame của union do các thành viên của union dùng chung vùng nhớ.
# Memory layout
## Text segment (code segment)
- Chứa mã má của chương trình
- Chỉ cho phép đọc
- Chưa con trỏ char hay hằng số (MacOs)
## Data segment
- Chưa các biến toàn cục (biến thông thường, biến con trỏ) được khởi tạo với giá trị khác 0
- Chứa biến Static (global + local) được khởi tạo với giá trị khác 0
- Có thể đọc và ghi dữ liệu
- Vùng nhớ sẽ được thu hồi sau khi kết thúc chương trình
**Ví dụ**
```c
#include <stdio.h>
const int a = 10;            // read only 
char *ptr = "hello world";   // read only
static float b = 3.5        // data segment
void display(){
    static int a = 5;           // data segment
    printf("%d\n", a);
}

int main(){

    return 0;
}
```
## Bss segment
- Chứa các biến toàn cục (biến thông thường, biến con trỏ) mà có giá trị bằng 0 hoặc không được khởi tạo
- Chứa biến static (global + local) có giá trị bằng 0 hoặc không được khởi tạo
- Có thể đọc và ghi dữ liệu
- Vùng nhớ sẽ được thu hồi sau khi kết thúc chương trình  
**Ví dụ**
```c
#include <stdio.h>
const int a = 0;   // Bss segment
char *ptr = NULL;  // Bss segment
static float b;        // Bss segment
void display(){
    static int a = 0;           // Bss segment
    printf("%d\n", a);
}

int main(){

    return 0;
}
```
## Stack segment
- Chứa các biến cục bộ và tham số
- Có thể đọc và ghi
- Vùng nhớ sẽ bị thu hồi sau khi kết thúc gọi hàm
**ví dụ**
```c

#include <stdio.h>        
void display(){
    int a = 0;   stack segment        
    printf("%d\n", a);
}
int sum(int a, int b){
    int c = a + b;      //a,b,c    stack segment
    return c;           
}
int main(){
    int x, y;  // stack segment
    return 0;
}
```
## Heap
- Dùng để cấp phát động vùng nhớ khi chương trình đang chạy
- Không tự động thu hồi vùng nhớ mà phải thu hồi thủ công
- có thể đọc và ghi dữ liệu
- Các hàm malloc(), Calloc(), realloc(), free() dùng để cấp phát động và thu hồi vùng nhớ
**Ví dụ**
```c
#include <stdio.h>
#include <stdlib.h>


int main(){
    int n = 5;
    int *ptr = (int*)malloc(n*sizeof(int));       // Cấp phát động 5 phần tử kiểu int
}
```
Khi cấp phát động như vậy thì bản thân con trỏ là biến cục bộ nên nằm ở phân vùng stack nhưng các địa chỉ được cấp phát động thì được chứa ở phân vùng heap mà con trỏ đang trỏ tới
## Phân biệt malloc(), calloc(), realloc()
### malloc()
Hàm malloc() (memory allocation) được dùng để cấp phát bộ nhớ có kích thước xác định nhưng không khởi tạo giá trị.
**Ví dụ**
```c
#include <stdio.h>
#include <stdlib.h> 
int main() {
    int *arr;
    int n = 5;
    // Cấp phát bộ nhớ cho mảng kiểu int gồm n phần tử
    arr = (int*)malloc(n * sizeof(int));
    retunr 0;
}
```
### calloc()
Hàm calloc() (contiguous allocation) cũng cấp phát động bộ nhớ nhưng khởi tạo giá trị 0 cho các byte dữ liệu
```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr;
    int n = 5;
    // Cấp phát bộ nhớ cho mảng kiểu int gồm n phần tử và khởi tạo giá trị thành 0
    arr = (int*)calloc(n, sizeof(int));
    // In mảng
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]); // Tất cả giá trị sẽ là 0
    }
    return 0;
}
```
### realloc()
Hàm realloc() (reallocation) được sử dụng để thay đổi kích thước bộ nhớ đã cấp phát, nếu kích thước mới lớn hơn thì sao chép dữ liệu từ bộ nhớ cũ qua bộ nhớ mới
```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr;
    int n = 5;
    // Cấp phát bộ nhớ cho mảng kiểu int gồm n phần tử
    arr = (int*)malloc(n * sizeof(int));
    // Thay đổi kích thước mảng
    n = 10; // Tăng kích thước lên 10
    arr = (int*)realloc(arr, n * sizeof(int));
    return 0;
}
```
## So sánh
|Hàm|Cấp phát bộ nhớ|Khởi tạo giá trị|Thay đổi kích thước|Kích thước|Trả về|
|---|---|---|---|---|---|
|Malloc()|Có|Không|Không|Kích thước xác định|Con trỏ tới vùng nhớ được cấp phát|
|Calloc()|Có|Có(0)|Số phần tử và kích thước mỗi phần tử|Con trỏ tới vùng nhớ được cấp phát|
|Realloc()|Có|Không|Có|Kích thước mới|Con trỏ tới bộ nhớ mới|
## So sánh Stack và Heap
### Giống nhau
- Đều cấp phát bộ nhớ để lưu trữ dữ liệu
- Các biến trong 2 phân vùng đều có thể được truy cập
- Đều có thể bị tràn
### Khác nhau
- stack dùng cơ chế LIFO (last in, first out) trong khi phân bố tự do hơn
- Tốc độ truy cập của stack nhanh hơn heap do quản lý đơn giản hơn
- Kích thước của stack bị giới hạn khi chạy chương trình nhưng heap có thể linh động hơn.
- Bộ nhớ stack được thu hồi khi ra khỏi phạm vi còn heap phải thu hồi bộ nhớ thủ công(free).
