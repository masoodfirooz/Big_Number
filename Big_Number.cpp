// Code by : Masood Firoozabadi
// Numbers are stored reversed !

#include "Big_Number.h"

#define L (numeric_limits<my_type>::digits10) // maximum number of digits stored in one element of the array
#define B ((int) pow ((double) 10, (double)(int) L)) // base
#define max(x,y) (((x)>(y))?(x):(y))

BIG_NUMBER::BIG_NUMBER () {
	for (int i = 0; i < LEN; i++)
		num[i] = 0;
	sign = '+';
	len = 1;
}

BIG_NUMBER::BIG_NUMBER (char* s) {
	char_to_BIG (s);
}

// !!!
BIG_NUMBER::BIG_NUMBER (int n) {
	if (n < 0) {
		n *= -1;
		sign = '-';
	}
	char s[L];
	s[0] = '\0';
	for (int i = 0; n; i++) {
		char c[10];
		c[0] = n % 10 + '0';
		c[1] = '\0';
		strcat (s, c);
		n /= 10;
	}
	int l = strlen (s);
	for (int i = 0; i < l / 2; i++) {
		char c = s[i];
		s[i] = s[l - i - 1];
		s[l - i - 1] = c;
	}
	char_to_BIG (s);
}

BIG_NUMBER::BIG_NUMBER (const BIG_NUMBER& bn) {
	for (int i = 0; i < LEN; i++)
		num[i] = 0;
	for (int i = 0; i < bn.len; i++) {
		this->num[i] = bn.num[i];
	}
	this->sign = bn.sign;
	this->len = bn.len;
}

BIG_NUMBER BIG_NUMBER::abs () {
	BIG_NUMBER out = *this;
	out.sign = '+';
	return out;
}

BIG_NUMBER& BIG_NUMBER::operator= (const BIG_NUMBER& bn) {
	for (int i = 0; i < LEN; i++)
		num[i] = 0;
	for (int i = 0; i < bn.len; i++) {
		this->num[i] = bn.num[i];
	}
	this->sign = bn.sign;
	this->len = bn.len;
	return *this;
}

void BIG_NUMBER::char_to_BIG (char* s) {
	sign = ((s[0] == '-') ? '-' : '+');
	s += (s[0] == '-' || s[0] == '+') ? 1 : 0;
	for (int i = 0; i < LEN; i++)
		num[i] = 0;
	len = strlen (s);
	for (int i = 0;i <= (len - 1) / L; i++)
		for (int j = 0; j < L; j++)
			if (len - (i + 1) * L + j >= 0)
				num[i] = 10 * num[i] + s[len - (i + 1) * L + j] - '0';
	len = (len - 1) / L + 1;
}

BIG_NUMBER BIG_NUMBER::cmpl9 (int l) {
	BIG_NUMBER out ((char*) "0");
	out.len = l;
	int m = B - 1;
	for (int i = 0; i < l; i++)
		out.num[i] = m - num[i];
	return out;
}

BIG_NUMBER BIG_NUMBER::cmpl10 (int l) {
	BIG_NUMBER out ((char*)"0");
	BIG_NUMBER one ((char*)"1");
	out = (*this).cmpl9 (l) + one;
	return out;
}

void BIG_NUMBER::do_carry () {
	for (int i = 0; i < len; i++) {
		num[i + 1] += num[i] / B;
		num[i] %= B;
		if (num[len] != 0)
			len++;
	}
}

ostream& operator<< (ostream& out, const BIG_NUMBER& bn) {
	if ((bn.sign == '-' && bn.num[bn.len - 1] != 0))
		out << "-";
	out << bn.num[bn.len - 1];
	for (int i = bn.len - 2; i >= 0; i--) {
		out << setfill ('0');
		out << setw(L) << bn.num[i];
	}
	
	return out;
}

bool BIG_NUMBER::operator< (BIG_NUMBER bn) {
	if (this->sign == '+' && bn.sign == '-')
		return false;
	if (this->sign == '-' && bn.sign == '+')
		return true;
	int i = max (this->len, bn.len);
	while (this->num[i] == bn.num[i] && i >= 0)
		i--;
	if (i < 0)
		return false;
	if (this->sign == '+')
		return this->num[i] < bn.num[i];
	else
		return this->num[i] > bn.num[i];
}

bool BIG_NUMBER::operator< (int n) {
	char s[LEN];
	int l = 0;
	while(n != 0)
	{
		s[l++] = (n % 10) + '0';
		n /= 10;
	}
	s[l] = '\0';
	BIG_NUMBER tn (s);
	return (*this < tn);
}

bool operator< (int n, BIG_NUMBER bn) {
	return !(bn >= n);
}

bool BIG_NUMBER::operator> (BIG_NUMBER bn) {
	if (this->sign == '+' && bn.sign == '-')
		return true;
	if (this->sign == '-' && bn.sign == '+')
		return false;
	int i = max(this->len, bn.len);
	while(this->num[i] == bn.num[i] && i >= 0)
		i--;
	if (i < 0)
		return false;
	if (this->sign == '+')
		return this->num[i] > bn.num[i];
	else
		return this->num[i] < bn.num[i];
}

bool BIG_NUMBER::operator> (int n) {
	char s[LEN];
	int l = 0;
	while (n != 0) {
		s[l++] = (n % 10) + '0';
		n /= 10;
	}
	s[l] = '\0';
	BIG_NUMBER tn (s);
	return (*this > tn);
}

bool operator> (int n, BIG_NUMBER bn) {
	return !(bn <= n);
}

