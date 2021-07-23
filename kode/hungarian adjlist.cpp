// C++ implementation of Hopcroft Karp algorithm for
// maximum matching
#include<bits/stdc++.h>
using namespace std;
#define NIL -10
#define INF INT_MAX

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
	//init dist U and V
	for(int i=0;i<m+1;i++){
		dist[i]=0;
	}
	// Initialize NIL as pair of all vertices
	for (int u=0; u<=m; u++)
		pairU[u] = NIL;
	for (int v=0; v<=n; v++)
		pairV[v] = NIL;

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
bool BipGraph::dijkstra(){
	
}
int BipGraph::hungarianMethod(){
	//for each left node do dijkstra
	for( int i=1;i<=m;i++){
		printf("dijkstra");
	}
	
	return sum();	
}
int BipGraph::hungarianMethod_v4(){
	//make each collumn have 0 value by sustracting with the lowest value in it
	for(int i=0;i<m;i++){
		//find min pada
		int minval=INF; 
		for(int j=0;j<n;j++){
			if(tmpcost[j*m+i]==NIL)continue;
			if(minval>tmpcost[j*m+i])minval=tmpcost[j*m+i];
			
			//found minimum as 0 the most minimum value
			if(minval==0){				
				break;
			}
		}
		if(minval>0){
			//do substract
			for(int j=0;j<n;j++){
				tmpcost[j*m+i]-=minval;
			}
		}
	
	}
	
	//do the same for the rows
	for(int i=0;i<n;i++){
		//find min pada
		int minval=INF; 
		for(int j=0;j<m;j++){
			if(minval>tmpcost[i*m+j])minval=tmpcost[i*m+j];
			
			//found minimum as 0 the most minimum value
			if(minval==0){				
				break;
			}
		}
		if(minval>0){
			//do substract
			for(int j=0;j<n;j++){
				tmpcost[j*m+i]-=minval;
			}
		}
	
	}
	adj = new list<int>[m+1];
	int matching=0,count=0; // init matching 0
	int minimum_dimension= ((m<n)? (m):(n)); // find minimum dimension duh
	while(matching< minimum_dimension and count<minimum_dimension){
	
		//make new hc-carp init
		adj->clear();
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(tmpcost[j*m+i]==0) adj[i].push_back(j);
			}
		}
		matching=hopcroftKarp();
		printf("debug: match found %d\n",matching);
		if(matching==minimum_dimension)return sum();
		
		//find min in tmp_cost_matrix where value not in matching
		int delta=INF;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(delta>tmpcost[j*m+i] && pairU[i]==NIL && pairV[j]==NIL) delta=tmpcost[j*m+i];
			}
		}
		 
		/*
			for each value in tmp_cost_matrix:
				if cost not in matching cost=cost-delta
				if cost in matching cost=cost+delta
		*/
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				//if cost not in matching cost=cost-delta
				if(pairU[i]==NIL && pairV[j]==NIL) tmpcost[j*m+i]-=delta;
				
				// if cost in matching cost=cost+delta
				else if(pairU[i]==NIL && pairV[j]==NIL)  tmpcost[j*m+i]+=delta;
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
	for(int i=0;i<=m;i++){
		if(pairU[i] != NIL)
			sum+=cost[i*m+pairU[i]];
	}
	return sum;	
}

// Constructor
BipGraph::BipGraph(int m, int n)
{
	this->m = m;
	this->n = n;
	cost = new int[(m+1)*(n+1)];
	for(int i=0;i<m+1)
		for(int j=0;j<n+1)
			cost[i*m+j]=NIL;
	tmpcost = new int[(m+1)*(n+1)];
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
	cost[u*m+v]=c;
	// m collumn n baris
	tmpcost[u*m+v]=c;
}

// Driver Program
int main()
{
	BipGraph g(3, 3);
	g.addEdge(1, 2, 1);
	g.addEdge(2, 3, 1);
	g.addEdge(1, 3, 1);
	g.addEdge(3, 2, 1);

	cout << "Size of maximum matching is " << g.hungarianMethod_v4();

	return 0;
}

