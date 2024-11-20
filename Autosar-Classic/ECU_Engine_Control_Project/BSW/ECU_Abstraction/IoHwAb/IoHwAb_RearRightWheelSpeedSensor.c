#include "IoHwAb_RearRightWheelSpeedSensor.h"
#include "../MCAL/Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include <stdio.h>
#include <stdlib.h>

// Giả lập cấu hình của cảm biến tốc độ
static RearRightSpeedSensor_ConfigType RearRightSpeedSensor_CurrentConfig;

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh sau phải.
 * @details Hàm này nhận một cấu trúc cấu hình, lưu lại cấu hình cho cảm biến tốc độ, 
 *          và khởi tạo ADC để đọc giá trị từ cảm biến tốc độ. 
 * @param   ConfigPtr  Con trỏ đến cấu trúc cấu hình của cảm biến tốc độ bánh sau phải.
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Có lỗi trong quá trình khởi tạo (ví dụ: con trỏ cấu hình null).
 */
Std_ReturnType IoHwAb_RearRightWheelSpeedSensor_Init(const RearRightSpeedSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to RearRightIoHwAb_SpeedSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến tốc độ vào biến toàn cục
    RearRightSpeedSensor_CurrentConfig.SpeedSensor_Channel = ConfigPtr->SpeedSensor_Channel;
    RearRightSpeedSensor_CurrentConfig.SpeedSensor_MaxValue = ConfigPtr->SpeedSensor_MaxValue;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Adc_Channel = ConfigPtr->SpeedSensor_Channel;
    Adc_Init(&adcConfig);

    // In ra thông tin cấu hình cảm biến tốc độ
    printf("Rear Right Wheel Speed Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", RearRightSpeedSensor_CurrentConfig.SpeedSensor_Channel);
    printf(" - Max Speed Value: %d km/h\n", RearRightSpeedSensor_CurrentConfig.SpeedSensor_MaxValue);

    return E_OK;
}

/**
 * @brief   Đọc giá trị từ cảm biến tốc độ bánh sau phải.
 * @details Hàm này đọc giá trị từ cảm biến tốc độ (thông qua ADC) và chuyển đổi 
 *          giá trị ADC sang tốc độ thực tế (giả lập). 
 * @param   SpeedValue  Con trỏ đến biến lưu giá trị tốc độ đọc được từ cảm biến (đơn vị: km/h).
 * @return  Std_ReturnType
 *          - E_OK: Đọc thành công và trả về giá trị tốc độ.
 *          - E_NOT_OK: Có lỗi trong quá trình đọc (ví dụ: con trỏ NULL hoặc lỗi ADC).
 */
Std_ReturnType IoHwAb_RearRightWheelSpeedSensor_Read(float* SpeedValue) {
    if (SpeedValue == NULL) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị từ kênh ADC
    uint16_t adcValue = 0;
    if (Adc_ReadChannel(RearRightSpeedSensor_CurrentConfig.SpeedSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang tốc độ (giả lập)
    *SpeedValue = ((float)adcValue / 1023.0f) * RearRightSpeedSensor_CurrentConfig.SpeedSensor_MaxValue;

    // In ra giá trị tốc độ
    printf("Reading Front Left Wheel Speed Sensor (ADC Channel %d): Speed = %.2f km/h\n",
           RearRightSpeedSensor_CurrentConfig.SpeedSensor_Channel, *SpeedValue);

    return E_OK;
}
