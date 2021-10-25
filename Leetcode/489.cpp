/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

class Solution {
public:
    enum direction : int { N=0, W, S, E };

    void cleanRoom(Robot& robot) {
        solve(robot, N, true);
    }
    
    void solve(Robot& robot, direction prev_dir, bool start=false) {
        if(hasDone()) {
            return;
        }
        status[c_row][c_col] = ING;
        robot.clean();
        for(int i=0; i<dirs.size(); i++) {
            direction back_dir = toOppositeDir(prev_dir);
            if(!start && toLeftDir(cur_dir, i) == back_dir)
                continue;
            if(tryMoveTo(robot, toLeftDir(cur_dir, i))) {
                solve(robot, cur_dir);
            }
        }
        backTo(robot, prev_dir);
    }
    
    bool hasDone() {
        return DONE == status[0][0];
    }
    
    bool tryMoveTo(Robot& robot, direction next_dir) {
        /// 1. turn to this way
/*
        cout << __func__ << ": From (" << c_row << "," << c_col << ")";
        cout << " To: (" << c_row+dir_vals[next_dir].first << ","
             << c_col+dir_vals[next_dir].second << ")" << endl;
*/
        turnTo(robot, next_dir);
        /// 2. move
        c_row += dir_vals[cur_dir].first;
        c_col += dir_vals[cur_dir].second;
        if(NONE == status[c_row][c_col] && robot.move()) {
            status[c_row][c_col] = ING;
//            cout << __func__ << " move - pass" << endl;
            return true;
        }
        c_row -= dir_vals[cur_dir].first;
        c_col -= dir_vals[cur_dir].second;
        if(NONE == status[c_row][c_col])
            status[c_row][c_col] = DONE;
//        cout << __func__ << " move - fail" << endl;
        return false;
    }
    
    /// 1,     1       
    /// p_row, p_col + offset = c_row, c_col
    void backTo(Robot& robot, direction prev_dir) {
/*
        cout << __func__ << ": previous dir " << prev_dir << endl;
        cout << __func__ << " mark (" << c_row << "," << c_col << ") is done" << endl;
*/
        status[c_row][c_col] = DONE;

        turnTo(robot, toOppositeDir(prev_dir));
        if(robot.move()) {
            c_row += dir_vals[cur_dir].first;
            c_col += dir_vals[cur_dir].second;
//            cout << __func__ << " backTo: (" << c_row << "," << c_col << ")" << endl;
            /// adjuct the direction to previous direction
            turnTo(robot, prev_dir);
            return;
        }
//        cout << __func__ <<": can't back to previous ...!" << endl;
    }
    
    void turnTo(Robot& robot, direction next_dir) {
        while(dirs[cur_dir] != next_dir) {
            cur_dir = nextDir();
            robot.turnLeft();
        }        
    }
    
    static direction toLeftDir(direction dir, int move) {
        return static_cast<direction>((static_cast<int>(dir)+move) % 4);
    }
    static direction toOppositeDir(direction dir) {
        return toLeftDir(dir, 2);
    }

    direction nextDir() {
        return toLeftDir(cur_dir, 1);
    }
    
private:
    enum status { NONE=0, ING=1, DONE=2};
    const vector<direction> dirs = {N, W, S, E};
    const vector<pair<int, int>> dir_vals = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
    direction cur_dir=N;
    int c_row=0, c_col=0;
    unordered_map<int, unordered_map<int, int>> status;
};