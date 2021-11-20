class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int lo=0, hi=letters.size()-1, idx=-1;
        while(lo <= hi) {
            int mid = lo+(hi-lo)/2;
            if(target == letters[mid]) {
                idx = mid;
                lo = mid+1;
            } else if(target > letters[mid]) {
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
        idx = (-1 != idx) ? idx+1 : lo;
        return idx != letters.size() ? letters[idx] : letters[0];
    }    
};