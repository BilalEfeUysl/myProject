#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

/*
OYUNU TANITAN VIDEOYA ASAGIDAKI LINK'DEN ULASABILIRSINIZ


https://youtu.be/_coY_4ouJJQ

*/

//Ana menuyu ekrana basan fonksiyon
int menu(){

	int n;
	printf("----------SKIPPITY----------\n\n\n\nOTOMATIK MOD(1)\n\nOTOMATIK MOD KAYITLI OYUN(2)\n\nMANUEL MOD(3)\n\nMANUEL MOD KAYITLI OYUN(4)\n\nQUIT(0)\n\nCHOICE: ");
	scanf("%d",&n);
	return n;
}

//dinamik sekilde oyuncunun istedigi boyutta oyun tahtasini olusturma
char ** creatematrix(int n){
	char ** matrix;
	int i;
	
	matrix = (char **)calloc(n,sizeof(char *));
	for(i=0;i<n;i++){
		matrix[i] = (char *)calloc(n,sizeof(char));
	}
	return matrix;
}

//oyun tahtasini ekrana yazdiran fonksiyon
void printmatrix(char **matrix,int n){
	int i,j;

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%c ",matrix[i][j]);
		}
		printf("\n");
	}
}

//rastgele taslari ortada bosluk olacak sekilde tahtaya koyma
void randommatrix(char **matrix, int n) {
    
    //bosluklarin kordinatlarýný x ve y degerlerine esitliyoruz
    int center = n / 2;
    int x1 = center - 1, y1 = center - 1;
    int x2 = center - 1, y2 = center;
    int x3 = center, y3 = center - 1;
    int x4 = center, y4 = center;
	char letters[] = {'A', 'B', 'C', 'D', 'E'};
	int sayi = 5,i,j,random; 
	
	
    srand(time(NULL)); 
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            
            if ((i == x1 && j == y1) || (i == x2 && j == y2) || (i == x3 && j == y3) || (i == x4 && j == y4)) {
                matrix[i][j] = ' ';
            } else {
                random = rand() % sayi;
                matrix[i][j] = letters[random];
            }
        }
    }
}

//oyuna devam edebilmek ve ya sonlandirabilmek icin herhangi oynanabilecek hamle olup olmadýgýný kontrol ediyor
int hamlekontrol(char **board,int N){
	int i,j,hamle;
	
	//ilk once i,j degerlerine göre o nokta dolu mu diye bakiyor ve sonra farklý yonler icin farklý kontroller yapilarak yapilabilecek hamle varsa degiskeni arttýrýyor ve fonksiyon bu degiskeni return ediyor
	hamle = 0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(board[i][j] != ' '){
				if(i>1){
					if(board[i-1][j] != ' '){
						if(board[i-2][j] == ' '){
							hamle += 1;
						}
					}
				}
				if(j<N-2){
					if(board[i][j+1] != ' '){
						if(board[i][j+2] == ' '){
							hamle += 1;
						}
					}
				}
				if(i<N-2){
					if(board[i+1][j] != ' '){
						if(board[i+2][j] == ' '){
							hamle += 1;
						}
					}
				}
				if(j>1){
					if(board[i][j-1] != ' '){
						if(board[i][j-2] == ' '){
							hamle += 1;
						}
					}
				}
			}
			
		}
	}
	
	if(hamle==0){
		return 1;
	}else{
		return 0;
	}
}

//en az aldigi tasi bularak skor olarak return ediyor
int skorhesap(int puan[][5],int oyuncu){
	int i,kucuk;
	
	kucuk = puan[oyuncu][0] ;
	for(i=1;i<5;i++){
		if(puan[oyuncu][i]<kucuk)
		kucuk = puan[oyuncu][i];
	}
	
	
	return kucuk;
}

//oyun sonlanmadan cikis yapilirsa oyun tahtasini oyuncu sirasini ve undo haklarini dosyaya yazan fonksiyon
void writefile(char **board,int puan[][5],int currentPlayer,int N,int undohak1,int undohak2){
	FILE *file;
	int i,j;
	
	file = fopen("dosya","w");
	for(i=0;i<2;i++){
		for(j=0;j<5;j++){
			fprintf(file,"%d ",puan[i][j]);
		}
		fprintf(file,"\n");
	}
	
	fprintf(file,"%d",currentPlayer);
	fprintf(file,"\n");
	fprintf(file,"%d ",undohak1);
	fprintf(file,"%d ",undohak2);
	fprintf(file,"\n");
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			fprintf(file,"%c",board[i][j]);
		}
		
	}
	fclose(file);
}

