#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int menu();
void inversematrix(int ,float **);
void elemination(float **,int );
void gaussSeidal(float **, float , float , float ,int ,float );
void gnEnterpolasyon(float **,int ,float ,float );

/*struct polinom{
	int isaret;
	float katsayi;
	float taban;
	float us;
} ;


float fh(char *, float );
float sayihesap(char *,int *);
int isArtieksi(char );
int isNumber(char );



float fh(char *fonk, float x){      //fonk'u verilen x de�erine g�re hesaplayan fonksiyon (fonksiyon hesaplay�c�)

	struct polinom *ayrikfonk;
	
	int i=0, j=0, k=0, structyer = 1, parametreyer = 1, flag = 0;
	float sonuc =0, yenisonuc = 0;
	char *parametreler;
	
	ayrikfonk = (struct polinom *)calloc(structyer,sizeof(struct polinom));
	
	while(fonk[i]!='\0'){
		
		ayrikfonk[j].isaret = 1;
		ayrikfonk[j].katsayi = 1;
		ayrikfonk[j].taban = 1;
		ayrikfonk[j].us = 1;
	
		if(isArtieksi(fonk[i])){
			if(fonk[i]=='+'){
				ayrikfonk[j].isaret = 1;
			}else{
				ayrikfonk[j].isaret = -1;
			}
			
			i++; 
		}
	
		if(isNumber(fonk[i]) || fonk[i] =='x'){
			if(fonk[i]=='x'){
				sonuc = x;
				i++;
			}else{
				sonuc = sayihesap(fonk,&i);			
			}

		
			if(fonk[i]=='*'){
				ayrikfonk[j].katsayi = sonuc;
				sonuc = 0;
				i++;
				if(isNumber(fonk[i]) || fonk[i] =='x'){
					if(fonk[i]=='x'){
						sonuc = x;
						i++;
					}else{
						sonuc = sayihesap(fonk,&i);			
					}			
				}
			
				if(fonk[i] == '^'){
					ayrikfonk[j].taban = sonuc;
					sonuc = 0 ;
					i++;
					if(isNumber(fonk[i]) || fonk[i] == 'x' ){
						if(fonk[i] == 'x'){
							sonuc = x;
							i++;
						}else{
							sonuc = sayihesap(fonk,&i);
						}
						ayrikfonk[j].us = sonuc;
						sonuc = 0;
					}
				}else{
					ayrikfonk[j].taban = sonuc;
					sonuc = 0;
				}
			
			}else if(fonk[i] == '^'){
				ayrikfonk[j].taban = sonuc;
				sonuc = 0 ;
				i++;
				if(isNumber(fonk[i]) || fonk[i] == 'x' ){
					if(fonk[i] == 'x'){
						sonuc = x;
						i++;
					}else{
						sonuc = sayihesap(fonk,&i);
					}
					ayrikfonk[j].us = sonuc;
					sonuc = 0;
				}
			}else{
				ayrikfonk[j].katsayi = sonuc;
				sonuc = 0;
			
			}
		
		}
		
		if(fonk[i] != '\0'){
			structyer++;
			ayrikfonk = (struct polinom *)realloc(ayrikfonk,structyer*sizeof(struct polinom));
			j++;
			if(flag == 0){
				flag++;
				parametreler = (char *)calloc(parametreyer,sizeof(char));
			}else{
				parametreyer++;
				parametreler = (char *)realloc(parametreler,parametreyer*sizeof(char));
			}
			
			parametreler[parametreyer-1]=fonk[i];
			i++;
		}
	}
	
	j=0;
	yenisonuc = (ayrikfonk[j].isaret)*(ayrikfonk[j].katsayi)*pow(ayrikfonk[j].taban,ayrikfonk[j].us);
	j++;
	while(j<structyer){
		if(parametreler[j-1] == '+'){
			yenisonuc = yenisonuc + ((ayrikfonk[j].isaret)*(ayrikfonk[j].katsayi)*pow(ayrikfonk[j].taban,ayrikfonk[j].us));
		}else{
			yenisonuc = yenisonuc - ((ayrikfonk[j].isaret)*(ayrikfonk[j].katsayi)*pow(ayrikfonk[j].taban,ayrikfonk[j].us));
		}
		j++;
	}
	
	return yenisonuc;
	
}

float sayihesap(char *fonk,int *i){
	float sonuc;
	int y;
	
	y = i[0];
	while(isNumber(fonk[y])){
		sonuc = sonuc*10 + (fonk[y] - '0');
		y++;
	}
	if(fonk[y]=='.'){
		y++;
		while(isNumber(fonk[y])){
			sonuc = sonuc + (1/10)*(fonk[y]-'0');
			y++;
		}
	}
	i[0] = y;
	return sonuc;
}

int isArtieksi(char a){
	if( a - '+' == 0 || a - '-' == 0){
		return 1;									//art� ve ya eksi olup olmad���n� kontrol etme
	}else{
		return 0;
	}
}
int isNumber(char a){  //say� m� kontrol ediyor
    return (a >= '0' && a <= '9');                              
}																				*/

