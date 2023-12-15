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
#define TUJANGAN_MAKAN 20000
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
void inputDataBaru(), login(), menuPilihanJabatan();

int validasiMasuk(){
    int pilihan,nilaiScanf;
    char enter;
    nilaiScanf = scanf("%d%c", &pilihan, &enter);
    if(nilaiScanf != 2 || pilihan < 0 || pilihan > 2 || enter != '\n'){
        fflush(stdin);
        printf("\n\t\t\t\t\t\t\e[31mInput tidak valid\e[0m");
        printf("\n\t\t\t\t\t\t\e[35mInput pilihan kembali :\e[0m");
        return validasiMasuk();
    }else{
        return pilihan;
    }
}
int validasiJabatan(){
    int pilihan,nilaiScanf;
    char enter;
    nilaiScanf = scanf("%d%c", &pilihan, &enter);
    if(nilaiScanf != 2 || pilihan < 1 || pilihan > 9 || enter != '\n'){
        fflush(stdin);
        printf("\n\t\t\t\t\t\t\e[31mInput tidak valid\e[0m");
        printf("\n\t\t\t\t\t\t\e[35mInput pilihan kembali :\e[0m");
        return validasiMasuk();
    }else{
        return pilihan;
    }
}

int validasiNip(const char *str){
    while(*str){
        if(!isdigit(*str)){
            return 0;
        }
        str++;
    }
    return 1;
}

