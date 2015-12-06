#include "xml-parser.h"

void parseXml(const char *argFileName)
{
	std::ifstream file;
	file.open("data/test-file", std::ifstream::in | std::ifstream::out);
	char dummy[256];
	file.get(&dummy[0], 256);
	for (int i = 0; i < 256; i++)
	{
		if (dummy[i] == '\0') break;
		std::cout << dummy[i];
	}
	rapidxml::xml_document<> doc;
	//doc.parse<0>
}
