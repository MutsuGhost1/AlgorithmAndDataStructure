class Solution {
public:
    int singleNumber(vector<int>& nums) {
        /// You must implement a solution 
        ///   with a linear runtime complexity and use only constant extra space.
        return reduce(nums.begin(),
                      nums.end(), 0,
                      [](int a, int b){ 
                          return a^b;
                      });
    }
};