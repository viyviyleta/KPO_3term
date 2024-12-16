#include "Deserializer.h"
#include <string>

vector<pair<int, char*>> Deserializer::Deserialize(ifstream& rd) {
	vector<pair<int, char*>> des;
	int val1;
	int len = 0;
	unsigned int val2;
	char firstByte;
	int counter = 0;
	rd.read(&firstByte, 1);
	int type = static_cast<int>(static_cast<unsigned char>(firstByte));
	ofstream wr("..\\asm4\\asm.asm");
	if (rd)
	{
		wr << HEADER;
		while (rd)
		{
			switch (type)
			{
			case 0x01:
				rd.read(reinterpret_cast<char*>(&val1), sizeof(val1));
				des.push_back(make_pair(val1, (char*)NULL));
				wr << "INT";
				wr << counter;
				wr << "\tSDWORD\t";
				wr << val1;
				wr << "\n";
				break;
			case 0x02:
				rd.read(reinterpret_cast<char*>(&val2), sizeof(val2));
				des.push_back(make_pair(val2, (char*)NULL));
				wr << "UNSIGNEDINT";
				wr << counter;
				wr << "\t" << "DWORD" << "\t";
				wr << val2;
				wr << "\n";
				break;
			}
			rd.read(&firstByte, 1);
			type = static_cast<int>(static_cast<unsigned char>(firstByte));
			counter++;
		}
	}
	wr << FOOTER;
	wr.close();
	return des;
}