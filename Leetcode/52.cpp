class Solution {
public:
    int totalNQueens(int n) {
        return countNQueuesSolution(n);
    }

    int countNQueuesSolution(const int kBoardSize, int c_row=0, int c_col=0) {
        /// stop when reaching the last row
        if(c_row >= kBoardSize) {
            return 1;
        }
        int sum = 0;
        for(int col=0; col<kBoardSize; col++)
            if(!hasAttack(c_row, col)) {
               /// move to next row only when we occupy the row
               occupied.push_back(make_pair(c_row, col));
               sum += countNQueuesSolution(kBoardSize, c_row+1, c_col);
               occupied.pop_back();
            }
        return sum;
    }
    
    bool hasAttack(int c_row, int c_col) {
        for(auto [row, col] : occupied)
            if(row == c_row || col == c_col || abs(row-c_row)==abs(col-c_col))
               return true;
        return false;
    }
    
private:
    vector<pair<int,int>> occupied;
};