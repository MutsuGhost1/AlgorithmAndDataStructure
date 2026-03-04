class Solution {
public:
    using PIS = pair<int,string>;
    vector<string> topKFrequent(vector<string>& words, int k) {
        /// Time  Complexity: O(N)
        /// Space Complexity: O(N)
        unordered_map<string,int> counter;
        for(string &word : words)
            counter[word]++;
        
        /// min-heap => 
        auto cmp = [](PIS &p1, PIS &p2) {
            return p1.first != p2.first ? p1.first > p2.first : p1.second < p2.second;
        };
        
        /// Time  Complexity: O(K + (N-K) LogK)
        /// Space Complexity: O(K)
        // min-heap
        priority_queue<PIS, vector<PIS>, decltype(cmp)> pq(cmp);
        for(auto [word, cnt] : counter) {
/*
            if(pq.size() >= k && (cnt > pq.top().first || cnt == pq.top().first && word < pq.top().second))
*/
            if(pq.size() >= k)
                if(auto p1=make_pair(cnt, word), p2=pq.top(); cmp(p1, p2))
                    pq.pop();
            if(pq.size() < k)
                pq.push(make_pair(cnt, word));
        }
        
        
        /// Time  Complexity: O(KLogK)
        /// Space Complexity: O(K)
        vector<string> ans;
        while(!pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};