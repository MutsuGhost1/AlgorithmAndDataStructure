class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        /// prerequsites[i] = [ai, bi] ==> bi -> ai

        /// 1. build essential data strcture
        vector<int> i_deg(numCourses, 0);
        vector<vector<int>> neighbors(numCourses);
        for(auto & prerequisite : prerequisites) {
            i_deg[prerequisite[0]]++;
            neighbors[prerequisite[1]].push_back(prerequisite[0]);
        }
        /// 2. run Kahn's algorithm
        return findTopologicalOrder(i_deg, neighbors);
    }
    bool findTopologicalOrder(vector<int> &i_deg, vector<vector<int>> &neighbors,
                              vector<int> *p_order=NULL) {
        queue<int> q;
        for(int i=0; i<i_deg.size(); i++)
            if(0 == i_deg[i])
                q.push(i);
        int cnt=0;
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            cnt++;
            if(p_order) p_order->push_back(v);
            for(auto neighbor : neighbors[v])
                if(0 < i_deg[neighbor] && 0 == --i_deg[neighbor])
                    q.push(neighbor);
        }
        return cnt == i_deg.size();
    }
};