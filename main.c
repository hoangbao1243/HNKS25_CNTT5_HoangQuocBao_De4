#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct {
    int maHang;
    char tenHang[50];
    int soLuong;
    float donGia;
} MatHang;

int timTheoMa(MatHang ds[], int currentLength, int maHang) {
    for (int i = 0; i < currentLength; i++) {
        if (ds[i].maHang == maHang) {
            return i;
        }
    }
    return -1;
}

void themMatHang(MatHang ds[], int *currentLength) {
    if (*currentLength >= MAX_SIZE) {
        printf("Danh sach da day\n");
        return;
    }

    int maHang;
    char tenHang[50];
    int soLuong;
    float donGia;

    printf("Nhap ma mat hang: ");
    scanf("%d", &maHang);

    if (timTheoMa(ds, *currentLength, maHang) != -1) {
        printf("Ma mat hang da ton tai\n");
        return;
    }

    getchar();
    printf("Nhap ten mat hang: ");
    fgets(tenHang, sizeof(tenHang), stdin);
    tenHang[strcspn(tenHang, "\n")] = '\0';

    do {
        printf("Nhap so luong: ");
        scanf("%d", &soLuong);
        if (soLuong < 0) {
            printf("So luong khong hop le\n");
        }
    } while (soLuong < 0);

    do {
        printf("Nhap don gia: ");
        scanf("%f", &donGia);
        if (donGia <= 0) {
            printf("Don gia khong hop le\n");
        }
    } while (donGia <= 0);

    ds[*currentLength].maHang = maHang;
    strcpy(ds[*currentLength].tenHang, tenHang);
    ds[*currentLength].soLuong = soLuong;
    ds[*currentLength].donGia = donGia;

    (*currentLength)++;

    printf("Them mat hang thanh cong\n");
}

void hienThiDanhSach(MatHang ds[], int currentLength) {
    if (currentLength == 0) {
        printf("Danh sach rong\n");
        return;
    }

    printf("\n%-10s %-25s %-12s %-15s %-15s\n",
           "Ma", "Ten mat hang", "So luong", "Don gia", "Thanh tien");

    for (int i = 0; i < currentLength; i++) {
        printf("%-10d %-25s %-12d %-15.0f %-15.0f\n",
               ds[i].maHang,
               ds[i].tenHang,
               ds[i].soLuong,
               ds[i].donGia,
               ds[i].soLuong * ds[i].donGia);
    }
}

void capNhatMatHang(MatHang ds[], int currentLength) {
    if (currentLength == 0) {
        printf("Danh sach rong\n");
        return;
    }

    int maHang;

    printf("Nhap ma mat hang can cap nhat: ");
    scanf("%d", &maHang);

    int index = timTheoMa(ds, currentLength, maHang);

    if (index == -1) {
        printf("Khong tim thay mat hang\n");
        return;
    }

    getchar();
    printf("Nhap ten mat hang moi: ");
    fgets(ds[index].tenHang, sizeof(ds[index].tenHang), stdin);
    ds[index].tenHang[strcspn(ds[index].tenHang, "\n")] = '\0';

    do {
        printf("Nhap so luong moi: ");
        scanf("%d", &ds[index].soLuong);
        if (ds[index].soLuong < 0) {
            printf("So luong khong hop le\n");
        }
    } while (ds[index].soLuong < 0);

    do {
        printf("Nhap don gia moi: ");
        scanf("%f", &ds[index].donGia);
        if (ds[index].donGia <= 0) {
            printf("Don gia khong hop le\n");
        }
    } while (ds[index].donGia <= 0);

    printf("Cap nhat thanh cong\n");
}

void xoaMatHang(MatHang ds[], int *currentLength) {
    if (*currentLength == 0) {
        printf("Danh sach rong\n");
        return;
    }

    int maHang;

    printf("Nhap ma mat hang can xoa: ");
    scanf("%d", &maHang);

    int index = timTheoMa(ds, *currentLength, maHang);

    if (index == -1) {
        printf("Khong tim thay mat hang\n");
        return;
    }

    for (int i = index; i < *currentLength - 1; i++) {
        ds[i] = ds[i + 1];
    }

    (*currentLength)--;

    printf("Xoa thanh cong\n");
}

