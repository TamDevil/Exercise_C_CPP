/***************************************************************************
 * @file    Traction_Control.c
 * @brief   Định nghĩa các hàm kiểm soát lực kéo.
 * @details File này chứa phần định nghĩa của các hàm kiểm soát lực kéo, bao gồm
 *          khởi tạo và đặt lực phanh.
 * @version 1.0
 * @date    2024-11-05
 * @author  Tâm Devil
 ***************************************************************************/

#include "Rte_TractionControl.h"   // Bao gồm interface của RTE cho Traction Control
#include "Traction_Control.h"
#include <stdio.h>  // Thư viện cho printf
#include <math.h>   // Thư viện cho abs

/**************************************************************************
 * @brief   Hàm khởi tạo hệ thống kiểm soát lực kéo
 * @details Hàm này khởi tạo các cảm biến tốc độ và hệ thống điều khiển phanh.
 * @return  void
 **************************************************************************/
void TractionControl_Init(void) {
    // Khởi tạo các cảm biến tốc độ và các bộ điêu khiển phanh
    Std_ReturnType status;

    printf("Khởi tạo hệ thống Traction Control...\n");

    // Khởi tạo cảm biến tốc độ bánh trước trái
    status = Rte_Call_RpFrontLeftWheelSpeedSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến tốc độ bánh trước trái đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tốc độ bánh trước trái.\n");
        return;
    }

    // Khởi tạo cảm biến tốc độ bánh trước phải
    status = Rte_Call_RpFrontRightWheelSpeedSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến tốc độ bánh trước phải đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tốc độ bánh trước phải.\n");
        return;
    }
    // Khởi tạo cảm biến tốc độ bánh sau trái
    status = Rte_Call_RpRearLeftWheelSpeedSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến tốc độ bánh sau trái đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tốc độ bánh sau trái.\n");
        return;
    }
    // Khởi tạo cảm biến tốc độ bánh sau phải
    status = Rte_Call_RpRearRightWheelSpeedSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến tốc độ bánh sau phải đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tốc độ bánh sau phải.\n");
        return;
    }

    // Khởi tạo bộ điều khiển phanh bánh trước trái
     status = Rte_Call_RpFrontLeftBrakeControl_Init();
    if (status == E_OK){
        printf("Bộ điều khiển phanh bánh trước trái đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo bộ điều khiển phanh bánh trước trái.\n");
        return;
    }
    // Khởi tạo bộ điều khiển phanh bánh trước phải
    status = Rte_Call_RpFrontRightBrakeControl_Init();
    if (status == E_OK) {
        printf("Bộ điều khiển phanh trước phải đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo bộ điều khiển phanh bánh trước phải.\n");
        return;
    }
    // Khởi tạo bộ điều khiển phanh bánh sau trái
    status = Rte_Call_RpRearLeftBrakeControl_Init();
    if (status == E_OK) {
        printf("Bộ điều khiển phanh sau trái đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo bộ điều khiển phanh bánh sau trái.\n");
        return;
    }
    // Khởi tạo bộ điều khiển phanh bánh sau phải
    status = Rte_Call_RpRearRightBrakeControl_Init();
    if (status == E_OK) {
        printf("Bộ điều khiển phanh sau phải đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo bộ điều khiển phanh bánh sau phải.\n");
        return;
    }

    printf("Hệ thống Torque Control đã sẵn sàng.\n");
}

/**************************************************************************
 * @brief   Hàm cập nhật hệ thống điều khiển lực kéo
 * @details Hàm này kiểm tra độ trượt của các bánh xe và điều khiển phanh.
 * @return  void
 **************************************************************************/
