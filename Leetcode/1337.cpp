class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        /// Time  Complexity: O(N LogK)
        /// Space Complexity: O(K)
        priority_queue<pair<int,int>> pq;
        for(int r=0; r<mat.size(); r++) {
            int power = accumulate(mat[r].begin(), mat[r].end() ,0);
            if(pq.size() == k && power < pq.top().first)
                pq.pop();
            if(pq.size() < k)
                pq.push(make_pair(power, r));
        }
        
        /// Time  Complexity: O(K LogK)
        /// Space Complexity: O(K)
        vector<int> ans;
        while(!pq.empty()) {
            auto [_, row] = pq.top();
            pq.pop();
            ans.insert(ans.begin(), row);
        }
        return ans;
    }
    
    vector<int> solve2(vector<vector<int>>& mat, int k) {
        /// Time  Complexity: O(N Log N)
        /// Space Complexity: O(N)
        vector<pair<int,int>> data;
        for(int r=0; r<mat.size(); r++)
            data.push_back(make_pair(accumulate(mat[r].begin(), mat[r].end() ,0), r));
        sort(data.begin(), data.end());

        /// Time  Complexity: O(K)
        /// Space Complexity: O(K)
        vector<int> ans;
        for(int i=0; i<k; i++)
            ans.push_back(data[i].second);
        return ans;       
    }
};