#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

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
#define GAJI_DIREKTUR    10010000
#define GAJI_MANAJER     9022000
#define GAJI_SUPERVISOR  8008000
#define SEKRE_BENDAHARA  8008000
#define GAJI_KADIV       7020000
#define GAJI_WAKADIV     6006000
#define GAJI_STAFFDIV    4524000
#define CLEANING_SERVIS  4004000

// per hari :
#define GAJI_DIREKTUR_HARIAN    385000
#define GAJI_MANAJER_HARIAN     347000
#define GAJI_SUPERVISOR_HARIAN  308000
#define SEKRE_BENDAHARA_HARIAN  308000
#define GAJI_KADIV_HARIAN       270000
#define GAJI_WAKADIV_HARIAN     231000
#define GAJI_STAFFDIV_HARIAN    174000
#define CLEANING_SERVIS_HARIAN  154000

int validasiMenu(), validasiPilihJabatan(), cekNIP(const char *str);
void login(), inputData(), menu(), menuPilihanJabatan(); 
void hitungbiayaHarian(char NIP[255], char nama[255], char jabatan[255]);
void menuMasuk(char NIP[50], char nama[50], char anak[1], char jabatan[50]);
void absensi(char NIP[50], char nama[50], char anak[1], char jabatan[50]);
void gajiFixed(char NIP[255], char nama[255], char anak[1], char jabatan[255]);
int validasiMasuk();

