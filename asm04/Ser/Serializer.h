#pragma once
#include <fstream>

class Serializer {
public:
	static void Serialize(std::ofstream& wr, int val);
	static void Serialize(std::ofstream& wr, unsigned int val);
};