#include <iostream>
#include <vector>

using namespace std;

/// The rule of big five in C++ 11
///   Reference: 
///   1. https://en.cppreference.com/w/cpp/language/rule_of_three
///   2. https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners 
class Data {
public:

	/// * constructor <-- we don't count it due to that we write it, so we need big five
	Data(int size = 10) : size(size), data{new int[size]} {
		cout << "default construcotr:" << this << endl;
		cout << endl;
	}

	/// 2. copy constructor
	///    it'll be invoked in below situations
	///    a. Data a=b;
	///    b. Data a(b);
	Data(const Data& other) : size(other.size), data{ new int[other.size] } {
		cout << "copy construcotr: new " << this << endl;
		cout << "copy construcotr: from " << &other << endl;
		cout << endl;
	}

	/// 3. copy assignment operator
	///    it'll be invoked in below situations
	///    a. Data a;
	///       a=b;
	Data& operator=(const Data& rhs) {
		cout << "copy assignment:" << this << endl;
		cout << endl;
		if (this != &rhs) {
			freeRes();
			cloneRes(rhs);
		}
		return *this;
	}

	/// 4. move constructor
	///    tips:
	///      1. memeber initialization list will be invoked prior to the code in move constructor
	///      2. it'll save the cost 
	///         a. when we create a tempory object and pass it to container, then the container won't do deeply copy
	Data(Data&& other) noexcept : size(other.size), data(other.data)  {
		cout << "move constructor:" << this << endl;
		cout << endl;
		other.size = 0;
		other.data = NULL;
	}

	/// 5. move assigment operator
	Data& operator=(Data&& rhs) noexcept {
		cout << "move assigment:" << this << endl;
		cout << endl;
		if (this != &rhs) {
			freeRes();
			size = rhs.size;
			data = rhs.data;
			rhs.size = 0;
			rhs.data = NULL;
		}
		return *this;
	}

	/// 1. destructor
	~Data() {
		cout << "destructor:" << this << endl;
		cout << endl;
		freeRes();
	}
private:
	void freeRes() {
		delete[] data;
	}

	void cloneRes(const Data &other) {
		size = other.size;
		data = new int[size];
	}

	int size;
	int* data;
};

void funcVal(const Data data) {
	cout << __func__ << ":" << &data << endl;
	cout << endl;
}

void funcRef(const Data &data) {
	cout << __func__ << ":" << &data << endl;
	cout << endl;
}

void funcMove(const Data&& data) {
	cout << __func__ << ":" << &data << endl;
	cout << endl;
}

class Node {
public:
	int val;
	Node* left;
	Node* right;

	Node() {}

	Node(int _val) {
		val = _val;
		left = NULL;
		right = NULL;
	}

	Node(int _val, Node* _left, Node* _right) {
		val = _val;
		left = _left;
		right = _right;
	}
};

class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		return solve(matrix, 0, matrix[0].size(), target);
	}

	/// dry run
	///
	/// [[-1], [-1]], row_size=2, col_size=1
	///
	/// > solve(matrix, 0, 1, 0) - c_row=0, col_size=1, target=0
	///   check - 0 >= 1 || 1 < 1 -- false
	///   check - pos = binSearch(matrix[0], 0, 0, 0)
	///                 > pos=-1
	///           pos=-1
	///   call - solve(matrix, 1, 1, 0)
	///   call - solve(matrix, 2, 1, 0)

	bool solve(vector<vector<int>>& matrix, int c_row, int col_size, int target) {
		if (c_row >= matrix.size() || col_size > matrix[0].size() || col_size < 1)
			return false;
		else {
			if (int pos = binSearch(matrix[c_row], 0, col_size - 1, target); pos >= 0)
				return true;
			else
				return solve(matrix, c_row + 1, min(-pos, (int)matrix.size()), target);
		}
	}

	int binSearch(vector<int>& nums, int lo, int hi, int target) {
			if (lo <= hi) {
				int mid = lo + (hi - lo) / 2;
				if (target > nums[mid]) {
					return binSearch(nums, mid + 1, hi, target);
				}
				else if (target < nums[mid]) {
					return binSearch(nums, lo, mid - 1, target);
				}
				else {
					return mid;
				}
			}
		return -(lo + 1);
	}
};

int factorial_non_tail_r(int n) {
	if (n <= 0) return 0;
	if (n == 1) return 1;
	return n*factorial_non_tail_r(n - 1);
}

int factorial_tail_r(int n, int cur_ans=1) {
	if (n <= 0) return 0;
	if (n == 1) return cur_ans;
	return factorial_tail_r(n - 1, cur_ans*n);
}

int main()
{
	cout << factorial_non_tail_r(5) << endl;
	cout << factorial_tail_r(5) << endl;
/*
	/// 1. pass an instance into a container 
	///    a. pass by value
	///    b. pass by move
	///    c. pass by reference
	Data tmpA;
	funcVal(tmpA);
	funcRef(tmpA);
	funcMove(move(tmpA));

	/// 2. retrieve a class from a container - move
	///    a. retrieve by value
	///    b. retrieve by move
	///    c. retrieve by reference
*/
}

