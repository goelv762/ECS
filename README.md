ustECS
===
ustECS is a header only entity component system implementation written in c++ without the use of any external libraries.

Installation
==
To use as a sub-module, add using git.
```bash
git submodule add https://github.com/goelv762/ustECS.git
```

Then in your `CMakeLists.txt` add:
```cmake
add_subdirectory(ustECS)
target_link_libraries(external INTERFACE ecs::ecs)
```
Note that this library **only** comes in header only format. The `CMakeLists.txt` files are for building and running tests.

Standalone
==
If you want to use this standalone first clone the repo.
```bash
git clone https://github.com/goelv762/ustECS.git
cd ustECS
```
To compile and run the tests:
```bash
cmake -B build
cmake --build build
./build/tests/ecs_tests
```

Usage
==
```cpp
// components are just structs
struct Position {
	double x{};
	double y{};
	double z{};
};

// use 'alias' to be able to register multiple resources of type int under the hood
using Offset = int;

// all systems must inherit from the base class 'System'
class MoveSystem : public System {
	void update(ECS& ecs) override {
		int offsetResource = ecs.getResource<Offset>();
		for (auto& [position] : ecs.query<Position>()) {
			position.x +=  1.0f + offsetResource;
			position.y += -1.0f + offsetResource;
			position.z +=  0.2f + offsetResource;
		}
	}
};

int main(int argc, char* argv[]) {
	// no args are required to initialise the ecs
	ECS ecs;

	// for the system to be ran later on, we need to register it
	ecs.registerSystem(std::make_unique<MoveSystem>());
	// resources are the global variables in the ecs (not tied to entities)
	ecs.initResource<Offset>(3);

	// adds an entity, represented by its ID
	ID entity = ecs.addEntity();
	// addComponent returns the component itself, so we can modify immediately
	// note that we dont have to register components as by adding them we register them
	ecs.addComponent<Position>(entity) = {
		.x = 1,
		.y = 64,
		.z = 49
	};

	// 'main loop'
	for (size_t i = 0; i < 5; i++) {
		// updates all registered systems
		ecs.updateSystems();
	}

  return 0;
}
```
