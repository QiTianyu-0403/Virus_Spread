#include<iostream>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<time.h>
#include<cmath> 
#include<stdio.h> 
#include<unordered_map>
#include<vector>
#include<algorithm> 
using namespace std;

#define LL long long
#define fgx cerr<<"--------------"<<endl;
#define dgx cerr<<"=============="<<endl;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}
const int MAXN = 2000010;
const int INF = 2147483600;
double SpreadDelta = 3.6/1000.0;//������Ⱦ���� ����1��-1�˴�Ⱦ��
double SDT2 = 3.6/700.0;//������Ⱦ���ʣ���1��-1�˴�Ⱦ�� 
const int LEN = 1001;//��ͼ���� 
const int BS = LEN/2+1;
const int Sq = LEN/2;
int Sum = 100000; //������ 
int Day=0; int Hv = 10;
int BED = 2000; //������ 
double MED=0;//��ҩ�з����� 
void gotoxy(int x,int y) { COORD pos; pos.X=2*x; pos.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); }
void color(int a){ SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a); return ;}
int Go[9]; int dis[9][2]={{0,1},{1,0},{0,-1},{-1,0}};
int GANRAN,GANRAN_now,OUTT,DEAD_now,ZHIYU;
unordered_map<LL,int> mp[25];
vector<int> Road[LEN*LEN*5];
int IDall,all=0; int FADay=0;
inline void Clear(){
	for(int i=1;i<=IDall;i++) Road[i].clear();
	for(int i=0;i<25;i++) mp[i].clear(); IDall=25; GANRAN=0,GANRAN_now=0,OUTT=0,DEAD_now=0;
} bool flag=0;
int GANRANlast;
inline void Change(){//ÿ����ĸ������ 
	if(!FADay) return ;
	SpreadDelta = 3.6/(1000.0*max(log2(FADay)/log2(1.1),1.0)-1000*((rand()%10)/100.0));
	SDT2 = 3.6/(700.0*max(log2(FADay)/log2(1.1),1.0)-700*((rand()%10)/100.0)); MED=min(pow(1.15,FADay-10),7.1);
}
struct data{ int x,y,Starve,disc,no,yes,die,hel,dec; bool last,vis; }ps[MAXN+1];
inline int opr(){ return (rand()&1)?-1:1; }
inline void Infect(int i){//i���²� 
	ps[i].no=2+rand()%5; ++GANRAN;
	ps[i].no=ps[i].no+rand()%10;
	ps[i].disc=1; return ;
}
int ALL=0;

const double Pi=acos(-1.0);
const double e =   2.718281828459 ;
const double a1 = 0.06;//��̬�ֲ�������aԽ�����ԽС���Ƽ�0.03~0.1 
const double a2 = 0.06;
const double b1 = 0;
const double b2 = 0;
const double p=0.0;
const double del=100.0;

