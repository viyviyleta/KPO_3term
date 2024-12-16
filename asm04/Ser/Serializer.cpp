#include "Serializer.h"

void Serializer::Serialize(std::ofstream& wr, int val) {
	auto curpos = wr.tellp();
	std::uint8_t intP = 0x01;
	wr.write(reinterpret_cast<const char*>(&intP), 1);
	wr.write(reinterpret_cast<const char*>(&val), sizeof(val));
}

void Serializer::Serialize(std::ofstream& wr, unsigned int val) {
	auto curpos = wr.tellp();
	std::uint8_t intP = 0x02;
	wr.write(reinterpret_cast<const char*>(&intP), 1);
	wr.write(reinterpret_cast<const char*>(&val), sizeof(val));
}
