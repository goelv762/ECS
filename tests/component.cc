#include <gtest/gtest.h>

#include "ecs/ecs.hpp"
#include "test_types.hpp"

TEST(Component, Create) {
	ECS ecs;

	ID entity = ecs.addEntity();
	ecs.addComponent<A>(entity) = { 2 };

	EXPECT_EQ(ecs.getComponent<A>(entity).a, 2);
}

TEST(Component, CreateMultiple) {
	ECS ecs;
	
	for (int i = 0; i < 5; i++) {
		ID entity = ecs.addEntity();
		ecs.addComponent<A>(entity) = { i + 1 };
	}

	for (int j = 0; j < 5; j++) {
		EXPECT_EQ(ecs.getComponent<A>(j).a, j + 1);
	}
}

TEST(Component, Query) {
	ECS ecs;

	ID e1 = ecs.addEntity();
	ecs.addComponent<A>(e1) = { 1 };
	ecs.addComponent<B>(e1) = { 1 };

	ID e2 = ecs.addEntity();
	ecs.addComponent<A>(e2) = { 2 };
	ecs.addComponent<B>(e2) = { 2 };
	
	for (auto& [a, b] : ecs.query<A, B>()) {
		EXPECT_EQ(a.a, b.b);
	}
}
