#pragma once

#include <memory>
#include <vector>

// forward declaration
class ECS;

class System {
	public:
		virtual void update(ECS& ecs) = 0;
		virtual ~System() = default;
};


class SystemManager {
	public:
		// use emplace back to add system
		// e.g. registerSystem(std::make_unique<SomeSystem>());
		void registerSystem(std::unique_ptr<System> system) {
			systems.push_back(std::move(system));
		}

		void updateAll(ECS& ecs) {
			for (auto& systemPtr : systems) {
				systemPtr->update(ecs);
			}
		}
		
		std::vector<std::unique_ptr<System>> systems;
};
