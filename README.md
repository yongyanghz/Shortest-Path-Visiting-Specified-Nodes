# Shortest-Path-Visiting-Specified-Nodes

We anticipated a programming competition of HUAWEI company.
http://codecraft.huawei.com/
The request of the issue:http://codecraft.huawei.com/home/detail
We implement the algorithm seaching for shortest path visiting specified nodes
According to  Toshihide Ibaraki's paper
   "Algorithms for Obtaining Shortest Paths Visiting Specified Nodes"
    SIAM Review Vol. 15, No. 2, Part 1 (Apr., 1973), pp. 309-317
Input file: 
   topo.csv: the information of the graph
   LinkID,SourceID,DestinationID,Cost
   example:
            0,0,1,1
            1,1,2,1
            2,2,3,1
            3,1,4,1
            4,4,3,1
            5,0,5,1
            6,5,2,1
   demand.csv: SourceID,DestinationID,IncludingSet
   example:
            0,1,2|3
Output file:
   result.csv: 1). If exits a path ,print the  LinkID in sequence,sepearted with '|';
               2) If such path not exits, print "Na".
   example:
            1|5|4


            
   
