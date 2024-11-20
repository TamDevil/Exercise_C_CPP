/***************************************************************************
 * @file    Rte_TractionControl.h
 * @brief   Khai báo các API và cấu trúc liên quan đến hệ thống kiểm soát lực kéo.
 * @details File này định nghĩa giao diện RTE cho hệ thống kiểm soát lực kéo, 
 *          bao gồm các hàm khởi tạo cảm biến/phanh, đọc tốc độ bánh xe, và 
 *          điều khiển lực phanh.
 * @version 1.0
 * @date    2024-11-05
 * @author  Tâm Devil
 ***************************************************************************/

#ifndef RTE_TRACTIONCONTROL_H
#define RTE_TRACTIONCONTROL_H

#include "Std_Types.h"  // Bao gồm các kiểu dữ liệu tiêu chuẩn
#include <stddef.h>  // Định nghĩa NULL



/**
 * @brief   Đọc tốc độ từ cảm biến bánh trước trái.
 * @param   Speed: Con trỏ đến biến lưu giá trị tốc độ đọc được (đơn vị: km/h).
 * @retval  Std_ReturnType:
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Lỗi (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpFrontLeftWheelSpeedSensor_Speed(float* Speed);

/**
 * @brief   Đọc tốc độ từ cảm biến bánh trước phải.
 * @param   Speed: Con trỏ đến biến lưu giá trị tốc độ đọc được (đơn vị: km/h).
 * @retval  Std_ReturnType:
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Lỗi (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpFrontRightWheelSpeedSensor_Speed(float* Speed);

/**
 * @brief   Đọc tốc độ từ cảm biến bánh sau trái.
 * @param   Speed: Con trỏ đến biến lưu giá trị tốc độ đọc được (đơn vị: km/h).
 * @retval  Std_ReturnType:
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Lỗi (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpRearLeftWheelSpeedSensor_Speed(float* Speed);

/**
 * @brief   Đọc tốc độ từ cảm biến bánh sau phải.
 * @param   Speed: Con trỏ đến biến lưu giá trị tốc độ đọc được (đơn vị: km/h).
 * @retval  Std_ReturnType:
 *          - E_OK: Đọc thành công.
 *          - E_NOT_OK: Lỗi (con trỏ NULL hoặc lỗi phần cứng).
 */
Std_ReturnType Rte_Read_RpRearRightWheelSpeedSensor_Speed(float* Speed);



/**
 * @brief   Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh trước trái.
 * @param   ForceValue: Giá trị lực phanh (đơn vị: N).
 * @retval  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Write_RpFrontLeftBrakeControl_SetForce(float ForceValue);

/**
 * @brief   Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh trước phải.
 * @param   ForceValue: Giá trị lực phanh (đơn vị: N).
 * @retval  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Write_RpFrontRightBrakeControl_SetForce(float ForceValue);

/**
 * @brief   Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh sau trái.
 * @param   ForceValue: Giá trị lực phanh (đơn vị: N).
 * @retval  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Write_RpRearLeftBrakeControl_SetForce(float ForceValue);

/**
 * @brief   Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh sau phải.
 * @param   ForceValue: Giá trị lực phanh (đơn vị: N).
 * @retval  Std_ReturnType:
 *          - E_OK: Ghi thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Write_RpRearRightBrakeControl_SetForce(float ForceValue);


/**
 * @brief   Khởi tạo cảm biến tốc độ bánh trước trái.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpFrontLeftWheelSpeedSensor_Init(void);

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh trước phải.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpFrontRightWheelSpeedSensor_Init(void);

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh sau trái.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpRearLeftWheelSpeedSensor_Init(void);

/**
 * @brief   Khởi tạo cảm biến tốc độ bánh sau phải.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpRearRightWheelSpeedSensor_Init(void);


/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh trước trái.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpFrontLeftBrakeControl_Init(void);

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh trước phải.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpFrontRightBrakeControl_Init(void);

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh sau trái.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpRearLeftBrakeControl_Init(void);

/**
 * @brief   Khởi tạo bộ điều khiển phanh bánh sau phải.
 * @retval  Std_ReturnType:
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Lỗi phần cứng.
 */
Std_ReturnType Rte_Call_RpRearRightBrakeControl_Init(void);

#endif // RTE_TRACTIONCONTROL_H
