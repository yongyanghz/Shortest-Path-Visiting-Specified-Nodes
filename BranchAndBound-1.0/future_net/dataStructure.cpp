/*This file contains the data structure here*/

#include"dataStructure.h"

using namespace std;

/*
 * Function: BuildAllEdges
 * ----------------------
 * Build all the edges using information stored in the topo,and put the edges in a vector.
 */
vector<Edge> BuildAllEdges(char *topo[5000], int edge_num)
{
	vector<Edge> all_edges ;
	for(int i=0;i<edge_num;i++){
		int *eArray;
		eArray = CharToEdge(topo[i]);
		Edge a_edge = CreateEdge(eArray);
		all_edges.push_back(a_edge);
	}
	return all_edges;
}
/*
 * Function: CreateEdge
 * ----------------------
 * Create an edge.
 */
Edge CreateEdge(int* eArray)
{
		Edge a_edge = new ENode;
		a_edge->edgeID = *eArray;
		a_edge->v1 =  *(eArray+1);
		a_edge->v2 =  *(eArray+2);
		a_edge->weight =  *(eArray+3);
		delete[] eArray;
		return a_edge;
}

/*
 * Function: CharToEdge
 * ----------------------
 * Convert the char* which contains the information of edge to an integer array.
 */
int* CharToEdge(char *edge)
{
	int *Sarray = new int[4];
	string strArray[4] = {"","","",""};
	int count_num = 0;
	for(size_t i =0;i <strlen(edge) ;i++){
		if(edge[i] == ',')   {// the data was splited by','
			Sarray[count_num] = atoi(strArray[count_num].c_str());	//convert string to int
			count_num++;
		}else{
			strArray[count_num].push_back(edge[i]);
		}

	}
    Sarray[count_num] = atoi(strArray[count_num].c_str());
    return Sarray;
}

/*
 * Function: ConvertDemandSet
 * ----------------------
 * Convert the char*  demand which contains the information of vertexes should be visited to an integer array.
 */
vector<Vertex> ConvertDemandSet(char *demand)
{
	vector<Vertex> darray;
	string str = "";
	for(size_t i =0;i <strlen(demand) ;i++){
		if(demand[i] == ',' || demand[i] == '|'){   // the data was split by','  or'|'
		    int value = atoi(str.c_str());	//convert string to int
			darray.push_back(value);
			str = "";
		}else{
			str.push_back(demand[i]);
		}

	}
    darray.push_back(atoi(str.c_str())) ;
    return darray;
}



/*
 * Function: GetVertexesNum
 * ----------------------
 * Count vertexes, and return the number of vertexes.
 */
int GetVertexesNum(vector<Edge> &all_edges)
{
    int maxVIndex = 0;
    int num = 0;
	for(size_t i=0;i<all_edges.size();i++){
            Edge e = all_edges[i];
		if(e->v1 > maxVIndex){
            maxVIndex = e->v1;
		}
		if(e->v2 > maxVIndex){
            maxVIndex = e->v2;
		}
    }
    num = maxVIndex+1;
	return num;
}

/*
 * Function: BuildGraph
 * ----------------------
 * Build the Graph in link list form,store the graph information in this graph.
 */
LGraph BuildGraph(int numV, vector<Edge> &all_edges,Vertex &p_source,Vertex &p_dest)
{
	LGraph gra;
	Edge e;
	gra = CreateGraph(numV);
	gra->numEdge = all_edges.size();
	if (gra->numEdge != 0) {
		for (int i = 0; i < gra->numEdge; i++) {
			e = all_edges[i];
			InsertEdge(gra, e,p_source,p_dest);
		}
	}
	return gra;
}
/*
 * Function: CreateGraph
 * ----------------------
 * Initialize a graph with numV vertexes but without any edge.
 */
LGraph CreateGraph(int numV)
{
	LGraph gra;
	gra = new GNode;
	gra->numVertex = numV;
	gra->numEdge = 0;
	for (int i = 0; i < numV; i++) {
		gra->Graph_row[i].firstEdge = NULL;
	}
	return gra;
}
/*
 * Function: InsertEdge;
 * ----------------------
 * Insert an edge to the graph.
 */
void InsertEdge(LGraph gra, Edge e, Vertex &p_source,Vertex &p_dest)
{


    if((e->v1 == p_dest) || (e->v2 == p_source)){}  //The last row and the first column not included
	else{
        PtrToAdjVNode newNode;
        /*Insert the edge in the adj list of out graph*/
        /*为出图插入边<v1,v2>*/
        /*为v2建立邻接点*/
        newNode = new AdjVNode;
        newNode->row = e->v1;
        newNode->col = e->v2;
        newNode->weight = e->weight;
        newNode->edgeID = e->edgeID;
        /*将v2插入到v1的后面，并将v1后面的元素接到v2后面*/
        newNode->nextRight = gra->Graph_row[e->v1].firstEdge;
        gra->Graph_row[e->v1].firstEdge = newNode;
	}
}

/*
 * Function: InsertSelfToSelfEdge
 * ----------------------
 * Insert edge f(i,i) = 0 for the vertex not in the visit vertexes set(Except the source and destination vertex).
 */
void InsertSelfToSelfEdge(LGraph gra,int numV,bitset<MAX_VERTEX_NUM>& visit,Vertex &p_source,Vertex &p_dest)
{
    for(int i = 0; i<numV;i++){ //source vertex and destination vertex is not included
        if(!visit[i] && (i!=p_source) &&(i != p_dest)){
            AdjV node = new AdjVNode;
            node->row = node->col = i;
            node->edgeID = -1;
            node->weight = 0;
            /*Insert to the row graph*/
            node->nextRight = gra->Graph_row[i].firstEdge;
            gra->Graph_row[i].firstEdge = node;
        }
    }
}


/*
 * Function: BuildVisitVertexSet
 * Usage: BuildVisitVertexSet(demandArray, p_source, p_dest, m_size);
 * ----------------------
 * Build visit vertexes set that demanded,return the visit vertex set.
 */
bitset<MAX_VERTEX_NUM> BuildVisitVertexSet(vector<Vertex> &demandArray,Vertex &p_source,Vertex &p_dest,int &m_size)
{
    bitset<MAX_VERTEX_NUM> visit_set;
	for(size_t j=2;j<demandArray.size();j++){
		visit_set.set(demandArray[j]);
	}
	return visit_set;
 }













