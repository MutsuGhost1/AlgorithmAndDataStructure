class Solution {
public:
    
    int numSquares(int n) {
        return solve2(n);
    }
    
    /// approach 1 - recursive with memoization
    int solve1(int n) {
        if (n <= 1)
            return n;
        else {
            if(0 == memo[n]){
                int min_sum = INT_MAX;
                for(int j=1; j*j<=n; j++)
                    min_sum = min(min_sum, numSquares(n-j*j)); 
                memo[n] = min_sum+1;
            }
            return memo[n];
        }        
    }
        
    /// approach 2 - dynamic programming
    int solve2(int n) {
        /// f(n) = min(f(n-s[i])+1) for all s[i] is a perfect square num <= n)
        /// f(0) = 0
        ///
        /// 1. overloapped sub-problems
        /// 2. optimal sub-structures
        /// 3. no-after effect
        vector<int> f(n+1, INT_MAX);
        f[0]=0;
        for(int i=1; i<=n; i++) {
            for(int j=1; j*j<=i; j++)
                f[i] = min(f[i], f[i-j*j]+1);
        }
        return f[n];
    }

    unordered_map<int, int> memo;
};

/// perfect square
///
/// 1. given a number n, return the least number of perfect square numbers that sum to n
///    f(n) = min(f(n-s[i]) for all s[i]<= n that s[i] is a square number <= n)
///    f(0) = 1

/// to culcuate the min # of perfect square that their sum is equal to n
/// f(n) = min(f(n-i))
///
/// perfect num that < n

/// f(n) = min(f(n-s[0]), ..., f(n-s[i-1])) + 1 for all s[i] is a square num that  < n
/// f(n) = n is n is a prime number