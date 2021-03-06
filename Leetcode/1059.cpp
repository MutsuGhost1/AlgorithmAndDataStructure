class Solution {
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        /// 1. build an adjacent list
        vector<vector<int>> neighbors(n);
        for(auto edge : edges)
            neighbors[edge[0]].push_back(edge[1]);

        if(0 != neighbors[destination].size())
            return false;

        /// 2. traverse
        vector<bool> visited(n, false);
        return dfs(neighbors, visited, source, destination);
    }

    bool dfs(vector<vector<int>> &neighbors, vector<bool> &visited, int cur, int dst) {
        /// has loop
        if(visited[cur])
            return false;
        
        /// arrive dst
        if(cur == dst) {
            return true;
        } else { 
        /// keep going
            visited[cur] = true;
            for(auto neighbor : neighbors[cur]) {
                if(!dfs(neighbors, visited, neighbor, dst)) {
                    return visited[cur] = false;
                }
            }
            visited[cur] = false;
            /// 0 != neighbors[cur].size() means we at least try 1 neighbor
            ///   and all of the neighbors reach the dst
            return 0 != neighbors[cur].size();
        }
    }
};

/// Time Complexity: ???
/// 1. O(|V|!) ??? the same as perumation ????
///
/// Space Complexity: O(|V|+|E|)
/// 1. Use space O(|V|) to store visited
/// 2. Use space O(|E|) to store adjacent list