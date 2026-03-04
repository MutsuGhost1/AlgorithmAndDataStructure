class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        return solve0(heights, bricks, ladders);
    }
    
    int solve0(vector<int>& heights, int bricks, int ladders) {
        vector<int> consume_bricks;
        priority_queue<int, vector<int>, greater<int>> min_pq;
        for(int i=0; i<heights.size()-1; i++) {
            int effort = heights[i+1]-heights[i];
            if(effort > 0) {
                if(bricks >= effort) {
                    bricks -= effort;
                    consume_bricks.push_back(effort);
                } else if (ladders > 0) {
                    ladders--;
                    min_pq.push(effort);
                } else {
                    /// try to make ladder to have best effort
                    if(!min_pq.empty() && !consume_bricks.empty()) {
                        /*
                                0  1  2  3  4  5     6
                              [ 1, 5, 1, 2, 3, 4,    10000], 4, 1
                              [ 4, 0, 1, 1, 1, 99996, 0]
                         */
                        bool change;
                        do {
                            change = false;
                            for(int &consume_brick : consume_bricks) {
                                int gain_effort = consume_brick - min_pq.top();
                                if(gain_effort > 0) {
                                    int tmp = consume_brick;
                                    consume_brick = min_pq.top();
                                    min_pq.pop();
                                    min_pq.push(tmp);
                                    bricks += gain_effort;
                                    change = true;
                                }
                            }                            
                        }while(change);

                        if(bricks >= min_pq.top()) {
                            bricks -= min_pq.top();
                            min_pq.pop();
                            ladders++;
                            i--;
                            continue;
                        }
                        if(bricks >= effort) {
                            i--;
                            continue;
                        }
                        return i;
                    } else {
                        return i;   
                    }                    
                }
            }
        }
        return heights.size()-1;        
    }
    
    
    int solve1(vector<int>& heights, int bricks, int ladders) {
        /// 1. find the state variables and the function/data struct 
        ///         that computes/retain ans to given states
        ///
        ///    let i means # of building
        ///    let b means # of bricks can be used
        ///    let l means # of ladders can be used
        ///
        ///    dp(i,b,l) is the farest # of build we can reach
        ///
        /// 2. find the recurrence relation to transition between states
        ///    dp(i,b,l)   =     dp(i+1, b, l)                                  if h[i] >= h[i+1]
        ///                = max(dp(i+1, b, l-1), dp(i+1, b-(h[i+1]-h[i], l)))  if h[i] <  h[i+1]
        ///
        /// 3. find the base cases
        ///    dp(i, b, l) = i  if i == heights.size()-1 || l == 0 && b < h[i+1]-h[i]
        ///
        ///    dp(heights.size()-1,x,x) = heights.size()-1  if i == heights.size()-1
        ///    dp(i, b, l) = i                              if l == 0 && b < h[i+1]-h[i]
        ///
        /// 4. find the ans
        ///    dp(0,b,l)
        ///
        /// set dp array
        vector<vector<vector<int>>> dp(heights.size(), 
                                       vector<vector<int>>(bricks+1, 
                                                           vector<int>(ladders+1, heights.size()-1)));
        for(int i=dp.size()-1; i>=0; i--)
            for(int b=0; b<dp[i].size(); b++)
                for(int l=0; l<dp[i][b].size(); l++) {
                    if(i == heights.size()-1 || 0 == l && b < heights[i+1]-heights[i]) {
                        dp[i][b][l] = i;
                    } else {
                        if(heights[i] >= heights[i+1])
                            dp[i][b][l] = dp[i+1][b][l];
                        else {
                            int max_val = INT_MIN;
                            if(b >= heights[i+1]-heights[i])
                                max_val = max(max_val, dp[i+1][b-(heights[i+1]-heights[i])][l]);
                            if(l >= 1)
                                max_val = max(max_val, dp[i+1][b][l-1]);                                
                            dp[i][b][l] = max_val;
                        }
                    }
                }
        return dp[0][bricks][ladders];
    }
    
    unordered_map<int,unordered_map<int,unordered_map<int,int>>> memo;
    vector<int> heights;
    int solve2(vector<int>& heights, int bricks, int ladders) {
        this->heights = heights;
        return dp(0, bricks, ladders);
    }
    
    int dp(int i, int b, int l) {
        if(heights.size()-1 == i || (l == 0 && b<heights[i+1]-heights[i]))
            return i;

        if(auto iter1=memo.find(i); iter1!=memo.end())
            if(auto iter2=iter1->second.find(b); iter2!=iter1->second.end())
                if(auto iter3=iter2->second.find(l); iter3!=iter2->second.end())
                    return memo[i][b][l];
        
        if(heights[i] >= heights[i+1])
            return memo[i][b][l] = dp(i+1, b, l);
        else {
            int max_val = INT_MIN;
            if(b >= heights[i+1]-heights[i])
                max_val = max(max_val, dp(i+1, b-(heights[i+1]-heights[i]), l));
            if(l > 0)
                max_val = max(max_val, dp(i+1, b, l-1));
            return memo[i][b][l] = max_val;
        }
    }
};
