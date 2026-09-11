#pragma once

#include "ecs/ecs.hpp"

struct A { int a; };
struct B { int b; };
struct C { int c; };
struct D { int d; };

class TestSystem : public System {
	void update(ECS& ecs) override {
		for (auto& [apple, banana, carrot] : ecs.query<A, B, C>()) {
			carrot.c += apple.a + banana.b;
		}
	}
};
