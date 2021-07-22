// C++ implementation of Hopcroft Karp algorithm for
// maximum matching
#include<bits/stdc++.h>
using namespace std;
#define NIL -10
#define INF INT_MAX
#define mp make_pair
// A class to represent Bipartite graph for Hopcroft
// Karp implementation
class BipGraph
{
	// m and n are number of vertices on left
	// and right sides of Bipartite Graph
	int m, n,matching;

	// adj[u] stores adjacents of left side
	// vertex 'u'. The value of u ranges from 1 to m.
	// 0 is used for dummy vertex
	list<int> *adj;

	// These are basically pointers to arrays needed
	int *pairU, *pairV, *dist, *cost, *forest,*tmpcost;

public:
	BipGraph(int m, int n); // Constructor
	void addEdge(int u, int v, int c); // To add edge

	// Returns true if there is an augmenting path
	bool bfs();

	// Adds augmenting path if there is one beginning
	// with u
	bool dfs(int u);

	// Returns size of maximum matching
	int hopcroftKarp();
	
	// Returns minimum cost matching using hungarian method
	int hungarianMethod();
	int hungarianMethod_v4();
	// Returns minimum cost matching using Auction
	int auction();
	void print_tmpcost_dbg();
	void print_cost_dbg();
	// Returns minimum cost matching using FlowAssign
	int flowAssign();
	int get_last_matching();
	// Create Forest and return true if found augmenting path 
	bool dijkstra();
	
	// Return sum of cost in matching
	int sum();
};
int BipGraph::get_last_matching(){
	return matching;
}
// Returns size of maximum matching
int BipGraph::hopcroftKarp()
{
 
    // Initialize NIL as pair of all vertices
    for (int u=0; u<=m; u++)
        pairU[u] = NIL;
    for (int v=0; v<=n; v++)
        pairV[v] = NIL;
 	for (int i=0;i<=m;i++)
 		dist[i]=0;
    // Initialize result
    int result = 0;
 
    // Keep updating the result while there is an
    // augmenting path.
    while (bfs())
    {
        // Find a free vertex
        for (int u=1; u<=m; u++)
 
            // If current vertex is free and there is
            // an augmenting path from current vertex
            if (pairU[u]==NIL && dfs(u))
                result++;
    }
    return result;
}
 
