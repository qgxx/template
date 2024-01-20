# Ford-Fullkerson增广

增广路：从源点到汇点的路径

Ford-Fullkerson算法的核心是找到`增广路`，然后在原图上减去各边与增广路相应的流量，
使容量更新为`残余容量`，继续使用残余容量不断找增广路。

N : count(vertex) ; M : count(edge)

## EK
O(NM^2)  
使用BFS寻找增广路得到通过每条边的流量，更新容量为残差容量，直到没有新的增广路

## Dinic
O(N^2M)
