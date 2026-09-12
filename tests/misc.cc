#include <gtest/gtest.h>

#include "ecs/ecs.hpp"

TEST(Misc, Resource) {
	ECS ecs;
	ecs.initResource<int>(3);

	EXPECT_EQ(ecs.getResource<int>(), 3);
}

TEST(Misc, ResourceMutliple) {
	ECS ecs;

	int a = 2; float b = 3.14f; bool c = false;

	ecs.initResource<int>(a);
	ecs.initResource<float>(b);
	ecs.initResource<bool>(c);

	EXPECT_EQ(ecs.getResource<int>(), a);
	EXPECT_EQ(ecs.getResource<float>(), b);
	EXPECT_EQ(ecs.getResource<bool>(), c);
}

TEST(Misc, ResourceGetError) {
	ECS ecs;
	// empty string just means expect any error msg
	EXPECT_DEATH(ecs.getResource<int>(), "");
}
