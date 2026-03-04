class Solution {
public:
    int mySqrt(int x) {
        // return solve1(x);
        return solve2(0, x, x);
    }
    
    int solve1(int x) {
        long i=0;
        while(i*i <= x)
            i++;
        return i-1;        
    }
    
    int solve2(int lo, int hi, int target) {
        if(lo <= hi) {
            long mid = lo + (hi-lo)/2;
            if(target == mid*mid)
                return mid;
            else if(target > mid*mid)
                return solve2(mid+1, hi, target);
            else
                return solve2(lo, mid-1, target);
        }
        
        /// lo   is the min position that is great than
        /// lo-1 is the max position that is less  than target
        return lo-1;
    }
         
};
