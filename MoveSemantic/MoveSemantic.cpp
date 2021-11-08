#include <iostream>
#include <algorithm>
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

vector<vector<int>> mergeTwo(vector<vector<int>>& s1, vector<vector<int>>& s2) {
	vector<vector<int>> s;
	int left = 0, right = 0, lh = 0, rh = 0;
	while (left < s1.size() && right < s2.size()) {
		if (s1[left][0] < s2[right][0]) {
			if (0 == s1[left][1]) {
				if (rh < lh) {
					s.push_back({ s1[left][0], rh });
				}
			}
			else {
				if (s1[left][1] > rh) {
					s.push_back(s1[left]);
				}
			}
			lh = s1[left][1];
			left++;
		}
		else {
			if (0 == s2[right][1]) {
				if (rh > lh) {
					s.push_back({ s2[right][0], lh });
				}
			}
			else {
				if (s2[right][1] > lh) {
					s.push_back(s2[right]);
				}
			}
			rh = s2[right][1];
			right++;
		}
	}
	while (left < s1.size())
		s.push_back(s1[left++]);
	while (right < s2.size())
		s.push_back(s2[right++]);
	return s;
}


class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		/// since C99, it allows VLA in stack
		int sum[4];

		///   sum = [0, 0, 0, 0]
		///    0  1  2  3
		/// 0 [2]           t[0].size()=1
		/// 1 [3][4]        t[1].size()=2
		/// 2 [6][5][7]     t[2].size()=3
		/// 3 [4][1][8][3]  t[3].size()=4
		///
		///
		/// dry run
		///
		memset(&sum, 0, sizeof(int) * triangle.size());
		for (int i = 0; i < triangle.size(); i++)
			for (int j = triangle[i].size() - 1; j >= 0; j--) {
				cout << i - 1 << " " << j - 1 << endl;
				int a = i - 1 >= 0 ? triangle[i - 1][j] : INT_MAX;
				int b = (i - 1 >= 0 && j - 1 >= 0) ? triangle[i - 1][j - 1] : INT_MAX;
				//int a=0, b=0;
				sum[j] += min(a, b);
			}
		for (auto i : sum)
			cout << i << " " << endl;
		return *min_element(sum, sum + triangle.size());
	}
};

int main()
{
	Solution ds;
	vector<vector<int>> data = { {2}, {3,4}, {6,5,7}, {4,1,8,3} };
	ds.minimumTotal(data);

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