/*int epsilonhesap(float a,float b,float epsilon,int i){
	
	if((a-b)<0){
		c = b-a;
	}else{
		c = a-b
	}
	
	if(c/(pow(2,i))>epsilon){
		return 1;
	}else{
		return 0;
	}
	
}*/
/*
void bisection(){
		 
	char fonk[500];
	float start,end,epsilon;
	int stop,max;
	
	printf("Fonksiyon: ");
	scanf(" %[^\n]", fonk);
	printf("\nBaslangic degerini giriniz: \n");
	scanf("%f",&start);
	printf("Bitis degerini giriniz: \n");
	scanf("%f",&end);
	printf("Hata degerini giriniz: \n");
	scanf("%f",&epsilon);
	printf("Durma kosulu 1->(f(x)<=epsilon) or 2->(((end-start)/2^n)<=epsilon): \n");
	scanf("%d",&stop);
	printf("Maksimum iterasyon degeri: \n");
	scanf("%d",&max);
	
	
	
	if(fh(fonk,start)*fh(fonk,end)<0){
		int i=0;
		float pozitif, negatif, yeni;
		
		if(fh(fonk,start)>fh(fonk,end)){
			pozitif = start;
			negatif = end;
		}
		else{
			pozitif = end;
			negatif = start;
		}																								*/
																								  
		/*while(epsilonhesap(pozitif,negatif,epsilon,i) && max > i){
			yeni = (pozitif+negatif)/2;
			
			printf("start: %f",);
		}
		
		*/																			/*
	}
	else{
		printf("Bu aralikta kok bulunamadi");
	}
	
	
	 
}											*/




//----------------------------------------------------------------------------------------------------

int menu(){		//
	int n;
	printf("--------MAIN MENU--------\n\n\n");
	printf("Quit: 0\nBisection: 1\nRegula-Falsi: 2\nNewton-Rapshon: 3\nInverse Matrix: 4\nGauss Elimination: 5\nGauss-Seidel: 6\nNumerical Differentiation: 7\nSimpson's Rule: 8\nTrapezoidal Rule: 9\nGregory-Newton: 10\n\nChoice: ");
	scanf("%d",&n);
	return n;
}

void inversematrix(int N,float **matrix){		//verilen matris ve matrisin boyutu ile matrisin tersini ekrana yazd�ran fonksiyon
	float **inverse;					
	int i,j,k;
	float bolme;
	inverse = (float**)calloc(N,sizeof(float *));
	for(i=0;i<N;i++){												
		inverse[i] = (float *)calloc(N,sizeof(float));	//matrisin tersini tutacak dinamik a��lan matris
	}
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(i==j){
				inverse[i][j] = 1;
			}else{							//birim matrisin de�erlerini at�yoruz
				inverse[i][j] = 0;
			}
		}
	}
	
	for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(i != j) {
                bolme = matrix[j][i] / matrix[i][i]; 				//s�rayla gezerek de�erleri g�ncelleye g�ncelleye matrisin tersini alan kod
                for(k = 0; k < N; k++) {						
                    matrix[j][k] = matrix[j][k] - matrix[i][k] * bolme;
                    inverse[j][k] = inverse[j][k] - inverse[i][k] * bolme;
                }
            }
        }
    }

    for(i = 0; i < N; i++) {
        bolme = matrix[i][i];
        for(j = 0; j < N; j++) {
            matrix[i][j] = matrix[i][j] / bolme;			//ilk matrisin k��egenini 1 e e�it olacak �ekilde de�erleri g�ncelleyen kod
            inverse[i][j] = inverse[i][j] / bolme;
        }
    }
	
	printf("\n\nMatrisin Tersi:\n\n");
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {					// ekrana yazd�rma
            printf("%8.2f ", inverse[i][j]);
        }
        printf("\n");
    }
	
	
}





