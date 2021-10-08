class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        return runBellmanFord(n, flights, src, dst, k);
    }
    
    int runBellmanFord(int v_num, vector<vector<int>>& edges, int src, int dst, int k) {
        const int kMax= 100000000;
        vector<int> prev_dist(v_num, kMax), curr_dist(v_num, kMax);
        
        /// init
        prev_dist[src] = curr_dist[src] = 0;
        
        /// use bellman ford algorithm - dynamic programming
        ///   > dist[k][u] = min(dist[k][u], dist[k-1][v] + w(v,u) for u,v is an ticket in flights)
        /// k+1 iteration
        for(int i=1 ; i<=k+1 ; i++) {
            for(auto edge : edges) {
                int src = edge[0], dst = edge[1], cost_src2dst = edge[2];
                if(curr_dist[dst] > prev_dist[src] + cost_src2dst)
                    curr_dist[dst] = prev_dist[src] + cost_src2dst;
            }
            /// copy current to previous
            prev_dist = curr_dist;
        }
        
        /// key points:
        /// 1. use for each with auto& to init a vector<vector<int>>
        /// 2. how to determine the default weight in the graph
        ///    e.g. 10000001 in this case
        return curr_dist[dst] < kMax ? curr_dist[dst] : -1  ;        
    }
};
/// TLE
class Solution {
public:
    using PII = pair<int,int>;
    const int kMax = 100000000;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dest, int k) {
        vector<vector<PII>> neighbors(n);
        for(auto &flight : flights)
            neighbors[flight[0]].push_back({flight[2], flight[1]});
        vector<bool> visited(n, false);
        int min_dist=kMax;
        dfs(neighbors, visited, src, dest, k+1, 0, 0, min_dist);
        return min_dist < kMax ? min_dist : -1;
    }
    
    void dfs(vector<vector<PII>> &neighbors, vector<bool> &visited, int cur, int dst, 
             const int max_deep, int cur_deep, int cur_dist, int &min_dist){
        /// pruning
        if(min_dist <= cur_dist || cur_deep > max_deep)
            return;
        if(cur == dst) {
            min_dist = min(min_dist, cur_dist);
        } else {
            visited[cur] = true;
            for(auto [dist, neighbor] : neighbors[cur]) {
                if(!visited[neighbor])
                    dfs(neighbors, visited, neighbor, dst, max_deep, cur_deep+1, cur_dist+dist, min_dist);
            }
            visited[cur] = false;
        }
    }
};