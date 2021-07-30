#include<bits/stdc++/h>
def NIL
def RIGHT
def LEFT

pq_heap{
	int name;//the number of the vertex
	int position;//left or right
	int dist;//one that must be sorted
	int before;//number of vertex that connected in this queue
}

int left[M],//left side matched with (number) of the right side NIL is not matched
	right[N]//right side matched with (number) of the left side NIL is not matched
;


dijkstra():
	pq,stack
	//for each unmatched vertex
	for(int i=0;i<m;i++){
		if(left[i]==NIL){
			//push into priority queue to found the match
			pq_heap tmp;
			//the vertex name 
			tmp.name=i;
			//the location of vertex left or right side
			tmp.position=LEFT;
			//the total weight backward vertex will be 0
			tmp.dist=0;
			//the vertex connected before this one
			tmp.before=NIL;
			pq.push(tmp);
		}
	}
	// while there is path
	set<int> passed;
	while(!pq.empty()){
		//if this vertex has been passed before
		pq_heap tmp=pq.pop();
		if(passed.count(tmp.name))continue;
		stack.push(tmp);
		//can be left or right so..... make it --cool-- different
		passed.insert(tmp.name+max(m,n)*tmp.position);
		//this vertex is unmatched on the right side add it into matching
		if(tmp.position==RIGHT and right[tmp.name]==NIL){
			//found the unmatched shortest distance vertex
			int positionnow=tmp.position,//the vertex which found to be unmatched
				before=tmp.before, //vertex before this one
				now=tmp.name; //vertex where the root finding start
				while(!stack.empty()){
					tmp=stack.pop();
					if(before==tmp.name && tmp.position==LEFT && positionnow==RIGHT){
						left[tmp.name]=now;
						right[now]=tmp.name;
						now=tmp.name;
						before=tmp.before;
						positionnow=LEFT;
						//must be the first added 
						if(tmp.before==NIL)return; 
					}
					//do the invers for the other side
					else if(before==tmp.name && tmp.position==RIGHT && positionnow==LEFT){
						right[tmp.name]=now;
						left[now]=tmp.name;
						now=tmp.name;
						before=tmp.before;
						positionnow=RIGHT;
						if(tmp.before==NIL)return; 
					}
					
				}
		}
		else{
			//not the unmatched shortest distance vertex
			//so i push all unpassed vertex
			if (tmp.position==LEFT){ //from the left side
				for(int j-0;j<n;j++){
					if(cost[tmp.name][j]!=NIL){
						//cost make sense or possible to go
						if(RIGHT[j]==NIL){
							//j is unmatched this must be forward link
							pq_heap newtmp;
							newtmp.name=j;
							newtmp.position=RIGHT;
							newtmp.distance=tmp.distance+cost[tmp.name][j];
							newtmp.before=tmp.name;
							pq.push(newtmp);
						}
					}
				}
			}
			else{
				if(right[tmp.name]!=NIL){
					//this is matched must have backward link
					pq_heap newtmp;
					newtmp.name=right[tmp.name];
					newtmp.position=LEFT;
					newtmp.distance=tmp.distance;
					newtmp.before=tmp.name;
				}
			}
		}
	}
	