void elemination(float **matrix,int N){		//eliminasyon y�ntemiyle de�i�ken de�erlerini hesaplama
						
	int i,j,k;
	float bolme, *degiskenler, sonuc;		
	
	degiskenler = (float *)calloc(N,sizeof(float));				//de�i�kenleri tutan pointer
	
	for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(j>i) {
                bolme = matrix[j][i] / matrix[i][i];				//matrisi �st ��gen haline getirme i�lemi
                for(k = 0; k < N+1; k++) {
                    matrix[j][k] = matrix[j][k] - matrix[i][k] * bolme;
                }
            }
        }
    }
    
    for(i = 0; i < N; i++) {
        bolme = matrix[i][i];
        for(j = 0; j < N+1; j++) {				   //k��egeni 1 e e�itleme	
            matrix[i][j] = matrix[i][j] / bolme;
        }
    }
    j = N-1;
    for(i=0;i<N;i++){
    	sonuc = 0;
    	if(j!=N-1){
    		for(k=0;k<N-j-1;k++){
    			sonuc += matrix[N-i-1][N-1-k]*degiskenler[N-1-k];
			}														//de�i�kenleri hesaplama
		}
		degiskenler[j] = matrix[j][N] - sonuc;
		j--;
	}
	printf("\n\n");
	for(i=0;i<N;i++){												//ekrana yazd�rma
		printf("%d. degiskenin degeri: %.2f\n",i+1,degiskenler[i]);
	}
    
}

void gaussSeidal(float **matrix, float x, float y, float z,int max,float epsilon){	
	
	float temp,x1,y1,z1;
	int i,buyuk = 0; 
	
	 	
   	for(i=1;i<3;i++){
   		if( fabs(matrix[i][0]) > fabs(matrix[buyuk][0])){
 			buyuk = i;										// x in mutlak en b�y�k katsay�s�n� bulma	
		}
	}
	if(buyuk != 0){
		for(i=0;i<4;i++){
			temp = matrix[0][i];
			matrix[0][i] = matrix[buyuk][i];	//denklemlerin yerlerini de�i�tirme
			matrix[buyuk][i] = temp;
		}
	}
	
	buyuk = 1;
	if(fabs(matrix[2][1])>fabs(matrix[1][1])){
		buyuk = 2; 
		for(i=0;i<4;i++){							//y i�in denklem yerini d�zenleme
			temp = matrix[1][i];
			matrix[1][i] = matrix[2][i];		
			matrix[2][i] = temp;
		}
	}
	
	i=0;
	printf("\n%d. iterasyon:\n",i+1);
	printf("x: %.3f\ny: %.3f\nz: %.3f\n",x,y,z);
	sleep(1);
	
	while(i<max){
		if((fabs(x-x1) >= epsilon || fabs(y-y1) >= epsilon || fabs(z-z1) >= epsilon)){
			printf("\n%d. iterasyon:\n",i+2);
			x1 = x;
			y1 = y;
			z1 = z;					//de�i�kenleri hesaplama a�amas�n� ekrana yazd�rma
		
			x = (matrix[0][3]-matrix[0][2]*z-matrix[0][1]*y)/matrix[0][0];
			y = (matrix[1][3]-matrix[1][2]*z-matrix[1][0]*x)/matrix[1][1];
			z = (matrix[2][3]-matrix[2][1]*y-matrix[2][0]*x)/matrix[2][2];
		
			printf("x: %.3f\ny: %.3f\nz: %.3f\n",x,y,z);
			sleep(1);
			i++;
		}else{
			i = max;
		}
		
	}
	
	
	printf("\n\nx: %.3f\ty: %.3f\tz: %.3f",x,y,z);
	
}


void gnEnterpolasyon(float **matrix,int N,float h,float x){
	
	float **enterpolasyon;
	int i,j;
	float arasonuc,sonuc=0;
	
	enterpolasyon = (float **)calloc(N,sizeof(float *));
	for(i=0;i<N;i++){
		enterpolasyon[i] = (float *)calloc(N,sizeof(float));
	}																	//dinamik yer a�ma
	
	for(i=0;i<N;i++){
		enterpolasyon[i][0] = matrix[i][1];		
	}
	
	for(i=0;i<N-1;i++){
		for(j=0;j<N-1-i;j++){														//enterpolasyon matrisi i�inde enterpolasyon grafi�ini olu�turuyor
			enterpolasyon[j][i+1] = enterpolasyon[j+1][i] - enterpolasyon[j][i];		
		}
	}
	
	
	for(i=0;i<N;i++){
		arasonuc = 1;
		for(j=0;j<i;j++){
			arasonuc = arasonuc*(x-matrix[j][0])/(h*(j+1));		//istenilen x de�erine g�re f(x) i hesaplama
		}
		sonuc += enterpolasyon[0][i]*arasonuc;
	}
	
	printf("x= %.2f icin f(x)= %.2f ",x,sonuc);
}










