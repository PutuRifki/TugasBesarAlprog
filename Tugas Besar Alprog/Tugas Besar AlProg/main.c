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

struct Tanggal
{
    char hari[100];
    char jam[100];
    char hadir[100];
};

struct hariLibur
{
    char date[100];
    char holiday[100];
};

struct hariLibur libur[100];
int counterLibur = 0;

struct Tanggal tgl[100];
int countTanggal = 0;

struct karyawan dataFiletxt[MAX_KARYAWAN];
int incrementKaryawan = 0;
void inputDataBaru(), login(), menu(), menuPilihanJabatan();
void menuMasuk(char NIP[50], char nama[50], char jabatan[50], char anak[2]), absensi(char NIP[50], char nama[50], char jabatan[50], char anak[2]), hitungGaji(char NIP[50], char nama[50], char jabatan[50], char anak[2]);

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
void hitungGaji(char NIP[50], char nama[50], char jabatan[50], char anak[2])
{
    struct Tanggal tempTanggal;

    time_t t = time(NULL);
    struct tm *tm_info;
    char tmpTgl[50];
    char cekTgl[50];
    char tmpJam[50];
    tm_info = localtime(&t);
    
    strftime(tmpTgl, 50,"%A %d-%m-%Y", tm_info);
    strftime(tmpJam, 50, "%H:%M", tm_info);

    int pilihan;
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

    printf("\n\t\t\t\t\t\x1b[1m\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
    printf("\n\t\t\t\t\t\xb3                  \e[96mSelamat datang\e[0m \e[32m%-30s\e[0m  \xb3", nama);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[96mNip\e[0m     \xb3  \e[32m%-25s\e[0m                            \xb3", NIP);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[96mJabatan\e[0m \xb3  \e[32m%-25s\e[0m                            \xb3", jabatan);
    printf("\n\t\t\t\t\t\x1b[1m\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xC1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n\n");

    barisAtas();
    printf("\n\t\t\t\t\t\xb3                        \e[32mInput data karyawan\e[0m                      \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4\x1b[m");

    printf("\n\t\t\t\t\t  \e[32mMasukan total jam lembur(maks : 40) :\e[0m ");
    jamLembur = validasiJamLembur();
    printf("\n\t\t\t\t\t\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xc4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
    printf("\n\t\t\t\t\t  \e[32mMasukan banyak hari cuti :\e[0m ");
    hariCuti = validasiAngka();

    system("cls");

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
    }else if(tempAnak >= 3){
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
    printf("\n\t\t\t\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
    printf("\n\t\t\t\t\t\xBA                         \e[32mRincian Gaji\e[0m                            \xBA");
    printf("\n\t\t\t\t\t\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9\x1b[m");
    printf("\n\t\t\t\t\t\xBA \e[96mNama\e[0m    : %-35s                   \xBA", nama);
    printf("\n\t\t\t\t\t\xBA \e[96mJabatan\e[0m : %-35s                   \xBA", jabatan);
    printf("\n\t\t\t\t\t\xBA \e[96mTanggal\e[0m : %-25s                             \xBA", tmpTgl);
    printf("\n\t\t\t\t\t\xBA \e[96mJam\e[0m     : %-25s                             \xBA", tmpJam);
    printf("\n\t\t\t\t\t\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xD1\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9\x1b[m");
    printf("\n\t\t\t\t\t\xBA \e[96m Banyak hari masuk\e[0m     \xB3  \e[32m%-5d\e[0m Hari                            \xBA", hariMasuk);
    printf("\n\t\t\t\t\t\xC7\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB6");
    printf("\n\t\t\t\t\t\xBA \e[96m Banyak hari cuti\e[0m      \xB3  \e[32m%-5d\e[0m Hari                            \xBA", hariCuti);
    printf("\n\t\t\t\t\t\xC7\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB6");
    printf("\n\t\t\t\t\t\xBA \e[96m Banyak jam cuti\e[0m       \xB3  \e[32m%-5d\e[0m jam                             \xBA", jamLembur);
    printf("\n\t\t\t\t\t\x1b[1m\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xD8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9");
    printf("\n\t\t\t\t\t\xBA \e[96m Biaya tunjangan anak\e[0m  \xB3  \e[32m%-3d\e[0m Anak \e[31mx\e[0m Rp. \e[32m%-10d\e[0m             \xBA", tempAnak, TUNJANGAN_ANAK);
    printf("\n\t\t\t\t\t\xBA                        \xB3  = Rp. \e[32m%-10d\e[0m                      \xBA", tunjanganAnak);
    printf("\n\t\t\t\t\t\x1b[1m\xC7\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB6");
    printf("\n\t\t\t\t\t\xBA \e[96m Gaji Lembur \e[0m          \xB3  \e[32m%-3d\e[0m Jam \e[31mx\e[0m Rp. \e[32m%-10d\e[0m              \xBA", jamLembur, LEMBUR);
    printf("\n\t\t\t\t\t\xBA                        \xB3  = Rp. \e[32m%-10d\e[0m                      \xBA", lembur);
    printf("\n\t\t\t\t\t\x1b[1m\xC7\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB6");
    printf("\n\t\t\t\t\t\xBA \e[96m Gaji di potong PPH\e[0m    \xB3  \e[32m%-2d\e[0m Bulan \e[31m:\e[0m Rp. \e[32m%-10d\e[0m             \xBA", 12, PPH21Terutang);
    printf("\n\t\t\t\t\t\xBA                        \xB3  = Rp. \e[32m%-10d\e[0m                      \xBA", PPH21);
    printf("\n\t\t\t\t\t\x1b[1m\xC7\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB6");
    printf("\n\t\t\t\t\t\xBA \e[96m Potongan cuti     \e[0m    \xB3  \e[32m%-3d\e[0m hari \e[31mx\e[0m Rp. \e[32m%-10d\e[0m             \xBA",hariCuti, biayaHarian);
    printf("\n\t\t\t\t\t\xBA                        \xB3  = Rp. \e[32m%-10d\e[0m                      \xBA", cuti);    
    printf("\n\t\t\t\t\t\x1b[1m\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xD8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9");
    printf("\n\t\t\t\t\t\xBA \e[96m Total gaji anda\e[0m       \xB3  Rp. \e[32m%-10d\e[0m                        \xBA", totalGaji);
    printf("\n\t\t\t\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCF\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    printf("\n\t\t\t\t\t  \e[32mTekan enter untuk lanjut...\e[0m");
    while(_getch() != '\r');
    system("cls");

    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[34mTerimakasih Telah Bekerja Keras\e[0m                 \xb3");
    printf("\n\t\t\t\t\t\xb3\x1b[1m                  \e[34mSilahkan pilih menu di bawah\e[0m                   \xb3");
    printf("\n\t\t\t\t\t\xb3                        %-10s                       \xb3",tmpTgl); 
    printf("\n\t\t\t\t\t\xb3                               %-10s                        \xb3",tmpJam);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3\e[32mNo.\e[0m\xb3  \e[32mCetak slip gaji\e[0m                                            \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m1.\e[0m\xb3  \e[31mCetak\e[0m                                                      \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m2.\e[0m\xb3  \e[31mKembali ke menu awal\e[0m                                       \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m"),pilihan = validasiMasuk();
    system("cls");
    char nameForFile[100];
    if(pilihan == 1){
        FILE *print;
        sprintf(nameForFile,"%s", nama);
        printf("%s",nameForFile);
        print = fopen (strcat(nameForFile,".txt"), "a+");
        fprintf(print,"\n\t\t\t\t\t||=======================================================================");
        fprintf(print,"\n\t\t\t\t\t||                  Rincian Gaji                                       ||");
        fprintf(print,"\n\t\t\t\t\t||=======================================================================");
        fprintf(print,"\n\t\t\t\t\t|| Nama    : %-35s                      ||", nama);
        fprintf(print,"\n\t\t\t\t\t|| Jabatan : %-35s                      ||", jabatan);
        fprintf(print,"\n\t\t\t\t\t|| Tanggal : %-25s                                ||", tmpTgl);
        fprintf(print,"\n\t\t\t\t\t|| Jam     : %-25s                                ||", tmpJam);
        fprintf(print,"\n\t\t\t\t\t||=====================================================================||");
        fprintf(print,"\n\t\t\t\t\t|| Banyak hari masuk\e[0m            || %-5d Hari                     ||", hariMasuk);
        fprintf(print,"\n\t\t\t\t\t||---------------------------------------------------------------------||");
        fprintf(print,"\n\t\t\t\t\t|| Banyak hari cuti                  || %-5d Hari                                                            ||", hariCuti);
        fprintf(print,"\n\t\t\t\t\t||=====================================================================||");
        fprintf(print,"\n\t\t\t\t\t|| Biaya tunjangan anak              || %-3d Anak x Rp. %-10d                            ||", tempAnak, TUNJANGAN_ANAK);
        fprintf(print,"\n\t\t\t\t\t||                                   ||  = Rp. %-10d                   ||", tunjanganAnak);
        fprintf(print,"\n\t\t\t\t\t||---------------------------------------------------------------------||");
        fprintf(print,"\n\t\t\t\t\t|| Gaji Lembur                       ||  %-3d Jam x Rp. %-10d          ||", jamLembur, LEMBUR);
        fprintf(print,"\n\t\t\t\t\t||                                   ||  = Rp. %-10d                   ||", lembur);
        fprintf(print,"\n\t\t\t\t\t||---------------------------------------------------------------------||");
        fprintf(print,"\n\t\t\t\t\t|| Gaji di potong PPH                ||  Rp. %-10d : %-2d Bulan        ||", PPH21Terutang, 12);
        fprintf(print,"\n\t\t\t\t\t||                                   ||  = Rp. %-10d                   ||", PPH21);
        fprintf(print,"\n\t\t\t\t\t||---------------------------------------------------------------------||");
        fprintf(print,"\n\t\t\t\t\t|| Potongan cuti                     ||  %-3d hari x Rp. %-10d         ||",hariCuti, biayaHarian);
        fprintf(print,"\n\t\t\t\t\t||                                   ||  = Rp. %-10d                   ||", PPH21);    
        fprintf(print,"\n\t\t\t\t\t||=====================================================================||");
        fprintf(print,"\n\t\t\t\t\t|| Total gaji anda                   ||  Rp. %-10d                     ||", totalGaji);
        fprintf(print,"\n\t\t\t\t\t||=====================================================================||");
        fclose(print);
    }else{
        menu();
    }
}
void saveAbsen(char tempNIP[50]){
    FILE *file = fopen(tempNIP, "w");
    for(int i = 0; i < countTanggal; ++i){
        fprintf(file, "%s,%s,%s\n", tgl[i].hari, tgl[i].jam, tgl[i].hadir);
    }
    fclose(file);
}

void bacaFileAbsen(char tempNIP[50]){
    FILE *file = fopen(tempNIP, "r");
    countTanggal = 0;
    while(fscanf(file, "%[^,],%[^,],%[^\n]\n", tgl[countTanggal].hari, tgl[countTanggal].jam, tgl[countTanggal].hadir) == 3){
        countTanggal++;
    }
    fclose(file);
}

void createFileAbsen(char NIP[50], char nama[50], char jabatan[50], char anak[2]){
    char tempNIP[50];
    strcpy(tempNIP, NIP);
    FILE *file = fopen(strcat(tempNIP, ".txt"), "a+");
    fclose(file);
    bacaFileAbsen(tempNIP);
    absensi(NIP, nama, jabatan, anak);
}

int cekTanggalMerah(char tmpDate[], int kembali){
    FILE *fLibur = fopen("daftarTglMerah2023.txt", "r");

    int countHoly = 0;
    while(fscanf(fLibur, "%[^,],%[^\n]\n", libur[counterLibur].date, libur[counterLibur].holiday)==2 ){
        counterLibur++;
    }

    for(int i = 0; i < countHoly; ++i){
        if(strcmp(tmpDate, libur[i].date) == 0 ){
            printf("hari ini adalah%s\n", libur[i].holiday);
            printf("Silahkan menikmati hari libur anda\n");
            printf("Tekan ENTER untuk lanjut");
            while(_getch() != '\r');
            fclose(fLibur);
            return kembali = 1;
        }
    }
}

void absensi(char NIP[50], char nama[50], char jabatan[50], char anak[2])
{
    system("cls");
    struct Tanggal tempTanggal;
    time_t t = time(NULL);
    struct tm *tm_info;
    char tmpHari[50];
    char tmpTgl[50];
    char tmpJam[50];
    char tempNip[50];
    int absen;
    int kembali = 0;
    char cekTgl[50];
    tm_info = localtime(&t);
    strcpy(tempNip, NIP);
    strcpy(tmpTgl, "25-12-2023");



    char tempNIP[50];
    int repeat = 0;

    strftime(tmpTgl, 50,"%A %d-%m-%Y", tm_info);
    strftime(tmpJam, 50, "%H:%M", tm_info);

    kembali = cekTanggalMerah(tmpTgl, kembali);
    if(kembali==1){
        return menuMasuk(NIP, nama, anak, jabatan);
    }

    if(strcmp(tmpHari, "Sunday")==0){
        printf("Hari ini adalah hari minggu, apakah anda ingin lembur?\n");
        printf("1. Ya\n");
        printf("2. Tidak\n");
        printf("Pilihan anda: \n");
        printf("> ");
        absen = validasiMasuk();
        switch(absen){
            case 1 :
                printf("tst");
                return;
            break;

            case 2 :
                printf("Anda akan dikembalikan ke menu.\n");
                printf("Tekan ENTER untuk lanjut");
                while(_getch() != '\r');
                return menuMasuk(NIP, nama, anak, jabatan);
            break;
        }
    }


    strcpy(tempNIP, NIP);
    FILE *file = fopen(strcat(tempNIP,".txt"), "a+");


    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[34mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3\x1b[1m                  \e[34mSilahkan Absensi terlebih dahulu\e[0m               \xb3");
    printf("\n\t\t\t\t\t\xb3                        %-10s                       \xb3",tmpTgl);
    printf("\n\t\t\t\t\t\xb3                               %-10s                        \xb3",tmpJam);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3\e[96mNo.\e[0m\xb3  \e[32mApakah anda Ingin Absen Hari ini\e[0m                           \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m1.\e[0m\xb3  \e[31mSaya ingin absen\e[0m                                           \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m2.\e[0m\xb3  \e[31mSaya tidak ingin absen\e[0m                                     \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m"),absen = validasiMasuk();
    system("cls");
        if(absen==1){

            int sudahAbsen = 0;
            for(int i = 0; i < countTanggal; ++i){
                if(strcmp(tmpTgl, tgl[i].hari) == 0 ){
                    sudahAbsen = 1;
                    barisAtas();
                    printf("\n\t\t\t\t\t\xb3                \e[32mAnda telah berhasil melakukan absen\e[0m              \xb3");
                    printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");

                    printf("\n\t\t\t\t\t  \e[34mSilahkan absen besok.\e[0m");
                    printf("\n\t\t\t\t\t  \e[34mTekan ENTER untuk lanjut...\e[0m");
                    while(_getch() != '\r');
                    menuMasuk(NIP, nama, jabatan, anak);
                    break;
                }
            }

            if(!sudahAbsen && absen == 1){
            strcpy(tgl[countTanggal].hari, tmpTgl);
            strcpy(tgl[countTanggal].jam, tmpJam);
            strcpy(tgl[countTanggal].hadir, "H");
            countTanggal++;

            printf("%s", tgl[countTanggal].hari);
            printf("\n\t\t\t\t\t");
            barisAtas();
            printf("\n\t\t\t\t\t\xb3                    \e[32mAnda berhasil absen hari ini\e[0m                \xb3");
            printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");

            

            saveAbsen(tempNIP);
            fclose(file);
            printf("\n\t\t\t\t\t \e[31mTekan ENTER untuk lanjut...\e[0m");
            while(_getch() != '\r');
            return menuMasuk(NIP, nama, jabatan, anak);
            }
        }
        else if(absen==2){
            barisAtas();
            printf("\n\t\t\t\t\t\xb3                   \e[32mAnda akan dikembalikan ke menu\e[0m                \xb3");
            printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");

            printf("\n\t\t\t\t\t  \e[32mTekan ENTER untuk lanjut...\e[0m");
            while(_getch() != '\r');
            return menuMasuk(NIP, nama, jabatan, anak);
        }else{
            system("cls");
            printf("\n\t\t\t\t\t \e[31mPilihan anda salah.\e[0m");
        }

    fclose(file);
    printf("\n\t\t\t\t\t %s", absen);
    printf("\n\t\t\t\t\t %d", repeat);
    printf("\n\t\t\t\t\t \e[32mTekan ENTER untuk lanjut...\e[0m");
    while(_getch() != '\r');
    menuMasuk(NIP, nama, anak, jabatan);
}
void menuMasuk(char NIP[50], char nama[50], char jabatan[50], char anak[2])
{
    system("cls");
    int pilihan;
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[96mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3\x1b[1m                           \e[34mPT. Toko Kita\e[0m                         \xb3\e[0m");
    printf("\n\t\t\t\t\t\xb3                                                                 \xb3");
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
        createFileAbsen(NIP, nama, jabatan, anak);
        break;
    case 2:
        hitungGaji(NIP, nama, jabatan, anak);
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
    printf("\n\t\t\t\t\t\xb3                 \e[96mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3\x1b[1m                           \e[34mPT. Toko Kita\e[0m                         \xb3\e[0m");
    printf("\n\t\t\t\t\t\xb3                      \e[34mDated : %-2d - %-2d - %-5d\e[0m                    \xb3", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3\e[96mNo.\e[0m\xb3  \e[34mSilahkan pilih menu di bawah ini\e[0m                           \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m1.\e[0m\xb3  \e[31mLogin\e[0m                                                      \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m2.\e[0m\xb3  \e[31mInput data karyawan baru\e[0m                                   \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xC5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3 \e[32m0.\e[0m\xb3  \e[31mKeluar          \e[0m                                           \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
    printf("\n\t\t\t\t\t    \e[96m-->>\e[0m"), pilihan = validasiMasuk();
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
    printf("\n\t\t\t\t\t\xb3                        \e[32mInput data Karyawan baru\e[0m                 \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4\x1b[m");
    printf("\n\t\t\t\t\t\xb3 \e[32m Masukan NIP anda : \e[0m");
    scanf("%s", new.nip);
    getchar();

    if (!validasiNip(new.nip))
    {
        
        barisAtas();
        printf("\n\t\t\t\t\t\xb3        \e[32mInput tidak Valid! Tolong Masukan NIP yang valid\e[0m      \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
        return inputDataBaru();
    }

    for (int i = 0; i < incrementKaryawan; ++i)
    {
        if (strcmp(new.nip, dataFiletxt[i].nip) == 0)
        {
            barisAtas();
            printf("\n\t\t\t\t\t\xb3          \e[32mNIP sudah ada! Tolong Masukan NIP kembali!!!\e[0m           \xb3");
            printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
            inputDataBaru();
            fflush(stdin);
            return inputDataBaru();
            break;
        }
    }
    printf("\n\t\t\t\t\t\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xc4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
    printf("\n\t\t\t\t\t\xb3  \e[32mMasukan nama anda :\e[0m");
    fgets(new.nama, sizeof(new.nama), stdin);
    new.nama[strcspn(new.nama, "\n")] = '\0';

    menuPilihanJabatan();
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m");
    pilihan = validasiJabatan();
    system("cls");
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
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                    \e[96mInput data karyawan\e[0m                          \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4\x1b[m");
    printf("\n\t\t\t\t\t\xb3    \e[32mMasukan jumlah anak anda:\e[0m ");
    scanf("%s", new.anak);
    getchar();
    printf("\n\t\t\t\t\t\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xc4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
    printf("\n\t\t\t\t\t\xb3    \e[32mSilahkan buat password anda:\e[0m ");
    scanf("%s", new.password);
    getchar();

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

    printf("\n\t\t\t\t\t   \e[31mData ==>> %s - %s - %s\e[0m              ", new.nip, new.nama, new.jabatan);
    printf("\n\t\t\t\t\t   \e[32mberhasil dimasukan, silahkan login kembali\e[0m");
    printf("\n\t\t\t\t\t   \e[32mTekan enter untuk lanjut...\e[0m");
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
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4\x1b[m");
    printf("\n\t\t\t\t\t\xb3 \e[32m Masukan NIP anda : \e[0m"),scanf("%s", cariNip);
    
    for (int i = 0; i < incrementKaryawan; ++i)
    {
        if (strcmp(cariNip, dataFiletxt[i].nip) == 0)
        {
            while (!match)
            {
                int j = 0;
                printf("\n\t\t\t\t\t\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xc4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4");
                printf("\n\t\t\t\t\t\xb3   \e[32mPassword :\e[0m");
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
                    strcpy(jabatan, dataFiletxt[i].jabatan);
                    strcpy(anak, dataFiletxt[i].anak);
                    system("cls");
                    menuMasuk(NIP, nama, jabatan, anak);
                    return;
                }
                else
                {
                    printf("\n\t\t\t\t\t   \e[31mPassword tidak valid!!!, masukan kembali password\e[0m");
                }
            }
        }
    }
    printf("\n\t\t\t\t\t   \e[31mNIP anda salah, Anda akan \e[0m");
    printf("\n\t\t\t\t\t   \e[32mTekan ENTER untuk lanjut...\e[0m");
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
                      dataFiletxt[incrementKaryawan].jabatan,
                      dataFiletxt[incrementKaryawan].anak,
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
