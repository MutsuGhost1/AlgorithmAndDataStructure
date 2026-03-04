class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        return findTopologicalOrder(numCourses, prerequisites);
    }
    
    vector<int> findTopologicalOrder(int numCourses, vector<vector<int>>& prerequisites){
        /// prerequisites[i] = [ai, bi] => bi -> ai
        vector<vector<int>> neighbors(numCourses);
        for(const auto &prerequisite : prerequisites)
            neighbors[prerequisite[1]].push_back(prerequisite[0]);

        vector<pair<vector<int>, bool>> ccs;
        findCCs(neighbors, ccs);
        
        vector<int> order;
        for(auto iter=ccs.rbegin(); iter != ccs.rend(); iter++)
            if(auto &[cc, hasCycle] = *iter; hasCycle) {
                return vector<int>();
            } else {
                for(int i=cc.size()-1; i>=0; i--)
                    order.push_back(cc[i]);
            }
        return order;
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