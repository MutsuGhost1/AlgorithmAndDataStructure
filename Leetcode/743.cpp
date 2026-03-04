class Solution {
public:
    using PII = pair<int,int>;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        /// Given an directed weighted graph
        ///   Return the (min) cost of time that all nodes receive the signal
        /// O(|E|)
        buildGraph(n, times);
        int visited_num = 0;
        /// O(Log|V|*|V|+|E|)
        vector<int> dists = runDijkstra(n, k, visited_num);
        return visited_num == n ? *max_element(dists.begin()+1, dists.end()) : -1;
    }

    /// O(|E|)
    void buildGraph(int size, vector<vector<int>>& times){
        neighbors.resize(size+1);
        for(auto &time : times)
            neighbors[time[0]].emplace_back(make_pair(time[2], time[1]));
    }
    
    vector<int> runDijkstra(int n, int src, int &visited_num){
        vector<int> dists(n+1, 101);
        vector<bool> visited(n+1, false);
        /// put curr dist from k to v
        dists[src]=0;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({dists[src], src});
        /// O(Log|V|*|V|+|E|)
        while(!pq.empty() && visited_num < n) {
            auto [_, v] = pq.top();
            pq.pop();
            if(!visited[v]) {
                visited_num++;
                visited[v]=true;
                for(auto [new_cost, neighbor] : neighbors[v])
                    if(!visited[neighbor] && dists[neighbor] > dists[v] + new_cost) {
                        dists[neighbor] = dists[v] + new_cost;
                        pq.push({dists[neighbor], neighbor});
                    }                
            }
        }
        return dists;
    }

private:
    vector<vector<PII>> neighbors;

};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        /// Given an directed weighted graph
        ///   Return the (min) cost of time that all nodes receive the signal
        return runBellmanFord(times, n, k);
    }
    
    int runBellmanFord(vector<vector<int>>& edges, int v_num, int src){
        const int kMax=100000;
        vector<int> prev_dists(v_num+1, kMax), curr_dists(v_num+1, kMax);
        prev_dists[src] = curr_dists[src] = 0;
        
        /// Time complexity: O(|V|*|E|)
        for(int i=1; i<v_num; i++) {
            for(auto edge : edges) {
                int src = edge[0], dst = edge[1], cost = edge[2];
            /*
                if(curr_dists[dst] > min(curr_dists[dst], prev_dists[src]+cost))
                    curr_dists[dst] = min(curr_dists[dst], prev_dists[src]+cost);
            */
                /// because the initial value of curr_dists[dst] is prev_dists[dst]
                ///   we can reduce the above to below
                if(curr_dists[dst] > prev_dists[src]+cost)
                    curr_dists[dst] = prev_dists[src]+cost;
            }
            prev_dists = curr_dists;
        }

        int result = *max_element(curr_dists.begin()+1, curr_dists.end());
        return result >= kMax ? -1 : result;        
    }
};

class Solution {
public:    
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        /// Given an directed weighted graph
        ///   Return the (min) cost of time that all nodes receive the signal
        vector<vector<int>> matrix = buildGraph(times, n+1);
        return runFloydWarshall(matrix, k, n+1);
    }
    
    vector<vector<int>> buildGraph(vector<vector<int>> times, int v_num) {
        vector<vector<int>> matrix(v_num, vector<int>(v_num, kIntMax));
        for(int i=0; i<v_num; i++)
            matrix[i][i]=0;
        for(auto &time : times)
            matrix[time[0]][time[1]] = time[2];
        return matrix;
    }
    
    int runFloydWarshall(vector<vector<int>> &matrix, int src, int v_num){
        for(int k=0; k<v_num; k++)
            for(int i=0; i<v_num; i++)
                for(int j=0; j<v_num; j++)
                    if(matrix[i][j] > matrix[i][k] + matrix[k][j])
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
        int result = *max_element(matrix[src].begin()+1, matrix[src].end());
        return result < kIntMax ? result : -1;
    }
    
private:
    const int kIntMax = 100000000;
};