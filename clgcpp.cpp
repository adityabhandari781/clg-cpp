
// q1
int electricityBill()
{
	int units;
	cout << "enter no of units used";
	cin >> units;

	float cost = 50.00;
	if (units < 0)
		cost = 0;
	else if (units <= 100)
		cost += 1.50 * units;
	else if (units <= 200)
		cost += 1.80 * units;
	else
		cost += 2.50 * units;

	if (cost >= 300.00)
		cost += cost * 15 / 100;
	return units;
}


// q2
class Student
{
	static int rollNo;
	char name[25];
	int test1, test2, test3;

public:
	void inputData();
	int avgMarks();
	void display();
};

int main()
{
	Student s[4]{};
	s[0].inputData();
}

int Student::rollNo = 0;

void Student::inputData()
{
	cout << "input roll number: ";
	cin >> rollNo;

	cout << "input name: ";
	cin >> name;

	cout << "input marks of test1: ";
	cin >> test1;

	cout << "input marks of test2: ";
	cin >> test2;

	cout << "input marks of test3: ";
	cin >> test3;
}

int Student::avgMarks()
{
	int min1 = min(test1, min(test2, test3));
	int totalMarks = test1 + test2 + test3 - min1;
	int avg = totalMarks / 2;
	return avg;
}

void Student::display()
{
	cout << "\n roll number: " << rollNo;
	cout << "\n name: " << name;
	cout << "\n marks of test1: " << test1;
	cout << "\n marks of test2: " << test2;
	cout << "\n marks of test3: " << test3;
}


// q3
class ShoppingList
{
	int codeNo;
	string name;
	vector<string> itemNames;
	vector<int> quantities;
	vector<int> prices;

public:
	ShoppingList(int codeNo_, string name_) : codeNo(codeNo_), name(name_) {};

	void addItem();
	void delItem();
	void print();
};

void ShoppingList::addItem()
{
	cout << "enter item name: ";
	string item;
	cin >> item;
	itemNames.push_back(item);

	cout << "enter number of items: ";
	int num;
	cin >> num;
	quantities.push_back(num);

	cout << "enter price of item: ";
	int price;
	cin >> price;
	prices.push_back(price);
	cout << '\n';
}

void ShoppingList::delItem()
{
	cout << "enter the name of the item to be deleted: ";
	string item;
	cin >> item;
	for (int i = 0; i < itemNames.size(); i++)
		if (itemNames[i] == item) {
			itemNames.erase(itemNames.begin() + i);
			quantities.erase(quantities.begin() + i);
			prices.erase(prices.begin() + i);
			return;
		}
	cout << "item not found\n";
}

void ShoppingList::print()
{
	cout << "code number: " << codeNo << endl;
	cout << "name: " << name << endl << endl;
	cout << "Item name\tQuantity\tPrice\n";
	int total{};
	for (int i = 0; i < itemNames.size(); i++) {
		cout << itemNames[i] << "\t\t" << quantities[i] << "\t\t" << prices[i] << '\n';
		total += quantities[i] * prices[i];
	}
	cout << '\n';

	cout << "The total price of the order is: " << total;
}


// q4
class Polynomial
{
	vector<int> coeffs; // here the ith index corresponds to the (coeffs.size() - i)th exponent

public:
	Polynomial(vector<int> arr) :coeffs(arr) {};

	Polynomial operator+(Polynomial p);
	void operator=(Polynomial p);
	Polynomial operator*(Polynomial p);

	friend istream& operator>>(istream& in, Polynomial& poly)
	{
		int termCount;
		cout << "Enter the number of terms in the polynomial: ";
		in >> termCount;
		poly.coeffs.resize(termCount);

		cout << "Enter coefficients from highest exponent to lowest:" << endl;
		for (int i = 0; i < termCount; i++)
			in >> poly.coeffs[i];
		return in;
	}

	friend ostream& operator<<(ostream& out, Polynomial& poly)
	{
		out << "Polynomial: ";
		int exponent = poly.coeffs.size() - 1;
		for (int i = 0; i < poly.coeffs.size(); ++i, exponent--)
			if (poly.coeffs[i] != 0) {
				if (!exponent)
					out << poly.coeffs[i];
				else if (exponent == 1)
					out << poly.coeffs[i] << "x";
				else
					out << poly.coeffs[i] << "x^" << exponent;
			
				if (i != poly.coeffs.size() - 1 && poly.coeffs[i + 1] >= 0)
					out << " + ";
			}

		out << endl;
		return out;
	}
	int compute(int x);
};

Polynomial Polynomial::operator+(Polynomial p)
{
	if (coeffs.size() < p.coeffs.size())
		swap(coeffs, p.coeffs);
	Polynomial ans(coeffs);
	for (int i = p.coeffs.size() - 1; i >= 0; i--)
		ans.coeffs[i] += p.coeffs[i];
	return ans;
}

void Polynomial::operator=(Polynomial p)
{
	coeffs = p.coeffs;
}

