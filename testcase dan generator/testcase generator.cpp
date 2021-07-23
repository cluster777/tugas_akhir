#include<bits/stdc++.h>
using namespace std;
string itos(int i) // convert int to string
{
    stringstream s;
    s << i;
    return s.str();
}

int randomint(int max,int min){
	return rand()%(max+1-min)+min;
}

string randomstring(int max,bool spchar){
	int top=rand()%max+1;
	string rnd="";
	for(int i=0;i<top;i++){
		rnd+=(char)(rand()%(26)+97);
	}
	return rnd;
}
string randomchoose(string * list){
	return list[randomint(list->size()-1,0)];
}
int main(){
	string fname;
	string plist[6]={"rook","bishop","pawn","king","queen","knight"};
	srand(time(0));
	ofstream outfile;
	
	//make 2 output file change the max i to make less or more
	for(int i=1;i<3;i++){
		fname="in"+itos(i)+".txt";
		outfile.open(fname.c_str());
		//the variable l for location p for piece max 64 min 1
		int n=10,l=60,p=60;
		outfile<<n<<endl;
		
		for(int j=0;j<n;j++){
			outfile<<l<<" "<<p<<endl;
			for(int k=0;k<l;k++){
				//the position and name of piece if want only certain piece in board change random choose
				outfile<<randomint(8,1)<<" "<<randomint(8,1)<<" "<<randomchoose(plist)<<endl;
			}
			for(int k=0;k<l;k++){
				//the target location on board trully random trust me
				outfile<<randomint(8,1)<<" "<<randomint(8,1)<<endl;
			}
		}
		outfile.close();	
	}
}
