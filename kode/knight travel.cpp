#include<bits/stdc++.h>
using namespace std;

int board[15][15];


void travel(int x,int y,int counter){
	counter++;
	if(counter==70)return;
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
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			board[i][j]=1000;
		}
	}
	board[0][0]=0;


	travel(0,0,0);
	
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
	
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
}
