#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_XE 100
#define MAX_KHACH 100

/* Bang gia va tien coc: index 0 = xe dap, 1 = xe so, 2 = xe ga */
const long long GIA_GIO[3]  = {15000, 20000, 25000};
const long long GIA_NGAY[3] = {50000, 120000, 150000};
const long long TIEN_COC[3] = {200000, 1000000, 1000000};

typedef struct {
    char maXe[10];
    int loai;                  /* 1: dap, 2: so, 3: ga */
    char bienSo[15];
    int dangThue;              /* 0: trong, 1: dang thue */
    int soLanThue;
    char sdtNguoiThue[11];     /* SDT khach dang thue xe */
} XeThue;

typedef struct {
    char sdt[11];
    char hoTen[50];
    int soLanThue;             /* So lan thue da hoan tat */
} KhachThue;

/* Nguyen mau ham */
void docDong(char *s, size_t kichThuoc);
int docSoNguyen(const char *loiNhac, int min, int max);
long long docSoTien(const char *loiNhac);
void docChuoi(const char *loiNhac, char *s, size_t kichThuoc);
int laSDTHopLe(const char *s);
int timViTriXe(const XeThue dsXe[], int nXe, const char *maXe);
int bienSoDaTonTai(const XeThue dsXe[], int nXe, const char *bienSo);
const char *tenLoaiXe(int loai);
long long tinhTienThue(int loai, int soGio);
KhachThue *timHoacTaoKhach(KhachThue ds[], int *n, const char *sdt);
void themXe(XeThue dsXe[], int *nXe);
void hienThiXeTrong(XeThue dsXe[], int nXe);
void choThueXe(XeThue dsXe[], int nXe, KhachThue dsKhach[], int *nKhach);
void traXe(XeThue dsXe[], int nXe, KhachThue dsKhach[], int nKhach,
           long long doanhThu[], long long *tongPhiSuaChua);
void lietKeXeDangThue(XeThue dsXe[], int nXe);
void thongKe(const XeThue dsXe[], int nXe, const KhachThue dsKhach[],
             int nKhach, const long long doanhThu[], long long tongPhiSuaChua);

int main(void) {
    XeThue dsXe[MAX_XE];
    KhachThue dsKhach[MAX_KHACH];
    int nXe = 0, nKhach = 0;
    long long doanhThu[3] = {0, 0, 0};
    long long tongPhiSuaChua = 0;
    int chon;

    /* Du lieu mau de thuan tien kiem thu */
    strcpy(dsXe[0].maXe, "XD01");
    dsXe[0].loai = 1;
    strcpy(dsXe[0].bienSo, "Khong co");
    dsXe[0].dangThue = 0;
    dsXe[0].soLanThue = 2;
    strcpy(dsXe[0].sdtNguoiThue, "");

    strcpy(dsXe[1].maXe, "XS01");
    dsXe[1].loai = 2;
    strcpy(dsXe[1].bienSo, "92C1-12345");
    dsXe[1].dangThue = 0;
    dsXe[1].soLanThue = 5;
    strcpy(dsXe[1].sdtNguoiThue, "");

    strcpy(dsXe[2].maXe, "XG01");
    dsXe[2].loai = 3;
    strcpy(dsXe[2].bienSo, "92C1-67890");
    dsXe[2].dangThue = 0;
    dsXe[2].soLanThue = 1;
    strcpy(dsXe[2].sdtNguoiThue, "");
    nXe = 3;

    strcpy(dsKhach[0].sdt, "0901234567");
    strcpy(dsKhach[0].hoTen, "Nguyen Van A");
    dsKhach[0].soLanThue = 3;
    nKhach = 1;

    do {
        printf("\n=== QUAN LY CHO THUE XE - HOI AN BIKE ===\n");
        printf("1. Them xe / Hien thi xe trong theo loai\n");
        printf("2. Cho thue xe\n");
        printf("3. Tra xe / Thanh toan\n");
        printf("4. Liet ke xe dang cho thue\n");
        printf("5. Thong ke doanh thu, xe duoc thue nhieu nhat, khach quen\n");
        printf("0. Thoat\n");

        chon = docSoNguyen("Chon chuc nang: ", 0, 5);

        switch (chon) {
            case 1: {
                int sub;
                printf("\n1. Them xe moi\n2. Xem xe trong\n");
                sub = docSoNguyen("Chon: ", 1, 2);
                if (sub == 1) {
                    themXe(dsXe, &nXe);
                } else {
                    hienThiXeTrong(dsXe, nXe);
                }
                break;
            }
            case 2:
                choThueXe(dsXe, nXe, dsKhach, &nKhach);
                break;
            case 3:
                traXe(dsXe, nXe, dsKhach, nKhach, doanhThu, &tongPhiSuaChua);
                break;
            case 4:
                lietKeXeDangThue(dsXe, nXe);
                break;
            case 5:
                thongKe(dsXe, nXe, dsKhach, nKhach, doanhThu, tongPhiSuaChua);
                break;
            case 0:
                printf("Da thoat chuong trinh!\n");
                break;
        }
    } while (chon != 0);

    return 0;
}