inline void NewPerson(int i,int x,int y){ ps[i].Starve=0; ps[i].x=x; ps[i].y=y; }
inline void Hospital(int i,bool nw){ //ҽԺ����ģ�� 
	if(nw){
		flag=1; if(!ps[i].vis) ++ALL,ps[i].vis=1;
		if(!BED) return ;
		ps[i].disc=2;
		ps[i].yes=16+(opr()*(rand()%6));
		if((int)(MED)) ps[i].yes-=rand()%(int)(MED*2); 
		ps[i].yes=max(ps[i].yes,rand()%3+3);
		ps[i].die=((rand()%200)<(7.2-MED));
		//�����ڳ��Ⱥ������ʶ���ҩ���о������й� 
		--BED;
	} --ps[i].yes;
	if(!ps[i].yes){
		if(!ps[i].die) ps[i].no=0,ps[i].disc=0,ps[i].hel=1,ps[i].Starve=Day+1,ps[i].vis=0;//��Ժ 
		++BED; return ;
	} return ;
}
const LL Mod = 998244353LL;
inline LL Hash(LL x,LL y,LL d){
	return (x*131LL%Mod*131LL%Mod+y*131LL%Mod+d)%Mod;
}
inline int disCenter(int x,int y){ return abs(x)+abs(y); }
bool Gx[MAXN+1];
inline double GetPi(double x,double y){//�˿ڷֲ�
	x=x/del; y=y/del;
	double P1=1.0/(2*Pi*a1*a2*sqrt(1-p*p));
	double P2=(-1.0/(2.0*(1-p*p)))*((x-b1)/a1*(x-b1)/a1+(y-b2)/a2*(y-b2)/a2-2*p*(x-b1)/a1*(y-b2)/a2);
	//cout<<x<<" "<<y<<":"<<P1<<" "<<P2<<" "<<P1*pow(e,P2)<<endl;
	return (double)(P1*pow(e,P2)); 
	/*
	if(k>LEN/4) return rand()%2;
	else if(k>LEN/8&&k<=LEN/4) return rand()%10+2;
	else return rand()%40+42;*/
}
int Cen=0;
inline void Push(int id,int i,int tim,bool v){ if(!mp[tim][id]) mp[tim][id]=++IDall; Road[mp[tim][id]].push_back(i); Gx[mp[tim][id]]=v; }
inline void GoOutside(int i){//ģ����к��� 
	bool To=(rand()%100>min(GetPi(ps[i].x,ps[i].y)*4,(double)80));
	//��������Ŀ�� 
	ps[i].Starve=Day+rand()%max(Hv,1)+1;
	ps[i].dec=Day;//�����һ�������ʲôʱ����ѧ����Ϊ(x+1)/2�� 
	++OUTT;
	if(To){//�������� 
		int leng=rand()%20+3;
		int x=ps[i].x,y=ps[i].y,tim=rand()%11+8;
		if(rand()%100<60) if(ps[i].disc)x=opr()*rand()%Sq,y=opr()*rand()%Sq;//����->���� 
		else x=opr()*rand()%50,y=opr()*rand()%50;//����->���� 
		while(leng){
			int d=rand()%4;
			Push(Hash(x+BS,y+BS,d),i,tim,disCenter(x,y)<LEN/8);
			x+=dis[d][0],y+=dis[d][1]; 
			--leng;
		} return ;
	} else{
		++Cen;
		int x=ps[i].x,y=ps[i].y,tim=rand()%11+8;
		while(x!=0||y!=0){//������ 
			int nd=0;
			for(int j=0;j<4;j++){
				int tx=x+dis[j][0],ty=y+dis[j][1];
				if(disCenter(tx,ty)<disCenter(x,y)){
					Go[++nd]=j;
				}
			} nd=rand()%nd+1;
			int d=Go[nd];
			Push(Hash(x+BS,y+BS,d),i,tim,disCenter(x,y)<LEN/8);
			x+=dis[d][0],y+=dis[d][1]; 
		} 
		Road[tim].push_back(i);
	}
}
inline void Spread(){//������һ��Ĵ��� 
	for(int i=1;i<=IDall;i++){
		int GET=0;
		for(int j=0,sz=Road[i].size();j<sz;j++){
			int id=Road[i][j];
			if(ps[id].disc) ++GET;
		}
		double no1=(1.0-(Gx[i]?SDT2:SpreadDelta)),noall=1.0; int C=GET; GET=min(GET,rand()%4+1);
		while(GET--) noall=noall*no1; noall=noall*10000;
		int Inc=0; 
		for(int j=0,sz=Road[i].size();j<sz;j++){
			if(rand()%10000+1<=noall||(ps[Road[i][j]].hel&&rand()%10<9)) continue;
			else Infect(Road[i][j]),++Inc;
		} Gx[i]=0;
	} return ;
}
inline void Move(int i){//ģ��i�ŵ���Ϊ 
	if(ps[i].die&&!ps[i].yes) return ;
	if(ps[i].disc==2) {Hospital(i,0); return ;} 
	if(ps[i].disc==1) {ps[i].no--; ps[i].no=max(ps[i].no,0);if(ps[i].no<=0) { Hospital(i,1); if(ps[i].yes) return ; }}
	if(!ps[i].vis&&ps[i].Starve<=Day) { GoOutside(i); }
}
LL Prs; vector<pair<int,int> > vec[2010];
double b[MAXN+1]; LL L[MAXN+1],R[MAXN+1];
struct DPs{ pair<int,int> a; double b;  }vc[MAXN+1];
bool cmp(DPs a,DPs b){
	return a.b<b.b;
}
inline void Init(){//��ͼ 
	LL Sum2=Sum; double sumP=0;
	int top=0;
	for(int i=-Sq;i<=Sq;i++){
		for(int j=-Sq;j<=Sq;j++){
			int bel=max(abs(i),abs(j));
			double T=GetPi(i,j);  sumP+=T;
			vc[++top].a=make_pair(i,j); vc[top].b=T;
		}
	}
	sort(vc+1,vc+top+1,cmp);
	for(int i=1;i<=top;i++){
		Prs=vc[i].b/sumP*Sum;
		if(!Prs) sumP-=vc[i].b; Sum2-=Prs;
		while(Prs--){
			++all; NewPerson(all,vc[i].a.first,vc[i].a.second);
		} 
	}
	if(Sum2) {
		while(Sum2--){
			++all; NewPerson(all,opr()*(rand()%50),opr()*(rand()%50));
		}
	} random_shuffle(ps+1,ps+all+1);
	return ;
}
inline int Col(int k){
	if(!k) return 15;
	if(k<=5) return 7;
	if(k<=10) return 8;
	if(k<=20) return 12;
	if(k<=50) return 4;
	return 13;
}
inline void prin(int n){
	color(Col(n)); 
	cout<<"��";
}
LL s[1110][1110];
inline int GETSUM(int x1,int y1,int x2,int y2){
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
int stv[MAXN+1];
bool OPEN; 
inline void Print(){//���ģ�� 
	for(int i=-Sq;i<=Sq;i++)
		for(int j=-Sq;j<=Sq;j++) s[BS+i][BS+j]=0;
	for(int i=0;i<=200;i++) stv[i]=0;
	for(int i=1;i<=all;i++){
		if(ps[i].disc&&(ps[i].disc!=2||ps[i].yes||!ps[i].die)) ++GANRAN_now;
		if(ps[i].disc==2&&ps[i].die&&!ps[i].yes) ++DEAD_now;
		if(ps[i].disc&&!(ps[i].disc==2&&ps[i].die&&!ps[i].yes)) s[BS+ps[i].y][BS+ps[i].x]++;
		if(ps[i].hel) ++ZHIYU,ps[i].hel=0;
		if(ps[i].disc) ps[i].last=1;
		stv[ps[i].Starve]++;
	}
	for(int i=-Sq;i<=Sq;i++)
		for(int j=-Sq;j<=Sq;j++) s[BS+i][BS+j]+=s[BS+i][BS+j-1]+s[BS+i-1][BS+j]-s[BS+i-1][BS+j-1];
	printf("���ڸ�Ⱦ����״̬��������%d\n",GANRAN_now);
	printf("Ŀǰδ��Ⱦ������������%d\n",Sum-GANRAN_now-DEAD_now);
	printf("������������%d\n",DEAD_now);
	printf("������������%d\n",ZHIYU);
	printf("ȷ����������%d\n",ALL);
	printf("ҽԺ��λʣ�ࣺ%d\n",BED);
	printf("���ճ���������%d\n",OUTT);
	printf("������Ⱦ������%d\n",GANRAN);
	printf("ģ���Ⱦ��ͼ��\n");
	int LENX=20;
	for(int i=-10;i<=10;i++){
		for(int j=-10;j<=10;j++){
			prin(GETSUM(i*2+1+BS,j*2+1+BS,(i+1)*2+BS,(j+1)*2+BS));
		} printf("\n");
	}
	if(OPEN){
		printf("ģ���Ⱦ��ͼ���ܣ���\n");
		for(int i=10;i<=LEN/LENX-10;i++){
		for(int j=10;j<=LEN/LENX-10;j++){
				prin(GETSUM((i-1)*LENX+1,(j-1)*LENX+1,i*LENX,j*LENX)/2);
			} printf("\n");
		}
	}
	if(!GANRAN_now) exit(0); GANRANlast=ALL;
}
bool pau;
double sec;

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int c= (int)time(0);
	puts("��������ָ�Ⱦ������ʱ�䱣��1��������������£��������򼴿�");
	printf("�Ƿ���������ܵ�ͼ(��(0)/��(1))��\n");
	cin>>OPEN;
	printf("�Ƿ���Ҫ�ֶ�����ÿ�����(��(0)/��(1))��\n");
	cin>>pau; 
	if(!pau){
		printf("������ÿ��������Ҫͣ����ʱ��(s)\n");
		cin>>sec;
	}
	bool chg=0;
	printf("�Ƿ���Ҫ�ı�Ĭ�ϲ���?(��(0)/��(1))\n"); cin>>chg; 
	if(chg){
		puts("����ĳЩ���Ϸ��������ܻ�ʹ��������������");
		printf("������ҽԺ������(�Ƽ�2000)\n");
		cin>>BED; 
		printf("������Ⱥ��Σ����ʶϵ��(5~50)\n");
		cin>>Hv; 
		printf("�������������(50000~500000���Ƽ�100000������Խ��������ʱ��Խ��)\n");
		cin>>Sum; 
	}
	srand(c);
	Init(); int sor;
	for(int i=1;i<=all;i++){
		if(disCenter(ps[i].x,ps[i].y)<2&&disCenter(ps[i].x,ps[i].y)){
			sor=i; break;
		}
	}
	Infect(sor);
	while(1){
		Clear(); Cen=0;
		if(flag)++FADay; ++Day;
		Change();
		cout<<ps[sor].Starve<<endl;
		for(int i=1;i<=all;i++) Move(i);
		Spread();
		system("cls");
		printf("�����ۼ���в%d��\n",Day-1);
		Print();
		if(FADay){
			for(int i=1;i<=all;i++){
				ps[i].Starve=Day+rand()%max(Hv,1)+1;
			}
		}
		if(pau) system("pause");
		else Sleep(sec*1000);
	}
	return 0;
}
