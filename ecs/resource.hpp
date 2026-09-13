#include <any>
#include <cstdlib>
#include <iostream>
#include <typeindex>
#include <unordered_map>

class ResourceManager {
	public:
		template <typename ResourceType>
		void initResource(ResourceType initialValue = {}) {
			resources[std::type_index(typeid(ResourceType))] = initialValue;
		}

		template <typename ResourceType>
		ResourceType& getResource() {
			if (!resourceExists<ResourceType>()) {
				std::cerr << "No resource exists with type " << getTypeName<ResourceType>() << std::endl;
				exit(EXIT_FAILURE);
			}

			std::any& resource = resources[std::type_index(typeid(ResourceType))];
			return std::any_cast<ResourceType&>(resource);
		}

		template <typename ResourceType>
		void deleteResource() {
			resources.erase(std::type_index(typeid(ResourceType)));
		}

	private:
		template <typename ResourceType>
		bool resourceExists() {
			return (resources.find(std::type_index(typeid(ResourceType))) != resources.end());
		}

		std::unordered_map<std::type_index, std::any> resources;
};
