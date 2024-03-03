#include <vector>
#include <iostream>
#include "Protobuf.hpp"

// To compile and run: `g++ example.cpp -o example && ./example`

void Dump(const char* data, size_t length)
{
	for (size_t i = 0; i < length; i++) {
		uint8_t c = (uint8_t)data[i];
		const char* chrmp = "0123456789ABCDEF";
		std::cout << chrmp[c >> 4] << chrmp[c & 0xF] << ' ';
	}
}

void Dump(const std::vector<uint8_t>& v)
{
	for (auto c : v) {
		const char* chrmp = "0123456789ABCDEF";
		std::cout << chrmp[c >> 4] << chrmp[c & 0xF] << ' ';
	}
}

const char g_data[] = "\x0A\x0C\x48\x65\x6C\x6C\x6F\x2C\x20\x77\x6F\x72\x6C\x64";
size_t g_dataSize = sizeof(g_data) - 1;

int main()
{
	Protobuf::ObjectBaseMessage* pObj = new Protobuf::ObjectBaseMessage();
	
	// Decode the message.
	Protobuf::DecodeBlock(g_data, g_dataSize, pObj);
	
	// Encode the message.
	std::vector<uint8_t> data;
	pObj->Encode(data);
	
	// Print out the original and the new data.
	std::cout << "Original data: ";
	Dump(g_data, g_dataSize);
	
	std::cout << "\nEncoded data:  ";
	Dump(data);
	
	std::cout << "\n";
	
	//Original data: 0A 0C 48 65 6C 6C 6F 2C 20 77 6F 72 6C 64
    //Encoded data:  0A 0C 48 65 6C 6C 6F 2C 20 77 6F 72 6C 64
	
	return 0;
}