Polynomial Polynomial::operator*(Polynomial p)
{
	if (coeffs.size() < p.coeffs.size())
		swap(coeffs, p.coeffs);
	Polynomial ans({});
	ans.coeffs.resize(coeffs.size() + p.coeffs.size() - 1);
	for (int i = 0; i < coeffs.size(); i++)
		for (int j = 0; j < p.coeffs.size(); j++)
			ans.coeffs[i + j] += coeffs[i] * p.coeffs[j];
	return ans;
}

int Polynomial::compute(int x)
{
	int ans = 0;
	for (int i = 0; i < coeffs.size(); i++)
		ans += coeffs[i] * pow(x, coeffs.size() - i - 1);
	return ans;
}


// q5
class Shape
{
public:
	virtual void readDimensions() {}
	virtual void computeArea() {}
};

class Circle : public Shape
{
	double radius;
	double area;

public:
	Circle() : radius(0), area(0) {}
	void readDimensions() override
	{
		cout << "Enter the radius of the circle: ";
		cin >> radius;
	}
	void computeArea() override
	{
		area = 3.14 * radius * radius;
	}
	void displayResults()
	{
		cout << "Circle - Radius: " << radius << ", Area: " << area << endl;
	}
};

class Rectangle : public Shape
{
	double length;
	double width;
	double area;

public:
	Rectangle() : length(0), width(0), area(0) {}
	void readDimensions() override
	{
		cout << "Enter the length of the rectangle: ";
		cin >> length;
		cout << "Enter the width of the rectangle: ";
		cin >> width;
	}
	void computeArea() override
	{
		area = length * width;
	}
	void displayResults()
	{
		cout << "Rectangle - Length: " << length << ", Width: " << width << ", Area: " << area << endl;
	}
};

class Square : public Shape
{
	double side;
	double area;

public:
	Square() : side(0), area(0) {}
	void readDimensions() override
	{
		cout << "Enter the side length of the square: ";
		cin >> side;
	}
	void computeArea() override
	{
		area = side * side;
	}
	void displayResults()
	{
		cout << "Square - Side: " << side << ", Area: " << area << endl;
	}
};


// q6
template <class T>
class GenericQueue
{
	T* arr;
	int front;
	int rear;
	int size;

public:

	GenericQueue(int size) : front(-1), rear(-1), size(size)
	{
		arr = new T[size];
	}
	void push(T val)
	{
		if (front == 0 && rear == size - 1 || rear == (front - 1) % (size - 1)) {
			cout << "queue is full!";
			return;
		}

		if (front == -1)
			front = 0;
		else if (rear == size - 1 && front != 0)
			rear = 0;
		else
			rear++;

		arr[rear] = val;
	}
	T pop()
	{
		if (front == -1) {
			cout << "queue is empty!";
			return INT_MIN;
		}

		T val = arr[front];
		if (front == rear)
			front = rear = -1;
		else if (front == size - 1)
			front = 0;
		else
			front++;

		return val;
	}
	void print()
	{
		if (front == -1) {
			cout << "queue is empty!";
			return;
		}

		if (rear >= front)
			for (int i = front; i <= rear; i++)
				cout << arr[i] << ' ';

		else {
			for (int i = front; i < size; i++)
				cout << arr[i] << ' ';

			for (int i = 0; i <= rear; i++)
				cout << arr[i] << ' ';
		}
	}
};


// q7
int q7()
{
	int size;
	cout << "enter size of vector: ";
	cin >> size;

	vector<int> v;
	while (size--) {
		int val;
		cout << "enter value: ";
		cin >> val;
		v.push_back(val);
	}

	list<int> myList(v.begin(), v.end());
	myList.sort();

	vector<int> lessThanTenVector;
	for (int val : myList)
		if (val < 10)
			lessThanTenVector.push_back(val);
		else
			break;

	cout << "\nOriginal Vector: ";
	for (int val : v)
		cout << val << ' ';
	
	cout << "\nSorted List: ";
	for (int val : myList)
		cout << val << ' ';

	cout << "\nSelected items less than 10: ";
	for (int val : lessThanTenVector)
		cout << val << ' ';

	return 0;
}


// q8
template<class T>
int searchElement(T arr[], int size, T key)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == key)
			return i;
	return -1;
}

int q8()
{
	int intArr[] = { 10, 20, 30, 40, 50 };
	int intKey = 30;

	int intResult = searchElement(intArr, 5, intKey);
	if (intResult != -1) 
		cout << "Integer Key found at index: " << intResult << endl;
	else 
		cout << "Integer Key not found" << endl;
	

	char charArr[] = { 'a','b','c','d','e' };
	char charKey = 'c';

	int charResult = searchElement(charArr, 5, charKey);
	if (charResult != -1) 
		cout << "Character Key found at index: " << charResult << endl;
	else 
		cout << "Character Key not found" << endl;
	

	double doubleArr[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	double doubleKey = 3.3;

	int doubleResult = searchElement(doubleArr, 5, doubleKey);
	if (doubleResult != -1) 
		cout << "Double Key found at index: " << doubleResult << endl;
	else 
		cout << "Double Key not found" << endl;
	return 0;
}
