#include "pch.h"
#include "LinkedList.h"

class LinkedListTest : public ::testing::Test {
protected:
	void SetUp() override {
	}

	// Create a couple of lists which both only have a single node which contains the same value
	std::unique_ptr<SinglyLinkedList<int>> list = std::make_unique<SinglyLinkedList<int>>(0);
	std::unique_ptr<SinglyLinkedList<int>> list2 = std::make_unique<SinglyLinkedList<int>>(0);
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

TEST_F(LinkedListTest, EqualityOperatorWhenEqual) {
	EXPECT_TRUE(list == list2);
}

TEST_F(LinkedListTest, EqualityOperatorWhenUnequal) {
	list2->PushTail(1);
	EXPECT_FALSE(list == list2);
}