
#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int size) : neighbors(size), visited(size) {

    }

    void addEdge(int v1, int v2) {
        assert(v1 >= 0 && v2 >= 0);
        neighbors[v1].push_back(v2);
    }

    void runDfs(int src) {
        vector<int> path;
        fill(visited.begin(), visited.end(), false);
        dfs(src, path);
        dumpPath(path);
    }

    void runDfsAll(int src, int dst) {
        vector<int> tmp;
        vector<vector<int>> paths;
        fill(visited.begin(), visited.end(), false);
        dfsAll(src, dst, tmp, paths);
        dumpPaths(paths);
    }

    void dumpPaths(vector<vector<int>> &paths) {
        cout << "path #: " << paths.size() << endl;
        for (int i = 0; i < paths.size(); i++) {
            cout << "[" << i + 1 << "] ";
            dumpPath(paths[i]);
        }
    }
    void dumpPath(vector<int>& path) {
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }

private:
    void dfsAll(int cur, int dst, vector<int> &path, vector<vector<int>> &paths) {
        /*
            if (!visited[cur]) {
            visited[cur] = true;
            path.emplace_back(cur);
            if (cur == dst) {
                paths.emplace_back(path);
            }
            else {
                for (auto neighbor : neighbors[cur])
                    dfsAll(neighbor, dst, path, paths);
            }
            visited[cur] = false;
            path.pop_back();
        }
     */

        visited[cur] = true;
        path.emplace_back(cur);
        if (cur == dst) {
            paths.emplace_back(path);
        } else {
            for (auto neighbor : neighbors[cur])
                if (!visited[neighbor]) {
                    dfsAll(neighbor, dst, path, paths);
                }
        }
        visited[cur] = false;
        path.pop_back();
    }

    void dfs(int cur, vector<int> &path) {
        visited[cur] = true;
        path.push_back(cur);
        for (auto neighbor : neighbors[cur])
            if (!visited[neighbor])
                dfs(neighbor, path);
    }
    // use unordered_map<vector<int>> 
    //   if the size |V| can't be given at compile time
    vector<vector<int>> neighbors;
    vector<bool> visited;
};

// Driver code
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    /*
               0 -> 1
               ^    |
        +-+    |    |
        | V    V    |
        +-3<-- 2<---+
     */

    cout << "DFS from vertex 2 is\n";
    g.runDfs(2);
    /*
         DFS from vertex 2 to vertex 3 are
         [1] 2 -> 0 -> 1 -> 3
         [2] 2 -> 3

         dry run:
         [0]: [1] -> [2]
         [1]: [2] -> [3]
         [2]: [0] -> [3]
         [3]: [3]

         [1] 2 -> 0 -> 1 -> 3
         [2] 2 -> 3
     */

    cout << "DFS from vertex 2 to vertex 3 are\n";
    g.runDfsAll(2, 3);

    return 0;
}
