#pragma once

#include <any>
#include <cstdint>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "types.hpp"
#include "resource.hpp"

#include "entity.hpp"
#include "component.hpp"
#include "system.hpp"


class ECS {
	public:
		// em functions
		ID addEntity() { return em.addEntity(); }

		void deleteEntity(ID id) {
			cm.deleteAllComponents(id, em.getBitmask(id));
			em.deleteEntity(id);
		}

		bool entityExists(ID id) { return em.exists(id); }
		Bitmask getEntityBitmask(ID id) { return em.getBitmask(id); }
		void addToBitmask(ID id, uint8_t typeIndex) { em.addToBitmask(id, typeIndex); }
		void deleteFromBitmask(ID id, uint8_t typeIndex) { em.deleteFromBitmask(id, typeIndex); }

		// cm functions
		template <typename Component>
		Component& addComponent(ID id) { 
			// check if entity exists yet
			if (!em.exists(id)) {
				std::cerr << "No entity exists with id no. " << id << std::endl;
				exit(em.exists(id));
			}

			// check if the component is registered
			if (cm.registry.find(typeid(Component)) == cm.registry.end()) {
				// if not registered, register !!
				cm.components.push_back(std::make_unique<SparseSet<Component>>());
				cm.registry[typeid(Component)] = cm.components.size() - 1;
			}

			em.addToBitmask(id, cm.registry[typeid(Component)]);

			return cm.addComponent<Component>(id); 
		}

		template <typename Component>
		void deleteComponent(ID id) {
			// check if entity exists yet
			if (!em.exists(id)) {
				std::cerr << "No entity exists with id no. " << id << std::endl;
				exit(em.exists(id));
			}

			// check if the component is registered
			if (cm.registry.find(typeid(Component)) == cm.registry.end()) {
				// if not registered, register !!
				cm.components.push_back(std::make_unique<SparseSet<Component>>());
				cm.registry[typeid(Component)] = cm.components.size() - 1;
			}

			em.deleteFromBitmask(id, cm.registry[typeid(Component)]);

			return cm.deleteComponent<Component>(id);
		}

		template <typename Component>
		Component& getComponent(ID id) { return cm.getComponent<Component>(id); }


		template <typename... Components>
		std::vector<std::tuple<Components&...>> query() {
			std::vector<std::tuple<Components&...>> result;
			// get the component with the smallest set from component manager (minimises bitmask checks that have to be done)
			std::vector<ID> smallestSet = cm.getSmallest<Components ...>(); 

			// create the bitmask to compare to
			Bitmask target = em.generateBitMask<Components ...>(cm);
			
			// vector to store successful candidates in
			std::vector<ID> matches{};
			// itterate over bitmasks of smallests set and check if they have the nececearry components
			for (ID candidate : smallestSet) {
				if ((em.getBitmask(candidate) & target) == target) {
					// this means that the entity has all the components we require !!
					result.emplace_back(getComponent<Components>(candidate)...);
				}
			}

			return result;
		}

		// sm functions
		void registerSystem(std::unique_ptr<System> system) { sm.registerSystem(std::move(system)); }
		void updateSystems() { sm.updateAll(*this); }

		// rm functions

		template <typename ResourceType>
		void initResource(ResourceType initialValue = {}) { rm.initResource(initialValue); }

		template <typename ResourceType>
		ResourceType& getResource() { return rm.getResource<ResourceType>(); }

		template <typename ResourceType>
		void deleteResource() { rm.deleteResource<ResourceType>(); };
		

	private:

		EntityManager em;
		ComponentManager cm;
		SystemManager sm;
	
		ResourceManager rm;
};
