class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        /*
             [-2,0,1,3]
             for(i=0; i<4; i++)
               left=1, right=3
               while(left<right)
                   -2+0+3=1 < 2
             
         */
        
        int cnt=0;
        for(int i=0; i<nums.size(); i++) {
            int left=i+1, right=nums.size()-1;
            while(left < right) {
                if(nums[i]+nums[left]+nums[right] < target) {
                    cnt += (right-left);
                    left++;
                } else {
                    right--;
                }
            }
        }
        return cnt;
    }
};