class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count=0, curSum=0;

        unordered_map<int,int> sumToCnt;

        /// sum(0~j) - sum(0~i) = sum(i+1 ~ j) = k
        /// sum(0~i) = sum(0~j)-k
        sumToCnt[0] = 1;
        for(int num : nums) {

            curSum += num;
            if(sumToCnt.count(curSum-k) > 0) {
                count += sumToCnt[curSum-k];
            }

            sumToCnt[curSum]++;
        }

        return count;
    }

    int subarraySumV1(vector<int>& nums, int k) {

        /// Time Complexity: O(N)
        /// Space Complexity: O(N)

        /// 1. calculate prefixSum array where prefixSum[i]
        /// 2. iterate all the prefixSum and count
        int count=0;

        /// vector(size, initial value)
        vector<int> prefixSums(nums.size(), 0);
        for(int i=0; i<nums.size(); i++) {
            if(i == 0) {
                prefixSums[i] = nums[i];
            } else {
                prefixSums[i] = prefixSums[i-1] + nums[i];                
            }
        }

        /// prefixSums[0] = 1
        /// prefixSums[1] = 0
        /// prefixSums[2] = 0

        unordered_map<int,int> valToCnt;

        /// k = prefixSums[j]-prefixSums[i]
        /// prefixSums[j] = k+prefixSums[i]
        /// prefixSums[i] = prefixSums[j] - k

        valToCnt[0] = 1;
        for(int j=0; j<prefixSums.size(); j++) {
            if(valToCnt.count(prefixSums[j]-k) > 0) {
                count += valToCnt[prefixSums[j]-k];
            }
            valToCnt[prefixSums[j]]++;
        }

        return count;
    }
};