void barisAtas(){
    printf("\x1b[1m\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
}

void barisBawah(){
    printf("\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
}


struct Karyawan
{
    char nama[MAX_NAMA_LEN];
    char NIP[MAX_NIP_LEN];
    char jabatan[MAX_JABATAN_LEN];
    char anak[MAX_ANAK_LEN];
    char password[MAX_PW_LEN];
};

struct Karyawan id_karyawan[MAX_KARYAWAN];
int counterKaryawan = 0;

void ulang(){
    int pilihan;
    printf("Apakah anda ingin ulang?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
    pilihan = validasiMasuk();
    if (pilihan==1)
    {
        menu();
    }else if(pilihan==2){
        system("cls");
        printf("Terimakasih");
        while(_getch() != '\r');
        system("cls");
    }
    
}
int validasiMenu(){
    int term;
    char enter;
    if(enter = scanf("%d%c", &term,&enter) != 2 || term < 1 || term > 3 || enter != '\n'){
        fflush(stdin);
        printf("\e[31mMasukan anda salah\e[0m\n");
        printf("Masukkan angka pengganti: ");
        return validasiMenu();
    }
    else{
        return term;
    }
}

int validasiPilihJabatan(){
    int term;
    char enter;
    if(enter = scanf("%d%c", &term,&enter) != 2 || term < 1 || term > 3 || enter != '\n'){
        fflush(stdin);
        printf("\e[31mMasukan anda salah\e[0m\n");
        printf("Masukkan angka pengganti: ");
        return validasiPilihJabatan();
    }
    else{
        return term;
    }
}

int validasiMasuk(){
    int term;
    char enter;
    if(enter = scanf("%d%c", &term,&enter) != 2 || term < 1 || term > 2 || enter != '\n'){
        fflush(stdin);
        printf("\e[31mMasukan anda salah\e[0m\n");
        printf("Masukkan angka pengganti: ");
        return validasiMasuk();
    }
    else{
        return term;
    }
}

void menuPilihanJabatan(){
    barisAtas();
    printf("\n\xb3\t\t   Pilih Jabatan anda: \t\t\t\xb3\n");
    printf("\xb3\t\t   1. Direktur \t\t\t\t\xb3\n");
    printf("\xb3\t\t   2. Manajer \t\t\t\t\xb3\n");
    printf("\xb3\t\t   3. Supervisor \t\t\t\xb3\n");
    barisBawah();
}

int cekNIP(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int validasiLembur(){
    int term;
    char enter;
    if(enter = scanf("%d%c", &term,&enter) != 2 || term < 1 || term > 40 || enter != '\n'){
        fflush(stdin);
        printf("\e[31mTotal Jam Lembur anda Lebih!\e[0m\n");
        printf("Masukkan kembali total jam lembur: ");
        return validasiLembur();
    }
    else{
        return term;
    }
}

void menu(){
    int pilihan;
    
    system("cls");
    barisAtas();
    printf("\n\xb3\t\tSilahkan pilih menu:     \t\t\xb3\n");
    printf("\xb3\t\t1. Login \t\t\t\t\xb3\n");
    printf("\xb3\t\t2. Input Data Karyawan Baru \t\t\xb3\n");
    printf("\xb3\t\t3. Keluar \t\t\t\t\xb3\n");
    barisBawah();
    printf("\nPilihan anda: ");
    pilihan = validasiMenu();
    if(pilihan==1){
        login();
    }
    else if(pilihan==2){
        inputData();
    }else if(pilihan==3){
        printf("Terimakasih");
    }
}

void gajiFixed(char NIP[255], char nama[255], char anak[1], char jabatan[255]){
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
    FILE *file = fopen(strcat(tempNIP, ".txt"), "r");
    if(file == NULL){
        printf("File tidak ditemukan.");
        return;
    }
    int hariMasuk = 0;
    char status;
    while((status = fgetc(file)) != EOF){
        if(status == 'H'){
            hariMasuk++;
        }
    }
    fclose(file);


    system("cls");
    printf("Selamat datang %s - %s - %s\n", NIP,nama,jabatan);

    printf("Masukkan total jam lembur (Maks 40): ");
    jamLembur = validasiLembur();

    printf("Masukkan banyak hari cuti: ");
    scanf("%d", &hariCuti);

    if(strcmp(jabatan, "Direktur") == 0){
        gajiPokok = GAJI_DIREKTUR;
        biayaHarian = GAJI_DIREKTUR_HARIAN;
    }
    else if(strcmp(jabatan, "Manajer") == 0){
        gajiPokok = GAJI_MANAJER;
        biayaHarian = GAJI_MANAJER_HARIAN;
    }
    else if(strcmp(jabatan, "Supervisor") == 0){
        gajiPokok = GAJI_SUPERVISOR;
        biayaHarian = GAJI_SUPERVISOR_HARIAN;
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
    PPH21 = PPH21Terutang/12;
    gajiPPH = gajiPokok - PPH21;

    gajiHarian = hariMasuk * biayaHarian;
    totalGaji = gajiHarian + tunjanganAnak + tunjanganMakan + lembur - PPH21 - cuti;

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
    ulang();

    // printf("\n\t\t ========================================================");
    // printf("\n\t\t ||                    \e[96mRincian Gaji\e[0m                    ||");
    // printf("\n\t\t ========================================================");
    // printf("\n\t\t | Maks. jam kerja/hari         = %.0lf jam                 |",);
    // printf("\n\t\t | Jam kerja                    = %-2.0lf jam                |",);
    // printf("\n\t\t | Lembur                       = %-2.0lf jam                |",kerja.jamLembur);
    // printf("\n\t\t ========================================================");
    // printf("\n\t\t | Gaji pokok    = %-2.0lf x Rp. %-10.0lf                  |",);
    // printf("\n\t\t |               = Rp. %-20.0lf             |",);
    // printf("\n\t\t |                                                      |");
    // printf("\n\t\t | Gaji lembur   = %-2.0lf x Rp. %-10.0lf                  |",);
    // printf("\n\t\t |               = Rp. %-20.0lf             |",);
    // printf("\n\t\t |                                                      |");
    // printf("\n\t\t | Total Gaji    = Rp. %-5.0lf + Rp. %-10.0lf           |",k);
    // printf("\n\t\t |               = Rp. %-20.0lf             |",);
    // printf("\n\t\t ========================================================");
    // printf("\n\t\t || Gaji anda    = Rp. %-20.0lf            ||",);
    // printf("\n\t\t ========================================================");
    // printf("\n\t\t");
}

void hitungbiayaHarian(char NIP[255], char nama[255], char jabatan[255]){
    int gajiPokok, totalGaji;
    char tempNIP[50];
    strcpy(tempNIP, NIP);
    system("cls");

    FILE *file = fopen(strcat(tempNIP, ".txt"), "r");
    if(file == NULL){
        printf("File tidak ditemukan.");
        return;
    }
    int hariMasuk = 0;
    char status;
    while((status = fgetc(file)) != EOF){
        if(status == 'H'){
            hariMasuk++;
        }
    }
    fclose(file);

    printf("Selamat datang %s - %s - %s\n", NIP,nama,jabatan);
    printf("Total Kehadiran (Hari): %d\n", hariMasuk);

    if(strcmp(jabatan, "Direktur") == 0){
        gajiPokok = GAJI_DIREKTUR_HARIAN;
    }
    else if(strcmp(jabatan, "Manajer") == 0){
        gajiPokok = GAJI_MANAJER_HARIAN;
    }
    else if(strcmp(jabatan, "Supervisor") == 0){
        gajiPokok = GAJI_SUPERVISOR_HARIAN;
    }

    totalGaji = (gajiPokok * hariMasuk) + (hariMasuk * TUNJANGAN_MAKAN);

    printf("Total gaji anda: Rp.%d", totalGaji);
}

void absensi(char NIP[50], char nama[50], char anak[1], char jabatan[50]){
    system("cls");

    char absen;
    char tempNIP[50];
    int repeat = 0;

    strcpy(tempNIP, NIP);
    FILE *file = fopen(strcat(tempNIP, ".txt"), "a+");
    while(repeat != 1){
        printf("Apakah anda ingin absen hari ini? (y/n)\n");
        printf("Pilihan anda:\n");
        scanf("%c", &absen);
        getchar();

        if(absen == 'Y' || absen == 'y'){
            fprintf(file, "H\n");
            printf("Anda berhasil absen untuk hari ini!\n");
            repeat++;
        }
        else if(absen == 'N' || absen == 'n'){
            printf("Anda akan dikembalikan ke menu.\n");
            repeat++;
        }else{
            system("cls");
            printf("Pilihan anda salah.\n");
        }
    }
    fclose(file);
    printf("Tekan ENTER untuk lanjut");
    while(_getch() != '\r');
    menuMasuk(NIP, nama, anak, jabatan);
}

void menuMasuk(char NIP[50], char nama[50], char anak[1], char jabatan[50]){
    int pilihan;
    system("cls");
    barisAtas();
    printf("\n\xb3\t\t      Selamat datang\t\t\t\xb3\n");
    printf("\xb3\t         %s - %s - %-10s\t\t\xb3\n", NIP, nama, jabatan);
    barisBawah();
    printf("\nSilahkan pilih dibawah ini.\n");
    printf("1. Absen Kehadiran\n");
    printf("2. Hitung gaji\n");
    printf("Pilihan anda: ");
    pilihan = validasiMasuk();
    switch(pilihan){
        case 1 :
            absensi(NIP, nama, anak, jabatan);
        break;

        case 2 :
            // hitungbiayaHarian(NIP, nama, jabatan);
            gajiFixed(NIP, nama, anak, jabatan);
        break;
    }
}

void inputData(){
    struct Karyawan newKaryawan;

    FILE *fp = fopen("dataKaryawan.txt", "w");
    if(fp==NULL){
        printf("Gagal Membuka File");
        return;
    }

    printf("Masukkan NIP anda: ");
    scanf("%s", newKaryawan.NIP);

    if(!cekNIP(newKaryawan.NIP)){
        printf("NIP tidak Valid! Tolong masukkan NIP yang valid!\n");
        inputData();
        return;
    }
    
    for(int i = 0; i < counterKaryawan; ++i){
        if(strcmp(newKaryawan.NIP, id_karyawan[i].NIP)==0){
            printf("NIP sudah ada! Tolong masukkan NIP yang baru!\n");
            inputData();
        }
    }

    printf("Masukkan nama: ");
    scanf("%s", newKaryawan.nama);

    int pilihJabatan;
    menuPilihanJabatan();
    printf("\nPilihan anda: ");
    pilihJabatan = validasiPilihJabatan();
    switch(pilihJabatan){
    case 1 :
        strcpy(newKaryawan.jabatan, "Direktur");
    break;

    case 2 :
        strcpy(newKaryawan.jabatan, "Manajer");
    break;

    case 3 :
        strcpy(newKaryawan.jabatan, "Supervisor");
    break;
    }

    printf("Berapa anak anda?: ");
    scanf("%s", newKaryawan.anak);
    getchar();

    printf("Silahkan buat password anda: ");
    scanf("%s", newKaryawan.password);

    strcpy(id_karyawan[counterKaryawan].NIP, newKaryawan.NIP);
    strcpy(id_karyawan[counterKaryawan].nama, newKaryawan.nama);
    strcpy(id_karyawan[counterKaryawan].jabatan, newKaryawan.jabatan);
    strcpy(id_karyawan[counterKaryawan].anak, newKaryawan.anak);
    strcpy(id_karyawan[counterKaryawan].password, newKaryawan.password);
    counterKaryawan++;

    for(int i = 0; i < counterKaryawan; ++i){
        fprintf(fp, "%s,%s,%s,%s,%s\n", id_karyawan[i].NIP, id_karyawan[i].nama, id_karyawan[i].jabatan, id_karyawan[i].anak, id_karyawan[i].password);
    }

    fclose(fp);

    barisAtas();
    printf("\n\xb3\tData %s - %s - %-10s\t\t\t\xb3\n", newKaryawan.NIP, newKaryawan.nama, newKaryawan.jabatan);
    barisBawah();
    printf("\nBerhasil dimasukkan ke dalam data, mohon log in ulang.\n");
    printf("Tekan ENTER untuk lanjut");
    while(_getch() != '\r');
    menu();
}

void login(){
    char searchNIP[MAX_NIP_LEN];
    char searchPassword[MAX_PW_LEN];
    char NIP[50];
    char nama[50];
    char jabatan[50];
    char ch;
    char anak[1];
    int match = 0;

    system("cls");
    barisAtas();
    printf("\n\xb3\t\t\t LOGIN \t\t\t\t\xb3\n");
    barisBawah();
    printf("\nTolong Masukkan NIP anda: ");
    scanf("%s", searchNIP);
    for(int i = 0; i < counterKaryawan; ++i){
        if(strcmp(searchNIP, id_karyawan[i].NIP) == 0){
            while(!match){
            int j = 0;

            printf("Password: ");
                while((ch = _getch()) != '\r' && j < 49) {
                    if(ch == '\b' && j > 0) { 
                        printf("\b \b");
                        j--;
                        continue;
                    }
                    searchPassword[j] = ch;
                    printf("*");
                    j++;
                }
                searchPassword[j] = '\0';

                if (strcmp(searchPassword, id_karyawan[i].password) == 0){
                    match++;
                    strcpy(NIP, id_karyawan[i].NIP);
                    strcpy(nama, id_karyawan[i].nama);
                    strcpy(anak, id_karyawan[i].anak);
                    strcpy(jabatan, id_karyawan[i].jabatan);
                    menuMasuk(NIP, nama, anak, jabatan);
                    return;
                }
                else{
                    system("cls");
                    printf("Password salah\n");
                    printf("Silahkan masukkan password ulang.\n");
                }
            }
        }
    }
    printf("NIP anda salah, mohon log in ulang\n");
    printf("Tekan ENTER untuk lanjut");
    while(_getch() != '\r');
    login();
}

int main(){
    FILE *fp = fopen("dataKaryawan.txt", "r");
    if(fp != NULL){
        while(fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",    id_karyawan[counterKaryawan].NIP, 
                                                                id_karyawan[counterKaryawan].nama, 
                                                                id_karyawan[counterKaryawan].jabatan, 
                                                                id_karyawan[counterKaryawan].anak,
                                                                id_karyawan[counterKaryawan].password
                                                                ) == 5){
            counterKaryawan++;
            // printf("%d", counterKaryawan);
        }
        fclose(fp);
        menu();
    }
    else{
        printf("File Tidak Ditemukan");
    }
    return 0;
}

// I Nyoman Gede Candra Wikananta (2305551065)
// Putu Rifki Dirkayuda (2305551068)
// Putu Devasya Aditya Widyadana (2305551071)
// Kelas A