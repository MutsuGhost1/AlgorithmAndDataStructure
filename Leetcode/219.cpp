class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,int> hmap;
        for(int i=0; i<nums.size(); i++)
            if(hmap.count(nums[i]) > 0) {
                if(i-hmap[nums[i]] <= k)
                    return true;
                else
                    /// update it
                    hmap[nums[i]] = i;
            } else {
                /// insert
                hmap[nums[i]] = i;
            }
        return false;
    }
};