#ifndef ANIMATIONHOLDER_HPP
#define ANIMATIONHOLDER_HPP

#include <ResourceSystem/ResourceHolder.hpp>
#include <ResourceSystem/Animation.hpp>

namespace mnk {

enum class AnimationId {
    Ship,
    Explosion,
};

typedef ResourceHolder<AnimationId, Animation> AnimationHolder;

}

#endif // ANIMATIONHOLDER_HPP
