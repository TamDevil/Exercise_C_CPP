# 1. Bitmask
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