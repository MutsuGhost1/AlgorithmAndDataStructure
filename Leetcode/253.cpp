class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

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
    ///   starti <= starti+1
};