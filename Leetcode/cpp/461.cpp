class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = x ^ y, cnt = 0;        
        /// count bit in res 

        while(0 != res){
            res &= res-1;
            cnt++;
        }
        return cnt;
    }
};

