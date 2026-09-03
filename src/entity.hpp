#pragma once

#include <cstdint>
#include <unordered_map>

#include "types.hpp"
#include "component.hpp"


class EntityManager {
	public:
		ID add() {
			// TODO freed IDs recycling
			// -> add delete entity function!
			ID id = currentID ++;
			bitmasks[id] = 0;
			return id;
		}

		bool exists(ID id) {
			return bitmasks.contains(id);
		}

		Bitmask getBitmask(ID id) {
			return bitmasks[id];
		}

		void updateBitmask(ID id, uint8_t typeIndex) {
			bitmasks[id] |= 1u << typeIndex;
		}
		
		template <typename ... Components>
		Bitmask generateBitMask(ComponentManager& cm) {
			Bitmask bm{ 0 };

			((bm |= 1u << cm.registry[typeid(Components)]), ...);

			return bm;
		}
	
	private:
		ID currentID{ 0 };
		std::unordered_map<ID, Bitmask> bitmasks;
};