//kaydedilen oyuna devam etmek istenirse kaydedilen dosyadan okuyan fonksiyon
void readfile(char **board,int puan[][5],int *currentPlayer,int N,int *undohak1,int *undohak2){
	FILE *file;
	int i,j;
	file = fopen("dosya","r");
	for(i=0;i<2;i++){
		for(j=0;j<5;j++){
			fscanf(file,"%d ",&puan[i][j]);
		}
	}
	
	fscanf(file,"%d",&currentPlayer);
	fscanf(file,"%d ",&undohak1);
	fscanf(file,"%d ",&undohak2);
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			fscanf(file,"%c",&board[i][j]);
		}
	}
	
	fclose(file);
	
}


int main(){
	int n,N,flag,x1,y1,x2,y2,xd1,xd2,yd1,yd2,currentPlayer=0,i,j,tekrar=0,kontrol=0,kazanan,hatali=0,undohak1 = 1,undohak2 = 1,donus = 0,bulundu=0,berabere = 0;
	char **board,secenek,temp1,temp2,enaz;
	int puan[2][5]={{0,0,0,0,0},{0,0,0,0,0}};
	
	do{
		//bu donguye girildigi gibi menu basilir ve istenen moda gore switch'e girip oyun baslar
		n = menu();
		system("cls");
		switch (n) {
			//cikis yapilirsa dinamik belleði serbest birakip oyundan cikiyor
			case 0:
				free(board);
            	break;
            // 1 ve ya 2 numara secilirse ayný case'e giriliyor
            case 1:
        	case 2:
        		flag = 0;
        		//eger 1.mod ile girilmisse ve ya kayýtlý mod ile girilmis ama kayitli olyun yoksa(yani donus degiskeni 1 degilse) oyun tahtasinin boyutu istenip tahta olusturuluyor
            	if(n==1||(n==2 && donus==0)){
            		printf("Oyun tahsatinin boyutunu giriniz: \n");
         		   	scanf("%d",&N);
            		board = creatematrix(N);
           		 	randommatrix(board,N);
				}
				
            	//eger kayýtlý mod calistirilmis ve onceden kayitli oyun varsa(yani donus degiskeni 1 ise) kayitli oyunu dosyadan okuyor
            	if(n==2 && donus==1){
            		readfile(board,puan,&currentPlayer,N,&undohak1,&undohak2);
				}
            
            	do{	
            		//her hamle basi oynanacak hamle olup olmadigini kontrol edip eger yoksa bi alttaki if kontrolune girerek sonuc ekranini bastiriyor daha hamle varsa ise else'in icine giriyor
					kontrol = hamlekontrol(board,N);
					
					if(kontrol == 1){
						system("cls");
						if(skorhesap(puan,0)>skorhesap(puan,1)){
							kazanan=1;
						}else if(skorhesap(puan,0)==skorhesap(puan,1)){
							
							berabere = 1;
							
						}else{
							kazanan=2;
						}
						if(berabere != 1){
							printf("----------OYUN BITTI----------\n\n1.OYUNCU SKORU: %d\n2.OYUNCU SKORU: %d\n\nKAZANANNN %d.OYUNCU",skorhesap(puan,0),skorhesap(puan,1),kazanan);
						
						}
						else{
							printf("----------OYUN BITTI----------\n\n1.OYUNCU SKORU: %d\n2.OYUNCU SKORU: %d\n\nBERABERE",skorhesap(puan,0),skorhesap(puan,1));
						
						}
						berabere = 0;
						printf("\n");
						system("PAUSE");
					}else{
						//skorlari oyun tahtasini ve oyuncu sirasini ekrana yaziyor
                		system("cls");
                		printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
                		printmatrix(board,N);
			    		printf("\n\nHamle sirasi %d. oyuncuda->\n",currentPlayer+1);
			    		
			    		donus = 0;
			    		//hatali hamle oldugu sürece isleyen do-while
			    		do{
			    			hatali=0;
			    			//eger cuurentPlayer = 0 ise sira gercek oyuncuda demek ve bizden hamle istiyor eðer currentPlayer = 1 ise sira bilgisayarda ve else koluna gecerek belli algoritmaya gore taslar seciliyor
			    			if(currentPlayer == 0){
			    				if(tekrar == 0){
			    					printf("\n\nOynatmak istediginiz tasin kordinatlarini giriniz:\n\nx: ");
			    					scanf("%d",&x1);
			    					x1--;
			    					printf("y: ");
			    					scanf("%d",&y1);
			    					y1--;
			    				}else{
			    					x1 = x2;
			    					y1 = y2;
			    				}
			    				
			    				printf("\n\nGoturmek istediginiz yerin kordinatlarini giriniz:\n\nx: ");
           	     		
                				scanf("%d",&x2);
                				x2--;
                				printf("y: ");
                				scanf("%d",&y2);
                				y2--;
                				
			    			}else{
			    				j=0;
			    				//algoritma kendisine lazim olan tasi almaya yonelik tasarlandi ilk once kendisinde olan en az tasi buluyor ve 'enaz' degiskenine o tasi atiyor
			    				for(i=1;i<5;i++){
			    					if(puan[currentPlayer][i]<puan[currentPlayer][j]){
			    						j = i;
			    					}
			    					
			    				}
			    				
			    				switch(j){
			    					case 0:
			    						enaz = 'A';
			    						break;
			    					case 1:
			    						enaz = 'B';
			    						break;
			    					case 2:
			    						enaz = 'C';
			    						break;
			    					case 3:
			    						enaz = 'D';
			    						break;
			    					case 4:
			    						enaz = 'E';
			    						break;				
			    							 
			    				}
			    				// tekrar degiskeni bir oyuncu bir tas oynadýktan sonra halen tas alabiliyorsa 1 degerine sahip oluyor o yuzden eger tekrar = 0 ise bu if'e giriyor deðil ise else'e giriyor
			    				if(tekrar == 0){
			    					//tum tahtayi gezerek o anki tasin alabilecegi taslara bakiyor eger enaz degiskenine esitse bunu ayri kaydediyor eger en az degiskeni deðil ise baska bi yerde yine kaydediliyor
			    					for(i=0;i<N;i++){
			    						for(j=0;j<N;j++){
			    							if(board[i][j] != ' '){
			    								if(j<N-2){
			    									if(board[i][j+1] != ' '){
			    										if(board[i][j+2] == ' '){
			    											if(board[i][j+1]== enaz){
			    												bulundu = 1;
			    												x1 = j;
			    												y1 = i;
			    												x2 = j+2;
			    												y2 = i;
			    											}else{
			    												xd1 = j;
			    											 	yd1 = i;
			    											 	xd2 = j+2;
			    											 	yd2 = i;
			    											}
			    										}
			    									}
			    								}
			    								if(i<N-2){
			    									if(board[i+1][j] != ' '){
			    										if(board[i+2][j] == ' '){
			    											if(board[i+1][j]== enaz){
			    												bulundu = 1;
			    												x1 = j;
			    												y1 = i;
			    												x2 = j;
			    												y2 = i+2;
			    											}else{
			    												xd1 = j;
			    											 	yd1 = i;
			    											 	xd2 = j;
			    											 	yd2 = i+2;
			    											}
			    										}
			    									}
			    								}
			    								if(j>1){
			    									if(board[i][j-1] != ' '){
			    										if(board[i][j-2] == ' '){
			    											if(board[i][j-1]== enaz){
			    												bulundu = 1;
			    												x1 = j;
			    												y1 = i;
			    												x2 = j-2;
			    												y2 = i;
			    											}else{
			    												xd1 = j;
			    											 	yd1 = i;
			    											 	xd2 = j-2;
			    											 	yd2 = i;
			    											}
			    										}
			    									}
			    								}
			    								if(i>1){
			    									if(board[i-1][j] != ' '){
			    										if(board[i-2][j] == ' '){
			    											if(board[i-1][j]== enaz){
			    												bulundu = 1;
			    												x1 = j;
			    												y1 = i;
			    												x2 = j;
			    												y2 = i-2;
			    											}else{
			    												xd1 = j;
			    											 	yd1 = i;
			    											 	xd2 = j;
			    											 	yd2 = i-2;
			    											}
			    										}
			    									}
			    								}
			    							}
			    							
			    						}
			    					}
			    					
			    					// enaz degiskenini alabildigi hamleyi bulamadiysa bulundu 0'e esit oluyor ve rastgele alabildigi baska bir hamleyi seciyor 
			    					if(bulundu == 0){
			    						x1 = xd1;
			    						y1 = yd1;
			    						x2 = xd2;
			    						y2 = yd2;
			    					}else{
			    						bulundu =0;
			    					}
			    				
								//tekrar degiskeni bir oyuncu bir tas oynadýktan sonra halen tas alabiliyorsa 1 degerine sahip oluyordu eger alabiliyorsa bu kola giriyor ve bi sonraki hamlesi icin yeni kordinatlari seciyor
			    				}else{
			    					x1 = x2;
			    					y1 = y2;
			    					//yine enaz alabilecegi tasi ariyor bulursa o hamleyi yapýyor bulamazsa yine rastgele bir hamle yapiyor
			    					if(x1<N-2){
			    						if(board[y1][x1+1] != ' '){
			    							if(board[y1][x1+2] == ' '){
			    								if(board[y1][x1+1] == enaz){
			    									bulundu = 1;
			    									j = x1+2;
			    									i = y1;
			    								}else{
			    									xd2 = x1 + 2;
			    									yd2 = y2;
			    								}
			    							}
			    						}
			    					}
			    					if(y1<N-2){
			    						if(board[y1+1][x1] != ' '){
			    							if(board[y1+2][x1] == ' '){
			    								if(board[y1+1][x1] == enaz){
			    									bulundu = 1;
			    									j = x1;
			    									i = y1+2;
			    								}else{
			    									xd2 = x1;
			    									yd2 = y2+2;
			    								}
			    							}
			    						}
			    					}
			    					if(x1>1){
			    						if(board[y1][x1-1] != ' '){
			    							if(board[y1][x1-2] == ' '){
			    								if(board[y1][x1-1] == enaz){
			    									bulundu = 1;
			    									j = x1-2;
			    									i = y1;
			    								}else{
			    									xd2 = x1-2;
			    									yd2 = y2;
			    								}
			    							}
			    						}
			    					}
			    					if(y1>1){
			    						if(board[y1-1][x1] != ' '){
			    							if(board[y1-2][x1] == ' '){
			    								if(board[y1-1][x1] == enaz){
			    									bulundu = 1;
			    									j = x1;
			    									i = y1-2;
			    								}else{
			    									xd2 = x1;
			    									yd2 = y2-2;
			    								}
			    							}
			    						}
			    					}
			    					
			    					if(bulundu==0){
			    						x2 = xd2;
			    						y2 = yd2;
			    					}else{
			    						x2 = j;
			    						y2 = i;
			    						bulundu = 0;
			    					}
			    					
			    				}
			    				
			    			}
			    			
			    			
			    			//undo yapabilmek icin surekli temp1 degiskeninde oynattýgý tasý tutuyor
                			temp1 = board[y1][x1];
                			
           	     			
                			//temp2 degiskeninde ise aldigi tasin ne oldugunu tutuyor
                			temp2 = board[(y2+y1)/2][(x1+x2)/2];
                			
                			//hatali hamle kontrolu
			    			if(board[y1][x1] == ' ' || board[y2][x2] != ' ' ||board[(y2+y1)/2][(x1+x2)/2]==' '){
			    				printf("\nHatali hamle tekrar bilgileri giriniz...");
			    				sleep(3);
			    				hatali = 1;
			    			}
			    			
			    		}while(hatali == 1);
			    		
			    		
			    		//aldigi tas sayilari 2x5' puan dizisinde tutuluyor bu switch'te de aldigi tasin degerini bir arttiriyor
                		switch(board[(y2+y1)/2][(x1+x2)/2]){
                			case 'A':
                				puan[currentPlayer][0] += 1;
                				break;
                			case 'B':
                				puan[currentPlayer][1] += 1;
                				break;
			    			case 'C':
			    				puan[currentPlayer][2] += 1;
                				break;
			    			case 'D':
			    				puan[currentPlayer][3] += 1;
                				break;
			    			case 'E':
			    				puan[currentPlayer][4] += 1;
                				break;
			    									
			    		}
			    		tekrar = 0;
			    		
			    		//oyun tahtasini hamleye gore duzenliyor
			    		if(board[(y2+y1)/2][(x1+x2)/2] != ' '){
			    			
			    			board[(y2+y1)/2][(x1+x2)/2] = ' ';
			    			board[y2][x2] = board[y1][x1];
			    			board[y1][x1] = ' ';
			    		
			    		}
			    		
			    		if(y2>1){
			    			if(board[y2-1][x2] != ' '){
			    				if(board[y2-2][x2] == ' '){
			    					tekrar = 1;
			    				}
			    			}
			    		}
			    		if(x2<N-2){
			    			if(board[y2][x2+1] != ' '){
			    				if(board[y2][x2+2] == ' '){
			    					tekrar = 1;
			    				}
			    			}
			    		}
			    		if(y2<N-2){
			    			if(board[y2+1][x2] != ' '){
			    				if(board[y2+2][x2] == ' '){
			    					tekrar = 1;
			    				}
			    			}
			    		}
			    		if(x2>1){
			    			if(board[y2][x2-1] != ' '){
			    				if(board[y2][x2-2] == ' '){
			    					tekrar = 1;
			    				}
			    			}
			    		}
			    		
			    		
			    		
			    		
                		
                		system("cls");
                		printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
                		printmatrix(board,N);
                		
                		//devam mi,undo mu,cikis mi yapmak istedigimizisoruyor 
                		printf("\n\nContinue(ENTER)\nUNDO(1)\nQuit(Esc)");
                		
                		//eger oyuncu bilgisayar degilse kullanýcýdan char aliyor bilgisayar ise direkt devam ediyor
                		if(currentPlayer == 0){
                			secenek = getch();
			    		}else{
			    			secenek = '\n';
			    		}
                		
                		//eger cikis yaparsa oyun bilgileri kayitli oyun oynamak istersek diye dosyaya yaziliyor
                		if(secenek == 27){
                			writefile(board,puan,currentPlayer,N,undohak1,undohak2);
                			donus = 1;
			    		}//eger undoyu secerse asagidaki kola giriyor ve aldigi satin degerini azaltiyor ve tahtayi eski haline guncelliyor ve undo hakkini bir azaltiyor
			    		else if(secenek == '1'){
			    			if(currentPlayer==1){//1. oyuncu icin bu islemi yapýyor 
			    				if(undohak1 == 1){
			    					if(tekrar == 0){
			    						if (currentPlayer == 0) {
  			    							currentPlayer = 1;
			    						} else {
   			    							currentPlayer = 0;
			    						}
			    					}
			    					switch(temp2){
			    						case 'A':
			    							puan[currentPlayer][0]--;
			    							break;
			    						case 'B':
			    							puan[currentPlayer][1]--;
			    							break;
			    						case 'C':
			    							puan[currentPlayer][2]--;
			    							break;
			    						case 'D':
			    							puan[currentPlayer][3]--;
			    							break;
			    						case 'E':
			    							puan[currentPlayer][4]--;
			    							break;
			    					}
			    			
			    					tekrar =0;
			    					board[y1][x1] = temp1;
			    					board[(y2+y1)/2][(x1+x2)/2] = temp2;
			    					board[y2][x2] = ' ';
			    					undohak1--;
			    					system("cls");
                					printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
                					printmatrix(board,N);
                					printf("\n\nContinue(ENTER)\nREDO(1)\nQuit(Esc)");
                					secenek = getch();
                					//devam,undo ve ya cýkýs gibi tekrardan char aliyor benzer islemleri tekrar yapiyor
                					if(secenek == 27){
                						writefile(board,puan,currentPlayer,N,undohak1,undohak2);
                						donus = 1;
			    					}else if(secenek == '1'){
			    						switch(temp2){
			    							case 'A':
			    								puan[currentPlayer][0]++;
			    								break;
			    							case 'B':
			    								puan[currentPlayer][1]++;
			    								break;
			    							case 'C':
			    								puan[currentPlayer][2]++;
			    								break;
			    							case 'D':
			    								puan[currentPlayer][3]++;
			    								break;
			    							case 'E':
			    								puan[currentPlayer][4]++;
			    								break;
			    						}
			    						
			    						board[(y2+y1)/2][(x1+x2)/2] = ' ';
			    						board[y2][x2] = board[y1][x1];
			    						board[y1][x1] = ' ';
			    						
			    						
			    					}
			    				}
			    			}else{//diger oyuncu icin buraya giriyor ve ayný islemleri bu oyuncu icin de yapiyor
			    				if(undohak2 == 1){
			    					if(tekrar == 0){
			    						if (currentPlayer == 0) {
  			    							currentPlayer = 1;
			    						} else {
   			    							currentPlayer = 0;
			    				 		}
			    					}
			    					
			    					switch(temp2){
			    						case 'A':
			    							puan[currentPlayer][0]--;
			    							break;
			    						case 'B':
			    							puan[currentPlayer][1]--;
			    							break;
			    						case 'C':
			    							puan[currentPlayer][2]--;
			    							break;
			    						case 'D':
			    							puan[currentPlayer][3]--;
			    							break;
			    						case 'E':
			    							puan[currentPlayer][4]--;
			    							break;
			    					}
			    			
			    					tekrar =0;
			    					board[y1][x1] = temp1;
			    					board[(y2+y1)/2][(x1+x2)/2] = temp2;
			    					board[y2][x2] = ' ';
			    					undohak2--;
			    					system("cls");
                					printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
                					printmatrix(board,N);
                					printf("\n\nContinue(ENTER)\nREDO(1)\nQuit(Esc)");
                					secenek = getch();
                					if(secenek == 27){
                						writefile(board,puan,currentPlayer,N,undohak1,undohak2);
                						donus = 1;
			    					}else if(secenek == '1'){
			    						switch(temp2){
			    							case 'A':
			    								puan[currentPlayer][0]++;
			    								break;
			    							case 'B':
			    								puan[currentPlayer][1]++;
			    								break;
			    							case 'C':
			    								puan[currentPlayer][2]++;
			    								break;
			    							case 'D':
			    								puan[currentPlayer][3]++;
			    								break;
			    							case 'E':
			    								puan[currentPlayer][4]++;
			    								break;
			    						}
			    						
			    						board[(y2+y1)/2][(x1+x2)/2] = ' ';
			    						board[y2][x2] = board[y1][x1];
			    						board[y1][x1] = ' ';
			    						
			    						
			    					}
			    				}
			    				
			    			}
			    			
			    		}
			    		//tekrardan alinabilecek hamle yoksa tekrar=0 oludugu icin oyuncuyu degistiriyor
			    		if(tekrar!=1){
			    			if (currentPlayer == 0) {
  			    			currentPlayer = 1;
			    			} else {
   			    				currentPlayer = 0;
			    			}
			    		}
					}	
				}while(flag == 0 && kontrol == 0 && donus == 0);
            	
            	
            	
            	printf("\n");
            	system("PAUSE");
        		
        		//oyundan ciktigi icin oyun tahtasýný bosaltiyor
        		for(i=0;i<N;i++){
        			for(j=0;j<N;j++){
        				board[i][j] = ' ';
					}
				}
        		
        		
 	      		break;
 	      		printf("\n");
            	system("PAUSE");
            	break;
      		case 3:
      		case 4:
      			//eger manuel yani 2 kisilik oyunu tercih ederse ister kayýtlý oyunu secsin ister en bastan oyuna girsin bu case e giriyor
        		flag = 0;
        		//eger 3 numarayý secerse yeni tahta olusturuyor veya kayitli oyunu secip kayitli oyun bulunmuyorsa yine buraya giriyor
            	if(n==3||(n==4 && donus==0)){
            		printf("Oyun tahsatinin boyutunu giriniz: \n");
         		   	scanf("%d",&N);
            		board = creatematrix(N);
           		 	randommatrix(board,N);
				}
				
            	//eger kayitli oyun bulunuyorsa buraya giriyor
            	if(n==4 && donus==1){
            		readfile(board,puan,&currentPlayer,N,&undohak1,&undohak2);
				}
            
            	do{
            		
					kontrol = hamlekontrol(board,N);
					
					//hamleyi kontrol ettiriyoruz var ise else donuyor yok ise if e girip oyunu bitiriyor
					if(kontrol == 1){
						system("cls");
						if(skorhesap(puan,0)>skorhesap(puan,1)){
							kazanan=1;
						}else if(skorhesap(puan,0)==skorhesap(puan,1)){
							
							berabere = 1;
							
						}else{
							kazanan=2;
						}
						if(berabere != 1){
							printf("----------OYUN BITTI----------\n\n1.OYUNCU SKORU: %d\n2.OYUNCU SKORU: %d\n\nKAZANANNN %d.OYUNCU",skorhesap(puan,0),skorhesap(puan,1),kazanan);
						
						}
						else{
							printf("----------OYUN BITTI----------\n\n1.OYUNCU SKORU: %d\n2.OYUNCU SKORU: %d\n\nBERABERE",skorhesap(puan,0),skorhesap(puan,1));
						
						}
						berabere = 0;
						printf("\n");
						system("PAUSE");
					}else{
            			system("cls");
            			printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
            			printmatrix(board,N);
						printf("\n\nHamle sirasi %d. oyuncuda->\n",currentPlayer+1);

						donus = 0;
						//hatalý hamle olduðu sürece devam eden do-while
						do{
							hatali=0;
							if(tekrar == 0){
								printf("\n\nOynatmak istediginiz tasin kordinatlarini giriniz:\n\nx: ");
								scanf("%d",&x1);
								x1--;
								printf("y: ");
								scanf("%d",&y1);
								y1--;
							}else{
								x1 = x2;
								y1 = y2;
							}
							
            				temp1 = board[y1][x1];
	
           		 			printf("\n\nGoturmek istediginiz yerin kordinatlarini giriniz:\n\nx: ");
	
            				scanf("%d",&x2);
            				x2--;
            				printf("y: ");
            				scanf("%d",&y2);
            				y2--;
	
            				temp2 = board[(y2+y1)/2][(x1+x2)/2];
	
							if(board[y1][x1] == ' ' || board[y2][x2] != ' ' ||board[(y2+y1)/2][(x1+x2)/2]==' '){
								printf("\nHatali hamle tekrar bilgileri giriniz...");
								sleep(3);
								hatali = 1;
							}

						}while(hatali == 1);


						//aldigi tasa gore tas sayilarini guncelleyen switch-case
            			switch(board[(y2+y1)/2][(x1+x2)/2]){
            				case 'A':
            					puan[currentPlayer][0] += 1;
            					break;
            				case 'B':
            					puan[currentPlayer][1] += 1;
            					break;
							case 'C':
								puan[currentPlayer][2] += 1;
            					break;
							case 'D':
								puan[currentPlayer][3] += 1;
            					break;
							case 'E':
								puan[currentPlayer][4] += 1;
            					break;

						}
						tekrar = 0;
						//girilen degerlere gore tahtayi guncelleyen kod
						if(board[(y2+y1)/2][(x1+x2)/2] != ' '){

							board[(y2+y1)/2][(x1+x2)/2] = ' ';
							board[y2][x2] = board[y1][x1];
							board[y1][x1] = ' ';

						}
						
						//halen alabilecegi tas var mi yok mu diye kontrol eden kod parcasi
						if(y2>1){
							if(board[y2-1][x2] != ' '){
								if(board[y2-2][x2] == ' '){
									tekrar = 1;
								}
							}
						}
						if(x2<N-2){
							if(board[y2][x2+1] != ' '){
								if(board[y2][x2+2] == ' '){
									tekrar = 1;
								}
							}
						}
						if(y2<N-2){
							if(board[y2+1][x2] != ' '){
								if(board[y2+2][x2] == ' '){
									tekrar = 1;
								}
							}
						}
						if(x2>1){
							if(board[y2][x2-1] != ' '){
								if(board[y2][x2-2] == ' '){
									tekrar = 1;
								}
							}
						}
						
						//tekrar alabilecegi hamle yoksa oyuncu sirasini degistiren kod
						if(tekrar!=1){
							if (currentPlayer == 0) {
  							currentPlayer = 1;
							} else {
   								currentPlayer = 0;
							}
						}

	
            			system("cls");
            			printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
            			printmatrix(board,N);
            			printf("\n\nContinue(ENTER)\nUNDO(1)\nQuit(Esc)");
            			secenek = getch();
						
						//eger cikarsak dosyaya kaydediyor
            			if(secenek == 27){
            				writefile(board,puan,currentPlayer,N,undohak1,undohak2);
            				donus = 1;
						}
						else if(secenek == '1'){//undo kýsmý bilgisayara karsi oynadigimizla ayni mantik
							if(currentPlayer==1){//1.oyuncu ise ona gore duzenliyor degilse diðer kýsýmda ikinci oyuncu icin duzenliyor
								if(undohak1 == 1){
									if(tekrar == 0){
										if (currentPlayer == 0) {
  											currentPlayer = 1;
										} else {
   											currentPlayer = 0;
										}
									}
									//aldigimiz tasi geri aliyor
									switch(temp2){
										case 'A':
											puan[currentPlayer][0]--;
											break;
										case 'B':
											puan[currentPlayer][1]--;
											break;
										case 'C':
											puan[currentPlayer][2]--;
											break;										
										case 'D':
											puan[currentPlayer][3]--;
											break;
										case 'E':
											puan[currentPlayer][4]--;
											break;
									}

									tekrar =0;
									board[y1][x1] = temp1;
									board[(y2+y1)/2][(x1+x2)/2] = temp2;
									board[y2][x2] = ' ';
									undohak1--;
									system("cls");
            						printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
            						printmatrix(board,N);
            						printf("\n\nContinue(ENTER)\nREDO(1)\nQuit(Esc)");
            						//cikarsak kaydediyor ve ya undo dersek islemleri tekrar geri aliyor
            						secenek = getch();
            						if(secenek == 27){
            							writefile(board,puan,currentPlayer,N,undohak1,undohak2);
            							donus = 1;
									}else if(secenek == '1'){
										switch(temp2){
											case 'A':
												puan[currentPlayer][0]++;
												break;
											case 'B':
												puan[currentPlayer][1]++;
												break;
											case 'C':
												puan[currentPlayer][2]++;
												break;
											case 'D':
												puan[currentPlayer][3]++;
												break;
											case 'E':
												puan[currentPlayer][4]++;
												break;
										}
										//tekrar oyun tahtasini duzenliyor
										board[(y2+y1)/2][(x1+x2)/2] = ' ';
										board[y2][x2] = board[y1][x1];		
										board[y1][x1] = ' ';


									}
								}
							}else{
								if(undohak2 == 1){
									if(tekrar == 0){
										if (currentPlayer == 0) {
  											currentPlayer = 1;
										} else {
   											currentPlayer = 0;
								 		}
									}
									//aldigimiz tasi geri aliyor
									switch(temp2){
										case 'A':
											puan[currentPlayer][0]--;
											break;
										case 'B':
											puan[currentPlayer][1]--;
											break;
										case 'C':
											puan[currentPlayer][2]--;
											break;
										case 'D':
											puan[currentPlayer][3]--;
											break;
										case 'E':
											puan[currentPlayer][4]--;
											break;
									}

									tekrar =0;
									board[y1][x1] = temp1;
									board[(y2+y1)/2][(x1+x2)/2] = temp2;
									board[y2][x2] = ' ';
									undohak2--;
									system("cls");
            						printf("1.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n2.OYUNCU-> A:%d B:%d C:%d D:%d E:%d   SKOR: %d\n\n\n\n",puan[0][0],puan[0][1],puan[0][2],puan[0][3],puan[0][4],skorhesap(puan,0),puan[1][0],puan[1][1],puan[1][2],puan[1][3],puan[1][4],skorhesap(puan,1));
            						printmatrix(board,N);
            						printf("\n\nContinue(ENTER)\nREDO(1)\nQuit(Esc)");
            						secenek = getch();
            						//cikarsak kaydediyor ve ya undo dersek islemleri tekrar geri aliyor
            						if(secenek == 27){
            							writefile(board,puan,currentPlayer,N,undohak1,undohak2);
            							donus = 1;
									}else if(secenek == '1'){
										switch(temp2){
											case 'A':
												puan[currentPlayer][0]++;
												break;
											case 'B':
												puan[currentPlayer][1]++;
												break;
											case 'C':
												puan[currentPlayer][2]++;
												break;
											case 'D':
												puan[currentPlayer][3]++;
												break;
											case 'E':
												puan[currentPlayer][4]++;
												break;
										}
										//tekrar oyun tahtasini duzenliyor	
										board[(y2+y1)/2][(x1+x2)/2] = ' ';
										board[y2][x2] = board[y1][x1];
										board[y1][x1] = ' ';


									}
								}

							}

						}
					}
					

				}while(flag == 0 && kontrol == 0 && donus == 0);
            	
            	
            	
            	printf("\n");
            	system("PAUSE");
        		
        		//oyun tahtasini bosaltiyor
        		for(i=0;i<N;i++){
        			for(j=0;j<N;j++){
        				board[i][j] = ' ';
					}
				}
        		
        		
 	      		break;
      	    default:
      			printf("Gecersiz secim.\n");
      			system("PAUSE");
   		}
   		system("cls");
	}while(n != 0);
	
}
