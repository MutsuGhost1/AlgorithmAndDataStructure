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
    void cleanRoom(Robot& robot) {
        solve(robot, N, true);
    }    
private:
    enum direction : int { N=0, W, S, E };

    void solve(Robot& robot, direction prev_dir, bool start=false) {
        if(DONE == status[0][0])
            return;
        clean(robot);
        for(direction next_dir : dirs) {
            if(!start && next_dir == toOppositeDir(prev_dir))
               continue;
            if(tryMoveTo(robot, next_dir))
                solve(robot, cur_dir);
        }
        backTo(robot, prev_dir);
    }
        
    bool tryMoveTo(Robot& robot, direction next_dir) {
        /// 1. turn to this way
        turnTo(robot, next_dir);
        /// 2. try move
        c_row += dir_vals[cur_dir].first;
        c_col += dir_vals[cur_dir].second;
        if(NONE == status[c_row][c_col] && robot.move()) {
            return true;
        } else {
            /// try fail - restore
            c_row -= dir_vals[cur_dir].first;
            c_col -= dir_vals[cur_dir].second;
            if(NONE == status[c_row][c_col])
                status[c_row][c_col] = DONE;
            return false;
        }
    }
    
    void clean(Robot& robot) {
        status[c_row][c_col]=ING;
        robot.clean();        
    }
    
    void backTo(Robot& robot, direction prev_dir) {
        status[c_row][c_col] = DONE;
        turnTo(robot, toOppositeDir(prev_dir));
        if(robot.move()) {
            c_row += dir_vals[cur_dir].first;
            c_col += dir_vals[cur_dir].second;
            turnTo(robot, prev_dir);
            return;
        }
    }
    
    void turnTo(Robot& robot, direction next_dir) {
        /// can be optimized
        while(dirs[cur_dir] != next_dir) {
            cur_dir = toLeftDir(cur_dir, 1);
            robot.turnLeft();
        }
    }
    
    static direction toLeftDir(direction dir, int times) {
        return static_cast<direction>((static_cast<int>(dir)+times)%4);
    }

    static direction toOppositeDir(direction dir) {
        return toLeftDir(dir, 2);
    }

    enum status { NONE=0, ING=1, DONE=2};
    const vector<direction> dirs = {N, W, S, E};
    const vector<pair<int, int>> dir_vals = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
    direction cur_dir=N;
    int c_row=0, c_col=0;
    unordered_map<int, unordered_map<int, int>> status;
};