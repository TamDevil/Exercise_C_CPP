/***************************************************************************
 * @file    Traction_Control.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến kiểm soát lực kéo
 * @details File này cung cấp giao diện cho việc kiểm soát lực kéo, bao gồm
 *          khởi tạo và đặt lực phanh
 * @version 1.0
 * @date    2024-11-05
 * @author  Tâm Devil
 ***************************************************************************/
#ifndef TRACTION_CONTROL_H
#define TRACTION_CONTROL_H

// Khai báo các hàm chính cho Traction Control
void TractionControl_Init(void);   // Hàm khởi tạo hệ thống kiểm soát lực kéo
void TractionControl_Update(void); // Hàm cập nhật hệ thống kiểm soát lực kéo

#endif // TRACTION_CONTROL_H
