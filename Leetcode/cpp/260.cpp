class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        /// 1. find num1^num2
        /// 2. due to num1 != num2, we can find a bit whose value is 1 in num1 and value is 0 in num2
        ///      for convenient, we find the 1st bit that is not 0 from LSB
        /// 3. use this bit to find num1, because every num has this bit occurs twice except num1
        
        int n1_xor_n2 = 0;
        for(int num : nums)
            n1_xor_n2 ^= num;
        
        int pos = (n1_xor_n2 == INT_MIN ? 0 : log2(n1_xor_n2 & ~(n1_xor_n2-1)));
/*
        int pos = 0, n = n1_xor_n2;
        while(1 != (n & 1) && n != 0) {
            n >>= 1;
            pos++;
        }
*/
        /// n & n-1
        int n1=0;
        for(int num : nums)
            if(num & (1 << pos))
                n1 ^=num;

        return {n1, n1_xor_n2^n1};
    }
};