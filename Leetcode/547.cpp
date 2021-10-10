class Solution {
public:
    
    void dfs(vector<vector<int>> &neighbors, vector<bool> &visited, int cur,
             vector<int> *p_path=NULL) {
        visited[cur] = true;
        if(p_path) p_path->push_back(cur);
        for(auto neighbor : neighbors[cur])
            if(!visited[neighbor])
                dfs(neighbors, visited, neighbor, p_path);
    }
    
    int findCC(int v_num, vector<vector<int>> &neighbors, vector<vector<int>> *p_ccs=NULL) {
        int cnt=0;
        vector<bool> visited(v_num, false);
        for(int i=0; i<visited.size(); i++) {
            if(!visited[i]) {
                cnt++;
                if(p_ccs) p_ccs->push_back(vector<int>()); 
                dfs(neighbors, visited, i, p_ccs ? &p_ccs->back() : NULL);
            }
        }
        return cnt;
    }
    
    int findCircleNum(vector<vector<int>>& board) {
        vector<vector<int>> neighbors(board.size());
        for(int i=0; i<board.size(); i++)
            for(int j=0; j<board[0].size(); j++)
                if(1 == board[i][j])
                    neighbors[i].push_back(j);
        // vector<vector<int>> ccs;
        return findCC(board.size(), neighbors/*, &ccs*/);
    }
};