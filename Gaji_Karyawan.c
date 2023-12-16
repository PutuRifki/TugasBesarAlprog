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

int validasi3Pilihan(), validasiPilihJabatan(), cekNIP(const char *str), validasi2Pilihan();
void login(), newDataKaryawan(), menu(), menuPilihanJabatan();
void inputDataKaryawan();
void bacaFileAbsen(char tempNIP[50]);
void saveAbsen(char tempNIP[50]);
void menuMasuk(char NIP[50], char nama[50], char anak[1], char jabatan[50]);
void createFileAbsen(char NIP[50], char nama[50], char anak[1], char jabatan[50]); 
void hitungbiayaHarian(char NIP[255], char nama[255], char jabatan[255]);
void menuMasuk(char NIP[50], char nama[50], char anak[1], char jabatan[50]);
void absensi(char NIP[50], char nama[50], char anak[1], char jabatan[50]);
void gajiFixed(char NIP[255], char nama[255], char anak[1], char jabatan[255]);

void barisAtas(){
    printf("\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
}

void barisBawah(){
    printf("\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
}

int Terimakasih(){
    system("cls");
    barisAtas();
    printf("\n\xb3\t\t    !!!Terimakasih!!!\t\t\t\xb3\n");
    barisBawah();
    while(_getch() != '\r');
    system("cls");
    return 0;
}

void ulang(char NIP[50], char nama[50], char anak[1], char jabatan[50]){
    int pilihan;
    printf("Apakah anda ingin ulang?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
    pilihan = validasi2Pilihan();
    if (pilihan==1)
    {
        menuMasuk(NIP, nama, anak, jabatan);
    }else if(pilihan==2){
        Terimakasih();
    }
    
}

struct Karyawan
{
    char nama[MAX_NAMA_LEN];
    char NIP[MAX_NIP_LEN];
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

struct Tanggal tgl[100];
int countTanggal = 0;

struct Karyawan id_karyawan[MAX_KARYAWAN];
int counterKaryawan = 0;

int validasi3Pilihan(){
    int term;
    char enter;
    if(enter = scanf("%d%c", &term,&enter) != 2 || term < 1 || term > 3 || enter != '\n'){
        fflush(stdin);
        printf("\e[31mMasukan anda salah\e[0m\n");
        printf("Masukkan angka pengganti: ");
        return validasi3Pilihan();
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

int validasi2Pilihan(){
    int term;
    char enter;
    if(enter = scanf("%d%c", &term,&enter) != 2 || term < 1 || term > 2 || enter != '\n'){
        fflush(stdin);
        printf("\e[31mMasukan anda salah\e[0m\n");
        printf("Masukkan angka pengganti: ");
        return validasi2Pilihan();
    }
    else{
        return term;
    }
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

void menu(){
    int pilihan;
    
    // system("cls");
    barisAtas();
    printf("\n\xb3\t\tSilahkan pilih menu:     \t\t\xb3\n");
    printf("\xb3\t\t1. Login \t\t\t\t\xb3\n");
    printf("\xb3\t\t2. Input Data Karyawan Baru \t\t\xb3\n");
    printf("\xb3\t\t3. Keluar \t\t\t\t\xb3\n");
    barisBawah();
    printf("\nPilihan anda: ");
    pilihan = validasi3Pilihan();
    if(pilihan==1){
        login();
    }
    else if(pilihan==2){
        newDataKaryawan();
    }else if(pilihan==3){
        fflush(stdin);
        Terimakasih();
        return;
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

    ulang(NIP, nama, anak, jabatan);
    return;
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

void createFileAbsen(char NIP[50], char nama[50], char anak[1], char jabatan[50]){
    char tempNIP[50];
    strcpy(tempNIP, NIP);
    FILE *file = fopen(strcat(tempNIP, ".txt"), "a+");
    fclose(file);
    bacaFileAbsen(tempNIP);
    absensi(NIP, nama, anak, jabatan);
}

void absensi(char NIP[50], char nama[50], char anak[1], char jabatan[50]){
    system("cls");

    struct Tanggal tempTanggal;

    time_t t = time(NULL);
    struct tm *tm_info;
    char tmpTgl[50];
    char cekTgl[50];
    char tmpJam[50];
    tm_info = localtime(&t);

    int absen;
    char tempNIP[50];
    int repeat = 0;

    strftime(tmpTgl, 50,"%A %d-%m-%Y", tm_info);
    strftime(tmpJam, 50, "%H:%M", tm_info);

    strcpy(tempNIP, NIP);
    FILE *file = fopen(strcat(tempNIP,".txt"), "a+");

    printf("Hari ini: %s\n", tmpTgl);
    printf("Jam: %s\n", tmpJam);

        printf("Apakah anda ingin absen hari ini?\n");
        printf("1. Ya\n");
        printf("2. Tidak\n");
        printf("Pilihan anda:\n");
        absen = validasi2Pilihan();
        if(absen==1){

            int sudahAbsen = 0;
            for(int i = 0; i < countTanggal; ++i){
                if(strcmp(tmpTgl, tgl[i].hari) == 0 ){
                    sudahAbsen = 1;
                    printf("Anda sudah absen untuk hari ini!\n");
                    printf("Silahkan absen besok.\n");
                    printf("Tekan ENTER untuk lanjut");
                    while(_getch() != '\r');
                    return menuMasuk(NIP, nama, anak, jabatan);
                    break;
                }
            }

            if(!sudahAbsen && absen == 1){
            strcpy(tgl[countTanggal].hari, tmpTgl);
            strcpy(tgl[countTanggal].jam, tmpJam);
            strcpy(tgl[countTanggal].hadir, "H");
            countTanggal++;

            fprintf(file, "%s,%s,%s\n", tgl[countTanggal].hari, tgl[countTanggal].jam, tgl[countTanggal].hadir);
            printf("%s", tgl[countTanggal].hari);
            printf("Anda berhasil absen untuk hari ini!\n");

            saveAbsen(tempNIP);
            fclose(file);
            printf("Tekan ENTER untuk lanjut");
            while(_getch() != '\r');
            return menuMasuk(NIP, nama, anak, jabatan);
            }
        }
        else if(absen==2){
            printf("Anda akan dikembalikan ke menu.\n");
            printf("Tekan ENTER untuk lanjut");
            while(_getch() != '\r');
            menuMasuk(NIP, nama, anak, jabatan);
        }else{
            system("cls");
            printf("Pilihan anda salah.\n");
        }

    fclose(file);
    printf("%s\n", absen);
    printf("%d", repeat);
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
    printf("3. Log Out\n");
    printf("Pilihan anda: ");
    pilihan = validasi3Pilihan();
    switch(pilihan){
        case 1 :
            createFileAbsen(NIP, nama, anak, jabatan);
        break;

        case 2 :
            // hitungbiayaHarian(NIP, nama, jabatan);
            gajiFixed(NIP, nama, anak, jabatan);
        break;

        case 3 :
            menu();
        break;
    }
}

void newDataKaryawan(){
    struct Karyawan newKaryawan;
    int ulang = 0;

    FILE *fp = fopen("dataKaryawan.txt", "w");
    if(fp==NULL){
        printf("Gagal Membuka File");
        return;
    }

    printf("Masukkan NIP anda: ");
    scanf("%s", newKaryawan.NIP);
    getchar();

    if(!cekNIP(newKaryawan.NIP)){
        printf("NIP tidak Valid! Tolong masukkan NIP yang valid!\n");
        fflush(stdin);
        return newDataKaryawan();
    }

    for(int i = 0; i < counterKaryawan; ++i){
        if(strcmp(newKaryawan.NIP, id_karyawan[i].NIP)==0){
            printf("NIP sudah ada! Tolong masukkan NIP yang baru!\n");
            fflush(stdin);
            return newDataKaryawan();
            break;
        }
    }

    printf("Masukkan nama: ");
    scanf("%s", newKaryawan.nama);
    getchar();

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
    getchar();

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