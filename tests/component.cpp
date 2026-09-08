#include <gtest/gtest.h>

#include "ecs/ecs.hpp"

struct A { int a; };
struct B { int b; };
struct C { int c; };
struct D { int d; };

TEST(Component, Create) {
	ECS ecs;

	ID entity = ecs.addEntity();
	ecs.addComponent<A>(entity) = {
		.a = 2
	};

	ASSERT_EQ(ecs.getComponent<A>(entity).a, 2);
}
