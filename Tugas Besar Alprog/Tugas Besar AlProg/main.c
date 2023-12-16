#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#define MAX_KARYAWAN 100
#define MAX_NIP_LEN 20
#define MAX_NAMA_LEN 100
#define MAX_JABATAN_LEN 100
#define MAX_PW_LEN 50
#define MAX_ANAK_LEN 5

#define LEMBUR 45000
#define TUNJANGAN_MAKAN 20000
#define TUNJANGAN_ANAK 125000

// per bulan
#define GAJI_DIREKTUR 10010000
#define GAJI_MANAJER 9022000
#define GAJI_SUPERVISOR 8008000
#define SEKRE_BENDAHARA 8008000
#define GAJI_KADIV 7020000
#define GAJI_WAKADIV 6006000
#define GAJI_STAFFDIV 4524000
#define CLEANING_SERVIS 4004000

// per hari
#define GAJI_DIREKTUR_HARIAN 385000
#define GAJI_MANAJER_HARIAN 347000
#define GAJI_SUPERVISOR_HARIAN 308000
#define SEKRE_BENDAHARA_HARIAN 308000
#define GAJI_KADIV_HARIAN 270000
#define GAJI_WAKADIV_HARIAN 231000
#define GAJI_STAFFDIV_HARIAN 174000
#define CLEANING_SERVIS_HARIAN 154000

struct karyawan
{
    char nama[MAX_NAMA_LEN];
    char nip[MAX_NIP_LEN];
    char jabatan[MAX_JABATAN_LEN];
    char anak[MAX_ANAK_LEN];
    char password[MAX_PW_LEN];
};
struct karyawan dataFiletxt[MAX_KARYAWAN];
int incrementKaryawan = 0;
void inputDataBaru(), login(), menuPilihanJabatan(), menuMasuk(char NIP[50], char nama[50], char anak[2], char jabatan[50]), absensi(char NIP[50], char nama[50], char anak[2], char jabatan[50]), hitungGaji(char NIP[50], char nama[50], char anak[2], char jabatan[50]);

int validasiMasuk()
{
    int pilihan, nilaiScanf;
    char enter;
    nilaiScanf = scanf("%d%c", &pilihan, &enter);
    if (nilaiScanf != 2 || pilihan < 0 || pilihan > 2 || enter != '\n')
    {
        fflush(stdin);
        printf("\n\t\t\t\t\t\t\e[31mInput tidak valid\e[0m");
        printf("\n\t\t\t\t\t\t\e[35mInput pilihan kembali :\e[0m");
        return validasiMasuk();
    }
    else
    {
        return pilihan;
    }
}
int validasiJamLembur()
{
    int angka, nilaiScanf;
    char enter;
    nilaiScanf = scanf("%d%c", &angka, &enter);
    if (nilaiScanf != 2 || angka < 0 || angka > 40 || enter != '\n')
    {
        fflush(stdin);
        printf("\n\t\t\t\t\t\t\e[31mInput tidak valid\e[0m");
        printf("\n\t\t\t\t\t\t\e[35mInput pilihan kembali :\e[0m");
        return validasiJamLembur();
    }
    else
    {
        return angka;
    }
}
int validasiAngka()
{
    int angka, nilaiScanf;
    char enter;
    nilaiScanf = scanf("%d%c", &angka, &enter);
    if (nilaiScanf != 2 || enter != '\n')
    {
        fflush(stdin);
        printf("\n\t\t\t\t\t\t\e[31mInput tidak valid\e[0m");
        printf("\n\t\t\t\t\t\t\e[35mInput pilihan kembali :\e[0m");
        return validasiAngka();
    }
    else
    {
        return angka;
    }
}
int validasiJabatan()
{
    int pilihan, nilaiScanf;
    char enter;
    nilaiScanf = scanf("%d%c", &pilihan, &enter);
    if (nilaiScanf != 2 || pilihan < 1 || pilihan > 9 || enter != '\n')
    {
        fflush(stdin);
        printf("\n\t\t\t\t\t\t\e[31mInput tidak valid\e[0m");
        printf("\n\t\t\t\t\t\t\e[35mInput pilihan kembali :\e[0m");
        return validasiJabatan();
    }
    else
    {
        return pilihan;
    }
}

