#pragma once

#include <map>
#include <typeindex>

class DependencyContainer
{
    std::map<std::type_index, void*> m_dependencies;

public:
    template <typename T>
    void Cache(T* object)
    {
        m_dependencies[std::type_index(typeid(T))] = object;
    }

    template <typename T>
    T* Resolve()
    {
        return static_cast<T*>(m_dependencies[std::type_index(typeid(T))]);
    }
};
