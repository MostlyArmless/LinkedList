#include "pch.h"
#include "LinkedList.h"

using ListPtr = std::unique_ptr<SinglyLinkedList<int>>;
using IntNode = SinglyLinkedListNode<int>;

class LinkedListTest : public ::testing::Test {	
protected:
	ListPtr listLength1;
	ListPtr listLength2;
	ListPtr listLength3;

	void SetUp() override {
		// Create a couple of lists which both only have a single node which contains the same value

		listLength1 = std::make_unique<SinglyLinkedList<int>>(0);
		listLength2 = std::make_unique<SinglyLinkedList<int>>(0);
		listLength3 = std::make_unique<SinglyLinkedList<int>>(0);

		listLength2->PushTail(1);
		listLength3->PushTail(1);
		listLength3->PushTail(2);
	}
};

TEST_F(LinkedListTest, Instantiation) {
	EXPECT_EQ(listLength1->GetTail()->data, 0);
	EXPECT_EQ(listLength1->GetLength(), 1);
}

TEST_F(LinkedListTest, PushTail) {
	listLength1->PushTail(1);
	EXPECT_EQ(listLength1->GetHead()->data, 0);
	EXPECT_EQ(listLength1->GetTail()->data, 1);
	EXPECT_EQ(listLength1->GetLength(), 2);
}

TEST_F(LinkedListTest, PushHead) {
	listLength1->PushHead(1);
	EXPECT_EQ(listLength1->GetHead()->data, 1);
	EXPECT_EQ(listLength1->GetTail()->data, 0);
	EXPECT_EQ(listLength1->GetLength(), 2);
}

TEST_F(LinkedListTest, ReverseListLength1) {
	auto headBefore = listLength1->GetHead();
	auto tailBefore = listLength1->GetTail();
	listLength1->ReverseList();
	auto headAfter = listLength1->GetHead();
	auto tailAfter = listLength1->GetTail();

	EXPECT_EQ(headBefore, tailAfter);
	EXPECT_EQ(tailBefore, headAfter);
	EXPECT_EQ(listLength1->GetLength(), 1);
}

TEST_F(LinkedListTest, ReverseListLength3) {
	auto headValueBefore = listLength3->GetHead()->data;
	auto tailValueBefore = listLength3->GetTail()->data;
	auto lengthBefore = listLength3->GetLength();
	listLength3->ReverseList();
	auto headValueAfter = listLength3->GetHead()->data;
	auto tailValueAfter = listLength3->GetTail()->data;
	auto lengthAfter = listLength3->GetLength();

	EXPECT_EQ(headValueBefore, tailValueAfter);
	EXPECT_EQ(tailValueBefore, headValueAfter);
	EXPECT_EQ(lengthBefore, lengthAfter);
}

TEST_F(LinkedListTest, DeleteOnlyNode) {
	EXPECT_TRUE(listLength1->DeleteNode(0));
	EXPECT_EQ(listLength1->GetLength(), 0);
}

TEST_F(LinkedListTest, DeleteNodeAtNegativePosition) {
	EXPECT_EQ(listLength1->GetLength(), 1);
	EXPECT_FALSE(listLength1->DeleteNode(-1));
	EXPECT_EQ(listLength1->GetLength(), 1);
}

TEST_F(LinkedListTest, DeleteNodeAtTail) {
	EXPECT_EQ(listLength2->GetLength(), 2) << "Length before should be 2";
	bool deleteSuccessful = listLength2->DeleteNode(1);
	EXPECT_TRUE(deleteSuccessful) << "Delete function should return true";
	EXPECT_EQ(listLength2->GetLength(), 1) << "Length after deletion should be 1";
	EXPECT_EQ(listLength2->GetDataAtPosition(0), 0);
}

TEST_F(LinkedListTest, DeleteNodeAtHead) {
	EXPECT_EQ(listLength2->GetLength(), 2) << "Length before should be 2";
	bool deleteSuccessful = listLength2->DeleteNode(0);
	EXPECT_TRUE(deleteSuccessful) << "Delete function should return true";
	EXPECT_EQ(listLength2->GetLength(), 1) << "Length after deletion should be 1";
	EXPECT_EQ(listLength2->GetDataAtPosition(0), 1);
}

TEST_F(LinkedListTest, EqualityOperatorWhenEqualAndSize2) {
	listLength1->PushTail(1);
	EXPECT_TRUE(*listLength1 == *listLength2);
}

TEST_F(LinkedListTest, EqualityOperatorWhenUnequalLengths) {
	EXPECT_FALSE(*listLength1 == *listLength2);
}

TEST_F(LinkedListTest, EqualityOperatorWhenEqualLengthsButUnequalData) {
	listLength1->PushTail(42);
	EXPECT_FALSE(*listLength1 == *listLength2);
}

TEST_F(LinkedListTest, InequalityOperatorWhenBothLength1) {
	listLength1->PushTail(1);
	EXPECT_TRUE(*listLength1 == *listLength2);
}

TEST_F(LinkedListTest, EqualityOperatorWhenUnequal) {
	EXPECT_FALSE(*listLength1 == *listLength2);
}

TEST(NodeEqualityOperatorWhenEqual) {
	auto node1 = IntNode(0);
	auto node2 = IntNode(0);

	ASSERT_TRUE(node1 == node2);
	ASSERT_FALSE(node1 != node2);
}

TEST(NodeEqualityOperatorWhenUnqualNextNodes) {
	auto node1 = IntNode(0);
	auto node2 = IntNode(0);
	auto nodeNext = IntNode(1);
	node1.next = std::make_shared<IntNode>(nodeNext);

	ASSERT_TRUE(node1 == node2);
	ASSERT_FALSE(node1 != node2);
}

TEST(NodeEqualityOperatorWhenUnqualNextValues) {
	auto node1 = std::make_shared<IntNode>(0);
	auto node2 = std::make_shared<IntNode>(1);

	ASSERT_FALSE(node1 == node2);
	ASSERT_TRUE(node1 != node2);
}