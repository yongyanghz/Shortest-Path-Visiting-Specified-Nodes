/*
 * File: route.h
 * ---------------------
 * This file contains the functions used in searching route.
 *
 * Simon Yang, Summer 2016
 */


#include "route.h"
/*
 * Function: search_route
 * ----------------------
 * This function is the main entrance of searching a shortest path
 */
void search_route(char *topo[5000], int edge_num, char *demand)
{
    const clock_t begin_time = clock();
    vector<IDType> result;            //Store the final result of shortest path
	vector<Edge> all_edges = BuildAllEdges(topo,edge_num);
	int numVertex = GetVertexesNum(all_edges);
	vector<Vertex> demandArray = ConvertDemandSet(demand);
	bitset<MAX_VERTEX_NUM> visit_set;
	Vertex p_source = demandArray[0];
	Vertex p_dest = demandArray[1];
	visit_set = BuildVisitVertexSet(demandArray,p_source,p_dest,numVertex);
	// Build the graph
	LGraph gra = BuildGraph(numVertex,all_edges,p_source,p_dest);
	InsertSelfToSelfEdge(gra,numVertex,visit_set,p_source,p_dest);
    if(!DFS(gra,p_source,p_dest)){
        cout<<"No solution, the source vertex and destination vertex is not connected!"<<endl;
        return;
    }
    // Use branch and bound to search the shortest path
    result = BranchAndBound(gra,visit_set,begin_time,p_source,p_dest);
    // Check the result
    if( result.size() && IsResultCorrect(all_edges, result,p_source,p_dest)){
			cout<<"The result is right!"<<endl;
    }
    else{
			cout<<"The result is wrong"<<endl;
    }
	// Print the results in the result.csv
 	for(std::vector<IDType>::iterator it = result.begin(); it != result.end(); ++it){
	  record_result(*it);
	  cout<<*it<<"|";
	}
    cout<<endl;
}

/*
 * Function: DFS
 * ----------------------
 * In this function DFS algorithm is used to check if the source vertex and
 * destination vertex are connected or not. If connected,return true,otherwise
 * return false.
 */
bool DFS(LGraph graph,Vertex p_source,Vertex p_dest)
{
	bool *check = new bool[graph->numVertex]; // Identifiers£¬represent if the vertex have been checked
 	bool *isIn = new bool[graph->numVertex];  // Identifiers£¬represent if the vertex is connected with source vertex
	for (int i = 0; i < graph->numVertex; i++) {  // Initialize the identifiers
		check[i] = false;
		isIn[i] = false;
	}
    DFSRecur(graph,p_source,check,isIn);
    isIn[p_source] = true;
    if (isIn[p_dest])  // the source vertex and destination vertex are connected
    	return true;
	else
	    return false;
}
/*
 * Function: DFSRecur
 * ----------------------
 * This function is the recursion part of DFS algorithm.
 */
void DFSRecur(LGraph graph,Vertex v,bool check[],bool isIn[])
{
	if (check[v]||graph->Graph_row[v].firstEdge == NULL) {
		return;
	}
	check[v] = true;
	PtrToAdjVNode currentNode = graph->Graph_row[v].firstEdge;
	while (currentNode!= NULL) {
		int i = currentNode->col;
		isIn[i] = true;
		DFSRecur(graph,i,check,isIn);
		currentNode = currentNode->nextRight;
	}
}

/*
 * Function: IsResultCorrect
 * ----------------------
 * This function checks the result,if right,return true,otherwise return false.
 */bool IsResultCorrect(vector<Edge> edges, vector<IDType> result,Vertex p_source,Vertex p_dest)
{
	size_t num = result.size();
	if(edges[result[0]]->v1 != p_source || num > edges.size() ||\
	    edges[result[num-1]]->v2 != p_dest){
	    	return false;
		}
	for(size_t i = 0;i<num-1;i++)
		if(edges[result[i]]->v2 != edges[result[i+1]]->v1 )
			return false;
    return true;
}







