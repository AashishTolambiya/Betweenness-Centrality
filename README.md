# Betweenness-Centrality for Network Graphs
The set of programs deals with betweenness centrality computation in networks. A network is represented as an undirected graph.
Betweenness centrality for a given vertex in a graph is the ratio of number of shortest paths passing through that vertex by the total number of shortest paths present in the graph. 
Graphs are stored in the form of adjacency lists, and betweenness centrality is computated using Floyd-Warshall Algorithm and Breadth First Search ALgorithm (Remember that, originally, Floyd Warshall algorithm is meant for directed graphs).
Computation of Betweenness Centrality (BC) requires counting the number of shortes paths passing through a vertex.
The programs are tested on large graphs with vertices ranging from 5000 to 20,000. The BC values from both the algorithms on a given graph are found to be identical.
The code also facilitates with Erdos-Renyi model random graph generator, which can be used to generate random graphs with different number of edges and vertices, and with different level of sparseness to be tested upon. 
