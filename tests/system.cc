#include <gtest/gtest.h>

#include "ecs/ecs.hpp"
#include "test_types.hpp"

TEST(System, CreateUse) {
	int a{ 1 }, b{ 2 }, c{ 3 };
	ECS ecs;

	ecs.registerSystem(std::make_unique<TestSystem>());

	ID entity = ecs.addEntity();
	ecs.addComponent<A>(entity) = { a };
	ecs.addComponent<B>(entity) = { b };
	ecs.addComponent<C>(entity) = { c };

	ecs.updateSystems();

	EXPECT_EQ(ecs.getComponent<C>(entity).c, a + b + c);
}
