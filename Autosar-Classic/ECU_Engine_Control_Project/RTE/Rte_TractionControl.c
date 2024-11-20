/***************************************************************************
 * @file    Rte_TractionControl.c
 * @brief   Định nghĩa các API giao tiếp RTE cho hệ thống kiểm soát lực kéo.
 * @details File này cung cấp các API để đọc dữ liệu từ cảm biến tốc độ bánh xe
 *          và ghi lực phanh yêu cầu tới các bộ điều khiển phanh, cũng như khởi 
 *          tạo các module liên quan. Các API tương tác với lớp phần cứng (IoHwAb).
 * @version 1.0
 * @date    2024-11-05
 * @author  Tâm Devil
 ***************************************************************************/


#include "Rte_TractionControl.h"   
#include "IoHwAb_FrontLeftWheelSpeedSensor.h"   // API IoHwAb để đọc cảm biến tốc độ bánh trước trái
#include "IoHwAb_FrontRightWheelSpeedSensor.h"  // API IoHwAb để đọc cảm biến tốc độ bánh trước phải
#include "IoHwAb_RearLeftWheelSpeedSensor.h"    // API IoHwAb để đọc cảm biến tốc độ bánh sau trái
#include "IoHwAb_RearRightWheelSpeedSensor.h"   // API IoHwAb để đọc cảm biến tốc độ bánh sau phải
#include "IoHwAb_FrontLeftBrakeControl.h"       // API IoHwAb để điều khiển lực phanh bánh trước trái
#include "IoHwAb_FrontRightBrakeControl.h"      // API IoHwAb để điều khiển lực phanh bánh trước phải
#include "IoHwAb_RearLeftBrakeControl.h"        // API IoHwAb để điều khiển lực phanh bánh sau trái
#include "IoHwAb_RearRightBrakeControl.h"       // API IoHwAb để điều khiển lực phanh bánh sau phải
#include "Std_Types.h"                          // Định nghĩa kiểu dữ liệu tiêu chuẩn


/**
 * @brief   Đọc tốc độ từ cảm biến bánh trước trái.
 * @details Hàm đọc dữ liệu tốc độ từ cảm biến bánh trước trái thông qua lớp IoHwAb.
 * @param   Speed: Con trỏ tới biến nhận giá trị tốc độ (km/h).
 * @return  Std_ReturnType: 
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Đọc thất bại (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpFrontLeftWheelSpeedSensor_Speed(float* Speed) {
    if (Speed == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_FrontLeftWheelSpeedSensor_Read(Speed);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến tốc độ bánh trước trái
}

/**
 * @brief   Đọc tốc độ từ cảm biến bánh trước phải.
 * @details Hàm đọc dữ liệu tốc độ từ cảm biến bánh trước phải thông qua lớp IoHwAb.
 * @param   Speed: Con trỏ tới biến nhận giá trị tốc độ (km/h).
 * @return  Std_ReturnType: 
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Đọc thất bại (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpFrontRightWheelSpeedSensor_Speed(float* Speed) {
    if (Speed == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_FrontRightWheelSpeedSensor_Read(Speed);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến tốc độ bánh trước phải
}

/**
 * @brief   Đọc tốc độ từ cảm biến bánh sau trái.
 * @details Hàm đọc dữ liệu tốc độ từ cảm biến bánh sau trái thông qua lớp IoHwAb.
 * @param   Speed: Con trỏ tới biến nhận giá trị tốc độ (km/h).
 * @return  Std_ReturnType: 
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Đọc thất bại (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpRearLeftWheelSpeedSensor_Speed(float* Speed) {
    if (Speed == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_RearLeftWheelSpeedSensor_Read(Speed);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến tốc độ bánh sau trái
}

/**
 * @brief   Đọc tốc độ từ cảm biến bánh sau phải.
 * @details Hàm đọc dữ liệu tốc độ từ cảm biến bánh sau phải thông qua lớp IoHwAb.
 * @param   Speed: Con trỏ tới biến nhận giá trị tốc độ (km/h).
 * @return  Std_ReturnType: 
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Đọc thất bại (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpRearRightWheelSpeedSensor_Speed(float* Speed) {
    if (Speed == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_RearRightWheelSpeedSensor_Read(Speed);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến tốc độ bánh sau phải
}


/**
 * @brief   Ghi lực phanh tới bộ điều khiển bánh trước trái.
 * @details Hàm ghi giá trị lực phanh yêu cầu tới bộ điều khiển phanh bánh trước trái.
 * @param   ForceValue: Lực phanh yêu cầu (đơn vị Newton, N).
 * @return  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Ghi thất bại (lỗi phần cứng).
 */
