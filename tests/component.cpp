#include <gtest/gtest.h>

#include "ecs/ecs.hpp"

struct A { int a; };
struct B { int b; };
struct C { int c; };
struct D { int d; };

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
	ecs.addComponent<A>(e1);

	ID e2 = ecs.addEntity();
	ecs.addComponent<B>(e2);

	EXPECT_EQ((ecs.queryComponents<B>()), std::vector<ID>{1});
}

TEST(Component, QueryMultiple) {
	ECS ecs;

	ID e1 = ecs.addEntity();
	ecs.addComponent<A>(e1);
	ecs.addComponent<B>(e1);

	ID e2 = ecs.addEntity();
	ecs.addComponent<C>(e2);
	ecs.addComponent<D>(e2);

	EXPECT_EQ((ecs.queryComponents<A, C>()), std::vector<ID>{});
	EXPECT_EQ((ecs.queryComponents<B, D>()), std::vector<ID>{});
	EXPECT_EQ((ecs.queryComponents<A, B>()), std::vector<ID>{0});
	EXPECT_EQ((ecs.queryComponents<C, D>()), std::vector<ID>{1});
}
