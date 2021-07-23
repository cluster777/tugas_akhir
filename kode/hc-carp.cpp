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
	int m, n;

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
	// Returns minimum cost matching using FlowAssign
	int flowAssign();
	
	// Create Forest and return true if found augmenting path 
	bool dijkstra();
	
	// Return sum of cost in matching
	int sum();
};

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
	int matching=0,count=0; // init matching 0
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
		
		matching=hopcroftKarp();
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
				//(pairU[i+1]==NIL || pairV[j+1]==NIL) pa
				if(delta>tmpcost[j*n+i] && (!leftclose[i] && !rightclose[j])) delta=tmpcost[j*n+i];
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

// Driver Program
int main()
{
	
	BipGraph g(3, 3);
	g.addEdge(0,0, 108);
	g.addEdge(0,1,125);
	g.addEdge(0,2,150);
	g.addEdge(1,0,150);
	g.addEdge(1,1,135);
	g.addEdge(1,2,175);
	g.addEdge(2,0,122);
	g.addEdge(2,1,148);
	g.addEdge(2,2,250);

	cout << "Size of maximum matching is " << g.hungarianMethod_v4();

	return 0;
}

