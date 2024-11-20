#include "IoHwAb_RearLeftBrakeControl.h"
#include "Pwm.h"  // Gọi API PWM từ MCAL
#include <stdio.h>
#include <stdlib.h>

// Giả lập cấu hình RearLeftBrakeDriver
static RearLeftBrakeDriver_ConfigType RearLeftBrakeDriver_CurrentConfig;

/**
 * @brief   Khởi tạo hệ thống điều khiển phanh bánh sau trái (RearLeftBrakeDriver).
 * @details Hàm này nhận một cấu trúc cấu hình, lưu lại cấu hình cho hệ thống điều khiển phanh,
 *          sau đó khởi tạo PWM để điều khiển phanh với các giá trị từ cấu hình.
 * @param   ConfigPtr  Con trỏ đến cấu trúc cấu hình RearLeftBrakeDriver, bao gồm kênh PWM và lực phanh tối đa.
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Có lỗi trong quá trình khởi tạo (ví dụ: con trỏ cấu hình null).
 */
Std_ReturnType IoHwAb_RearLeftBrakeControl_Init(const RearLeftBrakeDriver_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_RearLeftBrakeDriver_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình RearLeftBrakeDriver
    RearLeftBrakeDriver_CurrentConfig.Brake_Channel = ConfigPtr->Brake_Channel;
    RearLeftBrakeDriver_CurrentConfig.Brake_MaxForce = ConfigPtr->Brake_MaxForce;

    // Gọi API từ MCAL để khởi tạo PWM
    Pwm_ConfigType pwmConfig = {
        .Pwm_Channel = RearLeftBrakeDriver_CurrentConfig.Brake_Channel,
        .Pwm_Period = 1000, // 1 giây (1000ms)
        .Pwm_DutyCycle = 0  // Khởi tạo với duty cycle = 0%
    };
    Pwm_Init(&pwmConfig);

    // In ra thông tin cấu hình RearLeftBrakeDriver
    printf("Brake Driver Initialized with Configuration:\n");
    printf(" - Brake Channel: %d\n", RearLeftBrakeDriver_CurrentConfig.Brake_Channel);
    printf(" - Max Force: %d N\n", RearLeftBrakeDriver_CurrentConfig.Brake_MaxForce);

    return E_OK;
}

/**
 * @brief   Điều chỉnh lực phanh cho bánh sau trái.
 * @details Hàm này nhận một giá trị lực phanh và tính toán duty cycle tương ứng
 *          để điều khiển PWM cho phanh. Nếu giá trị lực phanh không hợp lệ,
 *          hàm sẽ trả về lỗi.
 * @param   ForceValue  Lực phanh cần thiết (đơn vị: N), phải nằm trong phạm vi từ 0 đến lực phanh tối đa.
 * @return  Std_ReturnType
 *          - E_OK: Điều chỉnh lực phanh thành công.
 *          - E_NOT_OK: Lực phanh không hợp lệ (vượt quá giới hạn hoặc âm).
 */
Std_ReturnType IoHwAb_RearLeftBrakeControl_SetForce(float ForceValue) {
    // Kiểm tra giá trị lực phanh hợp lệ
    if (ForceValue < 0.0f || ForceValue > RearLeftBrakeDriver_CurrentConfig.Brake_MaxForce) {
        printf("Error: Force value %.2f N out of range (Max: %d N).\n", ForceValue, RearLeftBrakeDriver_CurrentConfig.Brake_MaxForce);
        return E_NOT_OK;
    }

    // Tính toán tỷ lệ nhiệm vụ (duty cycle) dựa trên lực phanh
    uint16_t dutyCycle = (uint16_t)((ForceValue / RearLeftBrakeDriver_CurrentConfig.Brake_MaxForce) * 100);

    // Gọi API từ MCAL để cài đặt duty cycle của PWM
    Pwm_SetDutyCycle(RearLeftBrakeDriver_CurrentConfig.Brake_Channel, dutyCycle);

    // In ra giá trị lực phanh đã đặt
    printf("Setting Brake Force to %.2f N on Channel %d\n", ForceValue, RearLeftBrakeDriver_CurrentConfig.Brake_Channel);

    return E_OK;
}
