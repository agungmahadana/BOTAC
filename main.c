#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "function.h"

struct data {
    char pass[25];
    char name[25];
    int saldo;
};

char userSekarang(char *username);

int graph[V][V] = {{0, 36, 75, 15, 27, 0, 0, 0, 11},    // badung
				   {36, 0, 97, 0, 24, 0, 44, 18, 0},    // bangli
				   {75, 97, 0, 0, 0, 66, 116, 0, 64},   // buleleng
				   {15, 0, 0, 0, 29, 0, 0, 0, 0},       // denpasar
				   {27, 24, 0, 29, 0, 0, 0, 11, 0},     // gianyar
                   {0, 0, 66, 0, 0, 0, 0, 0, 72},       // jembrana
                   {0, 44, 166, 0, 0, 0, 0, 39, 0},     // karangasem
                   {0, 18, 0, 0, 11, 0, 39, 0, 0},      // klungkung
                   {11, 0, 64, 0, 0, 72, 0, 0, 0}};     // tabanan

int main() {
    
    char choice;
    struct data newItem;
    FILE *cek = fopen("Logout.txt", "r+"), *open;
    if(!cek){
        insert_choice:
        pembersih();
        header();
        menuAwal();
        scanf("%c", &choice);
        fflush(stdin);
        switch(choice) {
            case '1':
				if(open = fopen("Data-Base.csv", "r")){
                    fclose(open);
					login("Data-Base.csv");
					goto lanjut;
				}
				else{
					printf("\nBelum ada akun. Register dulu!\n");
					pause();
					goto insert_choice;
				}
                break;
            case '2':
                addAkun("Data-Base.csv");
                pause();
                goto lanjut;
                break;
            case '3':
                exit(0);
            default:
                goto insert_choice;
                break;
        }
        fclose(cek);
    }
    else{
        lanjut:
        fclose(cek);
        char username[25];
        FILE *fp = fopen("Logout.txt", "r+");
        fgets(username, sizeof(username), fp);
        fclose(fp);
        userSekarang(username);
    }
    return 0;
}

char userSekarang(char *username){
    menu_utama:
    pembersih();
    header();
    menuUtama(username);
    char menu;
    fflush(stdin);
    scanf("%c", &menu);
    
    switch(menu){
        case '1':
            pembersih();
            header();
            char tambah_saldo;
            cekSaldo("Data-Base.csv", username, 1);
            kembali_saldo:
            printf("\nIngin tambah saldo? [y/t] : ");
            fflush(stdin);
            scanf("%c", &tambah_saldo);
            if(tambah_saldo == 'Y' || tambah_saldo == 'y') {
                int plus, hasil;
                char tambah;
                hasil = (cekSaldo("Data-Base.csv", username, 2));
                printf("\nMasukkan jumlah saldo yang ingin ditambahkan : ");
	            scanf("%d", &plus);
                plus = hasil + plus;
                updateSaldo("Data-Base.csv", username, plus);
                printf("\nSaldo berhasil ditambahkan\n");
                getchar();
                pause();
                goto menu_utama;
            }
            else if(tambah_saldo == 'T' || tambah_saldo == 't') goto menu_utama;
            else {
                printf("\nPilihan anda salah");
                goto kembali_saldo;
            }
            break;
        case '2':
            pembersih();
            header();
            destinasi();
            int awal, tujuan;
            printf("\nPilih lokasi anda sekarang : ");
            scanf("%d", &awal);
            printf("Pilih lokasi tujuan : ");
            scanf("%d", &tujuan);
            fflush(stdin);
            awal -= 1;
            tujuan -= 1;
            pesan(graph, 10, awal, tujuan, "Data-Base.csv", username);
            kembali_pesan:
            printf("\nIngin kembali ke menu? [y/t]\n>> ");
            char kembali_pesan;
            fflush(stdin);
            scanf("%c", &kembali_pesan);
            fflush(stdin);
            if(kembali_pesan == 'y' || kembali_pesan == 'Y') goto menu_utama;
            else if(kembali_pesan == 't' || kembali_pesan == 't') exit(0);
            else {
                printf("\nPilihan anda salah");
                goto kembali_pesan;
            }
            break;
        case '3':
            remove("Logout.txt");
            printf("\nLogout berhasil\n");
            getchar();
            pause();
            return main();
            break;
        case '4':
            exit(0);
            break;
        default:
            goto menu_utama;
    }
}