#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define V 10
#define INFINITY 999

int graph[V][V] = {{0, 36, 75, 15, 27, 0, 0, 0, 11},    // badung
				   {36, 0, 97, 0, 24, 0, 44, 18, 0},    // bangli
				   {75, 97, 0, 0, 0, 66, 116, 0, 64},   // buleleng
				   {15, 0, 0, 0, 29, 0, 0, 0, 0},       // denpasar
				   {27, 24, 0, 29, 0, 0, 0, 11, 0},     // gianyar
                   {0, 0, 66, 0, 0, 0, 0, 0, 72},       // jembrana
                   {0, 44, 166, 0, 0, 0, 0, 39, 0},     // karangasem
                   {0, 18, 0, 0, 11, 0, 39, 0, 0},      // klungkung
                   {11, 0, 64, 0, 0, 72, 0, 0, 0}};     // tabanan

void pembersih(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void header(){
	printf("================================================\n");
	printf("                 TOKO JAYA ABADI                \n");
	printf("             !Bukan Bangunan Biasa!             \n");
	printf("================================================\n\n");
}

void menuutama(){
	// printf("     Selamat  datang  di  GoGorengan.  Kami\n     karyawan  GoGorengan,  siap  melayani.\n     Pilih apa yang ingin  kamu lakukan ya!\n\n");
	printf("     --------------------------------------     \n");
	printf("     |             Menu Utama             |     \n");
	printf("     --------------------------------------     \n");
	printf("     |         [1] Pesan Gorengan         |     \n");
	printf("     |         [2] Gopis                  |     \n");
	printf("     |         [3] Tema                   |     \n");
	printf("     --------------------------------------     \n\n");
	printf("================================================\n\n");
}

void djikstra(int G[V][V], int n, int startnode, int targetnode){
	int cost[V][V], distance[V], pred[V];
	int visited[V], count, mindistance, nextnode, i, j;
	char kota[10][11] = {"Badung", "Bangli", "Buleleng", "Denpasar", "Gianyar", "Jembrana", "Karangasem", "Klungkung", "Tabanan"}, satu[99], dua[99];
	// printf("%s\n", kota[6]);
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

	// for(i=0;i<n;i++){
	// 	printf("[%d][%d]\n", i,distance[i]);
	// 	printf("%d-%d\n", i,pred[i]);
	// }
	
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
  	int a, x=0, y[10], z=0;
	const int kecepatan=40;
	// char y[10];
	for(i=0; i<n; i++){
		// printf("tst");
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
		}
	}
}

int main(){
	pembersih();
	header();
	menuutama();
	int tujuan;
	printf("1. Badung\n2. Bangli\n3. Buleleng\n4. Denpasar\n5. Gianyar\n6. Jembrana\n7. Karangasem\n8. Klungkung\n9. Tabanan\n");
	scanf("%d", &tujuan);
	tujuan -= 1;
    djikstra(graph, V, 3, tujuan);
}