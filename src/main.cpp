#include <iostream>
#include "ecs.hpp"
struct A { int a; };
struct B { int b; };
struct C { int c; };
struct D { int d; };

class TestSystem : public System {
	void update(ComponentManager& cm, EntityManager& em) override {
	}
};

int main(void) {
	ECS ecs;
	ecs.registerSystem(std::make_unique<TestSystem>());
	
	for (int i = 0; i < 5; i++) {
		ID rock = ecs.addEntity();
		ecs.addComponent<B>(rock);
	}
		
	for (int i = 0; i < 5; i++) {
		ID rock = ecs.addEntity();
		ecs.addComponent<B>(rock);
		ecs.addComponent<D>(rock);
	}
	
	for (ID entity : ecs.queryComponents<B, D>()) {
		std::cout << entity << std::endl;
	}

	ecs.updateSystems();

	return 0;
}
