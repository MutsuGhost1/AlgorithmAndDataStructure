#include <iostream>

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

int main()
{
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
}

