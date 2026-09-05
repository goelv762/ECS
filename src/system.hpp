#include "component.hpp"
#include "entity.hpp"

class System {
	public:
		virtual void update(ComponentManager& cm, EntityManager& em) = 0;
};


class SystemManager {
	public:
		// use emplace back to add system
		// e.g. registerSystem(std::make_unique<SomeSystem>());
		void registerSystem(std::unique_ptr<System> system) {
			systems.push_back(std::move(system));
		}

		void updateAll(ComponentManager& cm, EntityManager& em) {
			for (auto& systemPtr : systems) {
				systemPtr->update(cm, em);
			}
		}

		std::vector<std::unique_ptr<System>> systems;
};
