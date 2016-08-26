/*
 * File: route.cpp
 * ---------------------
 * This file contains the implementations of functions used in searching route.
 *
 * Simon Yang, Summer 2016
 */
#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <vector>
#include<iostream>
#include<set>
#include<queue>
#include<string>
#include<cstring>
#include <stdlib.h>     /* atoi */
#include<stack>
#include <stdio.h>
#include<ctime>

#include "lib_record.h"
#include "dataStructure.h"
#include "branchAndBound.h"
using namespace std;
/*
 * Function: search_route
 * Usage: search_route(topo, 5000, demand);
 * ----------------------
 * This function is the main entrance of searching a shortest path
 */
void search_route(char *graph[5000], int edge_num, char *condition);
/*
 * Function: DFS
 * Usage: isConnected = DFS(gra,n1,n2);
 * ----------------------
 * In this function DFS algorithm is used to check if the source vertex and
 * destination vertex are connected or not. If connected,return true,otherwise
 * return false.
 */
bool DFS(LGraph gra,Vertex p_source,Vertex p_dest);
/*
 * Function: DFSRecur
 * Usage: DFSRecur(graph,p_source,check,isIn);
 * ----------------------
 * This function is the recursion part of DFS algorithm.
 */
void DFSRecur(LGraph graph,Vertex v,bool check[],bool isIn[]);
/*
 * Function: IsResultCorrect
 * Usage: isCorrect = IsResultCorrect(edges,result, p_source,p_dest)
 * ----------------------
 * This function checks the result,if right,return true,otherwise return false.
 */
bool IsResultCorrect(vector<Edge> edges, vector<IDType> result,Vertex p_source,Vertex p_dest);
/*----------------------------------------------------------------------------------------------------------*/
#endif


