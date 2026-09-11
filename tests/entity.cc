#include <gtest/gtest.h>

#include "ecs/ecs.hpp"

TEST(Entity, Create) {
	ECS ecs;

	ID entity = ecs.addEntity();

	ASSERT_EQ(entity, 0);
	EXPECT_EQ(ecs.getEntityBitmask(entity), 0);
}

TEST(Entity, CreateMultiple) {
	ECS ecs;

	for (int i = 0; i < 5; i++) {
		ID entity = ecs.addEntity();
		// allows for us to see at which itteration it fails
		SCOPED_TRACE(::testing::Message() << "iteration i=" << i);
		// ids should increment by 1 as well, thus be equal to i
		ASSERT_EQ(entity, i);
		// bitmasks should always init to 0 (uint32_t all 0 bits)
		EXPECT_EQ(ecs.getEntityBitmask(entity), 0);
	}
}

TEST(Entity, CreateDelete) {
	ECS ecs;

	// create 5 entities
	for (int i = 0; i < 5; i++) {
		ID entity = ecs.addEntity();
	}

	// delete 5 entities
	for (int j = 0; j < 5; j++) {
		ecs.deleteEntity(j);
	}

	// as 0 was deleted first it should be the first to be recycled
	EXPECT_EQ(ecs.addEntity(), 0);
}

TEST(Entity, CreateDeleteSkipping) {
	ECS ecs;

	// create 5 entities
	for (int i = 0; i < 5; i++) {
		ID entity = ecs.addEntity();
	}

	// current entity id should be 5 (e.g. next entity created should be of id 5)
	// dont check here as that would increment the id counter
	
	// delete first 4 entities
	for (int j = 0; j < 4; j++) {
		ecs.deleteEntity(j);
	}

	// the next entity ID given should be 0 as that was deleted first
	// this should continue to remain true incrementing up till 4
	
	for (int j = 0; j < 4; j++) {
		EXPECT_EQ(ecs.addEntity(), j);
	}

	// should be ID 5 not 4 as 4 was not deleted at the start
	EXPECT_EQ(ecs.addEntity(), 5);
}
