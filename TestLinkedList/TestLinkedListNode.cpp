#include "pch.h"
#include "LinkedList.h"

namespace LinkedListTesting {
	class LinkedListNodeTest : public ::testing::Test {
	protected:
		IntNodePtr node1;
		IntNodePtr node2;

		void SetUp() override {
			node1 = std::make_unique<IntNode>(0);
			node2 = std::make_unique<IntNode>(0);
		}
	};

	TEST_F(LinkedListNodeTest, NodeEqualityOperatorWhenEqual) {
		ASSERT_TRUE(*node1 == *node2);
		ASSERT_FALSE(*node1 != *node2);
	}

	TEST_F(LinkedListNodeTest, NodeEqualityOperatorWhenUnqualNextNodes) {
		auto nodeNext = IntNode(1);
		node1->next = std::make_unique<IntNode>(nodeNext);

		ASSERT_TRUE(*node1 != *node2);
		ASSERT_FALSE(*node1 == *node2);
	}

	TEST_F(LinkedListNodeTest, NodeEqualityOperatorWhenUnqualNextValues) {
		node2->data = 1;

		ASSERT_FALSE(*node1 == *node2);
		ASSERT_TRUE(*node1 != *node2);
	}
}