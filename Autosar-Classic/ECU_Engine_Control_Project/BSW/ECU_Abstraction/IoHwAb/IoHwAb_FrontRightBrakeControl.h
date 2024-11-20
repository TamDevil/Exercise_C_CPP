#ifndef IOHWAB_FRONTRIGHTBRAKECONTROL_H
#define IOHWAB_FRONTRIGHTBRAKECONTROL_H

#include "Std_Types.h"

/**
 * @brief   Cấu hình cho bộ điều khiển phanh bánh trước phải.
 * @details Cấu trúc này chứa các thông số cần thiết để cấu hình phanh,
 *          bao gồm kênh điều khiển PWM và giá trị lực phanh tối đa.
 */
typedef struct {
    uint8_t Brake_Channel;      // Kênh PWM điều khiển phanh
    uint16_t Brake_MaxForce;   // Lực phanh tối đa (N)
} FrontRightBrakeDriver_ConfigType;

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh trước phải.
 * @details Hàm này thiết lập cấu hình ban đầu cho bộ điều khiển phanh.
 *          Nó sử dụng thông tin từ cấu trúc cấu hình được truyền vào.
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình phanh.
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_FrontRightBrakeControl_Init(const FrontRightBrakeDriver_ConfigType* ConfigPtr);

/**
 * @brief   Điều chỉnh lực phanh bánh trước phải.
 * @details Hàm này thiết lập giá trị lực phanh mong muốn cho bánh trước phải.
 *          Giá trị lực được truyền vào phải nằm trong khoảng cho phép.
 * @param   ForceValue  Giá trị lực phanh mong muốn (đơn vị: N).
 * @return  Std_ReturnType
 *          - E_OK: Thiết lập lực phanh thành công.
 *          - E_NOT_OK: Thiết lập lực phanh thất bại.
 */
Std_ReturnType IoHwAb_FrontRightBrakeControl_SetForce(float ForceValue);

#endif /* IOHWAB_FRONTRIGHTBRAKECONTROL_H */
