#include "pch.h"
#include <iostream>
#include "LinkedList.h"

int main()
{	
	std::unique_ptr<SinglyLinkedList<int>> list = std::make_unique<SinglyLinkedList<int>>(0);
	std::unique_ptr<SinglyLinkedList<int>> list2 = std::make_unique<SinglyLinkedList<int>>(0);

	bool equal = list == list2;
}