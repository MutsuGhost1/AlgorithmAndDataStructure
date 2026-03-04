class Solution {
public:
    double myPow(double x, int n) {
        return solve2(x, n);
    }
    
    double solve2(double x, int n) {
        /// why this solution needn't to consider how to handle the overflow
        x = (n < 0) ? 1/x : x;
        if(0 == n)
            return 1;
        else if(1 == n)
            return x;
        else {
            double ans = solve2(x, abs(n)/2);
            return (0 == n%2) ? ans*ans : x*ans*ans;
        }
    }
    
    double solve1(double x, int n) {
        /// the problem must handle negative number
        bool is_neg_exp = false;
        if(n < 0) {
            is_neg_exp = true;
            n++;
            n=-n;
        }
        /// dry run
        ///
        /// x=2.0, n=-2
        ///
        /// is_neg_exp = true, n=1, x=2, ans=2
        /// ans = 1.0/(ans*x)
        double ans = myPowUtil(x, n);
        if(is_neg_exp)
        /// we should do n-- is equal to multiply with 1.0/x
            ans = 1.0/(ans*x);
        return ans;        
    }
    
private:
    double myPowUtil(double x, int n) {
        if(0 == n)
            return 1;
        else if(1 == n)
            return x;
        else {
            double ans = myPowUtil(x, n/2);
            ans *= ans;
            if(1 == n % 2)
                ans *= x;
            return ans;
        }
    }
};