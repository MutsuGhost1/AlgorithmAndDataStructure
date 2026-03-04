class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        /// Minimum Index Sum of Two Lists
        ///   
        unordered_map<string, int> hmap;
        for(int i=0; i<list1.size(); i++)
            hmap[list1[i]]=i;

        vector<string> ans;
        int min_sum=INT_MAX;
        for(int i=0; i<list2.size(); i++)
            if(hmap.count(list2[i]) > 0) {
                if(min_sum > i+hmap[list2[i]]) {
                    ans.clear();
                    min_sum = i+hmap[list2[i]];
                }
                if(min_sum == i+hmap[list2[i]])
                    ans.push_back(list2[i]);
            }
        return ans;
    }
};