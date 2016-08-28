# Shortest-Path-Visiting-Specified-Nodes

We anticipated a programming competition of HUAWEI company.
http://codecraft.huawei.com/

The request of the issue:http://codecraft.huawei.com/home/detail<br />

We implement the algorithm seaching for shortest path visiting specified nodes,<br />
According to  Toshihide Ibaraki's paper<br />
   "Algorithms for Obtaining Shortest Paths Visiting Specified Nodes"<br />
    SIAM Review Vol. 15, No. 2, Part 1 (Apr., 1973), pp. 309-317
    
Input file: <br />
topo.csv: the information of the graph <br />
 LinkID,SourceID,DestinationID,Cost <br />
 example: <br />
 0,0,1,1 <br />
 1,1,2,1 <br />
 2,2,3,1 <br />
 3,1,4,1 <br />
 4,4,3,1 <br />
 5,0,5,1 <br />
 6,5,2,1 <br />
 
demand.csv:source node, detination node,specified nodes to visit <br />
SourceID,DestinationID,IncludingSet<br />
example:<br />
         0,1,2|3<br />
         
Output file:<br />
result.csv: 1). If exits a path ,print the  LinkID in sequence,sepearted with '|';<br />
            2) If such path not exits, print "Na".<br />
example:<br />
         1|5|4<br />


            
   
