#include <stdlib.h>
#define V 10
#define INFINITY 999
FILE *main_db;

struct Data {
    char name[25];
    char pass[25];
    int saldo;
    struct Data *next;
};

char buffer[100];

void header();
void menuAwal();
void login(char *file);
void addAkun(char *file);
bool cekAkun(char *file, char *name2);
void menuUtama(char *username);
void destinasi();
void pesan(int G[V][V], int n, int startnode, int targetnode, char *file, char *username);
int cekSaldo(char *file, char *username, int pil);
void updateSaldo(char *file, char *username, int saldo);
void pembersih();
void pause();

void header(){
    printf(
        "=============================================================\n"
        "||                           BOTAC                         ||\n"
		"||  !Bali Online Transportation and Accomodation using C!  ||\n"
        "=============================================================\n"
    );
}

void menuAwal(){
    printf("\n1. Login\n2. Register\n3. Keluar\nPilihan : ");
}

void login(char *file){
	start:
	pembersih();
	header();
	char id[25], sandi[25];
	printf("\nUser Name : ");
	gets(id);
	if(!cekAkun(file, id)){
		printf("Password : ");
		gets(sandi);

		konfirmasi_sandi:
        printf("Konfirmasi password : ");
        char resandi[25];
        gets(resandi);

        if(strcmp(sandi, resandi) != 0) {
            printf("\nKonfirmasi password salah\n");
            goto konfirmasi_sandi;
        }
        else {
            main_db = fopen("Logout.txt", "a+");
            fprintf(main_db, "%s", id);
			fclose(main_db);
        }
	}
	else{
		printf("\nUser Name salah\n");
		pause();
		goto start;
	}
}

void addAkun(char *file){
    inputNama:
    pembersih();
    header();
    struct Data akun;
    printf("\nUser Name : ");
    fflush(stdin);
    gets(akun.name);

    if(cekAkun("Data-Base.csv", akun.name)) {
        printf("Password : ");
        fflush(stdin);
        gets(akun.pass);

        akun.saldo = 0;

        konfirmasi_password:
        printf("Konfirmasi password : ");
        char repass[25];
        gets(repass);

        if(strcmp(akun.pass, repass) != 0) {
            printf("Konfirmasi password salah\n");
            goto konfirmasi_password;
        }
        else {
            main_db = fopen(file, "a+");
            fprintf(main_db, "%s\n%s\n%d\n", akun.name,akun.pass,akun.saldo);
            fclose(main_db);
            main_db = fopen("Logout.txt", "a+");
            fprintf(main_db, "%s", akun.name);
			fclose(main_db);
        }
    }
    else {
        printf("\nUser name sudah digunakan, coba yang lain.\n");
        pause();
        pembersih();
        header();
        menuAwal();
        goto inputNama;
    }
}

bool cekAkun(char *file, char *name2) {
    bool status = true;
    main_db = fopen(file, "r+");
	char checking[25];
	strcpy(checking, name2);
    while(fgets(buffer, sizeof(buffer), main_db)) {
        if(strstr(buffer, checking) != 0) {
            status = false;
            break;
        }
    }
    return status;
    fclose(main_db);
}

void menuUtama(char *username){
    printf("\n[Selamat datang %s]\nMenu:\n1. Cek Saldo\n2. Pesan\n3. Logout\n4. Keluar\nPilihan : ", username);
}

void destinasi(){
    printf("\nDestinasi:\n1. Badung\n2. Bangli\n3. Buleleng\n4. Denpasar\n5. Gianyar\n6. Jembrana\n7. Karangasem\n8. Klungkung\n9. Tabanan\n");
}

