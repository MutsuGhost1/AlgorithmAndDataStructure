class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        return solve(matrix, 0, matrix[0].size(), target);
    }
    
    bool solve(vector<vector<int>>& matrix, int c_row, int col_size, int target) {
        if(c_row >= matrix.size() || col_size > matrix[0].size() || col_size < 1)
            return false;
        else {
            if(int pos = binSearch(matrix[c_row], 0, col_size-1, target); pos >= 0)
                return true;
            else
                return solve(matrix, c_row+1, min(-pos, (int)matrix[0].size()), target);
        }
    }
    
    int binSearch(vector<int> &nums, int lo, int hi, int target) {
        if(lo<=hi) {
            int mid = lo+(hi-lo)/2;
            if(target > nums[mid]) {
                return binSearch(nums, mid+1, hi, target);                
            }else if(target < nums[mid]) {
                return binSearch(nums, lo, mid-1, target);
            } else {
                return mid;
            }
        }
        return -(lo+1);
    }
};