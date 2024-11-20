#ifndef IOHWAB_REARLEFTWHEELSPEEDSENSOR_H
#define IOHWAB_REARLEFTWHEELSPEEDSENSOR_H

#include "Std_Types.h"


/**
 * @brief   Cấu hình cho cảm biến tốc độ bánh sau trái.
 * @details Cấu trúc này chứa các thông tin cần thiết để cấu hình cảm biến tốc độ,
 *          bao gồm kênh ADC được sử dụng và giá trị tốc độ tối đa.
 */
typedef struct {
    uint8_t SpeedSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến tốc độ
    uint16_t SpeedSensor_MaxValue; // Giá trị tốc độ tối đa mà cảm biến có thể đọc (km/h)
} RearLeftSpeedSensor_ConfigType;

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh sau trái.
 * @details Hàm này thực hiện cấu hình ban đầu cho cảm biến tốc độ, bao gồm
 *          việc gán kênh ADC và các tham số liên quan dựa trên cấu hình được cung cấp.
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình cảm biến tốc độ.
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_RearLeftWheelSpeedSensor_Init(const RearLeftSpeedSensor_ConfigType* ConfigPtr);

/**
 * @brief   Đọc giá trị tốc độ từ cảm biến bánh sau trái.
 * @details Hàm này lấy dữ liệu từ cảm biến tốc độ bánh sau trái và trả về
 *          giá trị tốc độ hiện tại qua con trỏ tham chiếu.
 * @param   SpeedValue  Con trỏ để lưu giá trị tốc độ đọc được (đơn vị: km/h).
 * @return  Std_ReturnType
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Đọc thất bại.
 */
Std_ReturnType IoHwAb_RearLeftWheelSpeedSensor_Read(float* SpeedValue);

#endif /* IOHWAB_REARLEFTWHEELSPEEDSENSOR_H */