void pesan(int G[V][V], int n, int startnode, int targetnode, char *file, char *username){
	int cost[V][V], distance[V], pred[V];
	int visited[V], count, mindistance, nextnode, i, j, harga;
	char kota[10][11] = {"Badung", "Bangli", "Buleleng", "Denpasar", "Gianyar", "Jembrana", "Karangasem", "Klungkung", "Tabanan"}, satu[99], dua[99];
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(G[i][j]==0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];
		}
	}
	for(i=0; i<n; i++){
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	
	while(count<n-1){
		mindistance = INFINITY;
		for(i=0; i<n; i++){
			if(distance[i]<mindistance&&!visited[i]){
				mindistance = distance[i];
				nextnode = i;
			}
		}
		visited[nextnode] = 1;
		for(i=0; i<n; i++){
			if(!visited[i]){
				if(mindistance+cost[nextnode][i]<distance[i]){
					distance[i] = mindistance+cost[nextnode][i];
					pred[i] = nextnode;
				}
			}
		}
		count++;
	}
  	int a, x=0, y[10], z=0, tarif=3000;
	const int kecepatan=40;
	for(i=0; i<n; i++){
		if(i==targetnode){
			printf("\nKota Asal       : %s", kota[startnode]);
			printf("\nKota Tujuan     : %s", kota[i]);
			printf("\nJarak Tempuh    : %d Km", distance[i]);
			printf("\nKecepatan       : %d Km/j", kecepatan);
			printf("\nRute Perjalanan : ");
			
			j = i;
			do{
				j = pred[j];
				y[x] = j;
				x++;
			}while(j!=startnode);
			for(int p=x-1; p>=0; p--){
				z = y[p];
				printf("%s -> ", kota[z]);
			}
			printf("%s", kota[targetnode]);
			a = distance[i];
			float b=a;
			int c=(float)b/kecepatan;
			b = b/kecepatan-c;
			int d=(float)b*60;
			if(a==0)
				printf("\nEstimasi Waktu  : 15 Menit\n");
			else if(c==0)
				printf("\nEstimasi Waktu  : %d Menit\n", d);
			else if(d==0)
				printf("\nEstimasi Waktu  : %d Jam\n", c);
			else
				printf("\nEstimasi Waktu  : %d Jam %d Menit\n", c,d);
			if(distance[i]==0) harga = 10000;
			else harga = tarif * distance[i];
			printf("Tarif           : Rp. %d\n", harga);
		}
	}
	bayar:
	printf("Pilih metode pembayaran :\n1. Cash\n2. Transfer\nPilihan : ");
	int metodeBayar;
	scanf("%d", &metodeBayar);
	if(metodeBayar==2){
		if(harga > cekSaldo(file, username, 2)){
			printf("Saldo tidak mencukupi. Cash saja!\n");
			goto bayar;
		}
		else{
			int saldo = cekSaldo(file, username, 2);
			saldo = saldo - harga;
			updateSaldo(file, username, saldo);
			printf("\nPembayaran berhasil");
		}
	}
}

int cekSaldo(char *file, char *username, int pil){
	main_db = fopen(file, "r");
	int count=0;
	char copy[25], tambah[100];
	strcpy(copy, username);
    while(fgets(buffer, sizeof(buffer), main_db)) {
		if(strstr(buffer, copy) != 0){
			count = 3;
		}
		if(count == 1){
			if(pil == 1){
				printf("\nSaldo anda : Rp. %s", buffer);
				break;
			}
			else if(pil == 2){
				strcpy(tambah, buffer);
				return atoi(tambah);
				break;
			}
		}
		count--;
    }
    fclose(main_db);
}

void updateSaldo(char *file, char *username, int saldo){
	main_db = fopen(file, "r+");
	FILE *temp = fopen("temp.csv", "w+");
	int count=0;
	char copy[25], tambah[100];
	strcpy(copy, username);
    while(fgets(buffer, sizeof(buffer), main_db)) {
		if(strstr(buffer, copy) != 0){
			count = 3;
		}
		if(count == 1){
			fprintf(temp, "%d\n", saldo);
		}
		else if(count != 1) fprintf(temp, "%s", buffer);
		count--;
	}
	fclose(main_db);
	fclose(temp);
	FILE *temp2 = fopen("temp.csv", "r+");
	main_db = fopen(file, "w+");
    while(fgets(buffer, sizeof(buffer), temp2)) {
		fprintf(main_db, "%s", buffer);
	}
	fclose(temp2);
	fclose(main_db);
	remove("temp.csv");
}

void pembersih(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void pause(){
    printf("Tekan enter untuk melanjutkan . . . ");
	getchar();
    printf("\n");
}