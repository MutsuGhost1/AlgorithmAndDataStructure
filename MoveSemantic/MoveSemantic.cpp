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


class Solution {
public:
	vector<int> sortArray(vector<int>& nums) {
		quickSort(nums, 0, nums.size()-1);
		return nums;
	}

	/// two pointer
	int partition(vector<int>& nums, int s, int e) {
/*
		int j = s, pi = e;
		for (int i = s; i < e; i++)
			if (nums[i] > nums[pi])
				swap(nums[i], nums[j++]);
		swap(nums[j], nums[pi]);
		return j;
*/
		cout << __func__ << endl;
		for (auto num : nums)
			cout << num << " ";
		cout << endl;
		int l = s, r = e, pivot = nums[s];
		while (l < r) {
			while (nums[l] < pivot) l++;
			while (nums[r] > pivot) r--;
			if (l < r) swap(nums[l++], nums[r--]);
		}
		for (auto num : nums)
			cout << num << " ";
		cout << endl;
		cout << "pivot:" << pivot << " l=" << l << endl;
		return l;
	}

	void quickSort(vector<int>& nums, int s, int e) {
		/// s == e means it's sorted, we needn't do anything
		if (s < e) {
			int p = partition(nums, s, e);
			quickSort(nums, s, p-1);
			quickSort(nums, p + 1, e);
		}
	}

	void mergeSortR(vector<int>& nums, int s, int e) {
		if (s >= e)
			return;
		else {
			int m = s + (e - s) / 2;
			mergeSortR(nums, s, m);
			mergeSortR(nums, m + 1, e);
			mergeTwo(nums, s, m, e);
		}
	}

	/// s 
	/// 0 1 2
	void mergeSortI(vector<int>& nums) {
		int len = nums.size();
		for (int seg = 1; seg < len; seg += seg)
			for (int start = 0; start < len; start += 2 * seg) {
				mergeTwo(nums, start, min(start + seg, len-1), min(start + 2 * seg, len-1));
			}
	}

	void mergeTwo(vector<int>& nums, int s, int m, int e) {
		if (m + 1 > e) return;

		int left = 0, right = 0;
		vector<int> l(nums.begin() + s, nums.begin() + m + 1);
		vector<int> r(nums.begin() + m + 1, nums.begin() + e + 1);
		l.push_back(INT_MAX);
		r.push_back(INT_MAX);
		for (int i = s; i <= e; i++)
			if (l[left] < r[right])
				nums[i] = l[left++];
			else
				nums[i] = r[right++];

		/*
				while(left<l.size() && right<r.size())
					if(l[left] < r[right])
						nums[start++] = l[left++];
					else
						nums[start++] = r[right++];
				while(left<l.size())
					nums[start++] = l[left++];
				while(right<r.size())
					nums[start++] = r[right++];
		*/
	}
};

int main()
{
	Solution s;
	vector<int> data = { -2,3,-5 };
	s.sortArray(data);

	for (auto i : data)
		cout << i << " ";
	cout << endl;
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

