#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector> 
#include <list>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>
using namespace std; 
//Adjacent node of a Node with v(vertex name) and distance with default 0
struct AdjacentNode
{
    int v,distance=0;
};
/*  Graph class that handles both directed Graph and Undirected Graph 
    Default is  Directed Graph
    for Undirected Graph pass false as second parameter to the constructor
*/
class Graph
{    
    int vertices;
    bool isDirected=true;
    list<AdjacentNode> *adj;
    void DFSutil(int start,bool *check);
    bool DCDUtil(int start,bool * check,bool *loop);
    public:
    //Constructor for Graph class
    Graph(int vertices,bool isDirected=true);
    //Adding an Edge with or without distance
    void addEdge(int source ,int destination,int dist=0);
    //Breadth First Search  using the Queue
    void BFS(int start);
    //Depth First Search using the recursion
    void DFS(int start);
    //Returns true if there are any cycles 
    bool DetectCycleDirected();
    void LongestPathUndirectedGraphUtil(int root,int current,bool *visited,int * distance,int sum);
    void LongestPathUndirectedGraph();    
};
Graph::Graph(int vertices,bool isDirected)
{   
    this->vertices=vertices;//number of vertices
    this->isDirected=isDirected;//is Directed or not
    adj=new list<AdjacentNode>[vertices];//Initialising the array of list of Adjacent node 
}
void Graph::addEdge(int src,int dest,int dist)
{
    //creating the node and pushing the node in the src node list
    AdjacentNode node;
    node.v=dest;
    node.distance=dist;
    adj[src].push_back(node);
    if(!isDirected)//if the graph id Undirected 
    {        
        AdjacentNode node1;
        node1.v=src;
        node1.distance=dist;
        adj[dest].push_back(node1);        
    }
}
void Graph::BFS(int start)
{
     /*logic:    1 push the root node in queue  and check of root is true
                2 loop until the queue is empty 
                    pop element 
                    insert all the adjacent nodes to the queue and check of node is true 
                    print the popped element
    */
    //creating Check array which verifies the vertex is visited or not 
    bool *check=new bool[100];
    //initilising the array false 
    for(int i=0;i<100;i++)
        check[i]=false;
    queue<int> q;   
    q.push(start);
    check[start]=true;
    int temp;
    while(!q.empty())
    {
        temp=q.front();
        q.pop();
        cout<<temp<<" ";
        for(list<AdjacentNode>::iterator i=adj[temp].begin();i!=adj[temp].end();i++)
        {
            if(check[(*i).v]==false)
            {
                q.push((*i).v);
                check[(*i).v]=true;   
            }
        }    
    }
}
void Graph::DFS(int start)
{
    /*logic :
                1 print root node and visited is true 
                2 loop through all adjacent nodes 
                3       if adjacent node is not visited 
                            go to step one with root being the adjacent node
                        else return 
    */
    bool *visited=new bool[vertices];
    for(int i=0;i<vertices;i++)
        visited[i]=false;
    DFSutil(start,visited);
    
}
void Graph::DFSutil(int start,bool *visited)
{
    if(visited[start]==true)
        return;
    cout<<start<<" ";
    visited[start]=true;
    for(list<AdjacentNode>::iterator i=adj[start].begin();i!=adj[start].end();i++)
        DFSutil((*i).v,visited);
    return;
}
bool Graph::DetectCycleDirected()
{    
    /*logic:
                1 Take two arrays one for visited and other for checking if the path is loop or not 
                2 take root node
                3 if loop value is already true then  return true                
                4 set the visited and loop values true
                5 loop for all the Adjacent nodes 
                    repeat step 2 with root being the adjacent node
                6 return false
    */     
    bool *check=new bool[vertices];
    bool *loop=new bool[vertices];
    bool out=false;
    for(int i=0;i<vertices;i++)
    {
        check[i]=false;
        loop[i]=false;
    }
    for(int i=0;i<vertices;i++)
    {
        if(check[i]==false)
            out=DCDUtil(i,check,loop);
        if(out==true)
            break;
    }
    return out;
}
bool Graph::DCDUtil(int start,bool *check,bool *loop)
{
    if(loop[start]==true)      
    if(check[start]==true)
        return false;
    check[start]=true;
    loop[start]=true;
    
    bool out=false;
    for(list<AdjacentNode>::iterator i=adj[start].begin();i!=adj[start].end();i++)
    {        
        out=DCDUtil((*i).v,check,loop);
        if(out==true)
            return out;
    }
    loop[start]=false;
    return out;
}
void Graph::LongestPathUndirectedGraphUtil(int root,int current,bool *visited,int * distance,int sum)
{
    if(visited[current]==false)
    {
        visited[current]=true;
        if(distance[current]<sum)
            distance[current]=sum; 
        for(list<AdjacentNode>::iterator i=adj[current].begin();i!=adj[current].end();i++)
        {
            int tempNode,tempSum;
            tempSum=(*i).distance;
            tempNode=(*i).v;
            LongestPathUndirectedGraphUtil(root,tempNode,visited,distance,sum+tempSum);           
        }
        visited[current]=false;
    }
}

void Graph::LongestPathUndirectedGraph()
{
    int sum=0;
    bool *visited=new bool[vertices];
    int *distance=new int[vertices];
    for(int i=0;i<vertices;i++)
    {
        visited[i]=false;
        distance[i]=0;
    }
    LongestPathUndirectedGraphUtil(0,0,visited,distance,sum);
    cout<<endl;
    cout<<endl;
    for(int i=0;i<vertices;i++)
        cout<<distance[i]<<" ";
}


int main()
{ 
     // Create a graph given in the above diagram
    Graph g(4,false);
    g.addEdge(0, 1,6);
    g.addEdge(1, 2,20);
    g.addEdge(1, 3,30);
   // g.addEdge(2, 0);
    g.addEdge(2, 3,1);
   // g.addEdge(3, 3);

 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
   g.LongestPathUndirectedGraph();

    cout<<g.DetectCycleDirected();
    return 0;

}
