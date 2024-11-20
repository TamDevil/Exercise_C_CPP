#ifndef IOHWAB_REARLEFTBRAKECONTROL_H
#define IOHWAB_REARLEFTBRAKECONTROL_H

#include "Std_Types.h"

/**
 * @brief   Cấu hình cho bộ điều khiển phanh bánh sau trái.
 * @details Cấu trúc này chứa các thông số cần thiết để cấu hình phanh,
 *          bao gồm kênh điều khiển PWM và giá trị lực phanh tối đa.
 */
typedef struct {
    uint8_t Brake_Channel;      // Kênh PWM điều khiển phanh
    uint16_t Brake_MaxForce;   // Lực phanh tối đa (N)
} RearLeftBrakeDriver_ConfigType;

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh sau trái.
 * @details Hàm này thiết lập cấu hình ban đầu cho bộ điều khiển phanh.
 *          Nó sử dụng thông tin từ cấu trúc cấu hình được truyền vào.
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình phanh.
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_RearLeftBrakeControl_Init(const RearLeftBrakeDriver_ConfigType* ConfigPtr);

/**
 * @brief   Điều chỉnh lực phanh bánh sau trái.
 * @details Hàm này thiết lập giá trị lực phanh mong muốn cho bánh sau trái.
 *          Giá trị lực được truyền vào phải nằm trong khoảng cho phép.
 * @param   ForceValue  Giá trị lực phanh mong muốn (đơn vị: N).
 * @return  Std_ReturnType
 *          - E_OK: Thiết lập lực phanh thành công.
 *          - E_NOT_OK: Thiết lập lực phanh thất bại.
 */
Std_ReturnType IoHwAb_RearLeftBrakeControl_SetForce(float ForceValue);

#endif /* IOHWAB_REARLEFTBRAKECONTROL_H */
