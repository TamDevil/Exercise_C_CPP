#include "IoHwAb_RearLeftWheelSpeedSensor.h"
#include "../MCAL/Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include <stdio.h>
#include <stdlib.h>

// Giả lập cấu hình của cảm biến tốc độ
static RearLeftSpeedSensor_ConfigType RearLeftSpeedSensor_CurrentConfig;

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh sau trái.
 * @details Hàm này nhận một cấu trúc cấu hình, lưu lại cấu hình cho cảm biến tốc độ, 
 *          và khởi tạo ADC để đọc giá trị từ cảm biến tốc độ. 
 * @param   ConfigPtr  Con trỏ đến cấu trúc cấu hình của cảm biến tốc độ bánh sau trái.
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Có lỗi trong quá trình khởi tạo (ví dụ: con trỏ cấu hình null).
 */
Std_ReturnType IoHwAb_RearLeftWheelSpeedSensor_Init(const RearLeftSpeedSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_RearLeftSpeedSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến tốc độ vào biến toàn cục
    RearLeftSpeedSensor_CurrentConfig.SpeedSensor_Channel = ConfigPtr->SpeedSensor_Channel;
    RearLeftSpeedSensor_CurrentConfig.SpeedSensor_MaxValue = ConfigPtr->SpeedSensor_MaxValue;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Adc_Channel = ConfigPtr->SpeedSensor_Channel;
    Adc_Init(&adcConfig);

    // In ra thông tin cấu hình cảm biến tốc độ
    printf("Rear Left Wheel Speed Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", RearLeftSpeedSensor_CurrentConfig.SpeedSensor_Channel);
    printf(" - Max Speed Value: %d km/h\n", RearLeftSpeedSensor_CurrentConfig.SpeedSensor_MaxValue);

    return E_OK;
}

/**
 * @brief   Đọc giá trị từ cảm biến tốc độ bánh sau trái.
 * @details Hàm này đọc giá trị từ cảm biến tốc độ (thông qua ADC) và chuyển đổi 
 *          giá trị ADC sang tốc độ thực tế (giả lập). 
 * @param   SpeedValue  Con trỏ đến biến lưu giá trị tốc độ đọc được từ cảm biến (đơn vị: km/h).
 * @return  Std_ReturnType
 *          - E_OK: Đọc thành công và trả về giá trị tốc độ.
 *          - E_NOT_OK: Có lỗi trong quá trình đọc (ví dụ: con trỏ NULL hoặc lỗi ADC).
 */
Std_ReturnType IoHwAb_RearLeftWheelSpeedSensor_Read(float* SpeedValue) {
    if (SpeedValue == NULL) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị từ kênh ADC
    uint16_t adcValue = 0;
    if (Adc_ReadChannel(RearLeftSpeedSensor_CurrentConfig.SpeedSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang tốc độ (giả lập)
    *SpeedValue = ((float)adcValue / 1023.0f) * RearLeftSpeedSensor_CurrentConfig.SpeedSensor_MaxValue;

    // In ra giá trị tốc độ
    printf("Reading Rear Left Wheel Speed Sensor (ADC Channel %d): Speed = %.2f km/h\n",
           RearLeftSpeedSensor_CurrentConfig.SpeedSensor_Channel, *SpeedValue);

    return E_OK;
}