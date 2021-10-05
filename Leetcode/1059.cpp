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
        if(!visited[cur]) {
            /// we can't put visited[cur] = true; here
            ///    > we should move it after this check
            if(cur == dst)
                return true;
            visited[cur] = true;
            for(auto neighbor : neighbors[cur]) {
                if(!dfs(neighbors, visited, neighbor, dst)) {
                    return visited[cur] = false;
                }
            }
            visited[cur] = false;
            return 0 != neighbors[cur].size();
        }
        /// loop
        return false;
    }
};