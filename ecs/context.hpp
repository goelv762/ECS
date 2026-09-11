#pragma once

#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
struct IGlobalData {
	    virtual ~IGlobalData() = default;
};

template <typename Type>
struct GlobalData : public IGlobalData {
	// can store multiple of the same type
	std::unordered_map<std::string, Type> data;
};

using Context = std::unordered_map<std::type_index, std::unique_ptr<IGlobalData>>;

// helper functions to actually use context
template <typename Type> 
Type& getContextData(Context& ctx, std::string name = "") {
	// use this to index into context map
	std::type_index index = std::type_index(typeid(Type));
	GlobalData<Type>& globalData = static_cast<GlobalData<Type>&>(ctx[index]);

	// use name to index into globalData
	return &globalData.data[name];
}

