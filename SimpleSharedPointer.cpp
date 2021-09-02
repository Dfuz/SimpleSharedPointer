#include "SimpleSharedPointer.h"
#include <memory>
using namespace std;

int main()
{
	{
		cout << "********** FIRST TEST *************" << endl;
		double value{ 13.3 };
		SharedPointer<double> ptr1(value);
		auto ptr2 = ptr1;
		cout << "ptr1.count = " << ptr1.getCount() << '\n'
			 << "ptr2.count = " << ptr2.getCount() << endl;
	}
	cout << endl;
	{
		cout << "********** SECOND TEST *************" << endl;
		SharedPointer<double> ptr1(new double(13.5));
		SharedPointer<double>* ptr2 = new SharedPointer<double>(ptr1);
		cout << "ptr1.count = " << ptr1.getCount() << '\n'
			 << "ptr2.count = " << ptr2->getCount() << endl;
		delete ptr2;
	}
	return 0;
}