int validasiNip(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

void barisAtas()
{
    printf("\n\t\t\t\t\t\x1b[1m\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
}

void barisBawah()
{
    printf("\n\t\t\t\t\t\xc3\xc4\xc4\xc4\xC1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4\x1b[m");
}
void hitungGaji(char NIP[50], char nama[50], char anak[2], char jabatan[50])
{
    int gajiPokok, totalGaji, biayaHarian, gajiHarian;
    int biayaJabatan;
    int gajiBersihSebulan, gajiBersihSetahun;
    int PTKP, PPH21Terutang, PPH21;
    int tunjanganAnak, tunjanganMakan;
    int tempAnak;
    int gajiPPH;
    int jamLembur, lembur;
    int hariCuti, cuti;
    char tempNIP[50];

    strcpy(tempNIP, NIP);
    FILE *fp = fopen(strcat(tempNIP, ".txt"), "r");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\t\e[31mFile tidak di temukan !!!\e[0m");
        return;
    }
    int hariMasuk = 0;
    char status;
    while ((status = fgetc(fp)) != EOF)
    {
        if (status == 'H')
        {
            hariMasuk++;
        }
    }
    fclose(fp);

    system("cls");

    printf("\n\t\t\t\x1b[1m\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
    printf("\n\t\t\t \e[96mSelamat datang\e[0m \e[32m%s\e[0m", nama);
    printf("\n\t\t\t \e[96mNip\e[0m     : \e[32m%s\e[0m", NIP);
    printf("\n\t\t\t \e[96mJabatan\e[0m : \e[32m%s\e[0m", jabatan);

    printf("\n\t\t\t\t\t Masukan total jam lembur(maks : 40) : ");
    jamLembur = validasiJamLembur();

    printf("\n\t\t\t\t Masukan banyak hari cuti : ");
    hariCuti = validasiAngka();

    if (strcmp(jabatan, "Direktur") == 0)
    {
        gajiPokok = GAJI_DIREKTUR;
        biayaHarian = GAJI_DIREKTUR_HARIAN;
    }
    if (strcmp(jabatan, "Manajer") == 0)
    {
        gajiPokok = GAJI_MANAJER;
        biayaHarian = GAJI_MANAJER_HARIAN;
    }
    if (strcmp(jabatan, "Supervisor") == 0)
    {
        gajiPokok = GAJI_SUPERVISOR;
        biayaHarian = GAJI_SUPERVISOR_HARIAN;
    }
    if (strcmp(jabatan, "Bendahara") == 0)
    {
        gajiPokok = SEKRE_BENDAHARA;
        biayaHarian = SEKRE_BENDAHARA_HARIAN;
    }
    if (strcmp(jabatan, "Sekretaris") == 0)
    {
        gajiPokok = SEKRE_BENDAHARA;
        biayaHarian = SEKRE_BENDAHARA_HARIAN;
    }
    if (strcmp(jabatan, "Kadiv") == 0)
    {
        gajiPokok = GAJI_KADIV;
        biayaHarian = GAJI_KADIV_HARIAN;
    }
    if (strcmp(jabatan, "Wakadiv") == 0)
    {
        gajiPokok = GAJI_WAKADIV;
        biayaHarian = GAJI_WAKADIV_HARIAN;
    }
    if (strcmp(jabatan, "StaffDiv") == 0)
    {
        gajiPokok = GAJI_STAFFDIV;
        biayaHarian = GAJI_STAFFDIV_HARIAN;
    }
    if (strcmp(jabatan, "Cleaning Service") == 0)
    {
        gajiPokok = CLEANING_SERVIS;
        biayaHarian = CLEANING_SERVIS_HARIAN;
    }

    tempAnak = atoi(anak);
    if(tempAnak == 1){
        tunjanganAnak = TUNJANGAN_ANAK;
    }else if(tempAnak == 2){
        tunjanganAnak = 2 * TUNJANGAN_ANAK;
    }else if(tempAnak == 3){
        tunjanganAnak = 3 * TUNJANGAN_ANAK;
    }

    cuti = hariCuti * biayaHarian;
    lembur = jamLembur * LEMBUR;
    tunjanganMakan = TUNJANGAN_MAKAN * hariMasuk;

    biayaJabatan = gajiPokok * 5/100;
    gajiBersihSebulan = gajiPokok - biayaJabatan;
    gajiBersihSetahun = gajiBersihSebulan * 12;
    PTKP = gajiBersihSetahun - 54000000;
    PPH21Terutang = PTKP * 5/100;
    PPH21 = PPH21Terutang / 12;
    gajiPPH = gajiPokok - PPH21;

    gajiHarian = hariMasuk * biayaHarian;
    totalGaji = gajiHarian + tunjanganAnak + tunjanganMakan;

    barisAtas();
    printf("\n\xb3\t\t      Selamat datang\t\t\t\xb3\n");
    printf("\xb3\t         %s - %s - %-10s\t\t\xb3\n", NIP, nama, jabatan);
    barisBawah();
    printf("\nBanyak hari masuk: %d\n", hariMasuk);
    printf("Biaya Tunjangan Makan:      Rp.%d\n", tunjanganMakan);
    printf("Biaya Tunjangan anak:       Rp.%d\n", tunjanganAnak);
    printf("Gaji Lembur:                Rp.%d\n", lembur);
    printf("Gaji dipotong PPH:          Rp.%d\n", PPH21); 
    printf("Potongan Cuti:              Rp.%d\n", cuti);
    printf("Total Gaji anda:            Rp.%d\n\n", totalGaji);


    // ulang();
}
void absensi(char NIP[50], char nama[50], char anak[2], char jabatan[50])
{
    char absen;
    char tempNip[50];
    int repeat = 0;
    strcpy(tempNip, NIP);
    FILE *fp = fopen(strcat(tempNip, ".txt"), "a+");
    while (repeat != 1)
    {
        printf("\n\t\t\t\t\t \e[31mApakah ingin absen hari ini??? (y/n)\e[0m");
        printf("\n\t\t\t\t\t    \e[31m-->>\e[0m"), scanf("%c", &absen);
        

        if (absen == 'y' || absen == 'Y')
        {
            fprintf(fp, "H\n");
            printf("\n\t\t\t\t\t \e[32mAnda berhasil absen hari ini\e[0m");
            repeat++;
        }
        else if (absen == 'N' || absen == 'n')
        {
            printf("\n\t\t\t\t\t \e[31m Anda akan dikembalikan ke menu\e[0m");
            repeat++;
        }
    }
    fclose(fp);
    printf("\n\t\t\t\t\t \e[32mTekan enter untuk lanjut...\e[0m");
    while (_getch() != '\r')
        ;
        system("cls");
    menuMasuk(NIP, nama, anak, jabatan);
}
void menuMasuk(char NIP[50], char nama[50], char anak[2], char jabatan[50])
{
    int pilihan;
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[34mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3\x1b[1m                           \e[34mPT. Toko Kita\e[0m                         \xb3\e[0m");
    printf("\n\t\t\t\t\t\xb3               \e[34mWelcome : %-2s - %-2s - %-25s\e[0m\xb3", NIP, nama, jabatan);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3\e[32mNo.\e[0m\xb3  \e[31mSilahkan pilih menu di bawah ini\e[0m                           \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m1.\e[0m\xb3  \e[31mAbsensi Kehadiran\e[0m                                          \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m2.\e[0m\xb3  \e[31mHitung Gaji\e[0m                                                \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m"), pilihan = validasiMasuk();
    switch (pilihan)
    {
    case 1:
        absensi(NIP, nama, anak, jabatan);
        break;
    case 2:
        hitungGaji(NIP, nama, anak, jabatan);
        break;
    }
}

void menu()
{
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    int pilihan;
    system("cls");
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[34mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3\x1b[1m                           \e[34mPT. Toko Kita\e[0m                         \xb3\e[0m");
    printf("\n\t\t\t\t\t\xb3                      \e[34mDated : %-2d - %-2d - %-5d\e[0m                    \xb3", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3\e[32mNo.\e[0m\xb3  \e[31mSilahkan pilih menu di bawah ini\e[0m                           \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m1.\e[0m\xb3  \e[31mLogin\e[0m                                                      \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m2.\e[0m\xb3  \e[31mInput data karyawan baru\e[0m                                   \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m0.\e[0m\xb3  \e[31mKeluar          \e[0m                                           \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m"), pilihan = validasiMasuk();
    if (pilihan == 1)
    {
        system("cls");
        login();
    }
    else if (pilihan == 2)
    {
        system("cls");
        inputDataBaru();
    }
    else
    {
        system("cls");
        barisAtas();
        printf("\n\t\t\t\t\t\xb3           \e[32mTerimakasih Telah Menggunakan Program Kami\e[0m            \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
    }
}
void inputDataBaru()
{
    int pilihan;
    struct karyawan new;
    FILE *fp = fopen("dataKaryawan.txt", "w");
    if (fp == NULL)
    {
        barisAtas();
        printf("\n\t\t\t\t\t\xb3           \e[31mGagall Membuka File\e[0m                     \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
        return;
    }
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                       \e[32m Input Data Karyawan\e[0m                      \xb3");
    printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
    printf("\n\t\t\t\t\tMasukan NIP anda :");
    scanf("%s", new.nip);

    if (!validasiNip(new.nip))
    {
        
        barisAtas();
        printf("\n\t\t\t\t\t\xb3        \e[32mInput tidak Valid! Tolong Masukan NIP yang valid\e[0m      \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
        inputDataBaru();
    }

    for (int i = 0; i < incrementKaryawan; ++i)
    {
        if (strcmp(new.nip, dataFiletxt[i].nip) == 0)
        {
            barisAtas();
            printf("\n\t\t\t\t\t\xb3           \e[32mNIP sudah ada! Tolong Masukan NIP kembali!!!\e[0m            \xb3");
            printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
            inputDataBaru();
        }
    }
    printf("\n\t\t\t\t\tMasukan nama anda :");
    scanf("%s", new.nama);

    menuPilihanJabatan();
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m"), pilihan = validasiJabatan();
    switch (pilihan)
    {
    case 1:
        strcpy(new.jabatan, "Direktur");
        break;
    case 2:
        strcpy(new.jabatan, "Manajer");
        break;
    case 3:
        strcpy(new.jabatan, "Supervisor");
        break;
    case 4:
        strcpy(new.jabatan, "Bendahara");
        break;
    case 5:
        strcpy(new.jabatan, "Sekretaris");
        break;
    case 6:
        strcpy(new.jabatan, "Kadiv");
        break;
    case 7:
        strcpy(new.jabatan, "Wakadiv");
        break;
    case 8:
        strcpy(new.jabatan, "StaffDiv");
        break;
    case 9:
        strcpy(new.jabatan, "Cleaning Service");
        break;
    }

    printf("\n\t\t\t\t\tMasukan jumlah anak anda: ");
    scanf("%s", new.anak);
    printf("\n\t\t\t\t\tSilahkan buat password anda: ");
    scanf("%s", new.password);

    strcpy(dataFiletxt[incrementKaryawan].nip, new.nip);
    strcpy(dataFiletxt[incrementKaryawan].nama, new.nama);
    strcpy(dataFiletxt[incrementKaryawan].jabatan, new.jabatan);
    strcpy(dataFiletxt[incrementKaryawan].anak, new.anak);
    strcpy(dataFiletxt[incrementKaryawan].password, new.password);
    incrementKaryawan++;

    for (int i = 0; i < incrementKaryawan; ++i)
    {
        fprintf(fp, "%s,%s,%s,%s,%s\n", dataFiletxt[i].nip, dataFiletxt[i].nama, dataFiletxt[i].jabatan, dataFiletxt[i].anak, dataFiletxt[i].password);
    }

    fclose(fp);

    
    printf("\n\t\t\t\t\t\e[32mData ==>> %s - %s - %s\e[0m              ", new.nip, new.nama, new.jabatan);
    printf("\n\t\t\t\t\t\e[31mData berhasil dimasukan, silahkan login kembali\e[0m");
    printf("\n\t\t\t\t\tTekan enter untuk lanjut.....");
    while(_getch() != '\r');
    system("cls");
    menu();
}

void menuPilihanJabatan()
{
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    system("cls");
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[34mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3\x1b[1m                           \e[34mPT. Toko Kita\e[0m                         \xb3\e[0m");
    printf("\n\t\t\t\t\t\xb3                      \e[34mDated : %-2d - %-2d - %-5d\e[0m                    \xb3", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3\e[32mNo.\e[0m\xb3  \e[32mSilahkan pilih jabatan anda\e[0m                                \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m1.\e[0m\xb3  \e[31mDirektur\e[0m                                                   \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m2.\e[0m\xb3  \e[31mManajer\e[0m                                                    \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m3.\e[0m\xb3  \e[31mSupervisor          \e[0m                                       \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m4.\e[0m\xb3  \e[31mBendahara          \e[0m                                        \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m5.\e[0m\xb3  \e[31mSekretaris          \e[0m                                       \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m6.\e[0m\xb3  \e[31mKadiv          \e[0m                                            \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m7.\e[0m\xb3  \e[31mWakadiv          \e[0m                                          \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m8.\e[0m\xb3  \e[31mStaffDiv          \e[0m                                         \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m9.\e[0m\xb3  \e[31mCleaning Service          \e[0m                                 \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
}

void login()
{
    system("cls");
    char cariNip[MAX_NIP_LEN];
    char cariPassword[MAX_PW_LEN];
    char NIP[50];
    char nama[50];
    char jabatan[50];
    char ch;
    char anak[2];
    int match = 0;

    barisAtas();
    printf("\n\t\t\t\t\t\xb3                        \e[32mSilahkan Login\e[0m                           \xb3");
    printf("\n\t\t\t\t\t\xc3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
    printf("\n\t\t\t\t\t\xc3 \e[32m Masukan NIP anda : \e[0m"), scanf("%s", cariNip);
    for (int i = 0; i < incrementKaryawan; ++i)
    {
        if (strcmp(cariNip, dataFiletxt[i].nip) == 0)
        {
            while (!match)
            {
                int j = 0;
                printf("\n\t\t\t\t\t\t \e[32mPassword :\e[0m ");
                while ((ch = _getch()) != '\r' && j < 49)
                {
                    if (ch == '\b' && j > 0)
                    {
                        printf("\b \b");
                        j--;
                        continue;
                    }
                    cariPassword[j] = ch;
                    printf("*");
                    j++;
                }
                cariPassword[j] = '\0';

                if (strcmp(cariPassword, dataFiletxt[i].password) == 0)
                {
                    match++;
                    strcpy(NIP, dataFiletxt[i].nip);
                    strcpy(nama, dataFiletxt[i].nama);
                    strcpy(anak, dataFiletxt[i].anak);
                    strcpy(jabatan, dataFiletxt[i].jabatan);
                    system("cls");
                    menuMasuk(NIP, nama, anak, jabatan);
                    return;
                }
                else
                {
                    system("cls");
                    printf("\n\t\t\t\t\t \e[31mPassword salah\e[0m");
                    printf("\n\t\t\t\t\t\e[32mSilahkan masukan password kembali\e[0m");
                }
            }
        }
    }
    printf("\n\t\t\t\t\t\e[31mNIP anda salah, mohon log in ulang\e[0m");
    printf("\n\t\t\t\t\t\e[32mTekan ENTER untuk lanjut...\e[0m");
    while (_getch() != '\r')
        ;
    login();
}
int main()
{
    FILE *fp = fopen("dataKaryawan.txt", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                      dataFiletxt[incrementKaryawan].nip,
                      dataFiletxt[incrementKaryawan].nama,
                      dataFiletxt[incrementKaryawan].anak,
                      dataFiletxt[incrementKaryawan].jabatan,
                      dataFiletxt[incrementKaryawan].password) == 5)
        {
            incrementKaryawan++;
        }
        fclose(fp);
        menu();
    }
    else
    {
        FILE *newFile = fopen("dataKaryawan.txt", "w");
        if (newFile != NULL)
        {
            // Tulis ke file atau lakukan operasi lainnya
            fclose(newFile);
        }
        else
        {
            printf("Gagal membuat file baru");
        }
        menu();
    }
    return 0;
}