#pragma once
#include <vector>
#include <iostream>

template <typename DataType>
class SinglyLinkedListNode {
	using Node = SinglyLinkedListNode<DataType>;
	using NodePtr = std::shared_ptr<Node>;
public:
	SinglyLinkedListNode(DataType data) :
		next(nullptr),
		data(data)
	{}

	SinglyLinkedListNode(const Node& otherNode) :
		next(otherNode.next),
		data(otherNode.data)
	{}
	~SinglyLinkedListNode() {}
	bool operator= (const Node& otherNode) {
		return data == otherNode.data && &next == &otherNode;
	}

	DataType data;
	NodePtr next;
	bool operator== (const Node& otherNode) {
		return data == otherNode.data && next == otherNode.next;
	}
	bool operator!= (const Node& otherNode) {
		return !(*this == otherNode);
	}
};

template <typename DataType>
class SinglyLinkedList {
public:
	using Node = SinglyLinkedListNode<DataType>;
	using NodePtr = std::shared_ptr<Node>;

	NodePtr head;
	NodePtr tail;

	SinglyLinkedList() :
		head(nullptr),
		tail(nullptr)
	{	};

	SinglyLinkedList(DataType data) :
		head(std::make_shared<Node>(data)),
		tail(head)
	{
	};

	~SinglyLinkedList() {};

	bool operator== (const SinglyLinkedList<DataType>& otherList) {
		auto node1 = head;
		auto node2 = otherList.head;

		while (node1 && node2) {
			if (node1->data != node2->data) {
				return false;
			}
			node1 = node1->next;
			node2 = node2->next;
		}

		if (!node1 != !node2) { // XOR => only one of the lists ended
			return false;
		}
		// Lists are the same length and full of the same data.
		return true;
	}

	bool operator!= (SinglyLinkedList otherList) {
		return !(this == otherList);
	}

	NodePtr GetTail() {
		return tail;
	}

	NodePtr GetHead() {
		return head;
	}

	int GetLength() {
		if (head == nullptr) {
			return 0;
		}
		if (head == tail) {
			return 1;
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
		if (head == nullptr) {
			head = std::make_shared<Node>(newData);
			tail = head;
		}
		else if (head == tail) {
			tail = std::make_shared<Node>(newData);
			head->next = tail;
			tail->next = nullptr;
		}
		else {
			tail->next = std::make_shared<Node>(newData);
			tail = tail->next;
		}
		return head;
	}

	NodePtr PushHead(DataType newData) {
		if (head == nullptr) {
			head = std::make_shared<Node>(newData);
			tail = head;
		}
		else {
			auto oldHead = head;
			head = std::make_shared<Node>(newData);
			head->next = oldHead;
		}
		return head;
	}

	void PrintList() {
		auto node = head;
		int nodeIndex = 0;
		static auto printNodeData = [](DataType data) {std::cout << data << std::endl; };
		if (node == nullptr) {
			std::cout << std::endl;
			return;
		}
		printNodeData(node->data);
		if (head == tail) {
			return; // Avoid double-printing the head for a length-1 list
		}

		while (node->next) {
			node = node->next;
			printNodeData(node->data);
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

	NodePtr GetNodeAtPosition(int positionFromHead) {
		int currentPosition = 0;
		NodePtr prev;
		auto curr = head;
		auto next = curr->next;

		while (currentPosition < positionFromHead && curr) {
			
		}
		
		return curr;
	}

	// Where 0 = tail, 1 = one node before the tail, etc.
	NodePtr GetNodeFromTail(int positionFromTail) {
		if (head == nullptr || tail == nullptr) {
			throw "Can't get node from tail, list is empty";
		}
		if (positionFromTail == 0) {
			return tail;
		}
		// Go all the way to the end, then backtrack.
		// Keep track of where we've been by copying the nodes to an array as we go
		std::vector<NodePtr> nodesInOrder{ head };

		auto node = head;
		while (node->next) {
			node = node->next;
			nodesInOrder.push_back(node);
		}
		if (positionFromTail < nodesInOrder.size()) {
			return nodesInOrder[nodesInOrder.size() - positionFromTail - 1];
		}
		else {
			throw "Attempt to access data before the beginning of SinglyLinkedList's head";
		}
	}

	DataType GetDataAtHead() {
		if (head != nullptr) {
			return head->data;
		}
		throw "Can't get data at head, the list has no head";
	}

	DataType GetDataAtTail() {
		if (tail != nullptr) {
			return tail->data;
		}
		throw "Can't get data at tail, the list has no tail";
	}

	DataType GetDataAtPosition(int positionFromHead) {
		auto node = GetNodeAtPosition(positionFromHead);
		if (node) {
			return node->data;
		}
	}

	bool DeleteNode(int positionFromHead) {
		if (!head || positionFromHead < 0) return false; // Empty list or invalid position

		if (positionFromHead == 0) {
			auto after = head->next;
			if (after) {
				head = after;
				return true;
			}
			head.reset();
			tail.reset();
			return true;
		}
		auto before = GetNodeAtPosition(positionFromHead - 1);
		if (!before) return false;

		auto target = before->next;
		if (!target) return false;

		auto after = target->next;

		if (after) {
			// Target is in the middle of the list
			before->next = after;
			return true;
		}
		// Target is tail
		before->next.reset();
		target.reset();
		tail.reset();
		return true;
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
};