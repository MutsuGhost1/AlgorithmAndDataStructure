class Solution {
public:
    double myPow(double x, int n) {
        bool is_negative = false;
        if(n < 0) {
            is_negative = true;
            n += 1;
            n = -n;
        }
        double ans = myPowHelper(x, n);
        if(is_negative) {
            ans = 1.0/(ans*x);
        }
        return ans;
    }
    
    double myPowHelper(double x, int n) {
        if(0 == n)
            return 1;
        if(1 == n)
            return x;
        if(0 == memo[n]) {
            /// n=3, n/2 = 1
            /// n=5, n/2 = 2
            double ans =  myPowHelper(x, n/2);
            ans *= ans;
            if(1 == n %2)
                ans *=x;
            memo[n] = ans;
        }
        return memo[n];
    }
    
    unordered_map<int, double> memo;
};