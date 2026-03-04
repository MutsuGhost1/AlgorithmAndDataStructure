class Solution {
public:

    struct ArrayHash {
        size_t operator() (const array<uint8_t,26> &arr) const {
            /// Time Complexity: O(26)
            /// Space Complexity: O(1)
            size_t hash_code = 0;

            for(uint8_t num : arr) {
                hash_code = hash_code * 31 + num;
            }

            return hash_code;
        }
    };

    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        /// Time Complexity:  O(k * n) where n is strs.size()
        /// Space Complexity: O(k * n) where is the average length of each str

        unordered_map<array<uint8_t,26>, vector<string>, ArrayHash> hashcodeToGroupStr;
        hashcodeToGroupStr.reserve(strs.size());

        for(const string& str : strs) {
            array<uint8_t,26> arr = toHashcode(str);
            hashcodeToGroupStr[arr].push_back(str);
        }

        vector<vector<string>> results;
        results.reserve(hashcodeToGroupStr.size());
        for(const auto &[arr, groupStr] : hashcodeToGroupStr) {
            results.push_back(groupStr);
        }

        return results;
    }

    array<uint8_t,26> toHashcode(const string& str) {
        /// Time Complexity: O(k)
        /// Space Complexity: O(26)

        /// encode as # of char
        array<uint8_t,26> charCount = {};

        for(char ch : str) {
            charCount[ch-'a']++;
        }

        return charCount;
    }
};