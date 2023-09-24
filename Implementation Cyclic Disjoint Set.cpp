#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int parent[255]={0};

struct Edge{
	int source;
	int destination;
};

struct Graph{
	int vertexCount;
	int edgeCount;
	Edge *edge;
};

Graph *createGraph(int vertexCount, int edgeCount){
	Graph *newGraph = (Graph*)malloc(sizeof(Graph));
	newGraph->vertexCount = vertexCount;
	newGraph->edgeCount = edgeCount;
	newGraph->edge = (Edge*)malloc(sizeof(Edge)*edgeCount);
	return newGraph;
}

void makeSet(int vertexCount){
	for(int i = 0;i<vertexCount;i++){
		parent[i] = i;
	}
	
}

int findParent(int vertex){
	if(parent[vertex] == vertex){
		return vertex;
	}
	parent[vertex] = findParent(parent[vertex]);
	return parent[vertex];
}

bool join(Graph *graph){
	for(int i = 0;i < graph->edgeCount;i++){
		int sourceParent = findParent(graph->edge[i].source);
		int destinationParent = findParent(graph->edge[i].destination);
		
		if(sourceParent == destinationParent){//terdapat cycle
			return true;
		}
		parent[sourceParent] = destinationParent;
	}
	
	return false;
}


bool isCyclic(Graph *graph){
	makeSet(graph->vertexCount);
	return join(graph);
}





int main(){
	

	
	Graph *graph = createGraph(4,4);
	
	graph->edge[0].source = 0;
	graph->edge[0].destination = 2;
	
	graph->edge[1].source = 2;
	graph->edge[1].destination = 1;
	
	
	graph->edge[2].source = 1;
	graph->edge[2].destination = 3;
	
	graph->edge[3].source = 2;
	graph->edge[3].destination = 3;
	
	if(isCyclic(graph)){
		printf("This graph is cyclic!");
	}
	else{
		printf("This graph is not cyclic!");
	}
	
	
	
	return 0;
}