// Returns true if there is an augmenting path, else returns
// false
bool BipGraph::bfs()
{
    queue<int> Q; //an integer queue
 
    // First layer of vertices (set distance as 0)
    for (int u=1; u<=m; u++)
    {
        // If this is a free vertex, add it to queue
        if (pairU[u]==NIL)
        {
            // u is not matched
            dist[u] = 0;
            Q.push(u);
        }
 
        // Else set distance as infinite so that this vertex
        // is considered next time
        else dist[u] = INF;
    }
 
    // Initialize distance to NIL as infinite
    dist[NIL] = INF;
 
    // Q is going to contain vertices of left side only.
    while (!Q.empty())
    {
        // Dequeue a vertex
        int u = Q.front();
        Q.pop();
 
        // If this node is not NIL and can provide a shorter path to NIL
        if (dist[u] < dist[NIL])
        {
            // Get all adjacent vertices of the dequeued vertex u
            list<int>::iterator i;
            for (i=adj[u].begin(); i!=adj[u].end(); ++i)
            {
                int v = *i;
 
                // If pair of v is not considered so far
                // (v, pairV[V]) is not yet explored edge.
                if (dist[pairV[v]] == INF)
                {
                    // Consider the pair and add it to queue
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }
 
    // If we could come back to NIL using alternating path of distinct
    // vertices then there is an augmenting path
    return (dist[NIL] != INF);
}
 
// Returns true if there is an augmenting path beginning with free vertex u
bool BipGraph::dfs(int u)
{
    if (u != NIL)
    {
        list<int>::iterator i;
        for (i=adj[u].begin(); i!=adj[u].end(); ++i)
        {
            // Adjacent to u
            int v = *i;
 
            // Follow the distances set by BFS
            if (dist[pairV[v]] == dist[u]+1)
            {
                // If dfs for pair of v also returns
                // true
                if (dfs(pairV[v]) == true)
                {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
 
        // If there is no augmenting path beginning with u.
        dist[u] = INF;
        return false;
    }
    return true;
}
 
void BipGraph::print_tmpcost_dbg(){
	for(int i=0;i<m*n;i++){
		if(i%n==0 && i>0)printf("\n");
		printf("%d ",tmpcost[i]);
		
	}
	printf("\n");
}
void BipGraph::print_cost_dbg(){
	for(int i=0;i<m*n;i++){
		if(i%n==0 && i>0)printf("\n");
		printf("%d ",cost[i]);
		
	}
	printf("\n");
}
int BipGraph::hungarianMethod_v4(){
	//make each collumn have 0 value by sustracting with the lowest value in it
	
	for(int i=0;i<m;i++){
		//find min pada
		int minval=INF;
		
		for(int j=0;j<n;j++){
			if(tmpcost[i*n+j]==NIL)continue;
			if(minval>tmpcost[i*n+j])minval=tmpcost[i*n+j];
			
			//found minimum as 0 the most minimum value
			if(minval==0){				
				break;
			}
		}
		// minval valid
		if(minval>0 && minval<INF){
			//do substract
			
			for(int j=0;j<n;j++){
				if(tmpcost[i*n+j]==NIL)continue;
				tmpcost[i*n+j]-=minval;
			}
		}
	
	}
	
	//do the same for the rows
	for(int i=0;i<n;i++){
		//find min pada
		int minval=INF; 
		for(int j=0;j<m;j++){
			
			if(tmpcost[j*n+i]==NIL)continue;
			if(minval>tmpcost[j*n+i])minval=tmpcost[j*n+i];
			
			//found minimum as 0 the most minimum value
			if(minval==0){				
				break;
			}
		}
		// minval valid
		if(minval>0 && minval<INF){
			//do substract
			for(int j=0;j<n;j++){
				if(tmpcost[j*n+i]==NIL)continue;
				tmpcost[j*n+i]-=minval;
			}
		}
	}

	adj = new list<int>[m+1];
	int count=0; // init matching 0
	int minimum_dimension= ((m<n)? (m):(n)); // find minimum dimension duh
	
	while(matching< minimum_dimension){
		//make new hc-carp init
		for(int i=0;i<m+1;i++){
			adj[i].clear();
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				
				if(tmpcost[i*n+j]==0) {
					adj[i+1].push_back(j+1);
					printf("debug: found candidate %d %d\n",i,j);
					
				}
			}
		}
		
		this->matching=hopcroftKarp();
		printf("the cost\n");
		print_cost_dbg();
		printf("theresidual\n");
		print_tmpcost_dbg();
		printf("\ndebug: match found %d\n",matching);
		
		if(matching==minimum_dimension)return sum();
		//find mvc
		bool leftclose[m+1],rightclose[n+1];
		for(int i=0;i<m+1;i++){
			leftclose[i]=false;
		}
		for(int i=0;i<n+1;i++){
			rightclose[i]=false;
		}
		//from the matching in pairU list all the matched in pair then tally the 0 choose the best
		for(int i=0;i<m;i++){
			if(pairU[i+1] != NIL){
				printf("found left %d or right %d\n",i,i*n+pairU[i+1]-1);
				int left=i,right=pairU[i+1]-1,leftcnt=0,rightcnt=0;
				for(int j=0;j<n;j++){
					//count for the left 
					if(tmpcost[left*n+j]==0)leftcnt++;
				}
				for(int j=0;j<m;j++){
					//count for the left 
					if(tmpcost[j*n+right]==0)rightcnt++;
					
				}
				//left win or draw
				if(leftcnt<=rightcnt){
					leftclose[left]=true;
					printf("left win\n");
				}
				//right win
				else {
					rightclose[right]=true;
					printf("right win\n");
				}
				
			}
			 
		}
		//find min in tmp_cost_matrix where value not in matching
		int delta=INF;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				
				if(delta>tmpcost[j*n+i] && (!leftclose[i] && !rightclose[j] && tmpcost[j*n+i]!=NIL)) delta=tmpcost[j*n+i];
			}
		}
		
		printf("debug: match not maximum -> found delta %d\n",delta);
		if(delta== 0)return sum();;
		/*
			for each value in tmp_cost_matrix:
				if cost not in matching cost=cost-delta
				if cost in matching cost=cost+delta
		*/
		
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				//if cost not in matching cost=cost-delta
				if(!leftclose[i] && !rightclose[j]) tmpcost[j*m+i]-=delta;
				
				// if cost in matching cost=cost+delta
				else if(leftclose[i] && rightclose[j])  tmpcost[j*m+i]+=delta;
			}
		}
		count++;
	}
	return sum();
}
int BipGraph::auction(){

	return sum();	
}


int BipGraph::flowAssign(){

	return sum();	
}
int BipGraph::sum(){
	int sum=0;
	// sum cost for each matched vertex from 1 side
	for(int i=0;i<m;i++){
		
		if(pairU[i+1] != NIL){
			printf("%d",i*n+pairU[i+1]-1);
			sum+=cost[i*n+pairU[i+1]-1];
		}
			
	}
	return sum;	
}

// Constructor
BipGraph::BipGraph(int m, int n)
{
	this->m = m;
	this->n = n;
	cost = new int[(m+1)*(n+1)];
	this->matching=0;
	tmpcost = new int[(m+1)*(n+1)];
	for(int i=0;i<m+1;i++)
		for(int j=0;j<n+1;j++)
			tmpcost[i*m+j]=NIL;
	// pairU[u] stores pair of u in matching where u
	// is a vertex on left side of Bipartite Graph.
	// If u doesn't have any pair, then pairU[u] is NIL
	// mem leak?
	pairU = new int[m+1];

	// pairV[v] stores pair of v in matching. If v
	// doesn't have any pair, then pairU[v] is NIL

	pairV = new int[n+1];

	// dist[u] stores distance of left side vertices
	// dist[u] is one more than dist[u'] if u is next
	// to u'in augmenting path

	dist = new int[m+1];
}

// To add edge from u to v and v to u
void BipGraph::addEdge(int u, int v, int c)
{
	//ini buat hc-carp
	// adj[u].push_back(v); // Add u to v’s list.
	cost[u*n+v]=c;
	// m collumn n baris
	tmpcost[u*n+v]=c;
}
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

// Driver Program
int main()
{
	
	//chess piece location(x,y),type/name
	vector<pair<pair<int,int>,char> >piece;
	//target location (x,y)
	vector<pair<int,int> >location;
	
	int p,l,t;
	//testcase scan
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		location.clear();
		piece.clear();
		scanf("%d %d",&p,&l);
		//init the bipgraph class p*l
		BipGraph g(p, l);
		//scan each piece
		while(p--){
			int x,y;
			char type;
			scanf("%d %d %c",&x,&y,&type);
			if(type=='k')scanf("%c",&type);
			piece.push_back(mp(mp(x,y),type));
			while(type!='\n')scanf("%c",&type);
		}
		//scan each target location
		for(int k=0;k<l;k++){
			int x,y;
			scanf("%d %d",&x,&y);
			location.push_back(mp(x,y));
		}
		//for each piece and location count the weight matrix
		for(int j=0;j<piece.size();j++){
			if(piece[j].second=='i'){//king
				for(int k=0;k<l;k++)
					if(location[k].first-piece[j].first.first<location[k].second-piece[j].first.second) g.addEdge(j,k,abs(location[k].first-piece[j].first.first));
					else  g.addEdge(j,k,abs(location[k].second-piece[j].first.second));
			}
			if(piece[j].second=='q'){//queen
				for(int k=0;k<l;k++)
					if(location[k].first==piece[j].first.first||location[k].second==piece[j].first.second||(possible('b',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second)&&(abs(location[k].first-piece[j].first.first)==abs(location[k].second-piece[j].first.second))))g.addEdge(j,k,1);
					//bishop+rook
					else g.addEdge(j,k,2);
			}
			if(piece[j].second=='n'){//knight
				for(int m=0;m<8;m++){
					for(int n=0;n<8;n++)board[m][n]=INF;
				}
				//pakai plot fill cari semua langsung
				board[piece[j].first.first][piece[j].first.second]=0;
				travel(piece[j].first.first-1,piece[j].first.second-1,0);
				for(int k=0;k<l;k++){
					g.addEdge(j,k,board[location[k].first-1][location[k].second-1]);
				}
				
			}
			if(piece[j].second=='r'){//rook
				for(int k=0;k<l;k++)
					if(location[k].first==piece[j].first.first||location[k].second==piece[j].first.second)g.addEdge(j,k,1);
					else g.addEdge(j,k,2);
			}
			if(piece[j].second=='b'){//bishop
				for(int k=0;k<l;k++)
					if(possible('B',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second))
						if((abs(location[k].first-piece[j].first.first)==abs(location[k].second-piece[j].first.second)))g.addEdge(j,k,1);
						else g.addEdge(j,k,2);
					else g.addEdge(j,k,NIL);
			}
			if(piece[j].second=='p'){//pawn
				for(int k=0;k<l;k++)
					if(possible('P',location[k].first,location[k].second,piece[j].first.first,piece[j].first.second))
						 g.addEdge(j,k,abs(location[k].first-piece[j].first.first));
					else g.addEdge(j,k,NIL);
			}
		}
		int res=g.hungarianMethod_v4();
		cout <<"Case "<<i<<": Secret reveals after moving "<<g.get_last_matching()<<" pieces with minimum number of moves " << res<<endl;
	}
	
	

	return 0;
}

