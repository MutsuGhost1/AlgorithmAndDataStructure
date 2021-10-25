class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        string tmp;
        vector<string> ans;
        solve(s, tmp, ans);
        return ans;
    }
    
    void solve(string s, string &tmp, vector<string> &ans) {
        if(s.empty()) {
            ans.push_back(tmp);
            return;
        }

        char ch=s[0];
        tmp.push_back(ch);
        solve(s.substr(1), tmp, ans);
        tmp.pop_back();
        if(isalpha(ch)) {
            ch = islower(ch) ? toupper(ch) : tolower(ch);
            tmp.push_back(ch);
            solve(s.substr(1), tmp, ans);
            tmp.pop_back();
        }
    }
};