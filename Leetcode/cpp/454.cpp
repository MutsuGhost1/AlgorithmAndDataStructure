class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        ///  idea:
        ///    a + b + c + d = target
        ///    a + b = target - (c+d)
        
        unordered_map<int,int> hmap;
        for(int num1 : nums1)
            for(int num2 : nums2)
                hmap[num1+num2]++;
        int cnt=0;
        for(int num3 : nums3)
            for(int num4 : nums4)
                if(hmap.count(-(num3+num4)) > 0)
                    cnt += hmap[-(num3+num4)];
        return cnt;
    }
};