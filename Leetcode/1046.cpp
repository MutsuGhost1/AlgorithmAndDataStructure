class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq(stones.begin(), stones.end());
        while(1 < pq.size()) {
            int t[2];
            for(int i=0; i<2; i++) {
                t[i] = pq.top();
                pq.pop();
            }
            if(t[0]-t[1] != 0)
                pq.push(t[0]-t[1]);
        }
        return pq.size() == 0 ? 0 : pq.top();
    }
};