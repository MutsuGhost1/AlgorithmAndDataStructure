class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        return solve2(nums);
    }
    
    int solve1(vector<int>& nums) {
        /// You must solve the problem without modifying the array nums and 
        ///   uses only constant extra space
        int d_num = -1;
        for(int num : nums)
            if(nums[abs(num)] > 0)
                nums[abs(num)] = -nums[abs(num)];
            else
                d_num = abs(num);
        /// restore
        for(int &num : nums)
            if(num < 0)
                num = -num;
        return d_num;        
    }
    
    /// wrong algorithm
    ///
    /// key point: the duplicate value will appear two or more times
    /// descrease and conquer
    int solve(vector<int>& nums) {
        int ans=0;
        for(int i=0; i<nums.size()-1; i++)
            ans += (nums[i]-i-1);
        ans += nums.back();
        return ans;
    }
    
    /// 1 ~ n, 找中間值 mid, 計算 1 ~ n+1 中, 有多少個數 <= mid,
    /// 用 cnt 統計整個 nums 中, cnt 用於計算 nums 有多少數 <= mid, 
    ///   若 cnt 等於 mid ,表示重複的數一定在 mid 的右側 (包含 mid)
    ///   若 cnt 大於 mid ,表示重複的數一定在 mid 的左側
    ///   若 cnt 小於 mid ,表示重複的數一定在 mid 的右側
    ///
    /// 終止條件
    ///
    ///        1  2  3  4  5  6  7
    ///        l        m        r
    ///        l  m     r
    ///       l/m r
    ///          l/r
    ///
    /// nums =[2, 2, 1, 3, 4, 5, 2]

    int solve2(vector<int>& nums) {
        int lo=1, hi=nums.size();
        while(lo < hi) {
            int mid = lo+(hi-lo)/2;
            int cnt = 0;
            for(int num : nums) {
                if(num <= mid)
                    cnt++;
            }
            if(cnt <= mid)
                lo = mid+1;
            else
            /// cnt > mid
                hi = mid;
        }
        return lo;
    }
};