#pragma once
#include <iostream>

template <typename DataType>
class SinglyLinkedListNode {
	using Node = SinglyLinkedListNode<DataType>;
	using NodePtr = std::shared_ptr<Node>;
public:
	SinglyLinkedListNode(DataType data) :
		next(nullptr),
		data(data)
	{
	}

	DataType data;
	NodePtr next;
};

template <typename DataType>
class SinglyLinkedList {
	using Node = SinglyLinkedListNode<DataType>;
using NodePtr = std::shared_ptr<Node>;
//typedef std::shared_ptr<SinglyLinkedListNode<DataType>> NodePtr;

public:
	SinglyLinkedList(DataType data) :
		head(std::make_shared<Node>(data)),
		tail(head)
	{
	};

	~SinglyLinkedList() {};

	NodePtr GetTail() {
		return tail;
	}

	NodePtr GetHead() {
		return head;
	}

	int GetLength() {
		if (!head) {
			return 0;
		}

		auto node = head;
		int length = 1;
		while (node->next) {
			node = node->next;
			length++;
		}
		return length;
	}

	NodePtr PushTail(DataType newData) {
		if (head) {
			tail->next = std::make_shared<Node>(newData);
			tail = tail->next;
		}
		else {
			head = std::make_shared<Node>(newData);
			tail = head;
		}
		return head;
	}

	NodePtr PushHead(DataType newData) {
		if (head) {
			auto temp = head;
			head = std::make_shared<SinglyLinkedListNode<DataType>>(newData);
			head->next = temp;
		}
		else {
			head = std::make_shared<SinglyLinkedListNode<DataType>>(newData);
			tail = head;
		}
		return head;
	}

	void PrintList() {
		auto node = head;
		while (node) {
			std::cout << node->data << std::endl;
			node = node->next;
		}
	}

	NodePtr Insert(DataType newData, int positionFromHead) {
		auto node = head;
		for (int i = 0; i < positionFromHead; i++)
		{
			node = node->next;
		}
		auto nextNode = node->next;
		auto newNode = std::make_shared<SinglyLinkedListNode<DataType>>(newData);
		node->next = newNode;
		newNode->next = nextNode;
	}

	void ReverseList() {
		// Iterative approach
		NodePtr prev; //nullptr
		auto curr = head;
		auto newTail = head;

		while (curr) {
			auto next = curr->next;
			// Point curr to prev
			curr->next = prev;
			// Move all pointers forward by one
			prev = curr;
			curr = next;
		}

		head = prev;
		tail = newTail;
	}

	bool operator== (SinglyLinkedList otherList) {
		if (GetHead() == otherList->GetHead() &&
			GetTail() == otherList->GetTail()) {
			return true;
		}
	}

	bool operator!= (SinglyLinkedList otherList) {
		return !()
	}

private:
	NodePtr head;
	NodePtr tail;
};