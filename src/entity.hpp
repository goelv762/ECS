#pragma once

#include <cstdint>
#include <unordered_map>

#include "types.hpp"
#include "component.hpp"


class EntityManager {
	public:
		ID addEntity() {
			ID id{ 0 };

			if (!recycle.empty()) {
				// recycles oldest deleted first
				id = recycle[0];
				recycle.erase(recycle.begin());
			} else {
				id = currentID ++;
			}

			bitmasks[id] = 0;
			return id;
		}

		void deleteEntity(ID id) {
			recycle.push_back(id);
			bitmasks.erase(id);
		}

		bool exists(ID id) {
			return bitmasks.contains(id);
		}

		Bitmask getBitmask(ID id) {
			return bitmasks[id];
		}

		void addToBitmask(ID id, uint8_t typeIndex) {
			// set to 1
			bitmasks[id] |= 1u << typeIndex;
		}

		void deleteFromBitmask(ID id, uint8_t typeIndex) {
			// set to 0
			bitmasks[id] &= ~(1u << typeIndex);
		}
		
		template <typename ... Components>
		Bitmask generateBitMask(ComponentManager& cm) {
			Bitmask bm{ 0 };

			((bm |= 1u << cm.registry[typeid(Components)]), ...);

			return bm;
		}
	
	private:
		ID currentID{ 0 };
		std::vector<ID> recycle;
		std::unordered_map<ID, Bitmask> bitmasks;
};

