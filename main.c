#include <stdio.h>
#include <string.h>

int main() {
    // Khai báo các mảng song song với tối đa 100 bản ghi
    char maPhieu[100][20];
    char maSach[100][20];
    int soNgayMuon[100];
    int soLuong = 0; // Biến theo dõi số lượng phần tử hiện tại

    int choice;

    do {
        // Hiển thị Menu
        printf("\n================ HỆ THỐNG QUẢN LÝ MƯỢN TRẢ SÁCH (LOGISTICS) ================\n");
        printf("1. Thêm mới phiếu mượn sách (Create)\n");
        printf("2. Hiển thị danh sách phiếu mượn & Tiền phạt quá hạn (Read)\n");
        printf("3. Cập nhật số ngày mượn sách (Update)\n");
        printf("4. Xác nhận trả sách / Xóa phiếu mượn (Delete)\n");
        printf("5. Thoát chương trình\n");
        printf("===========================================================================\n");
        printf("Lựa chọn của bạn (1-5): ");

        scanf("%d", &choice);
        while(getchar() != '\n'); // Làm sạch bộ đệm sau khi nhập số

        switch(choice) {
            case 1: {
                printf("\n--- THÊM MỚI PHIẾU MƯỢN ---\n");

                // Kiểm tra giới hạn mảng
                if (soLuong >= 100) {
                    printf("Bộ nhớ danh sách đã đầy, không thể thêm mới!\n");
                    break;
                }

                char tempMaPhieu[20];
                printf("Nhập mã phiếu: ");
                scanf("%19s", tempMaPhieu);
                while(getchar() != '\n'); // Làm sạch bộ đệm

                // Kiểm tra trùng lặp mã phiếu
                int isDuplicate = 0;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], tempMaPhieu) == 0) {
                        isDuplicate = 1;
                        break;
                    }
                }

                if (isDuplicate) {
                    printf("Mã phiếu đã tồn tại trong hệ thống!\n");
                    break;
                }

                // Lưu mã phiếu nếu không trùng
                strcpy(maPhieu[soLuong], tempMaPhieu);

                printf("Nhập mã sách: ");
                scanf("%19s", maSach[soLuong]);
                while(getchar() != '\n');

                // Nhập và kiểm tra số ngày mượn > 0
                do {
                    printf("Nhập số ngày mượn: ");
                    scanf("%d", &soNgayMuon[soLuong]);
                    while(getchar() != '\n');

                    if (soNgayMuon[soLuong] <= 0) {
                        printf("Số ngày mượn phải lớn hơn 0. Vui lòng nhập lại!\n");
                    }
                } while (soNgayMuon[soLuong] <= 0);

                soLuong++; // Tăng số lượng bản ghi
                printf("Thêm mới phiếu mượn thành công!\n");
                break;
            }

            case 2: {
                if (soLuong == 0) {
                    printf("Danh sách phiếu mượn hiện đang rỗng!\n");
                    break;
                }

                printf("\n================================ DANH SÁCH PHIẾU MƯỢN ================================\n");
                // Sử dụng định dạng cột để bảng hiển thị ngay ngắn
                printf("%-5s %-15s %-15s %-15s %-15s %-15s\n", "STT", "MÃ PHIẾU", "MÃ SÁCH", "SỐ NGÀY", "TRẠNG THÁI", "TIỀN PHẠT (VNĐ)");

                for (int i = 0; i < soLuong; i++) {
                    int tienPhat = 0;
                    char trangThai[20];

                    if (soNgayMuon[i] > 14) {
                        int ngayQuaHan = soNgayMuon[i] - 14;
                        tienPhat = ngayQuaHan * 5000;
                        strcpy(trangThai, "QUÁ HẠN");
                    } else {
                        tienPhat = 0;
                        strcpy(trangThai, "ĐÚNG HẠN");
                    }

                    printf("%-5d %-15s %-15s %-15d %-15s %-15d\n",
                           i + 1, maPhieu[i], maSach[i], soNgayMuon[i], trangThai, tienPhat);
                }
                printf("======================================================================================\n");
                break;
            }

            case 3: {
                char tempMaPhieu[20];
                printf("\nNhập mã phiếu cần cập nhật: ");
                scanf("%19s", tempMaPhieu);
                while(getchar() != '\n');

                int pos = -1;
                // Tìm kiếm tuyến tính
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], tempMaPhieu) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Không tìm thấy mã phiếu trong hệ thống!\n");
                } else {
                    printf("Số ngày mượn hiện tại của phiếu %s là: %d\n", maPhieu[pos], soNgayMuon[pos]);
                    printf("Nhập số ngày mượn mới: ");
                    scanf("%d", &soNgayMuon[pos]);
                    while(getchar() != '\n');

                    printf("Cập nhật số ngày mượn thành công!\n");
                }
                break;
            }

            case 4: {
                char tempMaPhieu[20];
                printf("\nNhập mã phiếu xác nhận trả/xóa: ");
                scanf("%19s", tempMaPhieu);
                while(getchar() != '\n');

                int pos = -1;
                // Tìm kiếm tuyến tính
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], tempMaPhieu) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Không tìm thấy mã phiếu cần xóa!\n");
                } else {
                    // Dời các phần tử phía sau lên trước 1 vị trí để ghi đè dữ liệu bị xóa
                    for (int i = pos; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(maSach[i], maSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                    }
                    soLuong--; // Giảm số lượng đi 1
                    printf("Xác nhận trả sách và xóa phiếu mượn thành công!\n");
                }
                break;
            }

            case 5:
                printf("\nĐã thoát chương trình. Chào tạm biệt!\n");
                break;

            default:
                printf("Lựa chọn không hợp lệ, vui lòng chọn lại!\n");
                break;
        }
    } while (choice != 5);

    return 0;
}