Std_ReturnType Rte_Write_RpFrontLeftBrakeControl_SetForce(float ForceValue) {
    return IoHwAb_FrontLeftBrakeControl_SetForce(ForceValue);  // Gọi API từ IoHwAb để ghi lực phanh yêu cầu tới phanh bánh trước trái
}

/**
 * @brief   Ghi lực phanh tới bộ điều khiển bánh trước phải.
 * @details Hàm ghi giá trị lực phanh yêu cầu tới bộ điều khiển phanh bánh trước phải.
 * @param   ForceValue: Lực phanh yêu cầu (đơn vị Newton, N).
 * @return  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Ghi thất bại (lỗi phần cứng).
 */
Std_ReturnType Rte_Write_RpFrontRightBrakeControl_SetForce(float ForceValue) {
    return IoHwAb_FrontRightBrakeControl_SetForce(ForceValue);  // Gọi API từ IoHwAb để ghi lực phanh yêu cầu tới phanh bánh trước phải
}

/**
 * @brief   Ghi lực phanh tới bộ điều khiển bánh sau trái.
 * @details Hàm ghi giá trị lực phanh yêu cầu tới bộ điều khiển phanh bánh sau trái.
 * @param   ForceValue: Lực phanh yêu cầu (đơn vị Newton, N).
 * @return  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Ghi thất bại (lỗi phần cứng).
 */
Std_ReturnType Rte_Write_RpRearLeftBrakeControl_SetForce(float ForceValue) {
    return IoHwAb_RearLeftBrakeControl_SetForce(ForceValue);  // Gọi API từ IoHwAb để ghi lực phanh yêu cầu tới phanh bánh sau trái
}

/**
 * @brief   Ghi lực phanh tới bộ điều khiển bánh sau phải.
 * @details Hàm ghi giá trị lực phanh yêu cầu tới bộ điều khiển phanh bánh sau phải.
 * @param   ForceValue: Lực phanh yêu cầu (đơn vị Newton, N).
 * @return  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Ghi thất bại (lỗi phần cứng).
 */
Std_ReturnType Rte_Write_RpRearRightBrakeControl_SetForce(float ForceValue) {
    return IoHwAb_RearRightBrakeControl_SetForce(ForceValue);  // Gọi API từ IoHwAb để ghi lực phanh yêu cầu tới phanh bánh sau phải
}


