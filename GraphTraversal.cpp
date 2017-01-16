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

using namespace std; // }}}
class Graph
{
    int vertices;
    list<int> *adj;
    public:
    Graph(int vertices);
    void addEdge(int source ,int destination);
    void BFS(int start);
    void DFS(int start);
    void printDFS(int start,bool *check);
    bool DetectCycleDirected();
    bool DCDUtil(int start,bool * check,bool *loop);
  

};
Graph::Graph(int vertices)
{
    this->vertices=vertices;
    adj=new list<int>[vertices];
}
void Graph::addEdge(int src,int dest)
{
    adj[src].push_back(dest);
}
void Graph::BFS(int start)
{
    bool *check=new bool[100];
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
        for(list<int>::iterator i=adj[temp].begin();i!=adj[temp].end();i++)
        {
            if(check[*i]==false)
            {
                q.push(*i);
                check[*i]=true;   
            }
        }    
    }
}
void Graph::DFS(int start)
{
    bool *visited=new bool[vertices];
    for(int i=0;i<vertices;i++)
        visited[i]=false;
    printDFS(start,visited);
    
}
void Graph::printDFS(int start,bool *visited)
{
    if(visited[start]==true)
        return;
    cout<<start<<" ";
    visited[start]=true;
    for(list<int>::iterator i=adj[start].begin();i!=adj[start].end();i++)
    {
        printDFS(*i,visited);
    }
    return;
}

bool Graph::DetectCycleDirected()
{
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
    //cout<<endl<<"start " << start<<endl;
    if(loop[start]==true)
        return true;
    if(check[start]==true)
        return false;
    check[start]=true;
    loop[start]=true;
    
    bool out=false;
    for(list<int>::iterator i=adj[start].begin();i!=adj[start].end();i++)
    {        
        out=DCDUtil(*i,check,loop);
        if(out==true)
            return out;
    }
    loop[start]=false;
    return out;
}

int main()
{ 
     // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);

    g.addEdge(1, 2);

    //g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2);
    g.DFS(2);
    cout<<g.DetectCycleDirected();
    return 0;

}
