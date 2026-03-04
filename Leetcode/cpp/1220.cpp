class Solution {
public:
    int countVowelPermutation(int n) {
        return solve2(n);
    }
    
   
    const vector<int> kBases = {5, 1, 2, 4, 2, 1};
    const int kMod = 1000000007;
    const vector<vector<int>> kRules={{1,2,3,4,5}, {2}, {1,3}, {1,2,4,5},{3,5},{1}};
    int solve0(int n) {
        /// 4 steps to solve DP problem
        /// 1. find state variables and function/data struct that compute/contain the ans to given states
        ///    let i is the len of letter
        ///    let j is the last vowel of the letter, we should follow the last vowel's rule
        ///    let dp(i, j) is the # of vowels permutation
        ////
        /// 2. find recurrence relation to transition between states
        ///    dp(i, j) = dp(i-1, 1) + dp(i-1, 2) + dp(i-1, 3) + dp(i-1, 4) + dp(i-1, 5) if j == 0
        ///
        /// 3. base cases
        ///     dp(1, 0) = 5 -> rule: prev 1+2+3+4+5
        ///     dp(1, 1) = 1 -> rule: prev 2
        ///     dp(1, 2) = 2 -> rule: prev 1+3
        ///     dp(1, 3) = 4 -> rule: prev 1+2+4+5
        ///     dp(1, 4) = 2 -> rule: prev 3+5
        ///     dp(1, 5) = 1 -> rule: prev 1
        ///
        /// 4. ans is
        ///     dp(n, 0)
        vector<vector<int>> dp(n, vector<int>(kRules.size()));
        /// base cases
        dp[0] = kBases;
        for(int i=1; i<dp.size(); i++)
            for(int j=0; j<dp[i].size(); j++)
                for(int r : kRules[j])
                    dp[i][j] = (dp[i][j] + dp[i-1][r]) % kMod;
        return dp[n-1][0];
    }
    
    int solve2(int n) {
        return dp(n-1, 0);
    }
    
    unordered_map<int, unordered_map<int,int>> memo;
    int dp(int i, int j) {
        if(0 == i)
            return kBases[j];
        if(auto iter1=memo.find(i); iter1!=memo.end())
            if(auto iter2=iter1->second.find(j); iter2!=iter1->second.end())
                return memo[i][j];
        int sum = 0;
        for(int k : kRules[j])
            sum = (sum + dp(i-1, k)) % kMod;
        return memo[i][j] = sum;
    }
    
    int solve3(int n) {
        ///
        /// 1. define state variables 
        ///      and function/data struct that compute/contain the answer to given states
        ///
        ///    let i is the length of vowel permutation
        ///    let j is the current starting vowel, 0=null, 1='a', 2='e', 3='i', 4='o', 5='u'
        ///    let dp(i, j) is the # of vowel permutation that start with j has length i
        ///
        /// 2. find the recurrence relation to transition between states
        ///    dp(i, j) = dp(i-1, 1) + dp(i-1, 2) + dp(i-1, 3) + dp(i-1, 4) + dp(i-1, 5) if j == 0
        ///             = dp(i-1, 2)              if j == 1
        ///             = dp(i-1, 1) + dp(i-1, 3) if j == 2
        ///             = dp(i-1, 1) + dp(i-1, 2) + dp(i-1, 4) + dp(i-1, 5)if j == 3
        ///             = dp(i-1, 3) + dp(i-1, 5) if j == 4
        ///             = dp(i-1, 1) if j == 5
        /// 3. find the base case
        ///
        ///    dp(i, 0) = 5 if j == 0
        ///    dp(i, 1) = 1 if j == 1
        ///    dp(i, 2) = 2 if j == 2
        ///    dp(i, 3) = 4 if j == 3
        ///    dp(i, 4) = 2 if j == 4
        ///    dp(i, 5) = 1 if j == 5
        ///
        /// 4. get ans = dp(n, 0)
        int kMod=1000000007;
        vector<vector<int>> dp(n+1, vector<int>(6, 1));
        /// base cases        
        dp[1][0]=5;
        dp[1][1]=1;
        dp[1][2]=2;
        dp[1][3]=4;
        dp[1][4]=2;
        dp[1][5]=1;
        for(int i=2; i<dp.size(); i++)
            for(int j=0; j<dp[i].size(); j++)
                switch(j) {
                    case 0:
                        dp[i][j] = (((dp[i-1][1] + dp[i-1][2]) % kMod + 
                                     (dp[i-1][3] + dp[i-1][4]) % kMod) % kMod + dp[i-1][5]) % kMod;
                        break;
                    case 1:
                        dp[i][j] = (dp[i-1][2]) % kMod;
                    break;
                    case 2:
                        dp[i][j] = (dp[i-1][1] + dp[i-1][3]) % kMod;
                    break;
                    case 3:
                        dp[i][j] = ((dp[i-1][1] + dp[i-1][2]) % kMod + 
                                    (dp[i-1][4] + dp[i-1][5]) % kMod) % kMod;
                    break;
                    case 4:
                        dp[i][j] = (dp[i-1][5] + dp[i-1][3]) % kMod;
                    break;
                    case 5:
                        dp[i][j] = (dp[i-1][1]) % kMod;
                    break;
                }
        return dp[n][0];
    }
};