class StockSpanner {
public:
    StockSpanner() {
        
    }
    
  
    int next(int price) {
        int span = 1;
        while(!states.empty() && price >= states.top().first) {
            span += states.top().second;
            states.pop();
        }
        states.push(make_pair(price, span));
        /// return getNext4(price);
        return span;
    }
    
    /// approach 1 - brust force
    /// time complexity:  O(N)
    /// space complexity: O(N)
    int getNext(int price) {
        int l=1;
        for(int i=prices.size()-1; i>=0; i--)
            if(prices[i] <= price)
                l++;
            else
                break;
        prices.push_back(price);
        return l;        
    }
    
    int getNext2(int price) {
        int span = 1, idx=data.size()-1;
        while(0 <= idx && data[idx].first <= price) {
            span += data[idx].second;
            idx -= data[idx].second;
        }
        data.push_back(make_pair(price, span));
        return span;
    }
    
    int getNext3(int price) {
        int span = 1;
        while(!states.empty() && states.top().first <= price) {
            span += states.top().second;
            states.pop();
        }
        states.push(make_pair(price, span));
        return span;
    }
    
    int getNext4(int price) {
        /// speed is the same as 3
        int span = 1;
        while(!stk.empty() && stk.top() <= price) {
            span += spans.back();
            stk.pop();
            spans.pop_back();
        }
        stk.push(price);
        spans.push_back(span);
        return span;
    }
    
private:
    stack<int> stk;
    vector<int> spans;
    vector<int> prices;
    vector<pair<int,int>> data;
    stack<pair<int,int>> states;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

/// input = [100,80,60,70,60,75,85]
/// output= [  1, 1, 1, 2, 1, 4, 6]
///
/// returns the span of that stock's price for the current day.
/// The span of the stock's price today is defined as 
///   the maximum number of consecutive days (starting from today 
///   and going backward) for which the stock price was 
///   less than or equal to today's price.