// Code by : Masood Firoozabadi
// Numbers are stored reversed !

#include <ostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

typedef unsigned int my_type; // this type will be used as the type of the array elements

#define LEN 1000 // length of the array

class BIG_NUMBER {
private:
	my_type num[LEN];
	char sign;
	int len;
	
	void char_to_BIG (char*);
	BIG_NUMBER cmpl9 (int);
	BIG_NUMBER cmpl10 (int);
	void do_carry ();
	
public:
	BIG_NUMBER (); // default constructor
	BIG_NUMBER (char*); // parameterized constructor
	BIG_NUMBER (int); // parameterized constructor
	BIG_NUMBER (const BIG_NUMBER&); // copy constructor
	BIG_NUMBER abs ();
	BIG_NUMBER& operator= (const BIG_NUMBER&); // assignment operator
	friend ostream& operator<< (ostream&, const BIG_NUMBER&);
	bool operator< (BIG_NUMBER);
	bool operator< (int);
	bool operator> (BIG_NUMBER);
	bool operator> (int);
	bool operator== (BIG_NUMBER);
	bool operator== (int);
	bool operator<= (BIG_NUMBER);
	bool operator<= (int);
	bool operator>= (BIG_NUMBER);
	bool operator>= (int);
	BIG_NUMBER operator+ (BIG_NUMBER);
	BIG_NUMBER operator+ (int);
	BIG_NUMBER operator- (BIG_NUMBER);
	BIG_NUMBER operator- (int);
	BIG_NUMBER operator* (BIG_NUMBER);
	BIG_NUMBER operator* (int);
	BIG_NUMBER operator/ (BIG_NUMBER);
	BIG_NUMBER operator/ (int);
	BIG_NUMBER operator% (BIG_NUMBER);
	BIG_NUMBER operator% (int);
	void operator+= (BIG_NUMBER);
	void operator+= (int);
	void operator-= (BIG_NUMBER);
	void operator-= (int);
	void operator*= (BIG_NUMBER);
	void operator*= (int);
	void operator/= (BIG_NUMBER);
	void operator/= (int);
	void operator%= (BIG_NUMBER);
	void operator%= (int);
};
