#include <string.h>
#include <iostream>
#include "Big_Number.h"

//using namespace std;

int main() {
	char *num = (char *)malloc(20);
	strcpy(num, "765656");
	BIG_NUMBER n1(num);
	cout << n1;
	return 0;
}
