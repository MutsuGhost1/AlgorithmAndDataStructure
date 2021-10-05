class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        
        /*
              [[0,0,0],
               [1,0,0],
               [1,1,0]]
    
              1. q = [(0, 0)], plen++ (plen=1)
                 q.pop()   -> q=[]
                 c_row=0, c_col=0
                 q.push((0,1))
                 q.push((1,1))
              2. q = [(0,1), (1,1)], plen++ (plen=2)
                 q.pop()        -> q=[(1,1)]
                 c_row=0, c_col=1
                 q.push((0,2)) -> q=[(1,1), (0,2)]
                 q.push((1,1)) -> q=[(1,1), (0,2), (1, 1)]
                 q.push((1,2)) -> q=[(1,1), (0,2), (1, 1), (1, 2)]
                 q.pop()       -> q=[(0,2), (1, 1), (1, 2)]
                 c_row=1, c_col=1
                 q.push((1,2)) -> q=[(0,2), (1, 1), (1, 2), (1, 2)]
                 q.push((2,2)) -> q=[(0,2), (1, 1), (1, 2), (1, 2), (2, 2)]
              3. q=[(0,2), (1, 1), (1, 2), (1, 2), (2, 2)], plen++ (plen=3)         
         */
        
        rowNum = grid.size();
        colNum = grid[0].size();
        if(0 == grid[0][0] && 0 == grid[rowNum-1][colNum-1]) {
            int plen=0;
            vector<vector<bool>> visited(rowNum, vector<bool>(colNum, false));
            queue<pair<int,int>> q({make_pair(0, 0)});
            while(!q.empty()) {
                plen++;
                for(int i=0, lvl_num=q.size(); i < lvl_num; i++) {
                    auto [curr_row, curr_col] = q.front();
                    q.pop();
                    /// notice: nested for loop
                    if(curr_row == rowNum-1 && curr_col == colNum-1)
                        return plen;
                    if(!visited[curr_row][curr_col]) {
                        visited[curr_row][curr_col] = true;
                        for(auto [o_r, o_c] : dirs) {
                            int n_row = curr_row + o_r, n_col = curr_col + o_c;
                            if(isValidCell(n_row, n_col) && 0 == grid[n_row][n_col])
                                q.push(make_pair(n_row, n_col));
                        }
                    }
                }
            }
            /// not found if q is empty
        }
        return -1;
    }
    
    bool isValidCell(int row, int col) {
        return 0 <= row && row < rowNum && 0 <= col && col < colNum;
    }
    
    vector<pair<int,int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, { 0, -1}, { 0, 1}, {1, -1}, {1, 0}, { 1, 1}};
    int rowNum;
    int colNum;
};