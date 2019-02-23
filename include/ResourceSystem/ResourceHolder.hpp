#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <Utilities/NonCopyable.hpp>
#include <string>
#include <map>
#include <memory>

namespace mnk {

template <typename Identifier, typename Resource>
class ResourceHolder : public NonCopyable {
public:
    template <typename... Parameters>
    void load(Identifier id, const std::string& filename, Parameters... parameters);
    void add(Identifier id, std::unique_ptr<Resource> pResource);
    void remove(Identifier id);
    void clear();
    const Resource& get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

}

#include "../../source/ResourceSystem/ResourceHolder.inl"

#endif // RESOURCEHOLDER_HPP