/**
 * @brief   Khởi tạo cảm biến tốc độ bánh trước trái.
 * @details Hàm khởi tạo cấu hình cho cảm biến tốc độ bánh trước trái với các thông số
 *          như kênh ADC và tốc độ tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpFrontLeftWheelSpeedSensor_Init(void) {
    // Cấu hình cho cảm biến tốc độ
    FrontLeftSpeedSensor_ConfigType speedSensorConfig = {
        .SpeedSensor_Channel = 1,        // Kênh ADC cho cảm biến tốc độ bánh trước trái
        .SpeedSensor_MaxValue = 200      // Tốc độ tối đa giả lập (200 km/h)
    };
    return IoHwAb_FrontLeftWheelSpeedSensor_Init(&speedSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tốc độ bánh trước trái
}

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh trước phải.
 * @details Hàm khởi tạo cấu hình cho cảm biến tốc độ bánh trước phải với các thông số
 *          như kênh ADC và tốc độ tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpFrontRightWheelSpeedSensor_Init(void) {
    // Cấu hình cho cảm biến tốc độ
    FrontRightSpeedSensor_ConfigType speedSensorConfig = {
        .SpeedSensor_Channel = 2,        // Kênh ADC cho cảm biến tốc độ bánh trước trái
        .SpeedSensor_MaxValue = 200      // Tốc độ tối đa giả lập (200 km/h)
    };
    return IoHwAb_FrontRightWheelSpeedSensor_Init(&speedSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tốc độ bánh trước trái
}

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh sau trái.
 * @details Hàm khởi tạo cấu hình cho cảm biến tốc độ bánh sau trái với các thông số
 *          như kênh ADC và tốc độ tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpRearLeftWheelSpeedSensor_Init(void) {
    // Cấu hình cho cảm biến tốc độ
    RearLeftSpeedSensor_ConfigType speedSensorConfig = {
        .SpeedSensor_Channel = 3,        // Kênh ADC cho cảm biến tốc độ bánh trước trái
        .SpeedSensor_MaxValue = 200      // Tốc độ tối đa giả lập (200 km/h)
    };
    return IoHwAb_RearLeftWheelSpeedSensor_Init(&speedSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tốc độ bánh trước trái
}

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh sau phải.
 * @details Hàm khởi tạo cấu hình cho cảm biến tốc độ bánh sau phải với các thông số
 *          như kênh ADC và tốc độ tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpRearRightWheelSpeedSensor_Init(void) {
    // Cấu hình cho cảm biến tốc độ
    RearRightSpeedSensor_ConfigType speedSensorConfig = {
        .SpeedSensor_Channel = 4,        // Kênh ADC cho cảm biến tốc độ bánh trước trái
        .SpeedSensor_MaxValue = 200      // Tốc độ tối đa giả lập (200 km/h)
    };
    return IoHwAb_RearRightWheelSpeedSensor_Init(&speedSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tốc độ bánh trước trái
}



/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh trước trái.
 * @details Hàm thiết lập cấu hình cho bộ điều khiển phanh bánh trước trái với các thông số
 *          như kênh điều khiển và lực phanh tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpFrontLeftBrakeControl_Init(void) {
    // Cấu hình cho bộ điều khiển phanh
    FrontLeftBrakeDriver_ConfigType BrakeDriverConfig = {
        .Brake_Channel = 1,              // Kênh điều khiển phanh trước trái
        .Brake_MaxForce = 1000           // Lực phanh tối đa giả lập (1000 N)
    };
    return IoHwAb_FrontLeftBrakeControl_Init(&BrakeDriverConfig);  // Gọi API từ IoHwAb để khởi tạo bộ điều khiển phanh bánh trước trái
}

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh trước phải.
 * @details Hàm thiết lập cấu hình cho bộ điều khiển phanh bánh trước phải với các thông số
 *          như kênh điều khiển và lực phanh tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpFrontRightBrakeControl_Init(void) {
    // Cấu hình cho bộ điều khiển phanh
    FrontRightBrakeDriver_ConfigType BrakeDriverConfig = {
        .Brake_Channel = 2,              // Kênh điều khiển phanh trước phải
        .Brake_MaxForce = 1000           // Lực phanh tối đa giả lập (1000 N)
    };
    return IoHwAb_FrontRightBrakeControl_Init(&BrakeDriverConfig);  // Gọi API từ IoHwAb để khởi tạo bộ điều khiển phanh bánh trước phải
}

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh sau trái.
 * @details Hàm thiết lập cấu hình cho bộ điều khiển phanh bánh sau trái với các thông số
 *          như kênh điều khiển và lực phanh tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpRearLeftBrakeControl_Init(void) {
    // Cấu hình cho bộ điều khiển phanh
    RearLeftBrakeDriver_ConfigType BrakeDriverConfig = {
        .Brake_Channel = 3,              // Kênh điều khiển phanh sau trái
        .Brake_MaxForce = 1000           // Lực phanh tối đa giả lập (1000 N)
    };
    return IoHwAb_RearLeftBrakeControl_Init(&BrakeDriverConfig);  // Gọi API từ IoHwAb để khởi tạo bộ điều khiển phanh bánh sau trái
}

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh sau phải.
 * @details Hàm thiết lập cấu hình cho bộ điều khiển phanh bánh sau phải với các thông số
 *          như kênh điều khiển và lực phanh tối đa.
 * @return  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi trong quá trình khởi tạo.
 */
Std_ReturnType Rte_Call_RpRearRightBrakeControl_Init(void) {
    // Cấu hình cho bộ điều khiển phanh
    RearRightBrakeDriver_ConfigType BrakeDriverConfig = {
        .Brake_Channel = 4,              // Kênh điều khiển phanh sau phải
        .Brake_MaxForce = 1000           // Lực phanh tối đa giả lập (1000 N)
    };
    return IoHwAb_RearRightBrakeControl_Init(&BrakeDriverConfig);  // Gọi API từ IoHwAb để khởi tạo bộ điều khiển phanh bánh sau phải
}
