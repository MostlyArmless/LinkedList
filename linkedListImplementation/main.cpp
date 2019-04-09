#include "pch.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "LinkedList.h"

int main(int argc, char* argv[])
{	
	// Populate linked list from file
	auto importFile = std::experimental::filesystem::path(argv[1]);
	std::cout << "Filename:\n" << importFile << std::endl;

	std::ifstream inStream(importFile);
	auto list = SinglyLinkedList<int>();
	try {
		std::string line;
		int lineNumber = 1;
		while (std::getline(inStream, line)) {
			list.PushTail(std::stoi(line));
			std::cout << "List length = " << list.GetLength() << std::endl;
			list.PrintList();
			std::cout << std::endl;
		}
	}
	catch (const std::exception&) {
		throw "Problem reading file.";
		inStream.close();
	}
	inStream.close();

	std::cout << "Printing contents of linked list:" << std::endl;
	list.PrintList();

	std::cout << "Done." << std::endl;

	return 0;
}