/* Doc mot dong an toan, dong thoi loai bo ky tu xuong dong */
void docDong(char *s, size_t kichThuoc) {
    size_t len;
    if (fgets(s, (int)kichThuoc, stdin) == NULL) {
        s[0] = '\0';
        return;
    }

    len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* Bo phan con lai neu nguoi dung nhap qua dai */
        }
    }
}

void docChuoi(const char *loiNhac, char *s, size_t kichThuoc) {
    do {
        printf("%s", loiNhac);
        docDong(s, kichThuoc);
        if (s[0] == '\0') {
            printf("Du lieu khong duoc de trong. Vui long nhap lai.\n");
        }
    } while (s[0] == '\0');
}

/* Doc so nguyen va kiem tra mien gia tri */
int docSoNguyen(const char *loiNhac, int min, int max) {
    char buf[100];
    char *end;
    long value;

    while (1) {
        printf("%s", loiNhac);
        docDong(buf, sizeof(buf));
        errno = 0;
        value = strtol(buf, &end, 10);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (buf[0] != '\0' && end != buf && *end == '\0' &&
            errno != ERANGE && value >= min && value <= max) {
            return (int)value;
        }
        printf("Du lieu khong hop le. Vui long nhap so tu %d den %d.\n", min, max);
    }
}

long long docSoTien(const char *loiNhac) {
    char buf[100];
    char *end;
    long long value;

    while (1) {
        printf("%s", loiNhac);
        docDong(buf, sizeof(buf));
        errno = 0;
        value = strtoll(buf, &end, 10);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (buf[0] != '\0' && end != buf && *end == '\0' &&
            errno != ERANGE && value >= 0) {
            return value;
        }
        printf("So tien khong hop le. Vui long nhap so nguyen khong am.\n");
    }
}

