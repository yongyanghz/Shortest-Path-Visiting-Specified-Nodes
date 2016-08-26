/**************************************************************************************************************
branchAndBound.cpp
   version 1.0 -  April 2016
   author: Simon Yang
   e-mail: yangyongeducation@163.com
   Code for Obtaining Shortest path visiting specified nodes, according to

   "Algorithms for Obtaining Shortest Paths Visiting Specified Nodes"
    SIAM Review Vol. 15, No. 2, Part 1 (Apr., 1973), pp. 309-317

   by

  Toshihide Ibaraki

**/
#include "branchAndBound.h"

#define LIMIT_TIME 9.9

using namespace std;
/* Function: BranchAndBound
 *------------------------------
 * Main Entrance of Branch And Bound method to find shortest path.
 */
vector<IDType> BranchAndBound(LGraph gra,bitset<MAX_VERTEX_NUM>& visit_set,\
                                clock_t begin_time,Vertex & p_s,Vertex & p_d)
{
    int dim = gra->numVertex;
    //Create matrix of weight and ID for convenience
    int** matrix_ID;
    int** matrix_weight;
    col *rowsol;
    row *colsol;
    cost *u,*v;
    rowsol = new col[dim];
    colsol = new row[dim];
    u = new cost[dim];
    v = new cost[dim];
    matrix_weight = new int*[dim];
    matrix_ID = new int*[dim];
     for(int i = 0;i<dim;i++){
        matrix_weight[i]  =  new int[dim];
        matrix_ID[i] = new int[dim];
     }
    AssignToIDMatrix(gra,matrix_ID);
    priority_queue<ActiveQ, vector<ActiveQ>, LessThanByZValue> pq;
    int z_star = MAX_WEIGHT+INFINITY_DISTANCE;   // record the weight of current shortest path
    vector<Pos> x_star;                          // record the  current shortest path
    ActiveQ initialQ;
    initialQ.z_value = 0;
    pq.push(initialQ);
    clock_t limit_time = CLOCKS_PER_SEC*LIMIT_TIME+begin_time;
    int sumCost;
    vector<vector<Pos> > components;
    while(!pq.empty()){
        //base condition ,the time is out
        if(clock()>limit_time){
           break;
        }
        vector<Pos> fc =  pq.top().f_constraint;
        AssignToWeightMatrix(gra,matrix_weight,fc);
        matrix_weight[p_d][p_s] = MAX_WEIGHT;
        sumCost = lap(dim,matrix_weight,rowsol,colsol,u,v);
        if(sumCost<z_star){
            components = GetComponets(dim,rowsol,p_s,p_d);
            if(components.size() == 1){
            // if only one component,terminate this branch
                    x_star = components[0];
                    z_star = sumCost;
            }
            else{
                //Take an inadequate component which has least edges ,use it to decompose Q problem
                int index = 1;
                for(size_t i = 1;i < components.size();i++)
                    if(components[i].size() < components[index].size())
                        index = i;
                AddDecompositionProblem(pq,sumCost,fc,components[index]);
            }
        }
        pq.pop();
    }
        vector<IDType> path = TransformToPath(matrix_ID,x_star);
        return path;
}

/* Function: AssignToIDMatrix
 *------------------------------
 * Assign the ids of edges to the ID matrix.
 */
void AssignToIDMatrix(LGraph gra,int** ID){
    int num = gra->numVertex;
    for(int i = 0;i<num;i++){
        AdjV node = gra->Graph_row[i].firstEdge;
        while(node!=NULL){
            int c = node->col;
            ID[i][c] = node->edgeID;
            node = node->nextRight;
        }
    }

}
/* Function: AssignToWeightMatrix
 *------------------------------
 * Assign the weights of edges to the weight matrix.
 */
void AssignToWeightMatrix(LGraph gra,int** weight,vector<Pos>& fc){
    int num = gra->numVertex;
    for(int i = 0;i < num;i++)
        for(int j = 0;j < num;j++){
            weight[i][j] = INFINITY_DISTANCE;
        }
    for(int i = 0;i < num;i++){
        AdjV node = gra->Graph_row[i].firstEdge;
        while(node!=NULL){
            int c = node->col;
            weight[i][c] = node->weight;
            node = node->nextRight;
        }
    }
    for(size_t i =0;i<fc.size();i++){
        weight[fc[i]->r][fc[i]->c] = INFINITY_DISTANCE;
    }
 }

/* Function: AddDecompositionProblem
 *------------------------------
 * Take an inadequate component which has least edges ,use it to decompose Q problem,
 * and add the subproblems to pq.
 */
void AddDecompositionProblem(priority_queue<ActiveQ, vector<ActiveQ>, LessThanByZValue> &pq,\
                             int sumCost,vector<Pos> old_fc, vector<Pos> edges)
{
     for(size_t i = 0;i<edges.size();i++){
        ActiveQ patialQ;
        Pos e  = edges[i];
        vector<Pos> newfc = old_fc;
        newfc.push_back(e);
        patialQ.z_value = sumCost;
        patialQ.f_constraint = newfc;
        pq.push(patialQ);
    }
}


/* Function: TransformToPath
 *------------------------------
 * Transform the route to an path which is consists of the edge id.
 */
vector<IDType> TransformToPath(int** ID,vector<Pos> compo){
    vector<IDType> path;
    for(size_t i = 0;i<compo.size();i++){
        path.push_back(ID[compo[i]->r][compo[i]->c]);
    }
    return path;
}

/* Function: GetTheComponents
 *------------------------------
 * Get the components of the solution of the assignment problem.
 */
vector<vector<Pos> >GetComponets(int dim,col *rowsol,Vertex &p_s,Vertex &p_d){
    vector<vector<Pos> > components;
    bitset<MAX_VERTEX_NUM> isChecked;
    for(int i = p_s;i<dim;i++){
       vector<Pos> compo = GetOneComponent(i,isChecked,rowsol,p_d);
         /* If there is a path or circuit,add it to the component. */
        if(compo.size() == 1&& \
            compo[0]->r == p_s && compo[0]->c == p_d){
            components.push_back(compo);
        }
        else if(compo.size()>1){
            components.push_back(compo);
        }
    }
     for(int i = p_s-1;i>=0;i--){
       vector<Pos> compo = GetOneComponent(i,isChecked,rowsol,p_d);
         /* If there is a path or circuit,add it to the component. */
        if(compo.size()>1){
            components.push_back(compo);
        }
    }
    return components;
 }
/* Function: GetOneComponent
 *------------------------------
 * Inline function of GetTheComponents , get one component.
 */
inline vector<Pos> GetOneComponent(int i, bitset<MAX_VERTEX_NUM>&isChecked, col *rowsol,Vertex &p_d){
    vector<Pos> compo;
    if(i == p_d ){
        isChecked.set(i);
        return compo;
    }
    if(!isChecked[i]){
        int row = i;
        int col;
        bool done = false;
        while(!done){
            col = rowsol[row];
            isChecked.set(row);
            Pos point = new PosNode;
            point->r = row;
            point->c = col;
            compo.push_back(point);
            if((col == p_d) || isChecked[col])
                done = true;
            else
                row = col;
        }
    }
        return compo;
}




bool operator<(const ActiveQ& q1, const ActiveQ& q2)
{
  return q1.z_value < q2.z_value;
}



