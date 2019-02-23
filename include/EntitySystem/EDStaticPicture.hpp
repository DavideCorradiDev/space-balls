#ifndef EDSTATICPICTURE_HPP
#define EDSTATICPICTURE_HPP

#include <EntitySystem/EntityData.hpp>
#include <ResourceSystem/TextureHolder.hpp>

namespace mnk {

class EDStaticPicture : public EntityData {
public:
    EDStaticPicture(TextureId textureId) :
        textureId(textureId){}
    virtual ~EDStaticPicture() {}

public:
    TextureId textureId;
};

}

#endif // EDSTATICPICTURE_HPP
