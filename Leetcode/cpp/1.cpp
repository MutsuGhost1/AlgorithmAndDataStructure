class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        /// we can't solve it easily by sorting due to we need return the index before sorting

        /// Use key as value of array
        /// Use val as index of array
        unordered_map<int,int> numToIdx;
        for(int i=0; i<nums.size(); i++) {
            if(numToIdx.count(target-nums[i])) {
                return {numToIdx[target-nums[i]], i};
            }
            /// Update key and value
            numToIdx[nums[i]] = i;
        }

        return {};
    }
};