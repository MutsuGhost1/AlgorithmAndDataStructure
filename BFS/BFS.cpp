#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int v_num) : neighbors(v_num) {

    }

    void addEdge(int v1, int v2) {
        neighbors[v1].push_back(v2);
    }

    bool isVisited(vector<int> &path, int v) {
        return find(path.begin(), path.end(), v) !=  path.end();
    }

    void bfs(int src, vector<int>& path) {
        vector<bool> visited(neighbors.size(), false);
        path.push_back(src);
        /// use pointer to have better performance
        queue<vector<int>*> q({&path});
        while (!q.empty()) {
            /// it's useful to know which level bfs is current at
            for (int i = 0, lvl_num = q.size(); i < lvl_num; i++) {
                auto& cur_path = *q.front();
                q.pop();
                int cur = cur_path[cur_path.size() - 1];
                for (auto neighbor : neighbors[cur]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        cur_path.push_back(neighbor);
                        q.push(&cur_path);
                    }
                }
            }
        }
    }

    void bfsAllPath(int src, int dst, vector<vector<int>>& paths) {
        /// tips:
        /// each bfs path is independent of other path (due to breath first search, it will traverse level by level)
        ///   thereore we can't share the data (state) between each path
        queue<vector<int>> q({{src}});
        while (!q.empty()) {
            /// TODO: check this
            ///   1. if we execute - auto &cur_path = q.front();
            ///      path will be free after executing q.pop()
            ///   2. use move for better performance
            ///       auto cur_path = move(q.front());
            auto cur_path = q.front();
            q.pop();
            int cur = cur_path[cur_path.size() - 1];
            if (cur == dst) {
                ///   2. use move for better performance
                ///       paths.push_back(move(cur_path));
                paths.push_back(cur_path); /// keep this copy
            }
            else {
                for (auto neighbor : neighbors[cur]) {
                    if (!isVisited(cur_path, neighbor)) {
                        vector<int> new_path(cur_path); /// we must copy it because cur_path still be used in this loop
                        new_path.push_back(neighbor);
                        ///   2. use move for better performance
                        ///      q.push(move(new_path));
                        q.push(new_path);
                    }
                }
            }
        }
    }
private:
    vector<vector<int>> neighbors;
};


// utility function for printing
// the found path in graph
void printPath(vector<int>& path) {
    for (auto v : path)
        cout << v << " ";
    cout << endl;
}

void printPaths(vector<vector<int>> &paths) {
    for (auto path : paths)
        printPath(path);
}

// utility function for finding paths in graph
// from source to destination
void findPaths(Graph& g, int src, int dst, vector<vector<int>> &paths) {
    g.bfsAllPath(src, dst, paths);
}

// driver program
int main()
{
    Graph g(4);
    /// 1. build graph
    g.addEdge(0, 3);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 0);
    g.addEdge(2, 1);

    int src = 2, dst = 3;
    vector<vector<int>> paths;
    cout << "path from src " << src
        << " to dst " << dst << " are \n";
    // function for finding the paths
    findPaths(g, src, dst, paths);
    printPaths(paths);

    cout << "bfs from src " << src << endl;
    vector<int> path;
    g.bfs(src, path);
    printPath(path);

    return 0;
}

/*  Output
    path from src 2 to dst 3 are
    2 0 3
    2 1 3
    2 0 1 3

    Complexity
 */