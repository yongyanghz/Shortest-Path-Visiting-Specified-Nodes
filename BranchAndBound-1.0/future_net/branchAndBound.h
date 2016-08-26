/*
 * File: brandAndBranch.h
 * ---------------------------
 * Header file of brandAndBranch.cpp
 *
 * Simon Yang, Summer 2016
 */

#ifndef BRANDANDBOUND_H_INCLUDED
#define BRANDANDBOUND_H_INCLUDED


#include<queue>
#include<ctime>

#include "dataStructure.h"
#include "lib_record.h"
#include "lap.h"
using namespace std;

/* Active problem structure in brand and branch method*/
struct ActiveQ{
    int z_value;
    vector<Pos> f_constraint;
};
/* Use this struct to compare elements in priority queue*/
struct LessThanByZValue
{
  bool operator()(const ActiveQ& q1, const ActiveQ& q2) const
  {
    return q1.z_value > q2.z_value;
  }
};
/* Function: BranchAndBound
 * Usage: path = BranchAndBound(gra,visit_set,begin_time,p_s,p_d);
 *------------------------------
 * Main Entrance of Branch And Bound method to find shortest path.
 */
vector<IDType> BranchAndBound(LGraph gra,bitset<MAX_VERTEX_NUM>& visit_set,\
                            clock_t begin_time,Vertex & p_s,Vertex & p_d);
/* Function: GetTheComponents
 * Usage: components = GetTheComponents(dim,rowsol,n1,n2);
 *------------------------------
 * Get the components of the solution of the assignment problem.
 */
vector<vector<Pos> >GetComponets(int dim,col *rowsol,Vertex &p_s,Vertex &p_d);
/* Function: GetOneComponent
 * Usage: component = GetOneComponent(i,isChecked, rowsol,p_d);
 *------------------------------
 * Inline function of GetTheComponents , get one component.
 */
inline vector<Pos> GetOneComponent(int i, bitset<MAX_VERTEX_NUM>&isChecked, col *rowsol,Vertex &p_d);
/* Function: AddDecompositionProblem
 * Usage: AddDecompositionProblem(pq,sumCost,old_fc,edges);
 *------------------------------
 * Take an inadequate component which has least edges ,use it to decompose Q problem,
 * and add the subproblems to pq.
 */
void AddDecompositionProblem(priority_queue<ActiveQ, vector<ActiveQ>, LessThanByZValue> &pq,\
                             int sumCost,vector<Pos> old_fc, vector<Pos> edges);
/* Function: TransformToPath
 * Usage: path = TransformToPath(id,compo);
 *------------------------------
 * Transform the route to an path which is consists of the edge id.
 */
vector<IDType> TransformToPath(int** ID,vector<Pos> compo);

/* Function: AssignToIDMatrix
 * Usage: AssignToIDMatrix(gra,ID);
 *------------------------------
 * Assign the ids of edges to the ID matrix.
 */
void AssignToIDMatrix(LGraph gra,int** ID );
/* Function: AssignToWeightMatrix
 * Usage: AssignToWeightMatrix(gra,wei);
 *------------------------------
 * Assign the weights of edges to the weight matrix.
 */
void AssignToWeightMatrix(LGraph gra,int** weight,vector<Pos>& fc);



bool operator<(const ActiveQ& q1, const ActiveQ& q2);

#endif // BRANDANDBOUND_H_INCLUDED

