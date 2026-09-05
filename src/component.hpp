#pragma once

#include "types.hpp"

#include <bitset>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

class ISparseSet {
public:
    virtual ~ISparseSet() = default;
    virtual void del(ID id) = 0;
    virtual bool contains(ID id) const = 0;
	virtual std::vector<ID> getIDs() const = 0;
	virtual size_t size() const = 0;
};

template <typename Component> // max entities is defined above, no need to pass in
class SparseSet : public ISparseSet {
	public:
		bool contains(ID id) const override {
			return id < sparse.size()
				&& sparse[id] < dense.size()
				&& denseToID[sparse[id]] == id;
		}

		void containsErr(ID id) const {
			bool result = contains(id);
			if (!result) {
				std::cerr << "ID no. " << id << " does not exist in sparse set of type '" << getTypeName<Component>() << "'" << std::endl;
				exit(result);
			}
		}

		Component& get(ID id) {
			containsErr(id);
			return dense[sparse[id]];
		}

		Component& add(ID id) {
			// if the entity already exists, it just passes back the original data
			if (!contains(id)) {
				if (id >= sparse.size()) {
					sparse.resize(id + 1);
				}
				
				dense.emplace_back();
				denseToID.push_back(id);

				sparse[id] = dense.size() - 1;
			}

			// for (auto& temp : sparse) {
			// 	std::cout << temp << std::endl;
			// }

			return get(id);
		}

		std::vector<ID> getIDs() const override {
			return denseToID;
		}

		void del(ID id) override {
			containsErr(id);
			// swap and delete with last element of dense
			// then point sparse to new location
			size_t idxToRemove = sparse[id];
			size_t lastIdx = dense.size() - 1;
			ID lastID = denseToID[lastIdx];   // the entity that owns the last slot

			dense[idxToRemove] = dense[lastIdx];     // move component data
			denseToID[idxToRemove] = lastID;   // move ownership tag
			sparse[lastID] = idxToRemove;        // repoint that entity's sparse entry

			dense.pop_back();
			denseToID.pop_back();	
		}

		size_t size() const override {
			return dense.size();
		}

	private:
		std::vector<Component> dense{};
		std::vector<ID> denseToID{};
		std::vector<ID> sparse{};
};

class ComponentManager {
	public:
		// indecies of vector map to target bitmask
		std::vector<std::unique_ptr<ISparseSet>> components;
		std::unordered_map<std::type_index, uint32_t> registry;

		template <typename Component>
		SparseSet<Component>* getSparseSet() {
			// ensure that component is registered <=> ensure component sparse set exists
			auto it = registry.find(typeid(Component));
			if (it == registry.end()) {
				return nullptr;
			}
			// get sparse set that the component belongs to
			// (.get returns the raw pointer from unique, not the .get defined in ss!!)
			return static_cast<SparseSet<Component>*>(components[registry[typeid(Component)]].get());
		}

		template <typename Component>
		Component& addComponent(ID id) { return getSparseSet<Component>()->add(id); }

		template <typename Component>
		void deleteComponent(ID id) { getSparseSet<Component>()->del(id); }

		template <typename Component>
		Component& getComponent(ID id) { return getSparseSet<Component>()->get(id); }


		void deleteAllComponents(ID id, Bitmask bm) {
			std::bitset<32> bs = std::bitset<32>(bm);
			for (size_t i = 0; i < bs.size(); i++) {
				if (bs[i]) {
					// i is the index into components vector for given component
					auto& sparseSet = components[i];
					sparseSet->del(id);
				}
			}
		}

		template <typename... Components>
		std::vector<ID> getSmallest() {
			bool allRegistered = true;

			// find the smallest sparse set
			ISparseSet* small = nullptr;

			// define a lambda function to compare size of given sparse set to current smallest
			auto considerType = [&]<typename Component>() {
				// we have already checked that the components are registered !
				auto* set = getSparseSet<Component>();
				if (!set) {
					allRegistered = false;
					return;
				}
				// !small for first one, small is just a null ptr at the moment
				if (!small || set->size() < small->size()) {
					small = set;
				}
			};

			// run comparison for all queried components
			(considerType.template operator()<Components>(), ...);

			// if a component has not been registered, that means that no entities can exist in that set
			// if the smallest set has no entities, the intersection of this set and any other must be empty
			if (!allRegistered || small->getIDs().size() == 0) {
				return {};
			}

			return small->getIDs();
		}

	
	private:
		
};

