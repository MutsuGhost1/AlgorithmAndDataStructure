class Solution {
public:
    class DisjointSet {
    public:
        DisjointSet(int size) : parents(size) {
            iota(parents.begin(), parents.end(), 0);
        }
        int find(int v){
            if(v != parents[v])
                return parents[v] = find(parents[v]);
            return v;
        }
        bool unionSet(int v1, int v2){
            if(int r1=find(v1), r2=find(v2); r1!=r2){
                parents[r2] = r1;
                return true;
            }
            return false;
        }
    private:
        vector<int> parents;
    };
    
    int minCostConnectPoints(vector<vector<int>>& points) {
        const int kNum = points.size();
        /// 1. construct edge info
        ///    time complexity:  O(|E|) = O(|V|^2)
        ///    space complexity: O(|E|) = O(|V|^2)
        vector<vector<int>> edges;
        for(int i=0; i<kNum; i++)
            for(int j=i+1; j<kNum; j++) {
                int cost = calDist(points[i][0], points[i][1], points[j][0], points[j][1]);
                edges.push_back({cost, i, j});
            }
        
        /// 2. sorting
        /// O(|E|Log|E|) = O(|V^2|Log|V^2|)
        sort(edges.begin(), edges.end());
        /// 3. run kruskal's algorithm
        ///    time complexity: O(|E|*alpha(|V|)) = O(|V^2|)
        ///    space complexity: O(N)
        int edge_num = 0, cost = 0;
        DisjointSet ds(kNum);
        for(auto &edge : edges) {
            if(ds.unionSet(edge[1], edge[2])) {
                cost += edge[0];
                if(++edge_num >= kNum)
                    break;
            }
        }
        
        return cost;
    }
    int calDist(int x1, int y1, int x2, int y2){
        return abs(x1-x2) + abs(y1-y2);
    }   
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        const int kNum = points.size();
        /// 1. construct adjacent list
        ///    time  complexity: O(|E|) = O(|V|^2)
        ///    space complexity: O(|E|) = O(|V|^2)
        vector<vector<pair<int,int>>> neighbors(kNum);
        for(int i=0; i<kNum-1; i++)
            for(int j=i+1; j<kNum; j++) {
                int cost = calDist(points[i][0], points[i][1], points[j][0], points[j][1]);
                //cout << "cost(" <<i << "," <<j << ")=" << cost << endl;
                neighbors[i].push_back(make_pair(cost, j));
                neighbors[j].push_back(make_pair(cost, i));
            }
        
        ///
        /// 2. init priority queue
        ///    time  complexity: O(|1|)
        ///    space complexity: O(|V|) + O(|E|), O(|E|) = O(|V|^2)
        int v_num=0, cost=0, src=0;
        vector<bool> visited(kNum, false);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push(make_pair(cost, src));

        /// 3. run prim's algorithm
        ///    time  complexity: O(|V|*(Log|V|+|V|)) = O(|V|^2 + |V|Log|V|)
        while(!pq.empty() && v_num < kNum) {
            auto [cur_cost, v] = pq.top();
            pq.pop();
            if(!visited[v]) {
                visited[v]=true;
                /// because we'll update data for un-visited vertex
                ///   we should check it before we update data
                v_num++;
                cost += cur_cost;
                for(auto [new_cost, neighbor] : neighbors[v]) {
                    if(!visited[neighbor])
                        pq.push(make_pair(new_cost, neighbor));
                }
                cout << endl;
            }
        }
        return cost;
    }
    
    int calDist(int x1, int y1, int x2, int y2){
        return abs(x1-x2) + abs(y1-y2);
    }
    
};