void timMatHangTheoTen(MatHang ds[], int currentLength) {
    char tenHang[50];
    int found = 0;

    getchar();
    printf("Nhap ten mat hang can tim: ");
    fgets(tenHang, sizeof(tenHang), stdin);
    tenHang[strcspn(tenHang, "\n")] = '\0';

    for (int i = 0; i < currentLength; i++) {
        if (strcmp(ds[i].tenHang, tenHang) == 0) {
            if (found == 0) {
                printf("\n%-10s %-25s %-12s %-15s %-15s\n",
                       "Ma", "Ten mat hang", "So luong", "Don gia", "Thanh tien");
            }

            printf("%-10d %-25s %-12d %-15.0f %-15.0f\n",
                   ds[i].maHang,
                   ds[i].tenHang,
                   ds[i].soLuong,
                   ds[i].donGia,
                   ds[i].soLuong * ds[i].donGia);

            found = 1;
        }
    }

    if (found == 0) {
        printf("Khong co mat hang nao khop\n");
    }
}

void thongKeKhoHang(MatHang ds[], int currentLength) {
    if (currentLength == 0) {
        printf("Danh sach rong\n");
        return;
    }

    float tongGiaTri = 0;
    int demSapHet = 0;
    int maxIndex = 0;

    for (int i = 0; i < currentLength; i++) {
        float thanhTien = ds[i].soLuong * ds[i].donGia;

        tongGiaTri += thanhTien;

        if (ds[i].soLuong < 5) {
            demSapHet++;
        }

        if (thanhTien > ds[maxIndex].soLuong * ds[maxIndex].donGia) {
            maxIndex = i;
        }
    }

    printf("Tong gia tri kho: %.0f dong\n", tongGiaTri);

    printf("\nDanh sach mat hang sap het:\n");

    for (int i = 0; i < currentLength; i++) {
        if (ds[i].soLuong < 5) {
            printf("Ma: %d | Ten: %s | So luong: %d\n",
                   ds[i].maHang, ds[i].tenHang, ds[i].soLuong);
        }
    }

    printf("So mat hang sap het: %d\n", demSapHet);

    printf("\nMat hang co thanh tien lon nhat:\n");
    printf("Ma: %d\n", ds[maxIndex].maHang);
    printf("Ten: %s\n", ds[maxIndex].tenHang);
    printf("So luong: %d\n", ds[maxIndex].soLuong);
    printf("Don gia: %.0f\n", ds[maxIndex].donGia);
    printf("Thanh tien: %.0f\n",
           ds[maxIndex].soLuong * ds[maxIndex].donGia);
}

void hienThiMenu() {
    printf("\n===== QUAN LY MAT HANG =====\n");
    printf("1. Them mat hang\n");
    printf("2. Hien thi danh sach mat hang\n");
    printf("3. Cap nhat mat hang theo ma\n");
    printf("4. Xoa mat hang theo ma\n");
    printf("5. Tim mat hang theo ten\n");
    printf("6. Thong ke kho hang\n");
    printf("0. Thoat\n");
    printf("Chon chuc nang: ");
}

int main() {
    MatHang ds[MAX_SIZE];
    int currentLength = 0;

    while (1) {
        int userChoose;
        hienThiMenu();

        scanf("%d", &userChoose);

        switch (userChoose) {
            case 1:
                themMatHang(ds, &currentLength);
                break;
            case 2:
                hienThiDanhSach(ds, currentLength);
                break;
            case 3:
                capNhatMatHang(ds, currentLength);
                break;
            case 4:
                xoaMatHang(ds, &currentLength);
                break;
            case 5:
                timMatHangTheoTen(ds, currentLength);
                break;
            case 6:
                thongKeKhoHang(ds, currentLength);
                break;
            case 0:
                printf("Tam biet!\n");
                return 0;
            default:
                printf("Lua chon khong hop le\n");
        }
    }

    return 0;
}
