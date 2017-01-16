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
                check[*i]==true;
                
            
        }
    }
    
}
}
int main()
{ 
     // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2);
    return 0;

}
