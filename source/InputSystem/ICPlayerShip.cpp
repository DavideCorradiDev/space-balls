#include <InputSystem/ICPlayerShip.hpp>
#include <MessageSystem/MsgCmdTurnLeft.hpp>
#include <MessageSystem/MsgCmdTurnRight.hpp>
#include <MessageSystem/MsgCmdAccelerate.hpp>
#include <MessageSystem/MsgCmdStop.hpp>
#include <MessageSystem/MsgCmdAttack.hpp>

namespace mnk {

ICPlayerShip::~ICPlayerShip() {}

void ICPlayerShip::handleInputCode(sf::Time dt, InputCode inputCode) {
    switch(inputCode) {
    case InputCode::TurnLeft:
        sendMessageToEntity(MsgCmdTurnLeft(dt));
        break;
    case InputCode::TurnRight:
        sendMessageToEntity(MsgCmdTurnRight(dt));
        break;
    case InputCode::Accelerate:
        sendMessageToEntity(MsgCmdAccelerate());
        break;
    case InputCode::Stop:
        sendMessageToEntity(MsgCmdStop());
        break;
    case InputCode::Attack:
        sendMessageToEntity(MsgCmdAttack());
        break;
    }
}

}
