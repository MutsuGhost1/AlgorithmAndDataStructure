class Solution {
public:
    
    using PII=pair<int,int>;
    
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());   
        return solve1(intervals);
    }
    
    int solve1(vector<vector<int>>& intervals) {
        priority_queue<PII, vector<PII>,greater<PII>> min_pq;
        for(auto &interval : intervals) {
            if(!min_pq.empty() && interval[0] >= min_pq.top().first)
                min_pq.pop();
            min_pq.push(make_pair(interval[1], interval[0]));
        }
        return min_pq.size();        
    }
    
    int solve2(vector<vector<int>>& intervals) {
        vector<vector<int>> rooms;
        for(auto &interval : intervals) {
            bool room_found = false;
            for(auto &room : rooms)
                if(room[1] <= interval[0]) {
                    room = interval;
                    room_found = true;
                    break;
                }
            if(!room_found)
                rooms.push_back(interval);
        }
        return rooms.size();        
    }
    
    /// we sort the time intervals
    ///   intervali = (starti, endi)
    ///           0 <= starti < endi < 10^6
    ///
    ///   starti <= starti+1
};