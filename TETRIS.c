#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main(){
	char baslik[] = "---------------TETRIS---------------";
	int x,y,i,j,randomindex,flag=0,tus2,k,skor,best=0;
	char tus,tus1,tus3;
	char board[100][100];
	
	do{
		flag=0;
		skor=0;
		printf("%s\n",baslik);
			
		sleep(1);
		printf("\n\nKONTROLLER:\n\n-Oyun esnasinda cikmak isterseniz '*' tusuna basiniz.\n\n-Oyunda sagda verilen rastgele sekilleri dondurmek icin 'R' tusuna basiniz.\n\n-Seklin nasil olacagina dondurerek karar verdiyseniz 'SPACE' tusuna basip \nindirmek istediginiz kordinatlari girdikten sonra 'ENTER' tusuna basiniz. ");
		sleep(12);
		system("cls");
		printf("\n\n Oyunun yatay boyutunu giriniz: ");
		scanf("%d", &x);
		printf("\n\n Oyunun dikey boyutunu giriniz: ");
		scanf("%d", &y);

		//oyun tahtas�n� olu�turan d�ng�ler.
		for(i=0;i<y+1;i++){
			for(j=0;j<x+10;j++){
				board[i][j] = ' ';
			}
		}
		for(i=0,j=0;i<y+1;i++){
			board[i][j] = '|';
		}
		for(i=y,j=1;j<x+1;j++){
			board[i][j] = '_';
		}
		for(i=0,j=x+1;i<y+1;i++){
			board[i][j] = '|';
		}

		for(i=2,j=x+6;j<x+9;j++){
			board[i][j]='-';
		}
		for(i=6,j=x+6;j<x+9;j++){
			board[i][j]='-';
		}
		for(i=3,j=x+5;i<6;i++){
			board[i][j] = '|';
		}
		for(i=3,j=x+9;i<6;i++){
			board[i][j] = '|';
		}

		sleep(1);

		printf("\n\nOyunun baslamasi icin bir tusa tiklayin ");

		tus = getch();

		if(tus != 0){
			system("cls");

			printf("Oyun basliyor...");

			sleep(1);

			system("cls");

			do{
				system("cls");

				for(i=3;i<6;i++){  //sa� kutucu�u s�f�rlama
							for(j=x+6;j<x+9;j++){
								board[i][j] = ' ';
							}
						}

				randomindex = rand()%8;

				//random �ekil se�ip yandaki kutuya yazma i�lemi.
				if(randomindex==0){
					for(i=5,j=x+6;j<x+9;j++){
							board[i][j] = 'X';
						}
				}
				else if(randomindex==1){
					for(j=x+6,i=3;i<6;i++){
							board[i][j] = 'X';
					}
				}
				else if(randomindex==2){
					board[3][x+7] = 'X';
					board[4][x+7] = 'X';
					board[4][x+6] = 'X';
					board[5][x+6] = 'X';
				}
				else if(randomindex==3){
					board[4][x+7] = 'X';
					board[4][x+6] = 'X';
					board[5][x+7] = 'X';
					board[5][x+8] = 'X';
				}
				else if(randomindex==4){
					board[4][x+7] = 'X';
					board[4][x+6] = 'X';
					board[5][x+6] = 'X';
					board[5][x+7] = 'X';
				}
				else if(randomindex==5){
					board[5][x+6] = 'X';
					board[5][x+7] = 'X';
				}
				else if(randomindex==6){
					board[4][x+6] = 'X';
					board[5][x+6] = 'X';
				}
				else if(randomindex==7){
					board[5][x+6] = 'X';
				}


				for(i=0;i<y+1;i++){     //ekrana yazma d�ng�s�
					for(j=0;j<x+10;j++){
						printf("%c",board[i][j]);
					}
					printf("\n");
				}
				printf("Skor: %d",skor);
				do{  //Burada �ekli yerle�tiriyoruz
					tus1 = getch();

					if(tus1==' '){
						skor++;
						printf("\nKonumu girin: ");
						scanf("%d",&tus2);
						if(randomindex==0){
							i=0;
							while(board[i][tus2]==' ' && board[i][tus2+1]==' ' && board[i][tus2+2]==' ' && i<y){
								i++;  //bo�lu�u kontrol etme d�ng�s�
							}
							k=i;
							if(i!=0){
								board[i-1][tus2] = 'X';
								board[i-1][tus2+1] = 'X';  //yerle�tirme
								board[i-1][tus2+2] = 'X';
							}
							else{
								flag = 1;  //ta�arsa diye
							}
						}
						else if(randomindex==1){
							i=0;
							while(board[i][tus2]==' ' && i<y){
								i++;    //bo�luk kontrol
							} 
							k=i;
							if(i!=2 && i!=1 && i!=0){
								board[i-1][tus2]='X';
								board[i-2][tus2]='X'; //yerle�tirme
								board[i-3][tus2]='X';
							}
							else{
								flag=1;  //ta�arsa diye
							}	
						}
						else if(randomindex==2){
							i=0;
							while(board[i][tus2]==' ' && board[i+1][tus2]==' ' && board[i][tus2+1]==' ' && i<y-1){
								i++;      //bo�luk kontrol
							}
							k=i;
							if(i!=0 && i!=1 && i!=2){
								board[i][tus2]='X';
								board[i-1][tus2]='X';    //yerle�tirme
								board[i-1][tus2+1]='X';
								board[i-2][tus2+1]='X';							
							}
							else{
								flag=1;   //ta�arsa diye
							}
						}
						else if(randomindex==3){
							i=0;
							while(board[i][tus2]==' ' && board[i][tus2+1]==' ' && board[i+1][tus2+1]==' ' && board[i+1][tus2+2]==' ' && board[i][tus2+2]==' '   ){
								i++;  //bo�luk kontrol
							}
							k=i;
							if(i!=0){
								board[i][tus2+2]='X';
								board[i][tus2+1]='X';
								board[i-1][tus2+1]='X';  //yerle�tirme
								board[i-1][tus2]='X';
							}
							else{
								flag=1;  //ta�ma
							}
						}
						else if(randomindex==4){
							i=0;
							while(board[i][tus2]==' ' && board[i][tus2+1]==' ' ){  //bo�luk kkontrol etme
								i++;
							}
							k=i;
							if(i!=0 && i!=1){
								board[i-1][tus2]='X';
								board[i-1][tus2+1]='X';      //yerle�tirme	
								board[i-2][tus2]='X';
								board[i-2][tus2+1]='X';
							}
							else{
								flag=1;
							}
						}
						else if(randomindex==5){
							i=0;
							while(board[i][tus2]==' ' && board[i][tus2+1]==' '){    //bo�luk kontrol�
								i++;
							}
							k=i;
							if(i!=0){
								board[i-1][tus2]='X';   
								board[i-1][tus2+1]='X';      //yerle�tirme
							}
							else{
								flag=1;
							}
						}
						else if(randomindex==6){
							i=0;  
							while(board[i][tus2]==' '){       //bo�luk kontrol�
								i++;
							}
							k=i;
							if(i!=0 && i!=1){ 
								board[i-1][tus2]='X';       //yerle�tirme
								board[i-2][tus2]='X';
							}
							else{
								flag=1;
							}
						}
						else if(randomindex==7){
							i=0;
							while(board[i][tus2]==' '){        //bo�luk kontrol�	
								i++;
							}
							k=i;
							if(i!=0){
								board[i-1][tus2]='X';          //yerle�tirme
							}
							else{
								flag=1;
							}
						}

					  	system("cls");
					}
					else if(tus1=='r'||tus1=='R'){       //d�nd�r�l�rse index numaras�n� de�i�tirsin diye 
						if(randomindex==0){
							randomindex = 1;
						}
						else if(randomindex==1){
							randomindex = 0;
						}
						else if(randomindex==2){
							randomindex = 3;
						}
						else if(randomindex==3){
							randomindex = 2;
						}else if(randomindex==5){
							randomindex = 6;
						}
						else if(randomindex==6){
							randomindex = 5;
						}

						for(i=3;i<6;i++){  //sa� kutucu�u s�f�rlama
							for(j=x+6;j<x+9;j++){
								board[i][j] = ' ';
							}
						}

						if(randomindex==0){    //yeni indexe g�re tekrardan sa� kutuyu tan�mlama
						for(i=5,j=x+6;j<x+9;j++){
								board[i][j] = 'X';
							}
						}
						else if(randomindex==1){
							for(j=x+6,i=3;i<6;i++){
								board[i][j] = 'X';
							}
						}
						else if(randomindex==2){
							board[3][x+7] = 'X';
							board[4][x+7] = 'X';
							board[4][x+6] = 'X';
							board[5][x+6] = 'X';
						}
						else if(randomindex==3){
							board[4][x+7] = 'X';
							board[4][x+6] = 'X';
							board[5][x+7] = 'X';
							board[5][x+8] = 'X';
						}
						else if(randomindex==4){
							board[4][x+7] = 'X';
							board[4][x+6] = 'X';
							board[5][x+6] = 'X';
							board[5][x+7] = 'X';
						}
						else if(randomindex==5){
							board[5][x+6] = 'X';
							board[5][x+7] = 'X';
						}
						else if(randomindex==6){
							board[4][x+6] = 'X';
							board[5][x+6] = 'X';
						}
						else if(randomindex==7){
							board[5][x+6] = 'X';
						}

						system("cls");

						for(i=0;i<y+1;i++){     //ekrana yazma d�ng�s�
							for(j=0;j<x+10;j++){
								printf("%c",board[i][j]);
							}
							printf("\n");
						}
						printf("Skor: %d",skor);

					}
					else if(tus1=='*'){
						flag=1;
					} 
				}while(tus1!=' ' && tus1!='*');


				if(randomindex==0||randomindex==5||randomindex==7){
					j=1;
					while(board[k-1][j]=='X'){
						j++;                        //sat�r kontrol
					}
					if(j==x+1){
						for(i=k-2;i>-1;i--){
							for(j=1;j<x+1;j++){          //e�er sat�r�n tamam� x ise �st�ndeki sat�rlar� bi a�a�� kayd�r�yor
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}

				}
				else if(randomindex==1){
					j=1;
					while(board[k-3][j]=='X'){
						j++;
					}
					if(j==x+1){                           //�st kutular� kontrol
						for(i=k-4;i>-1;i--){
							for(j=1;j<x+1;j++){
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
					j=1;
					while(board[k-2][j]=='X'){
						j++;
					}
					if(j==x+1){
						for(i=k-3;i>-1;i--){
							for(j=1;j<x+1;j++){           //orta kutular� kontrol
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
					j=1;
					while(board[k-1][j]=='X'){
						j++;
					}
					if(j==x+1){
						for(i=k-2;i>-1;i--){               //alt kutular� kontrol
							for(j=1;j<x+1;j++){
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
				}
				else if(randomindex==2){
					j=1;
					while(board[k-2][j]=='X'){
						j++;
					}                                     //�st kutular� kontrol
					if(j==x+1){
						for(i=k-3;i>-1;i--){
							for(j=1;j<x+1;j++){
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
					j=1;
					while(board[k-1][j]=='X'){
						j++;
					}
					if(j==x+1){                        //orta kutular� kontrol
						for(i=k-2;i>-1;i--){
							for(j=1;j<x+1;j++){
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
					j=1;
					while(board[k][j]=='X'){
						j++;
					}
					if(j==x+1){
						for(i=k-1;i>-1;i--){                       //alt kutular� kontrol
							for(j=1;j<x+1;j++){
								board[i+1][j]=board[i][j];       
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
				}
				else if(randomindex==3){
					j=1;
					while(board[k-1][j]=='X'){
						j++;                        //�st kutular� kontrol etme
					}
					if(j==x+1){
						for(i=k-2;i>-1;i--){
							for(j=1;j<x+1;j++){         
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
					j=1;
					while(board[k][j]=='X'){
						j++;                         //alt kutular� kontrol etme
					}
					if(j==x+1){
						for(i=k-1;i>-1;i--){
							for(j=1;j<x+1;j++){
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
				}
				else if(randomindex==4||randomindex==6){
					j=1;
					while(board[k-2][j]=='X'){
						j++;
					}
					if(j==x+1){
						for(i=k-3;i>-1;i--){
							for(j=1;j<x+1;j++){     //�st kutuyu kontrol
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
					j=1;
					while(board[k-1][j]=='X'){
						j++;
					}
					if(j==x+1){
						for(i=k-2;i>-1;i--){
							for(j=1;j<x+1;j++){         //alt kutuyu kontrol 
								board[i+1][j]=board[i][j];
							}
						}
						for(i=0,j=1;j<x+1;j++){
							board[i][j]=' ';          //en �ste bo� sat�r eklemek
						}
						skor=skor+3;
					}
				}

				system("cls");

				for(i=0;i<y+1;i++){     //ekrana yazma d�ng�s�
					for(j=0;j<x+10;j++){
						printf("%c",board[i][j]);
					}
					printf("\n");
				}
				printf("Skor: %d",skor);
				
				

			}while(flag!=1);
		}
		
		system("cls");
		
		printf("Skor: %d \nTekrar oynamak icin SPACE tusunu basiniz. Eger Oyunu kapatmak istiyorsaniz herhangi bir tusa basabilirsiniz.",skor);
		
		tus3=getch();
		
		system("cls");
		
		if(best<skor){
			best = skor;
		}
		
	}while(tus3==32);	
	
	printf("En Yuksek Skor: %d",best);
	
	return 0;
}











