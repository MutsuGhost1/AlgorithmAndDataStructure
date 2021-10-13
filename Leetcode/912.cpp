class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        //insertionSort(nums);
        //selectionSort(nums);
        //bubbleSort(nums);
        //quickSort(nums, 0, nums.size()-1);
        //mergeSortI(nums);
        mergeSortR(nums, 0, nums.size()-1);
        return nums;
    }
    
    void mergeTwo(vector<int>& nums, int lo, int mid, int hi) {
        vector<int> left(nums.begin()+lo, nums.begin()+mid+1);
        vector<int> right(nums.begin()+mid+1, nums.begin()+hi+1);

        int l=0, r=0, i=lo;
        while(l<left.size() && r<right.size())
            if(left[l] < right[r])
                nums[i++] = left[l++];
            else
                nums[i++] = right[r++];
        while(l<left.size())
            nums[i++] = left[l++];
        while(r<right.size())
            nums[i++] = right[r++];
    }

    void mergeSortR(vector<int>& nums, int lo, int hi) {
        if(lo < hi) {
            int mid = lo+(hi-lo)/2;
            mergeSortR(nums, lo, mid);
            mergeSortR(nums, mid+1, hi);
            mergeTwo(nums, lo, mid, hi);
        }
    }
    
    void mergeSortI(vector<int>& nums) {
        int len = nums.size();
        for(int seg=1; seg<len; seg+=seg)
            for(int lo=0; lo<len; lo+=2*seg) {
                int mid = min(lo+seg-1, len-1);
                int hi = min(lo+seg*2-1, len-1);
                mergeTwo(nums, lo, mid, hi);
            }
    }
    
    int partition(vector<int>& nums, int s, int e) {
        swap(nums[e], nums[s+rand()%(e-s)]);
        int i=s;
        int pivot=nums[e];
        for(int j=s; j<e; j++)
            if(nums[j] < pivot)
                swap(nums[i++], nums[j]);
        swap(nums[i], nums[e]);
        return i;
    }
    
    void quickSort(vector<int>& nums, int s, int e){
        if(s < e) {
            int p = partition(nums, s, e);
            quickSort(nums, s, p-1);
            quickSort(nums, p+1, e);
        }
    }
    
    void bubbleSort(vector<int>& nums) {
        for(int i=nums.size()-1; i>0; i--)
            for(int j=0; j<i ; j++)
                if(nums[j] > nums[j+1])
                    swap(nums[j], nums[j+1]);
    }
    
    void selectionSort(vector<int>& nums){
        for(int i=0; i<nums.size(); i++) {
            /// find min
            int min_idx=i;
            for(int j=i+1; j<nums.size(); j++)
                if(nums[j] < nums[min_idx])
                    min_idx=j;
            swap(nums[min_idx], nums[i]);
        }
    }
    
    void insertionSort(vector<int>& nums) {
        /// tips 
        /// we keep j as the insertion point if we stop at j
        /// when we stop at j, j must be copy to j+1
        for(int i=1, j; i<nums.size(); i++) {
            int tmp = nums[i];
            for(j=i; j>0 ; j--)
                if(tmp < nums[j-1])
                    nums[j] = nums[j-1];
                else
                    break;
            swap(tmp, nums[j]);
        }
    }        
};  