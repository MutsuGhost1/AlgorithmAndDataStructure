class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int held=INT_MIN, freeze=INT_MIN;
        for(int i=1; i<=prices.size(); i++) {
            freeze = max(freeze, held+prices[i-1]);
            held = max(held, 0-prices[i-1]);
        }
        return max(0, freeze);
//      return solve2(prices);
    }
    
    int solve2(vector<int>& prices) {
        this->prices = prices;
        return max(0, dp(prices.size(), 2));
    }
    unordered_map<int,unordered_map<int,int>> memo;
    vector<int> prices;
    int dp(int i, int j) {
        if(0 == i || 0 == j)
            return 0 == j ? 0 : -10001;
        if(auto iter=memo.find(i); iter!=memo.end())
            if(auto iter2=iter->second.find(j); iter2!=iter->second.end())
                return memo[i][j];
        switch(j) {
            case 1:
                return memo[i][j]=max(dp(i-1, 1), dp(i-1, 0)-prices[i-1]);
            case 2:
                return memo[i][j]=max(dp(i-1, 2), dp(i-1, 1)+prices[i-1]);
            default:
                return -1;
        }
    }
};

///
///           0 1 2 3 4 5
/// prices = [7,1,5,3,6,4]
///
/// 1. define state variables and funtion that return the ans to given states
///    let i be the i-th day
///    let j is the state
///           0 is empty
///           1 is held
///           2 is freeze
///    let dp(i, j) is the max profit for current state
///
/// 2. find the recurrence relation to transition between states
///    dp(i, 0) = dp(i-1, 0)                                1 <= i < prices.size()
///    dp(i, 1) = max(dp(i-1, 1), dp(i-1, 0)-prices[i-1])
///    dp(i, 2) = max(dp(i-1, 2), dp(i-1, 1)+prices[i-1])
///
/// 3. find the base cases
///    dp(0, 0) = 0
///    dp(0, 1) = INT_MIN
///    dp(0, 2) = INT_MIN
///
/// 4. the ans is max(dp(i, 0), dp(i, 2))
///