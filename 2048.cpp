#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
IMAGE background;
IMAGE ch;
IMAGE img[11];
IMAGE bk[4][4];
int map[4][4]={0};
char point[5];
int pt,none,re=0;

void prepare(){
	int m,n;
	initgraph(400,500);
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	setfont(25,0,"Britannic Bold");
	loadimage(&background,"resource/background.jpg");
	loadimage(&img[0],"resource/2.jpg");
	loadimage(&img[1],"resource/4.jpg");
	loadimage(&img[2],"resource/8.jpg");
	loadimage(&img[3],"resource/16.jpg");
	loadimage(&img[4],"resource/32.jpg");
	loadimage(&img[5],"resource/64.jpg");
	loadimage(&img[6],"resource/128.jpg");
	loadimage(&img[7],"resource/256.jpg");
	loadimage(&img[8],"resource/512.jpg");
	loadimage(&img[9],"resource/1024.jpg");
	loadimage(&img[10],"resource/2048.jpg");
	loadimage(&img[11],"resource/4096.jpg");
	putimage(0,0,&background);
	for(m=0;m<4;m++){
		for(n=0;n<4;n++){
			getimage(&bk[m][n],5+100*m,103+100*n,100+100*m,198+100*n);
		}
	}
	getimage(&ch,84,20,124,40);
}

void start(){
	int m,n;
	pt=0;none=16;
	point[0]='0';
	point[1]='0';
	point[2]='0';
	point[3]='0';
	point[4]='0';
	for(m=0;m<4;m++){
		for(n=0;n<4;n++){
			map[m][n]=0;
		}
	}
}

void save_score(){
	FILE *fp;
	fp=fopen("res/score","a+");
	fprintf(fp,"%d\n",pt);
}

void save(){
	FILE *fp;
	int m,n;
	fp=fopen("res/saved.sav","w+");
	for(m=0;m<4;m++){
		for(n=0;n<4;n++){
			fprintf(fp,"%d ",map[m][n]);
		}
	}
	fprintf(fp,"%d",pt);
}

void load(){
	FILE *fp;
	int m,n;
	fp=fopen("res/saved.sav","r");
	for(m=0;m<4;m++){
		for(n=0;n<4;n++){
			fscanf(fp,"%d ",&map[m][n]);
		}
	}
	fscanf(fp,"%d",&pt);
}

void print(){
	int m,n;
	for(m=0;m<4;m++){
		for(n=0;n<4;n++){
			switch(map[m][n]){
			case 0:putimage(5+100*m,103+100*n,&bk[m][n]);break;
			case 2:putimage(5+100*m,103+100*n,&img[0]);break;
			case 4:putimage(5+100*m,103+100*n,&img[1]);break;
			case 8:putimage(5+100*m,103+100*n,&img[2]);break;
			case 16:putimage(5+100*m,103+100*n,&img[3]);break;
			case 32:putimage(5+100*m,103+100*n,&img[4]);break;
			case 64:putimage(5+100*m,103+100*n,&img[5]);break;
			case 128:putimage(5+100*m,103+100*n,&img[6]);break;
			case 256:putimage(5+100*m,103+100*n,&img[7]);break;
			case 512:putimage(5+100*m,103+100*n,&img[8]);break;
			case 1024:putimage(5+100*m,103+100*n,&img[9]);break;
			case 2048:putimage(5+100*m,103+100*n,&img[10]);break;
			case 4096:putimage(5+100*m,103+100*n,&img[11]);break;
			}
		}
	}
	sprintf(point,"%d",pt);
	putimage(84,20,&ch);
	outtextxy(84,20,point);
}

int gotch(){
	switch(getch()){
		case 224:
		switch(getch()){
			case 72:return 1;
			case 80:return 2;
			case 75:return 3;
			case 77:return 4;
		}
		case 119: return 11;
		case 115: return 12;
		case 97: return 13;
		case 100: return 14;
		case 49:return 5;//1
		case 50:return 6;//2
		case 51:return 7;//3
		case 106:return 15;//j
		case 107:return 16; //k
		case 108:return 17;//l
		case 27:return -1;//ESC
		case 122:return 21;//z
		case 120:return 22;//x
		case 99:return 23;//c
	}
}

void makething(){
	int x,y,wrong,num=0;
	srand(time(NULL));
	while(num<(none/8)+1){
		for(wrong=1;wrong;){
			x=rand()%4;y=rand()%4;
			if(map[x][y]==0){
				if(pt<50) map[x][y]=2;
				else if(pt<200) {
					switch(rand()%2){
					case 0:map[x][y]=2;break;
					case 1:map[x][y]=4;break;}
				}
				else if(pt<600) {
					switch(rand()%3){
					case 0:map[x][y]=2;break;
					case 1:map[x][y]=4;break;
					case 2:map[x][y]=8;break;}
				}
				else {
					switch(rand()%4){
					case 0:map[x][y]=2;break;
					case 1:map[x][y]=4;break;
					case 2:map[x][y]=8;break;
					case 3:map[x][y]=16;break;}
				}
			num++;wrong=0;
			}
		}
	}
}


void main_run(){
	int m,n,dx,dy,i;
	switch(gotch()){
	case 1:dx=0;dy=-1;break;
	case 2:dx=0;dy=1;break;
	case 3:dx=-1;dy=0;break;
	case 4:dx=1;dy=0;break;
	case 22:re=2;return;break;
	case 23:re=1;save_score();return;break;
	case -1:save();save_score();exit(-1);break;
	default: main_run();
	}
	i=3;none=0;
	do{
		for(m=0;m<4;m++){
			for(n=0;n<4;n++){
				if(map[m][n]!=0&&m+dx>=0&&m+dx<=3&&n+dy>=0&&n+dy<=3){
					if(map[m+dx][n+dy]==0){
						map[m+dx][n+dy]=map[m][n];map[m][n]=0;
					}
					else if(map[m+dx][n+dy]==map[m][n]){
						map[m+dx][n+dy]=map[m][n]*2;map[m][n]=0;pt+=map[m+dx][n+dy];
					}
					else ;
				}
				else if(map[m][n]==0)	none++;
			}
		}
		i--;
	}while(i);
	if(none==0){
		MessageBox(0,TEXT("你输了(～￣▽￣)～ "),TEXT("2048的游戏通知"),MB_OK);
		re=1;
		save_score();
	}
	none/=3;
}

int main(){
	prepare();
	start();
	while(1){
		if(re==1) {start();re=0;}
		else if(re==2){start();load();re=0;goto res;}
		while(re==0){
			makething();
res:
			print();
			main_run();
		}
	}
	getch();
	return 0;
}
