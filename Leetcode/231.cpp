class Solution {
public:
    bool isPowerOfTwo(int n) {
        // return n != 0 && n != INT_MIN &&  0 == (n & (n-1)) ;
        return n > 0 &&  0 == (n & (n-1)) ;
    }
};