void TractionControl_Update(void) {
    float FrontLeft_speed = 0.0f;
    float FrontRight_speed = 0.0f;
    float RearLeft_speed = 0.0f;
    float RearRight_speed = 0.0f;
    float Vehicle_speed = 0.0f;
    float FrontLeft_force = 0.0f;
    float FrontRight_force = 0.0f;
    float RearLeft_force = 0.0f;
    float RearRight_force = 0.0f;

    // Đọc dữ liệu từ cảm biến tốc độ bánh trước trái
    if (Rte_Read_RpFrontLeftWheelSpeedSensor_Speed(&FrontLeft_speed) == E_OK) {
        printf("Tốc độ bánh trước trái hiện tại: %.2f km/h\n", FrontLeft_speed);
    } else {
        printf("Lỗi khi đọc cảm biến tốc độ bánh trước trái!\n");
    }

    // Đọc dữ liệu từ cảm biến tốc độ bánh trước phải
    if (Rte_Read_RpFrontRightWheelSpeedSensor_Speed(&FrontRight_speed) == E_OK) {
        printf("Tốc độ bánh trước phải hiện tại: %.2f km/h\n", FrontRight_speed);
    } else {
        printf("Lỗi khi đọc cảm biến tốc độ bánh trước phải!\n");
    }

    // Đọc dữ liệu từ cảm biến tốc độ bánh sau trái
    if (Rte_Read_RpRearLeftWheelSpeedSensor_Speed(&RearLeft_speed) == E_OK) {
        printf("Tốc độ bánh sau trái hiện tại: %.2f km/h\n", RearLeft_speed);
    } else {
        printf("Lỗi khi đọc cảm biến tốc độ banh sau trái!\n");
    }

    // Đọc dữ liệu từ cảm biến tốc độ bánh sau phải
    if (Rte_Read_RpRearRightWheelSpeedSensor_Speed(&RearRight_speed) == E_OK) {
        printf("Tốc độ bánh sau phải hiện tại: %.2f km/h\n", RearRight_speed);
    } else {
        printf("Lỗi khi đọc cảm biến tốc độ bánh sau phải!\n");
    }

    // Tính toán độ trượt cho từng bánh xe
    Vehicle_speed = (FrontLeft_speed + FrontRight_speed + RearLeft_speed + RearRight_speed) / 4.0;
    float FrontLeft_Slip = abs(FrontLeft_speed - Vehicle_speed) / Vehicle_speed;
    float FrontRight_Slip = abs(FrontRight_speed - Vehicle_speed) / Vehicle_speed;
    float RearLeft_Slip = abs(RearLeft_speed - Vehicle_speed) / Vehicle_speed;
    float RearRight_Slip = abs(RearRight_speed - Vehicle_speed) / Vehicle_speed;

    // Ngưỡng trượt cho phép
   static float Slip_Threshold = 0.3;    // Biến static chỉ được dùng trong file source này
    // Lực phanh yêu cầu
    static float Desired_Force = 300;    // Biến static chỉ được dùng trong file source này

    // Kiểm tra độ trượt của từng bánh và kích hoạt phanh nếu cần

    // Kiểm tra độ trượt bánh trước trái
    if (FrontLeft_Slip > Slip_Threshold) {
    // Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh trước trái
    FrontLeft_force = Desired_Force * FrontLeft_Slip;
    if (Rte_Write_RpFrontLeftBrakeControl_SetForce(FrontLeft_force) == E_OK) {
        printf("Đã gửi lực phanh yêu cầu tới phanh bánh trước trái.\n");
    } else {
        printf("Lỗi khi gửi lực phanh tới phanh bánh trước trái!\n");
    }
} else {
    FrontLeft_force = 0;  // Nhả phanh, không áp dụng lực phanh nữa
    if (Rte_Write_RpFrontLeftBrakeControl_SetForce(FrontLeft_force) == E_OK) {
        printf("Đã nhả phanh bánh trước trái.\n");
    } else {
        printf("Lỗi khi nhả phanh bánh trước trái!\n");
    }
}

    // Kiểm tra độ trượt bánh trước phải 
    if (FrontRight_Slip > Slip_Threshold) {
    // Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh trước phải
    FrontRight_force = Desired_Force * FrontRight_Slip;
    if (Rte_Write_RpFrontRightBrakeControl_SetForce(FrontRight_force) == E_OK) {
        printf("Đã gửi lực phanh yêu cầu tới phanh bánh trước phải.\n");
    } else {
        printf("Lỗi khi gửi lực phanh tới phanh bánh trước phải!\n");
    }
} else {
    FrontRight_force = 0;  // Nhả phanh, không áp dụng lực phanh nữa
    if (Rte_Write_RpFrontRightBrakeControl_SetForce(FrontRight_force) == E_OK) {
        printf("Đã nhả phanh bánh trước phải.\n");
    } else {
        printf("Lỗi khi nhả phanh bánh trước phải!\n");
    }
}

    // Kiểm tra độ trượt bánh sau trái
    if (RearLeft_Slip> Slip_Threshold) {
    // Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh sau trái
    RearLeft_force = Desired_Force * RearLeft_Slip;
    if (Rte_Write_RpRearLeftBrakeControl_SetForce(RearLeft_force) == E_OK) {
        printf("Đã gửi lực phanh yêu cầu tới phanh bánh sau trái.\n");
    } else {
        printf("Lỗi khi gửi lực phanh tới phanh bánh sau trái!\n");
    }
} else {
    RearLeft_force = 0;  // Nhả phanh, không áp dụng lực phanh nữa
    if (Rte_Write_RpRearLeftBrakeControl_SetForce(RearLeft_force) == E_OK) {
        printf("Đã nhả phanh bánh sau trái.\n");
    } else {
        printf("Lỗi khi nhả phanh bánh sau trái!\n");
    }
}

    // Kiểm trả độ trượt bánh sau phải
    if (RearRight_Slip > Slip_Threshold) {
    // Ghi lực phanh yêu cầu tới bộ điều khiển phanh bánh sau phải
    RearRight_force = Desired_Force * RearRight_Slip;
    if (Rte_Write_RpRearRightBrakeControl_SetForce(RearRight_force) == E_OK) {
        printf("Đã gửi lực phanh yêu cầu tới phanh bánh sau phải.\n");
    } else {
        printf("Lỗi khi gửi lực phanh tới phanh bánh sau phải!\n");
    }
} else {
    RearRight_force = 0;  // Nhả phanh, không áp dụng lực phanh nữa
    if (Rte_Write_RpRearRightBrakeControl_SetForce(RearRight_force) == E_OK) {
        printf("Đã nhả phanh bánh sau phải.\n");
    } else {
        printf("Lỗi khi nhả phanh bánh sau phải!\n");
    }
}

    // In ra lực phanh yêu cầu ở bánh trước trái
    printf("Lực phanh ở bánh trước trái: %.2f N\n", FrontLeft_force);

    // In ra lực phanh yêu cầu ở bánh trước phải
    printf("Lực phanh ở bánh trước phải: %.2f N\n", FrontRight_force);

    // In ra lực phanh yêu cầu ở bánh sau trái
    printf("Lực phanh ở bánh sau trái: %.2f N\n", RearLeft_force);

    // In ra lực phanh yêu cầu ở bánh sau phải
    printf("Lực phanh ở bánh sau phải: %.2f N\n", RearRight_force);

}
