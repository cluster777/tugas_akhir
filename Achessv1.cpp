#include<bits/stdc++.h>
#define mp make_pair
#define INF 1000000000
using namespace std;


bool possible(char type, int col,int row,int colt,int rowt){
	//pawn only move on 1 collumn
	if(type=='P'){
		if(row==rowt)return true;
		else return false;
	}
	//bishop only move on 1 color (diagonal cannot  
	else if(type=='B'){
		if(abs(col-row)%2==abs(colt-rowt)%2)return true;
		else return false;
	}
	else return true;
}

int board[8][8];

void travel(int x,int y,int counter){

	counter++;
	if(counter==7)return;
	if(x+2<7&&y+1<8&& board[x+2][y+1]>counter){
			board[x+2][y+1]=counter;
			travel(x+2,y+1,counter);
		}
		if(x+2<8&&y-1>=0&& board[x+2][y-1]>counter){
			board[x+2][y-1]=counter;
			travel(x+2,y-1,counter);
		}
		if(x-2>=0&&y+1<8&& board[x-2][y+1]>counter){
			board[x-2][y+1]=counter;
			travel(x-2,y+1,counter);
		}
		if(x-2>=0&&y-1>=0&& board[x-2][y-1]>counter){
			board[x-2][y-1]=counter;
			travel(x-2,y-1,counter);
		}
		
		if(x+1<8&&y+2<8&& board[x+1][y+2]>counter){
			board[x+1][y+2]=counter;
			travel(x+1,y+2,counter);
		}
		if(x-1>=0&&y+2<8&& board[x-1][y+2]>counter){
			board[x-1][y+2]=counter;
			travel(x-1,y+2,counter);
		}
		if(x+1<8&&y-2>=0&& board[x+1][y-2]>counter){
			board[x+1][y-2]=counter;
			travel(x+1,y-2,counter);
		}
		if(x-1>=0&&y-2>=0&& board[x-1][y-2]>counter){
			board[x-1][y-2]=counter;
			travel(x-1,y-2,counter);
		}
}

int main(){
	int p,l,t;
	vector<pair<pair<int,int>,char> >piece;
	vector<pair<int,int> >location;
	//ini buat daftar jarak enaknya vector of vector jarak[piece][tujuan]
	int jarak[64][64];
	
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		piece.clear();
		location.clear();
		printf("Case %d: ",i);
		scanf("%d %d",&p,&l);
		while(p--){
			int x,y;
			char type;
			scanf("%d %d %c",&x,&y,&type);
			if(type=='k')scanf("%c",&type);
			piece.push_back(mp(mp(x,y),type));
			while(type!='\n')scanf("%c",&type);
		}
		for(int k=0;k<l;k++){
			int x,y;
			scanf("%d %d",&x,&y);
			location.push_back(mp(x,y));
		}
		//mencari jarak antar piece dan tujuan
		for(int j=0;j<piece.size();j++){
			if(piece[j].second=='i'){//king
				for(int k=0;k<l;k++)
					if(location[k].first-piece[j].first.first<location[k].second-piece[j].first.second)jarak[j][k]=abs(location[k].first-piece[j].first.first);
					else jarak[j][k]=abs(location[k].second-piece[j].first.second);
			}
			if(piece[j].second=='q'){//queen
				for(int k=0;k<l;k++)
					if(location[k].first==piece[j].first.first||location[k].second==piece[j].first.second||(possible('b',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second)&&(abs(location[k].first-piece[j].first.first)==abs(location[k].second-piece[j].first.second))))jarak[j][k]=1;
					//bishop+rook
					else jarak[j][k]=2;
			}
			if(piece[j].second=='n'){//knight
				//pakai plot fill cari semua langsung
				for(int m=0;m<8;m++){
					for(int n=0;n<8;n++)board[m][n]=INF;
				}
				board[piece[j].first.first][piece[j].first.second]=0;
				travel(piece[j].first.first-1,piece[j].first.second-1,0);
				for(int k=0;k<l;k++){
					jarak[j][k]=board[location[k].first-1][location[k].second-1];
				}
				
			}
			if(piece[j].second=='r'){//rook
				for(int k=0;k<l;k++)
					if(location[k].first==piece[j].first.first||location[k].second==piece[j].first.second)jarak[j][k]=1;
					else jarak[j][k]=2;
			}
			if(piece[j].second=='b'){//bishop
				for(int k=0;k<l;k++)
					if(possible('B',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second))
						if((abs(location[k].first-piece[j].first.first)==abs(location[k].second-piece[j].first.second)))jarak[j][k]=1;
						else jarak[j][k]=2;
					else jarak[j][k]=1000000;
			}
			if(piece[j].second=='p'){//pawn
				for(int k=0;k<l;k++)
					if(possible('P',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second))
						jarak[j][k]=abs(location[k].first-piece[j].first.first);
					else jarak[j][k]=1000000;
			}
		}
		printf("\n");
		
		//mencari jarak yang terpendek agar sejumlah tempat tertempati cari algo
		
		printf("\n");
		for(int j=0;j<piece.size();j++){
			for(int k=0;k<l;k++){
				printf("%d ",jarak[j][k]);
				
			}
			printf("\n");
		}
	}
	return 0;
}

