# 无向连通图的最小生成树(MST) ： 边权和最小的生成树  

只有连通图才能生成，非连通图只能生成森林

## 瓶颈生成树
生成树的最大权值在无向图 G 的所有生成树中最小。  
最小生成树是瓶颈生成树的充分不必要条件，即MST一定是瓶颈生成树。  


## 最小瓶颈路
无向图 G 中 u 到 v 的最小瓶颈路是指，u 到 v 的简单路径的最大边权是所有 u 到 v 的简单路径中最小的。     
因为最小瓶颈路不是唯一的，一般会要求求最大边权，可以使用Kruskal + 树剖 / 倍增


## Kruskal重构树
按照边权将边升序，每个节点当作一个集合。  
然后开始遍历边进行加边，如果边两端节点不处于同一个集合，就新建一个节点，新节点的左右儿子分别是两个节点所在集合的根节点。（或者说把两个集合合并为一个集合）  
然后将边权作为新节点的点权。  
最终经过n-1此操作后得到的就是Kruskal重构树，这棵二叉树恰有n个叶节点。  
如果原无向图并不能保证任意两点之间连通，添加完所有边之后则可能会生成森林，此时可以另外加点并且点权为-1表示两个点不连通。  
也可以不这样搞，直接倒着写好倍增之后，单独求每个树的深度。    

在原图上任意两点u, v之间的所有简单路径上最大边权的最小值（即最小瓶颈路的最大边权）  
= 在重构树上u, v两点$LCA(u, v)$的权值。  

### 扩展
如果反过来即降序加边建树。  
在原图上任意两点u, v之间的所有简单路径上最小边权的最大值  
= 在重构树上u, v两点$LCA(u, v)$的权值。