class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() <= 1) return intervals;

        /// the defeault compare behavior for vector<int>
        ///   is lexicalgraphical comparison
        ///   compare the elements from index 0 to length-1
        sort(intervals.begin(), intervals.end());

        /// sorting by (x, y)

        vector<vector<int>> results;
        results.push_back(intervals[0]);
        for(int i=1; i<intervals.size(); i++) {
            /// if two interval have overlapping then merge
            if(intervals[i][0] <= results.back()[1]) {
                results.back()[1] = max(results.back()[1], intervals[i][1]);
            } else {
                results.push_back(intervals[i]);
            }
        }

        /// Dry Run
        /// last interval is merged
        ///
        /// intervals = [[1,4],[4,5]], size()=2
        /// results = [[1,4]]
        /// i=1
        /// if(intervals[i][0] <= results.back()[1]) then merge
        /// -> results = [[1, 5]]

        return results;
    }
};