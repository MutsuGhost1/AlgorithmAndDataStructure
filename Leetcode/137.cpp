class Solution {
public:
    int singleNumber(vector<int>& nums) {
        return solve0(nums);
    }
    
    int solve1(vector<int>& nums) {
        int ans = 0;
        for(int i=0; i<32; i++) {
            int cnt = 0;
            for(int num : nums) {
                cnt += ((num >> i) & 1);
            }
            if(0 != cnt%3)
                ans |= (1 << i);
        }
        return ans;
    }
    
    int solve0(vector<int>& nums) {
        int seen_once=0, seen_twice=0;
        for(int num : nums) {
            seen_once = ~seen_twice & (seen_once^num);
            seen_twice = ~seen_once & (seen_twice^num);
        }
        return seen_once;
    }
    
};

/*

     define 
         seen_once  -> set bit as 1 when bit exactly occur once
         seen_twice -> set bit as 1 when bit exactly occur twice

     dry run
     i = 0
                   V
     2 = 0b0000 0010
     2 = 0b0000 0010
     3 = 0b0000 0011
     2 = 0b0000 0010
     
   ans = 0b0000 0011
     
 */