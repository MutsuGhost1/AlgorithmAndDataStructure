class Solution {
public:
    int kthGrammar(int n, int k) {
        if(1 == n)
            return 0;
        else {
            bool isOdd = 0 != k%2;
            if(0 == kthGrammar(n-1, (1+k)/2))
                return isOdd ? 0 : 1;
            else
                return isOdd ? 1 : 0;
        }
    }
};