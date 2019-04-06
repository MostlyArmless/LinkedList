//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"
#include "linkedList.h"

namespace LinkedListTesting {
	using IntList = SinglyLinkedList<int>;
	using IntListPtr = std::unique_ptr<IntList>;
	
	using IntNode = SinglyLinkedListNode<int>;
	using IntNodePtr = std::unique_ptr<IntNode>;
}