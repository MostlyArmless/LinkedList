#include "pch.h"
#include "LinkedList.h"

namespace LinkedListTesting {
	class LinkedListTest : public ::testing::Test {
	protected:
		IntListPtr listLength0;
		IntListPtr listLength1;
		IntListPtr listLength2;
		IntListPtr listLength3;

		void SetUp() override {
			// Create a couple of lists which both only have a single node which contains the same value

			listLength0 = std::make_unique<IntList>();
			listLength1 = std::make_unique<IntList>(0);
			listLength2 = std::make_unique<IntList>(0);
			listLength3 = std::make_unique<IntList>(0);

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

	TEST_F(LinkedListTest, GetNodeFromTail) {
		auto tailNode = listLength3->GetNodeFromTail(0);
		auto headNode = listLength3->GetNodeFromTail(2);
		EXPECT_EQ(tailNode->data, 2);
		EXPECT_EQ(headNode->data, 0);

		EXPECT_ANY_THROW(listLength0->GetNodeFromTail(0));
		EXPECT_ANY_THROW(listLength1->GetNodeFromTail(2));
		EXPECT_ANY_THROW(listLength0->GetNodeFromTail(-1));
		EXPECT_ANY_THROW(listLength3->GetNodeFromTail(-1));
	}

	//TEST_F(LinkedListTest, GetNodeFromTailBeforeStartOfList) {
	//	EXPECT_ANY_THROW(listLength1->GetNodeFromTail(3));
	//}

	TEST_F(LinkedListTest, PrintListLength0) {
		testing::internal::CaptureStdout();
		listLength0->PrintList();
		std::string actual = testing::internal::GetCapturedStdout();
		// For consistency with non-zero length lists, we expect there to be a newline printed for empty lists
		std::string expected = "\n";
		ASSERT_EQ(actual, expected);
	}

	TEST_F(LinkedListTest, PrintListLength1) {
		testing::internal::CaptureStdout();
		listLength1->PrintList();
		std::string actual = testing::internal::GetCapturedStdout();
		std::string expected = "0\n";
		ASSERT_EQ(actual, expected);
	}

	TEST_F(LinkedListTest, PrintListLength2) {
		testing::internal::CaptureStdout();
		listLength2->PrintList();
		std::string actual = testing::internal::GetCapturedStdout();
		std::string expected = "0\n1\n";
		ASSERT_EQ(actual, expected);
	}

	TEST_F(LinkedListTest, GetDataAtHead) {
		ASSERT_ANY_THROW(listLength0->GetDataAtHead());
		ASSERT_EQ(listLength1->GetDataAtHead(), 0);
		ASSERT_EQ(listLength2->GetDataAtHead(), 0);
	}

	TEST_F(LinkedListTest, GetDataAtTail) {
		ASSERT_ANY_THROW(listLength0->GetDataAtTail());
		ASSERT_EQ(listLength1->GetDataAtTail(), 0);
		ASSERT_EQ(listLength2->GetDataAtTail(), 1);
		ASSERT_EQ(listLength3->GetDataAtTail(), 2);
	}

}