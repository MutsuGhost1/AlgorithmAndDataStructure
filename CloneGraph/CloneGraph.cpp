// A C++ program to Clone an Undirected Graph
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

struct GraphNode
{
    int val;

    GraphNode() : val(0) {}
    GraphNode(int val) : val(val) {}

    //A neighbour vector which contains addresses to
    //all the neighbours of a GraphNode
    vector<GraphNode*> neighbours;
};

GraphNode* cloneGraphDfs(GraphNode* node, unordered_map<GraphNode*, GraphNode*>& visited) {
    if (node) {
        if (auto t = visited.find(node); t != visited.end())
            return visited[node];
        else {
            /// clone node & mark as visited
            GraphNode* new_node = new GraphNode(node->val);
            visited[node] = new_node;
            /// clone neighbors
            for (auto neighbor : node->neighbours)
                new_node->neighbours.push_back(cloneGraphDfs(neighbor, visited));
            return new_node;
        }
    }
    return NULL;
}

// A function which clones a Graph and
// returns the address to the cloned
// src node
GraphNode* cloneGraph(GraphNode* src)
{
    unordered_map<GraphNode*, GraphNode*> visited;
    return cloneGraphDfs(src, visited);
}

// Build the desired graph
GraphNode* buildGraph()
{
    /*
        Note : All the edges are Undirected
        Given Graph:
        1--2
        | |
        4--3
    */
    GraphNode* node1 = new GraphNode();
    node1->val = 1;
    GraphNode* node2 = new GraphNode();
    node2->val = 2;
    GraphNode* node3 = new GraphNode();
    node3->val = 3;
    GraphNode* node4 = new GraphNode();
    node4->val = 4;
    vector<GraphNode*> v;
    v.push_back(node2);
    v.push_back(node4);
    node1->neighbours = v;
    v.clear();
    v.push_back(node1);
    v.push_back(node3);
    node2->neighbours = v;
    v.clear();
    v.push_back(node2);
    v.push_back(node4);
    node3->neighbours = v;
    v.clear();
    v.push_back(node3);
    v.push_back(node1);
    node4->neighbours = v;
    return node1;
}

// A simple bfs traversal of a graph to
// check for proper cloning of the graph
void bfs(GraphNode* src)
{
    queue<GraphNode*> q({src});
    unordered_map<GraphNode*, bool> visited;
    while (!q.empty()) {
        for (int i = 0, lvl_num = q.size(); i < lvl_num; i++) {
            GraphNode* curr_node = q.front();
            q.pop();
            cout << "Value of Node " << curr_node->val << "\n";
            cout << "Address of Node " << curr_node << "\n";
            if (!visited[curr_node]) {
                visited[curr_node] = true;
                for (auto neighbor : curr_node->neighbours) {
                    q.push(neighbor);
                }
            }
        }
    }
}

// Driver program to test above function
int main()
{
    GraphNode* src = buildGraph();
    cout << "BFS Traversal before cloning\n";
    bfs(src);
    GraphNode* newsrc = cloneGraph(src);
    cout << "BFS Traversal after cloning\n";
    bfs(newsrc);
    return 0;
}

/*  Output in C++

    BFS Traversal before cloning
    Value of Node 1
    Address of Node 0x24ccc20
    Value of Node 2
    Address of Node 0x24ccc50
    Value of Node 4
    Address of Node 0x24cccb0
    Value of Node 3
    Address of Node 0x24ccc80

    BFS Traversal after cloning
    Value of Node 1
    Address of Node 0x24cd030
    Value of Node 2
    Address of Node 0x24cd0e0
    Value of Node 4
    Address of Node 0x24cd170
    Value of Node 3
    Address of Node 0x24cd200
 */