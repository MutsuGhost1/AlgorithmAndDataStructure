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

class Solution {
public:

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> neighbors(numCourses);
        for(auto &prerequisite : prerequisites)
            neighbors[prerequisite[0]].push_back(prerequisite[1]);
        vector<pair<vector<int>, bool>> ccs;
        findCCs(neighbors, ccs);
        return ccs.end() == find_if(ccs.begin(), ccs.end(), [](const pair<vector<int>, bool> &p){ return p.second;});
    }
    
    void findCCs(vector<vector<int>> &neighbors, vector<pair<vector<int>, bool>> &ccs) {
        vector<bool> visited(neighbors.size(), false);
        vector<bool> in_call_stack(neighbors.size(), false);
        for(int i=0; i<visited.size(); i++)
            if(!visited[i]) {
                vector<int> cc;
                bool hasCycle=false;
                dfsUtil(neighbors, visited, i, &in_call_stack, &cc, hasCycle);
                ccs.emplace_back(make_pair(cc, hasCycle));
            }
    }
    
    void dfsUtil(vector<vector<int>> &neighbors, vector<bool> &visited, int cur,
                 vector<bool> *p_in_call_stack,
                 vector<int> *p_cc, bool &hasCycle) {
        if(hasCycle) return;
        visited[cur] = true;
        if(p_in_call_stack) (*p_in_call_stack)[cur] = true;
        for(auto neighbor : neighbors[cur]) {
            if(p_in_call_stack && (*p_in_call_stack)[neighbor]) {
                hasCycle=true;
                return;
            }
            if(!visited[neighbor])
                dfsUtil(neighbors, visited, neighbor, p_in_call_stack, p_cc, hasCycle);
        }
        // put it when all children visited
        if(p_cc) (*p_cc).push_back(cur);
        if(p_in_call_stack) (*p_in_call_stack)[cur] = false;
    }
};