void barisAtas(){
    printf("\n\t\t\t\t\t\x1b[1m\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
}

void barisBawah(){
    printf("\n\t\t\t\t\t\xc3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4\x1b[m");
}

void menu()
{
    int pilihan;
    system("cls");
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[34mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3                           \e[34mPT. Toko Kita\e[0m                         \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3  \e[32m Silahkan pilih menu di bawah ini\e[0m                              \xb3");
    printf("\n\t\t\t\t\t\xb3                                                                 \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m1.\e[0m \e[31mAbsensi Kehadiran\e[0m                                           \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m2.\e[0m \e[31mHitung Gaji Anda\e[0m                                            \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m0.\e[0m \e[31mKeluar          \e[0m                                            \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m") , pilihan = validasiMasuk();
    if(pilihan == 1){
        system("cls");
        login();
    }else if(pilihan == 2){
        system("cls");
        inputDataBaru();
    }else{
        system("cls");
        barisAtas();
        printf("\n\t\t\t\t\t\xb3           \e[32mTerimakasih Telah Menggunakan Program Kami\e[0m            \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");

    }                                                    
}
void inputDataBaru(){
    int pilihan;
    struct karyawan new;
    FILE *fp = fopen("dataKaryawan.txt", "w");
    if(fp == NULL){
        barisAtas();
        printf("\n\t\t\t\t\t\xb3           \e[31mGagall Membuka File\e[0m                     \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
        return;
    }
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                       \e[32m Input Data Karyawan\e[0m                      \xb3");
    printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
    printf("\n\t\t\t\t\tMasukan NIP anda :");
    scanf("%s", &new.nip);

    if(!validasiNip(new.nip)){
        system("cls");
        barisAtas();
        printf("\n\t\t\t\t\t\xb3        \e[32mInput tidak Valid! Tolong Masukan NIP yang valid!!!\e[0m      \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
        inputDataBaru();
    }

    for(int i = 0;i < incrementKaryawan; ++i){
        if(strcmp(new.nip, dataFiletxt[i].nip) == 0){
        barisAtas();
        printf("\n\t\t\t\t\t\xb3           \e[32mNIP sudah ada! Tolong Masukan NIP yang valid!!!\e[0m          \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");
        inputDataBaru();
        }
    }
    printf("\n\t\t\t\t\tMasukan nama anda :");
    scanf("%s", &new.nama);

    int pilihanJabatan;
    menuPilihanJabatan();
    printf("\n\t\t\t\t\t    \e[31m-->>\e[0m") , pilihan = validasiJabatan();
    switch(pilihanJabatan){
        case 1 : strcpy(new.jabatan, "Direktur");
        break;
        case 2 : strcpy(new.jabatan, "Manajer");
        break;
        case 3 : strcpy(new.jabatan, "Supervisor");
        break;
        case 4 : strcpy(new.jabatan, "Bendahara");
        break;
        case 5 : strcpy(new.jabatan, "Sekretaris");
        break;
        case 6 : strcpy(new.jabatan, "Kadiv");
        break;
        case 7 : strcpy(new.jabatan, "Wakadiv");
        break;
        case 8 : strcpy(new.jabatan, "StaffDiv");
        break;
        case 9 : strcpy(new.jabatan, "Cleaning Service");
        break;
    }

    printf("\n\t\t\t\t\tMasukan jumlah anak anda: ");
    scanf("%s",&new.anak);
    printf("\n\t\t\t\t\tSilahkan buat password anda: ");
    scanf("%s",&new.password);
    printf("\n\t\t\t\t\tTekan enter untuk lanjut.....");
    while(_getch() != '\r');
    system("cls");

    strcpy(dataFiletxt[incrementKaryawan].nip, new.nip);
    strcpy(dataFiletxt[incrementKaryawan].nama, new.nama);
    strcpy(dataFiletxt[incrementKaryawan].jabatan, new.jabatan);
    strcpy(dataFiletxt[incrementKaryawan].anak, new.anak);
    strcpy(dataFiletxt[incrementKaryawan].password, new.password);
    incrementKaryawan++;

    for(int i = 0; i < incrementKaryawan; ++i){
        fprintf(fp, "%s,%s,%s,%s,%s\n", dataFiletxt[i].nip, dataFiletxt[i].nama, dataFiletxt[i].jabatan,dataFiletxt[i], dataFiletxt[i].anak, dataFiletxt[i].password);
    }

        fclose(fp);
        barisAtas();
        printf("\n\t\t\t\t\t\xb3           \e[32mData %s - %s - %-10s\e[0m                     \xb3",new.nip, new.nama, new.jabatan);
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[0m");
        printf("\n\t\t\t\t\t\e[31mBerhasil dimasukan ke dalam data, silahkan login kembali\e[0m");
        printf("\n\t\t\t\t\tTekan enter untuk lanjut.....");
        while(_getch() != '\r');
        menu();
}

void menuPilihanJabatan(){
    system("cls");
    barisAtas();
    printf("\n\t\t\t\t\t\xb3                 \e[34mSelamat Datang Karyawan Perusahaan\e[0m              \xb3");
    printf("\n\t\t\t\t\t\xb3                           \e[34mPT. Toko Kita\e[0m                         \xb3");
    printf("\n\t\t\t\t\t\xC3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xB4");
    printf("\n\t\t\t\t\t\xb3  \e[32m Silahkan pilih Jabatan anda\e[0m                                   \xb3");
    printf("\n\t\t\t\t\t\xb3                                                                 \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m1.\e[0m \e[31mDirektur\e[0m                                                    \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m2.\e[0m \e[31mManajer\e[0m                                                     \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m3.\e[0m \e[31mSupervisor          \e[0m                                        \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m4.\e[0m \e[31mBendahara           \e[0m                                        \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m5.\e[0m \e[31mSekretaris          \e[0m                                        \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m6.\e[0m \e[31mKadiv               \e[0m                                        \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m7.\e[0m \e[31mWakadiv             \e[0m                                        \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m8.\e[0m \e[31mStaffDiv            \e[0m                                        \xb3");
    printf("\n\t\t\t\t\t\xb3  \e[32m9.\e[0m \e[31mCleaning Service    \e[0m                                        \xb3");
    barisBawah();
    printf("\n\t\t\t\t\t\xb3  \e[32m Pilihan anda (contoh : 1) \e[0m                                    \xb3");
    
    }

void login(){
    char cariNip[MAX_NIP_LEN];
    char cariPassword[MAX_PW_LEN];
    char NIP[50];
    char jabatan[50];
    char ch;
    char anak[2];
    int match = 0;

        barisAtas();
        printf("\n\t\t\t\t\t\xb3           \e[32Login\e[0m                     \xb3");
        printf("\n\t\t\t\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9\x1b[m");

    
}
int main()
{
    FILE *fp = fopen("dataKaryawan.txt", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                      dataFiletxt[MAX_KARYAWAN].nama,
                      dataFiletxt[MAX_KARYAWAN].nip,
                      dataFiletxt[MAX_KARYAWAN].jabatan,
                      dataFiletxt[MAX_KARYAWAN].anak,
                      dataFiletxt[MAX_KARYAWAN].password) == 5)
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