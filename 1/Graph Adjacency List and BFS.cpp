#include<iostream>
#include<vector>
#include <fstream>
#include <cstdlib>
#include<iterator>
#include <queue>

using namespace std;

void add_edge(vector<vector<int>>& adj, int a, int b) {     //add the edges in adj list.
    adj[a].push_back(b);
}

vector<int> BFS(const vector<vector<int>>& ADJ,int s,int N){    //BFS implementation.
    vector<int> result;     //where to put the final ans to be print out.
    queue<int> q;       //The Queue to run BFS.
    vector<bool> visited(N, false);     //Used to check if the Node hav been visited.

    visited[s]=true;
    q.push(s);

    while (!q.empty()){         //if the Queue isn't empty, 
        int curr = q.front();   //pop the queue and let it be the curr node
        q.pop();
        result.push_back(curr);     //Then add it in the result.

        for(int x:ADJ[curr]){       //check if the adjacent node are visited
            if(!visited[x]){        //if not, label as visited and put it in the queue.
                visited[x]=true;
                q.push(x);
            }
        }
    }
    return result;
    
}

int main(){

    ifstream in("test.txt");
    if (!in) {
        cout << "failed" << endl;
        exit(1);
    }

    int N,E,a,b;
    in >> N >> E ;  //N=nodes,E=edges

    vector<vector<int>> adj(N);
    
    for(int i=1;i<=E;i++){  //make the adj list
        in >> a >> b;
        add_edge(adj,a,b);
    }

    in.close();

    int start = 1;
    vector<int> bfs = BFS(adj,start,N);

    for(auto i:bfs) {   //show the bfs result
        cout<<i<<" ";
    }
    system("pause");
    return 0;
    
}