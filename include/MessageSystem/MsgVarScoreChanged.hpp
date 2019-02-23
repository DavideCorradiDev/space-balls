#ifndef MSGVARSCORECHANGED_HPP
#define MSGVARSCORECHANGED_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgVarScoreChanged : public Message {
public:
    MsgVarScoreChanged(unsigned int score) : score(score) {}
    virtual ~MsgVarScoreChanged() {}

public:
    unsigned int score;
};

}

#endif // MSGVARSCORECHANGED_HPP
