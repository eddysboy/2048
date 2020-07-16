#include <bits/stdc++.h>
#include <conio.h>
#define LL long long
#define pb push_back
#define mp make_pair
#define INF 0x3f3f3f3f
#define Inf 1000000000000000000LL
#define F first
#define S second
using namespace std;
typedef pair<int,int>pii;
int grid[4][4];
bool chk[4][4];
int score;
bool game_over;
bool moved;
int rnd;
int next_rand(){return rnd=rand();}
void rndgrid(){
	while(1){
		int x=next_rand()%4,y=next_rand()%4;
		if(grid[x][y])continue;
		else{
			int tp=next_rand()%10;
			int q=(tp==0?2:1);
			grid[x][y]=(q<<1);
			break;
		}
	}
}
void update(){
	system("cls");
	printf("\e[1;34m");
	printf(" ┌──┐  ┌──┐        ┌──┐ \n");
	printf("    │  │  │  │  │  │  │ \n");
	printf(" ┌──┘  │  │  └──┤  ├──┤ \n");
	printf(" │     │  │     │  │  │ \n");
	printf(" └──┘  └──┘     │  └──┘ \n");
	printf("                         \e[0m--by Eddysboy\n");
	printf("\e[35mR 开始   E 退出   F 从存档载入\n");
	printf("ASDW 或←↑↓→ 移动方块\n");
	cout<<setw(20)<<score<<endl;
	cout<<endl;
	printf("\e[37m");
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			printf("\e[1;37m");
			if(grid[i][j]==0)printf("  -  ");
			if(grid[i][j]==2)printf("\e[40m  2  ");
			if(grid[i][j]==4)printf("\e[41m  4  ");
			if(grid[i][j]==8)printf("\e[42m  8  ");
			if(grid[i][j]==16)printf("\e[43m 16  ");
			if(grid[i][j]==32)printf("\e[44m 32  ");
			if(grid[i][j]==64)printf("\e[45m 64  ");
			if(grid[i][j]==128)printf("\e[33;46m 128 ");
			if(grid[i][j]==256)printf("\e[33;47m 256 ");
			if(grid[i][j]==512)printf("\e[33m 512 ");
			if(grid[i][j]==1024)printf("\e[33m 1024");
			if(grid[i][j]==2048)printf("\e[33m 2048");
			if(grid[i][j]==4096)printf("\e[33m 4096");
			if(grid[i][j]==8192)printf("\e[33m 8192");
			printf("\e[0m");
		}
		puts("");
	}
	puts("");
}
void init_with_save(){
	FILE *fp=fopen("save.dat","r");
	if(fp==NULL){
		puts("存档文件已损坏！");
		fflush(fp);
		return;
	}
	if(fscanf(fp,"%d",&score)==EOF){
		puts("存档文件已损坏！");
		fflush(fp);
		return;
	}
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(fscanf(fp,"%d",&grid[i][j])==EOF){
				puts("存档文件已损坏！");
				fflush(fp);
				return;
			}
	fflush(fp);
	// freopen("/dev/tty","r",stdin);
	puts("导入成功！");
	update();
}
void init_grid(){
	score=0;
	srand(time(NULL));
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			grid[i][j]=0;
	rndgrid(),rndgrid();
}
void move_up(){
	while(1){
		bool flg=1;
		for(int i=1;i<4;i++)
			for(int j=0;j<4;j++)
				if(!grid[i-1][j]&&grid[i][j]){moved=1,flg=0;break;}
		if(flg)return;
		for(int i=0;i<3;i++)
			for(int j=0;j<4;j++)
				if(!grid[i][j]&&grid[i+1][j])
					grid[i][j]=grid[i+1][j],grid[i+1][j]=0;
	}
}
void move_down(){
	while(1){
		bool flg=1;
		for(int i=0;i<3;i++)
			for(int j=0;j<4;j++)
				if(!grid[i+1][j]&&grid[i][j]){moved=1,flg=0;break;}
		if(flg)break;
		for(int i=3;i>=1;i--)
			for(int j=0;j<4;j++)
				if(!grid[i][j]&&grid[i-1][j])
					grid[i][j]=grid[i-1][j],grid[i-1][j]=0;
	}
}
void move_left(){
	while(1){
		bool flg=1;
		for(int i=0;i<4;i++)
			for(int j=1;j<4;j++)
				if(!grid[i][j-1]&&grid[i][j]){moved=1,flg=0;break;}
		if(flg)return;
		for(int i=0;i<4;i++)
			for(int j=0;j<3;j++)
				if(!grid[i][j]&&grid[i][j+1])
					grid[i][j]=grid[i][j+1],grid[i][j+1]=0;
	}
}
void move_right(){
	while(1){
		bool flg=1;
		for(int i=0;i<4;i++)
			for(int j=0;j<3;j++)
				if(!grid[i][j+1]&&grid[i][j]){moved=1,flg=0;break;}
		if(flg)break;
		for(int i=0;i<4;i++)
			for(int j=3;j>=1;j--)
				if(!grid[i][j]&&grid[i][j-1])
					grid[i][j]=grid[i][j-1],grid[i][j-1]=0;
	}
}
void grid_up(){
	move_up();
	for(int i=0;i<3;i++)
		for(int j=0;j<4;j++){
			if(grid[i][j]&&grid[i][j]==grid[i+1][j]&&!chk[i][j]){
				grid[i][j]+=grid[i+1][j];
				grid[i+1][j]=0;
				score+=grid[i][j];
				chk[i][j]=1,moved=1;
			}
		}
	move_up();
}
void grid_down(){
	move_down();
	for(int i=3;i>=1;i--)
		for(int j=0;j<4;j++){
			if(grid[i][j]&&grid[i][j]==grid[i-1][j]&&!chk[i][j]){
				grid[i][j]+=grid[i-1][j];
				grid[i-1][j]=0;
				score+=grid[i][j];
				chk[i][j]=1,moved=1;
			}
		}
	move_down();
}
void grid_left(){
	move_left();
	for(int i=0;i<4;i++)
		for(int j=0;j<3;j++){
			if(grid[i][j]&&grid[i][j]==grid[i][j+1]&&!chk[i][j]){
				grid[i][j]+=grid[i][j+1];
				grid[i][j+1]=0;
				score+=grid[i][j];
				chk[i][j]=1,moved=1;
			}
		}
	move_left();
}
void grid_right(){
	move_right();
	for(int i=0;i<4;i++)
		for(int j=3;j>=1;j--){
			if(grid[i][j]&&grid[i][j]==grid[i][j-1]&&!chk[i][j]){
				grid[i][j]+=grid[i][j-1];
				grid[i][j-1]=0;
				score+=grid[i][j];
				chk[i][j]=1,moved=1;
			}
		}
	move_right();
}
void Exit(){
	puts("");
	freopen("save.dat","w",stdout);
	printf("%d\n",score);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			cout<<grid[i][j]<<' ';
		puts("");
	}
	exit(0);
}
void copy(int tp[4][4],int grid[4][4]){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			tp[i][j]=grid[i][j];
}
bool check(){
	int tp[4][4],pscore=score;
	copy(tp,grid);
	grid_up();
	copy(grid,tp);
	grid_down();
	copy(grid,tp);
	grid_left();
	copy(grid,tp);
	grid_right();
	copy(grid,tp);
	score=pscore;
	return moved;
}
int main(){
	rndgrid(),rndgrid();
	// init_with_save();
	Beg:;
	update();
	while(check()){
		char ch=getch();
//		cout<<int(ch)<<endl;
		if(ch==-32){
			ch=getch();
		}else ch=tolower(ch);
		memset(chk,0,sizeof chk);
		moved=0;
		if(ch=='w'||ch==72)grid_up();
		if(ch=='s'||ch==80)grid_down();
		if(ch=='a'||ch==75)grid_left();
		if(ch=='d'||ch==77)grid_right();
		if(ch=='r'){
			init_grid();
			goto Beg;
		}
		if(ch=='e')Exit();
		if(ch=='f'){
			init_with_save();
			continue;
		}
		if(moved)rndgrid();
		update();
	}
	puts("Game Over!");
	puts("print R to restart");
	char ch;
	cin>>ch;
	ch=tolower(ch);
	if(ch=='r'){
		init_grid();
		goto Beg;
	}
	Exit();
	return 0;
}
