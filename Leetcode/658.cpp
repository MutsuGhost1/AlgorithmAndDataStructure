class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        if(arr.size() <= k)
            return arr;
        int left=searchInsert(arr, x), right=left;
        if(0 == left)
            return vector<int>(arr.begin(), arr.begin()+k);

        /// left will >= 1
        left--;        
        while(right-left-1 < k) {
            if(0 <= left && right < arr.size()) {
                if(isCloser(arr[left], arr[right], x))
                    left--;
                else
                    right++;
            } else if(0 <= left) {
                left--;
            } else {
                right++;                
            }
        }
        return vector<int>(arr.begin()+left+1, arr.begin()+right);
    }
    
    int searchInsert(vector<int>& arr, int target){
        int lo=0, hi=arr.size()-1;
        while(lo <= hi) {
            int mid = lo+((hi-lo)>>1);
            if(target == arr[mid])
                return mid;
            else if(target > arr[mid])
                lo = mid+1;
            else
                hi = mid-1;
        }
        return lo;
    }
    
private:
    bool isCloser(int a, int b, int x) {
        int diff = abs(a-x)-abs(b-x);
        if(0 == diff)
            return a < b;
        else if(0 < diff)
            return false;
        else
            return true;
    }
};