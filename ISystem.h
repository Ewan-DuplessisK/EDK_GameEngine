#ifndef ORPG_GAMEENGINE_ISYSTEM_H
#define ORPG_GAMEENGINE_ISYSTEM_H

#include <string>

enum EventType;

class ISystem {
public:
    virtual void handleMessage(EventType type,void* eventPtr)=0;
    unsigned int uID;
    std::string systemType;
};


#endif //ORPG_GAMEENGINE_ISYSTEM_H