int main(){
	int n, N, i, j, buyuk,max;
	float x,y,z,temp,h,epsilon;
	float **matrix;
	char dizi[200];
	
	do{  // her seferinde i�lemden ��kt�ktan sonra ekrana bas�lacak men� i�in kulland���m do-while d�ng�s� i�lem sonunda her �ey silinip men� tekrar bas�l�yor
		n = menu();
		
		switch(n){
			case 1:
				//bisection();
				break;
				
			case 2:
				
				break;
				
			case 3:
				
				break;
				
			case 4:
				system("cls");
				printf("Gireceginiz NxN matrisin N degeri nedir:\n");
				scanf("%d",&N);
				
				matrix = (float **)calloc(N,sizeof(float *));
				for(i=0;i<N;i++){
					matrix[i] = (float *)calloc(N,sizeof(float));
				}
				
				printf("Matris elemanlarini girin:\n");
    			for(i = 0; i < N; i++) {
        			for(j = 0; j < N; j++) {
            			printf("matris[%d][%d]: ", i, j);
            			scanf("%f", &matrix[i][j]);
        			}
   				}
   				
				inversematrix(N,matrix);
				
				printf("\n\n");
				system("pause");
				free(matrix);
				break;
				
			case 5:
				system("cls");
				printf("Kac degiskenli fonksiyon icin kullanmak istiyorsunuz:\n");
				scanf("%d",&N);
				
				matrix = (float **)calloc(N,sizeof(float *));
				for(i=0;i<N;i++){
					matrix[i] = (float *)calloc(N+1,sizeof(float));
				}
				
				
				printf("Lutfen denklemin degerlerini matris seklinde giriniz\n");
				for(i = 0; i < N; i++) {
        			for(j = 0; j < N +1; j++) {
            			printf("matris[%d][%d]: ", i, j);
            			scanf("%f", &matrix[i][j]);
        			}
   				}
   				
				
				elemination(matrix,N);
				
				printf("\n\n");
				system("pause");
				free(matrix);
				break;
				
			case 6:
				system("cls");
				printf("Lutfen matris halinde denklem degerlerini giriniz:\n\n");
				matrix = (float **)calloc(3,sizeof(float *));
				for(i=0;i<3;i++){
					matrix[i] = (float *)calloc(4,sizeof(float));
				}
				for(i = 0; i < 3; i++) {
        			for(j = 0; j < 4; j++) {
            			printf("matris[%d][%d]: ", i, j);
            			scanf("%f", &matrix[i][j]);
        			}
   				}
   				printf("x'in baslagic degerini giriniz:\n");
   				scanf("%f",&x);
   				printf("y'nin baslagic degerini giriniz:\n");
   				scanf("%f",&y);
				printf("z'nin baslagic degerini giriniz:\n");
				scanf("%f",&z);
				
				printf("\nMaksimum iterasyon sayisi:\n");
				scanf("%d",&max);
				
				printf("\nEpsilon degeri:\n");
				scanf("%f",&epsilon);
				gaussSeidal(matrix,x,y,z,max,epsilon);
				
				printf("\n\n");
				system("pause");
				free(matrix);
				break;
				
			case 7:
				
				break;
				
			case 8:
				
				break;
				
			case 9:
				
				break;
				
			case 10:
				system("cls");
				printf("x'in kac tane degeri icin f(x)'i gireceksiniz:\n");
				scanf("%d",&N);
				
				printf("\nEnterpolasyon ile hangi x degerinin sonucunu istiyorsunuz:\n");
				scanf("%f",&x);
				
				matrix = (float **)calloc(N,sizeof(float *));
				for(i=0;i<N;i++){
					matrix[i] = (float *)calloc(2,sizeof(float));
				}
				for(i=0;i<N;i++){
					printf("\nx%d: ",i);
					scanf("%f",&matrix[i][0]);
					printf("f(x%d): ",i);
					scanf("%f",&matrix[i][1]);
				}
				
				h =	 matrix[1][0] - matrix[0][0];
				
				gnEnterpolasyon(matrix,N,h,x);
				
				printf("\n\n");
				system("pause");
				free(matrix);
				
				break;			
		}
		system("cls");
		
	}while(n != 0);
}
