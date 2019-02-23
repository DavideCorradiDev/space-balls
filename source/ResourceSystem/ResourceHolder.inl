#include <cassert>

namespace mnk {

template <typename Identifier, typename Resource>
template <typename... Parameters>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& filename, Parameters... parameters) {
    std::unique_ptr<Resource> resource(new Resource());
    bool loaded = resource->loadFromFile(filename, parameters...);
    assert(loaded);
    assert(mResourceMap.find(id) == mResourceMap.end());
    mResourceMap.insert(std::make_pair(id, std::move(resource)));
}

template <typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::add(Identifier id, std::unique_ptr<Resource> pResource) {
    assert(mResourceMap.find(id) == mResourceMap.end());
    mResourceMap.insert(std::make_pair(id, std::move(pResource)));
}

template <typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::remove(Identifier id) {
    mResourceMap.erase(id);
}

template <typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::clear() {
    mResourceMap.clear();
}

template <typename Identifier, typename Resource>
const Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) const {
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *(found->second);
}

}
