class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        /// approach 1, bruce force - TLE
        return findLargestRectArea(heights);
    }
    
    /// TLE
    int findLargestRectArea(vector<int>& heights) {
        int max_area = heights[0], min_h = heights[0];
        for(int i=1; i<heights.size(; i++)) {
            for(int seg=2; seg<=start+1; seg++) {
                min_h = min(min_h, heights[start-seg+1]);
                max_area = max(max_area, min_h*seg);
                if(0 == min_h) break;
            }
        }
        return max_area;
    }
};