bool BIG_NUMBER::operator== (BIG_NUMBER bn) {
	return !(*this < bn || bn < *this);
}

bool BIG_NUMBER::operator== (int n) {
	char s[LEN];
	int l = 0;
	while(n != 0) {
		s[l++] = (n % 10) + '0';
		n /= 10;
	}
	s[l] = '\0';
	BIG_NUMBER tn (s);
	return !(*this < tn || tn < *this);
}

bool operator== (int n, BIG_NUMBER bn) {
	return (bn == n);
}

bool BIG_NUMBER::operator<= (BIG_NUMBER bn) {
	return (*this < bn) || (*this == bn);
}

bool BIG_NUMBER::operator<= (int n) {
	char s[LEN];
	int l = 0;
	while (n != 0) {
		s[l++] = (n % 10) + '0';
		n /= 10;
	}
	s[l] = '\0';
	BIG_NUMBER tn (s);
	return (*this < tn || *this == tn);
}

bool operator<= (int n, BIG_NUMBER bn) {
	return !(bn > n);
}

bool BIG_NUMBER::operator>= (BIG_NUMBER bn) {
	return (*this > bn) || (*this == bn);
}

bool BIG_NUMBER::operator >= (int n) {
	char s[LEN];
	int l = 0;
	while (n != 0) {
		s[l++] = (n % 10) + '0';
		n /= 10;
	}
	s[l] = '\0';
	BIG_NUMBER tn (s);
	return (*this > tn) || (*this == tn);
}

bool operator>= (int n, BIG_NUMBER bn) {
	return !(bn <= n);
}

BIG_NUMBER BIG_NUMBER::operator+ (BIG_NUMBER bn) {
	if (this->sign == bn.sign) {
		BIG_NUMBER out ((char*) "0");
		int m = max(this->len, bn.len);
		for (int i = 0; i < m; i++) {
			int plus = this->num[i] + bn.num[i];
			out.num[i + 1] += plus / B;
			out.num[i] += plus % B;
		}
		out.do_carry ();
		out.sign = this->sign;
		return out;
	}
	else
		return ((this->sign == '-') ? bn - this->abs () : *this - bn.abs ());
}

BIG_NUMBER BIG_NUMBER::operator+ (int n) {
	this->num[0] += n;
	do_carry ();
	return *this;
}

BIG_NUMBER operator+ (int n, BIG_NUMBER bn) {
	return (bn + n);
}

BIG_NUMBER BIG_NUMBER::operator- (BIG_NUMBER bn) {
	if (this->sign == bn.sign) {
		if (this->sign == '-')
			return *this + bn.abs ();
		BIG_NUMBER out ((char*) "0");
		if(*this == bn)
			return out;
		if(*this < bn) {
			out = bn - *this;
			out.sign = '-';
			return out;
		}
		if(*this > bn) {
			out.sign = '+';
			int m = max (this->len, bn.len);
			out = *this + bn.cmpl10 (m);
			out.num[out.len - 1] = 0;
			while (out.num[out.len - 1] == 0)
				out.len--;
			return out;
		}
	}
	else {
		bn.sign = this->sign;
		return *this + bn;
	}
	return *this; // to rectify a warning.
}

BIG_NUMBER BIG_NUMBER::operator- (int n) {
	BIG_NUMBER tn (n);
	return *this - tn;
}

BIG_NUMBER operator- (int n, BIG_NUMBER bn) {
	BIG_NUMBER tn (n);
	return n - bn;
}

BIG_NUMBER BIG_NUMBER::operator* (BIG_NUMBER bn) {
	BIG_NUMBER out ((char*) "0");
	out.sign = ((this->sign == bn.sign) ? '+' : '-');
	for (int i = 0; i < this->len; i++)
		for (int j = 0; j < bn.len; j++)
			out.num[i + j] += this->num[i] * bn.num[j];
	out.do_carry ();
	return out;
}

BIG_NUMBER BIG_NUMBER::operator* (int n) {
	for (int i = 0; i < this->len; i++)
		this->num[i] *= n;
	do_carry ();
	return *this;
}

BIG_NUMBER operator* (int n, BIG_NUMBER bn) {
	return (bn * n);
}

BIG_NUMBER BIG_NUMBER::operator/ (BIG_NUMBER bn) {
	BIG_NUMBER tn1 ((char*) "0");
	BIG_NUMBER tn2 ((char*) "0");
	BIG_NUMBER out ((char*) "0");
	while (*this >= bn) {
		int t = 0;
		while (tn1 < bn) {
			tn1 = tn1 * B;
			tn1 = tn1 + this->num[this->len - t];
			t++;
		}
		tn2 = bn;
		t = 1;
		while (tn2 <= tn1) {
			t++;
			tn2 = tn2 + bn;
		}
		t--;
		tn2 = tn2 - bn;
		for (int i = 0; i < this->len - tn1.len; i++)
			tn2 = tn2 * B;
		*this = *this - tn2;
		out = out * B;
		out = out + t;
	}
	return out;
}

BIG_NUMBER BIG_NUMBER::operator/ (int n) {
	BIG_NUMBER tn (n);
	return *this / tn;
}

BIG_NUMBER operator/ (int n, BIG_NUMBER bn) {
	BIG_NUMBER tn (n);
	return (tn / bn);
}

BIG_NUMBER BIG_NUMBER::operator% (BIG_NUMBER bn) {
	return *this - (*this / bn) * bn;
}

BIG_NUMBER BIG_NUMBER::operator% (int n) {
	return *this - (*this / n) * n;
}
