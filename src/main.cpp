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

	ID rock = ecs.addEntity();
	
	ecs.addComponent<B>(rock) = { .b = 2 };
	ecs.addComponent<D>(rock) = { .d = 5 };

	std::cout << ecs.getComponent<B>(rock).b + ecs.getComponent<D>(rock).d << std::endl;

	ecs.deleteComponent<B>(rock);
	ecs.deleteEntity(rock);

	std::cout << ecs.getComponent<B>(rock).b + ecs.getComponent<D>(rock).d << std::endl;

	return 0;
}
