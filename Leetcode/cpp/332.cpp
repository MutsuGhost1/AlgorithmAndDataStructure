class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        /// Try all the edges permutation
        
        ///   You may assume all tickets form at least one valid itinerary. 
        ///   You must use all the tickets once and only once.

        /// Use backtracking to get a valid itinerary
        ///
        /// 1. according to the lexcial order
        sort(tickets.begin(), tickets.end());
        /// 2. build the graph using adjacent list
        unordered_map<string, int> visited;
        unordered_map<string, vector<string>> neighbors;
        for(auto ticket : tickets) {
            neighbors[ticket[0]].push_back(ticket[1]);
            visited[ticket[0]+ticket[1]]++;
        }

        vector<string> path;
        bool done=false;
        dfs(neighbors, visited, "JFK", path, tickets.size(), done);
        return path;
    }
    
    bool dfs(unordered_map<string, vector<string>> &neighbors, unordered_map<string, int> &visited,
             string cur, vector<string> &path, int ticket_num, bool &done) {
        if(done) return true;
        if(0 == ticket_num) {
            /// the first path is our ans because we sort it according lexical
            path.push_back(cur);
            return done = true;
        } else {
            path.push_back(cur);
            for(auto neighbor : neighbors[cur]) {
                if(0 < visited[cur+neighbor]) {
                    visited[cur+neighbor]--;
                    if(dfs(neighbors, visited, neighbor, path, ticket_num-1, done))
                        return true;
                    visited[cur+neighbor]++;
                }
            }
            path.pop_back();
        }
        return false;
    }
};

/// Time  Complexity: O(|E|!)
/// Space Complexity: O(|V| + |E|)