namespace mnk {

template <typename ObjType>
GameSystem<ObjType>::~GameSystem() {}

template <typename ObjType>
void GameSystem<ObjType>::update(sf::Time dt) {
    auto it = mpObjects.begin();
    while(it != mpObjects.end()) {
        if((*it)->isDeleted()) {
            it = mpObjects.erase(it);
        } else if((*it)->isActive()) {
            onUpdateObject(dt, **it);
            ++it;
        } else if((*it)->isSetForActivation()) {
            // Make some special system initialization.
            // Doing it here ensures that the method is not called in the middle of the creation of an entity.
            onAddObject(**it);
            (*it)->setActive();
        } else {
            ++it;
        }
    }
    onUpdateEnd(dt);
}

template <typename ObjType>
void GameSystem<ObjType>::handleMessage(const Message& message) {
    MessageHandler::handleMessage(message);
    sendMessageToObjects(message);
}

template <typename ObjType>
const typename GameSystem<ObjType>::ObjectsList& GameSystem<ObjType>::getObjectsList() const { return mpObjects; }

template <typename ObjType>
void GameSystem<ObjType>::addObject(ObjectPtr pObject) {
    assert(pObject && "GameSystem::addObject - pObject is nullptr.");
    assert(!pObject->getpSystem() && "GameSystem::addObject - the GameObject is already member of a GameSystem.");
    pObject->setpSystem(this);
    mpObjects.push_back(std::move(pObject));
}

template <typename ObjType>
void GameSystem<ObjType>::removeObject(ObjType& object) {
    assert(object.getpSystem == this && "GameSyste::removeObject - GameObject is not member of the system.");
    object.setpSystem(nullptr);
    mpObjects.remove(object);
}

template <typename ObjType>
void GameSystem<ObjType>::sendMessageToObjects(const Message& message) const {
    for(const ObjectPtr& pObject : mpObjects) {
        pObject->handleMessage(message);
    }
}

template <typename ObjType>
void GameSystem<ObjType>::onAddObject(ObjType& object) {}

template <typename ObjType>
void GameSystem<ObjType>::onUpdateObject(sf::Time dt, ObjType& object) {}

template <typename ObjType>
void GameSystem<ObjType>::onUpdateEnd(sf::Time dt) {}

}
