#include "pch.h"
#include "LinkedList.h"

class LinkedListTest : public ::testing::Test {
	//using ListPtr = std::unique_ptr<SinglyLinkedList<int>>;
protected:
	void SetUp() override {
	}

	// Create a couple of lists which both only have a single node which contains the same value
	std::shared_ptr<SinglyLinkedList<int>> list = std::make_unique<SinglyLinkedList<int>>(0);
	std::shared_ptr<SinglyLinkedList<int>> list2 = std::make_unique<SinglyLinkedList<int>>(0);

	static bool LinkedListTest::checkEqual(std::shared_ptr<SinglyLinkedList<int>> list, std::shared_ptr<SinglyLinkedList<int>> list2) {
		auto node1 = list->GetHead();
		auto node2 = list2->GetHead();

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
};

TEST_F(LinkedListTest, Instantiation) {
	EXPECT_EQ(list->GetTail()->data, 0);
	EXPECT_EQ(list->GetLength(), 1);
}

TEST_F(LinkedListTest, PushTail) {
	list->PushTail(1);
	EXPECT_EQ(list->GetHead()->data, 0);
	EXPECT_EQ(list->GetTail()->data, 1);
	EXPECT_EQ(list->GetLength(), 2);
}

TEST_F(LinkedListTest, PushHead) {
	list->PushHead(1);
	EXPECT_EQ(list->GetHead()->data, 1);
	EXPECT_EQ(list->GetTail()->data, 0);
	EXPECT_EQ(list->GetLength(), 2);
}

TEST_F(LinkedListTest, ReverseListLength1) {
	auto headBefore = list->GetHead();
	auto tailBefore = list->GetTail();
	list->ReverseList();
	auto headAfter = list->GetHead();
	auto tailAfter = list->GetTail();

	EXPECT_EQ(headBefore, tailAfter);
	EXPECT_EQ(tailBefore, headAfter);
	EXPECT_EQ(list->GetLength(), 1);
}

TEST_F(LinkedListTest, ReverseListLength3) {
	list->PushTail(1);
	list->PushTail(2);

	auto headValueBefore = list->GetHead()->data;
	auto tailValueBefore = list->GetTail()->data;
	auto lengthBefore = list->GetLength();
	list->ReverseList();
	auto headValueAfter = list->GetHead()->data;
	auto tailValueAfter = list->GetTail()->data;
	auto lengthAfter = list->GetLength();

	EXPECT_EQ(headValueBefore, tailValueAfter);
	EXPECT_EQ(tailValueBefore, headValueAfter);
	EXPECT_EQ(lengthBefore, lengthAfter);
}

TEST_F(LinkedListTest, DeleteOnlyNode) {
	EXPECT_TRUE(list->DeleteNode(0));
	EXPECT_EQ(list->GetLength(), 0);
}

TEST_F(LinkedListTest, DeleteNodeFromEmptyList) {
	EXPECT_FALSE(list->DeleteNode(1));
	EXPECT_EQ(list->GetLength(), 1);
}

TEST_F(LinkedListTest, DeleteNodeAtNegativePosition) {
	EXPECT_EQ(list->GetLength(), 1);
	EXPECT_FALSE(list->DeleteNode(-1));
	EXPECT_EQ(list->GetLength(), 1);
}

TEST_F(LinkedListTest, DeleteNodeAtTail) {
	list->PushTail(1);
	EXPECT_EQ(list->GetLength(), 2) << "Length before should be 2";
	bool deleteSuccessful = list->DeleteNode(1);
	EXPECT_TRUE(deleteSuccessful) << "Delete function should return true";
	EXPECT_EQ(list->GetLength(), 1) << "Length after deletion should be 1";
	EXPECT_EQ(list->GetDataAtPosition(0), 0);
}

TEST_F(LinkedListTest, DeleteNodeAtHead) {
	list->PushTail(1);
	EXPECT_EQ(list->GetLength(), 2) << "Length before should be 2";
	bool deleteSuccessful = list->DeleteNode(0);
	EXPECT_TRUE(deleteSuccessful) << "Delete function should return true";
	EXPECT_EQ(list->GetLength(), 1) << "Length after deletion should be 1";
	EXPECT_EQ(list->GetDataAtPosition(0), 1);
}

TEST_F(LinkedListTest, EqualityOperatorWhenBothLength1) {
	EXPECT_TRUE(LinkedListTest::checkEqual(list, list2));
}

TEST_F(LinkedListTest, EqualityOperatorWhenBothEmpty) {
	EXPECT_TRUE(LinkedListTest::checkEqual(list, list2));
}

TEST_F(LinkedListTest, EqualityOperatorWhenUnequal) {
	list2->PushTail(1);
	EXPECT_FALSE(list == list2);
}