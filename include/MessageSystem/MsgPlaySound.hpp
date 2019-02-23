#ifndef MSGPLAYSOUND_HPP
#define MSGPLAYSOUND_HPP

#include <MessageSystem/Message.hpp>
#include <ResourceSystem/SoundBufferHolder.hpp>

namespace mnk {

class MsgPlaySound : public Message {
public:
    MsgPlaySound(SoundBufferId soundId) :
        soundId(soundId) {}
    virtual ~MsgPlaySound() {}

public:
    SoundBufferId soundId;
};

}

#endif // MSGPLAYSOUND_HPP