int laSDTHopLe(const char *s) {
    int i;
    if (strlen(s) != 10) {
        return 0;
    }
    for (i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

int timViTriXe(const XeThue dsXe[], int nXe, const char *maXe) {
    int i;
    for (i = 0; i < nXe; i++) {
        if (strcmp(dsXe[i].maXe, maXe) == 0) {
            return i;
        }
    }
    return -1;
}

int bienSoDaTonTai(const XeThue dsXe[], int nXe, const char *bienSo) {
    int i;
    if (strcmp(bienSo, "Khong co") == 0 || strcmp(bienSo, "Khong") == 0) {
        return 0; /* Xe dap co the khong co bien so */
    }
    for (i = 0; i < nXe; i++) {
        if (strcmp(dsXe[i].bienSo, bienSo) == 0) {
            return 1;
        }
    }
    return 0;
}

const char *tenLoaiXe(int loai) {
    switch (loai) {
        case 1: return "Xe dap";
        case 2: return "Xe so";
        case 3: return "Xe tay ga";
        default: return "Khong ro";
    }
}

/* Tinh theo cach co loi nhat cho khach; so ngay duoc lam tron len */
long long tinhTienThue(int loai, int soGio) {
    int idx = loai - 1;
    long long tienGio = (long long)soGio * GIA_GIO[idx];
    int soNgay = (soGio + 23) / 24;
    long long tienNgay = (long long)soNgay * GIA_NGAY[idx];
    return (tienGio < tienNgay) ? tienGio : tienNgay;
}

/* Tim khach theo SDT; neu chua co thi tao moi va tang *n */
KhachThue *timHoacTaoKhach(KhachThue ds[], int *n, const char *sdt) {
    int i;
    for (i = 0; i < *n; i++) {
        if (strcmp(ds[i].sdt, sdt) == 0) {
            return &ds[i];
        }
    }

    if (*n >= MAX_KHACH) {
        return NULL;
    }

    strcpy(ds[*n].sdt, sdt);
    docChuoi("Khach moi! Nhap ho ten khach: ", ds[*n].hoTen, sizeof(ds[*n].hoTen));
    ds[*n].soLanThue = 0;
    (*n)++;
    return &ds[*n - 1];
}

void themXe(XeThue dsXe[], int *nXe) {
    XeThue x;

    if (*nXe >= MAX_XE) {
        printf("Kho xe da day!\n");
        return;
    }

    while (1) {
        docChuoi("Nhap ma xe (toi da 9 ky tu): ", x.maXe, sizeof(x.maXe));
        if (timViTriXe(dsXe, *nXe, x.maXe) == -1) {
            break;
        }
        printf("Ma xe da ton tai. Vui long nhap ma khac.\n");
    }

    x.loai = docSoNguyen("Nhap loai xe (1: dap, 2: so, 3: ga): ", 1, 3);

    if (x.loai == 1) {
        docChuoi("Nhap bien so (nhap 'Khong co' neu xe dap khong co bien so): ",
                 x.bienSo, sizeof(x.bienSo));
    } else {
        docChuoi("Nhap bien so xe: ", x.bienSo, sizeof(x.bienSo));
    }

    if (x.loai != 1 && (strcmp(x.bienSo, "Khong") == 0 ||
                        strcmp(x.bienSo, "Khong co") == 0)) {
        printf("Xe may phai co bien so hop le. Huy thao tac them xe.\n");
        return;
    }

    if (bienSoDaTonTai(dsXe, *nXe, x.bienSo)) {
        printf("Bien so da ton tai. Huy thao tac them xe.\n");
        return;
    }

    x.dangThue = 0;
    x.soLanThue = 0;
    strcpy(x.sdtNguoiThue, "");

    dsXe[*nXe] = x;
    (*nXe)++;
    printf("Them xe thanh cong!\n");
}

void hienThiXeTrong(XeThue dsXe[], int nXe) {
    int loai = docSoNguyen("Nhap loai xe muon xem (1: dap, 2: so, 3: ga): ", 1, 3);
    int i, dem = 0;

    printf("\n--- DANH SACH %s CON TRONG ---\n", tenLoaiXe(loai));
    for (i = 0; i < nXe; i++) {
        if (dsXe[i].loai == loai && dsXe[i].dangThue == 0) {
            printf("Ma: %-8s | Bien so: %-12s | Da thue: %d lan\n",
                   dsXe[i].maXe, dsXe[i].bienSo, dsXe[i].soLanThue);
            dem++;
        }
    }
    if (dem == 0) {
        printf("Khong co xe nao con trong!\n");
    }
}

void choThueXe(XeThue dsXe[], int nXe, KhachThue dsKhach[], int *nKhach) {
    char maXe[10], sdt[100]; /* Buffer rong de phat hien SDT nhap qua 10 so */
    int idxXe, i;
    KhachThue *kh;
    long long coc;
    char xacNhan[10];

    printf("\n--- DANH SACH XE CON TRONG ---\n");
    for (i = 0; i < nXe; i++) {
        if (dsXe[i].dangThue == 0) {
            printf("%s | %-10s | Bien so: %s\n",
                   dsXe[i].maXe, tenLoaiXe(dsXe[i].loai), dsXe[i].bienSo);
        }
    }

    docChuoi("Nhap ma xe muon thue: ", maXe, sizeof(maXe));
    idxXe = timViTriXe(dsXe, nXe, maXe);

    if (idxXe == -1) {
        printf("Khong tim thay ma xe!\n");
        return;
    }
    if (dsXe[idxXe].dangThue == 1) {
        printf("Xe nay hien dang duoc thue!\n");
        return;
    }

    while (1) {
        docChuoi("Nhap SDT khach thue (10 chu so): ", sdt, sizeof(sdt));
        if (laSDTHopLe(sdt)) {
            break;
        }
        printf("SDT phai gom dung 10 chu so.\n");
    }

    /* Chi tao khach moi sau khi xac nhan khach chap nhan nop coc */
    coc = TIEN_COC[dsXe[idxXe].loai - 1];
    printf("Tien coc can thu: %lld VND\n", coc);
    docChuoi("Xac nhan da thu du tien coc? (Y/N): ", xacNhan, sizeof(xacNhan));
    if (toupper((unsigned char)xacNhan[0]) != 'Y' || xacNhan[1] != '\0') {
        printf("Da huy giao dich thue xe.\n");
        return;
    }

    kh = timHoacTaoKhach(dsKhach, nKhach, sdt);
    if (kh == NULL) {
        printf("Danh sach khach da day! Khong the cho thue xe.\n");
        return;
    }

    dsXe[idxXe].dangThue = 1;
    strcpy(dsXe[idxXe].sdtNguoiThue, kh->sdt);

    printf("\n--- PHIEU THUE XE ---\n");
    printf("Khach hang: %s (%s)\n", kh->hoTen, kh->sdt);
    printf("So lan thue da hoan tat truoc do: %d\n", kh->soLanThue);
    printf("Xe thue: %s (%s)\n", dsXe[idxXe].maXe, tenLoaiXe(dsXe[idxXe].loai));
    printf("Tien coc da xac nhan: %lld VND\n", coc);
    printf("Cho thue xe thanh cong!\n");
}

void traXe(XeThue dsXe[], int nXe, KhachThue dsKhach[], int nKhach,
           long long doanhThu[], long long *tongPhiSuaChua) {
    char maXe[10];
    int idxXe, i, soGio, loai;
    char xacNhan[10];
    KhachThue *kh = NULL;
    long long phiHuHong, tienThueGoc, tienThueThucTe;
    long long coc, tongThanhToan, chenhLech;

    docChuoi("Nhap ma xe can tra: ", maXe, sizeof(maXe));

    idxXe = -1;
    for (i = 0; i < nXe; i++) {
        if (strcmp(dsXe[i].maXe, maXe) == 0 && dsXe[i].dangThue == 1) {
            idxXe = i;
            break;
        }
    }

    if (idxXe == -1) {
        printf("Ma xe khong ton tai hoac xe khong o trang thai cho thue!\n");
        return;
    }

    for (i = 0; i < nKhach; i++) {
        if (strcmp(dsKhach[i].sdt, dsXe[idxXe].sdtNguoiThue) == 0) {
            kh = &dsKhach[i];
            break;
        }
    }

    soGio = docSoNguyen("Nhap so gio thue (lon hon 0): ", 1, 1000000);
    phiHuHong = docSoTien("Nhap phi sua chua hu hong (0 neu khong co): ");

    loai = dsXe[idxXe].loai;
    tienThueGoc = tinhTienThue(loai, soGio);
    tienThueThucTe = tienThueGoc;

    /* Khach quen la khach co it nhat 3 lan thue da hoan tat truoc lan nay */
    if (kh != NULL && kh->soLanThue >= 3) {
        tienThueThucTe = tienThueGoc * 95 / 100;
    }

    coc = TIEN_COC[loai - 1];
    tongThanhToan = tienThueThucTe + phiHuHong;
    chenhLech = coc - tongThanhToan;

    printf("\n--- HOA DON TRA XE ---\n");
    printf("Tien thue goc: %lld VND\n", tienThueGoc);
    if (kh != NULL && kh->soLanThue >= 3) {
        printf("Giam gia khach quen 5%%: -%lld VND\n",
               tienThueGoc - tienThueThucTe);
    }
    printf("Tien thue sau giam gia: %lld VND\n", tienThueThucTe);
    printf("Phi hu hong: %lld VND\n", phiHuHong);
    printf("Tien coc da nop: %lld VND\n", coc);

    if (chenhLech >= 0) {
        printf("Tien hoan lai cho khach: %lld VND\n", chenhLech);
    } else {
        printf("Tien coc khong du, khach can tra them: %lld VND\n", -chenhLech);
    }

    docChuoi("Xac nhan da thu them/hoan tien va ket toan xong? (Y/N): ",
             xacNhan, sizeof(xacNhan));
    if (toupper((unsigned char)xacNhan[0]) != 'Y' || xacNhan[1] != '\0') {
        printf("Chua ket toan. Giu nguyen trang thai xe dang thue; vui long thuc hien lai sau.\n");
        return;
    }

    /* Ghi nhan doanh thu thue rieng; phi sua chua duoc theo doi rieng */
    doanhThu[loai - 1] += tienThueThucTe;
    *tongPhiSuaChua += phiHuHong;

    dsXe[idxXe].dangThue = 0;
    dsXe[idxXe].soLanThue++;
    strcpy(dsXe[idxXe].sdtNguoiThue, "");
    if (kh != NULL) {
        kh->soLanThue++;
    }
    printf("Da cap nhat trang thai xe: xe hien con trong.\n");
}

void lietKeXeDangThue(XeThue dsXe[], int nXe) {
    int i, dem = 0;
    printf("\n--- DANH SACH XE DANG CHO THUE ---\n");

    for (i = 0; i < nXe; i++) {
        if (dsXe[i].dangThue == 1) {
            printf("Ma: %-8s | Loai: %-10s | Bien so: %-12s | SDT khach: %s\n",
                   dsXe[i].maXe, tenLoaiXe(dsXe[i].loai),
                   dsXe[i].bienSo, dsXe[i].sdtNguoiThue);
            dem++;
        }
    }
    if (dem == 0) {
        printf("Hien khong co xe nao dang cho thue.\n");
    }
}

void thongKe(const XeThue dsXe[], int nXe, const KhachThue dsKhach[],
             int nKhach, const long long doanhThu[], long long tongPhiSuaChua) {
    int i, maxIdx = -1, demKhach = 0;
    long long tongDoanhThu = 0;

    printf("\n--- BAO CAO THONG KE ---\n");
    for (i = 0; i < 3; i++) {
        printf("Doanh thu cho thue %s: %lld VND\n",
               tenLoaiXe(i + 1), doanhThu[i]);
        tongDoanhThu += doanhThu[i];
    }
    printf("Tong doanh thu cho thue: %lld VND\n", tongDoanhThu);
    printf("Tong phi sua chua thu duoc: %lld VND\n", tongPhiSuaChua);

    /* Chi thong ke xe co phat sinh luot thue */
    for (i = 0; i < nXe; i++) {
        if (dsXe[i].soLanThue > 0 &&
            (maxIdx == -1 || dsXe[i].soLanThue > dsXe[maxIdx].soLanThue)) {
            maxIdx = i;
        }
    }

    if (maxIdx == -1) {
        printf("Chua co xe nao duoc thue.\n");
    } else {
        printf("Xe duoc thue nhieu nhat: %s (%s) - %d lan\n",
               dsXe[maxIdx].maXe, tenLoaiXe(dsXe[maxIdx].loai),
               dsXe[maxIdx].soLanThue);
    }

    printf("Danh sach khach quen (tu 3 lan thue tro len):\n");
    for (i = 0; i < nKhach; i++) {
        if (dsKhach[i].soLanThue >= 3) {
            printf("- %s (SDT: %s) - %d lan thue\n",
                   dsKhach[i].hoTen, dsKhach[i].sdt, dsKhach[i].soLanThue);
            demKhach++;
        }
    }
    if (demKhach == 0) {
        printf("Chua co khach quen nao.\n");
    }
}
