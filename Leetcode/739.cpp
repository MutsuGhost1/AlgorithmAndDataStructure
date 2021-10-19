class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
      const int kSize = temperatures.size();
      vector<int> ans(kSize, 0);
      stack<pair<int,int>> states;
      
      for(int i=kSize-1; i>=0; i--) {
          int days=0;
          while(!states.empty() && temperatures[i] >= states.top().first) {
             days += states.top().second+1;
             states.pop();
          }
          states.push(make_pair(temperatures[i], days));
          ans[i]= (1 == states.size()) ? 0 : days+1;
      }
      return ans;        
    }
};