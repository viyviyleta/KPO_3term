#include <iostream>
#include "Serializer.h"

using namespace std;

int main() {
	int val1;
	cin >> val1;
	unsigned int val2;
	cin >> val2;
	ofstream wr;
	wr.open("ser.bin");
	Serializer::Serialize(wr, val1);
	Serializer::Serialize(wr, val2);
	wr.close();
}