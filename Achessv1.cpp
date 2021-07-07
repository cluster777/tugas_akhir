#include<bits/stdc++.h>
#define mp make_pair
using namespace std;


bool possible(char type, int col,int row,int colt,int rowt){
	if(type=='P'){
		if(col==colt)return true;
		else return false;
	}
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
	if(x+2<15&&y+1<15&& board[x+2][y+1]>counter){
			board[x+2][y+1]=counter;
			travel(x+2,y+1,counter);
		}
		if(x+2<15&&y-1>=0&& board[x+2][y-1]>counter){
			board[x+2][y-1]=counter;
			travel(x+2,y-1,counter);
		}
		if(x-2>=0&&y+1<15&& board[x-2][y+1]>counter){
			board[x-2][y+1]=counter;
			travel(x-2,y+1,counter);
		}
		if(x-2>=0&&y-1>=0&& board[x-2][y-1]>counter){
			board[x-2][y-1]=counter;
			travel(x-2,y-1,counter);
		}
		
		if(x+1<15&&y+2<15&& board[x+1][y+2]>counter){
			board[x+1][y+2]=counter;
			travel(x+1,y+2,counter);
		}
		if(x-1>=0&&y+2<15&& board[x-1][y+2]>counter){
			board[x-1][y+2]=counter;
			travel(x-1,y+2,counter);
		}
		if(x+1<15&&y-2>=0&& board[x+1][y-2]>counter){
			board[x+1][y-2]=counter;
			travel(x+1,y-2,counter);
		}
		if(x-1>=0&&y-2>=0&& board[x-1][y-2]>counter){
			board[x-1][y-2]=counter;
			travel(x-1,y-2,counter);
		}
}

int main(){
	string test="40c3";
	cout<<stoi(test,nullptr,16);
	int p,l,t;
	vector<pair<pair<int,int>,char> >piece;
	vector<pair<int,int> >location;
	//ini buat daftar jarak enaknya vector of vector jarak[piece][tujuan]
	int jarak[64][64];
	
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		printf("Case %d: ",i);
		scanf("%d %d",p,l);
		while(p--){
			int x,y;
			char type;
			scanf("%d %d %c",&x,&y,&type);
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
			if(piece[j].second=='k'){//king
				for(int k=0;k<l;k++)
					if(location[k].first-piece[j].first.first>location[k].second-piece[j].first.second)jarak[j][k]=abs(location[k].first-piece[j].first.first);
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
				board[piece[j].first.first][piece[j].first.second]=0;
				travel(piece[j].first.first,piece[j].first.second,0);
				for(int k=0;k<l;k++){
					jarak[j][k]=board[location[k].first][location[k].second];
				}
				
			}
			if(piece[j].second=='r'){//rook
				for(int k=0;k<l;k++)
					if(location[k].first==piece[j].first.first||location[k].second==piece[j].first.second)jarak[j][k]=1;
					else jarak[j][k]=2;
			}
			if(piece[j].second=='b'){//bishop
				for(int k=0;k<l;k++)
					if(possible('b',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second))
						if((abs(location[k].first-piece[j].first.first)==abs(location[k].second-piece[j].first.second)))jarak[j][k]=1;
						else jarak[j][k]=2;
					else jarak[j][k]=1000000;
			}
			if(piece[j].second=='p'){//pawn
				for(int k=0;k<l;k++)
					if(possible('p',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second))
						jarak[j][k]=abs(location[k].first-piece[j].first.first);
					else jarak[j][k]=1000000;
			}
		}
		//mencari jarak yang terpendek agar sejumlah tempat tertempati cari algo
		
	}
	return 0;
}

