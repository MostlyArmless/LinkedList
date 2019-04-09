#include "pch.h"
#include "LinkedList.h"

namespace LinkedListTesting {
	class LinkedListNodeTest : public ::testing::Test {
	protected:
		IntNodePtr node1;
		IntNodePtr node2;
		IntNodePtr node3;

		void SetUp() override {
			node1 = std::make_unique<IntNode>(0);
			node2 = std::make_unique<IntNode>(0);
			node3 = std::make_unique<IntNode>(1);
		}
	};

	TEST_F(LinkedListNodeTest, NodeEqualityOperatorWhenEqual) {
		EXPECT_TRUE(*node1 == *node2);
		EXPECT_FALSE(*node1 != *node2);
	}

	TEST_F(LinkedListNodeTest, NodeEqualityOperatorWhenUnqualNextNodes) {
		auto nodeNext = IntNode(1);
		node1->next = std::make_unique<IntNode>(nodeNext);

		EXPECT_TRUE(*node1 != *node2);
		EXPECT_FALSE(*node1 == *node2);
	}

	TEST_F(LinkedListNodeTest, NodeEqualityOperatorWhenUnqualNextValues) {
		node2->data = 1;

		EXPECT_FALSE(*node1 == *node2);
		EXPECT_TRUE(*node1 != *node2);
	}

	TEST_F(LinkedListNodeTest, AssignmentOperator) {
		EXPECT_FALSE(*node1 == *node3);
		*node3 = *node1;
		EXPECT_TRUE(*node1 == *node3);
	}
}