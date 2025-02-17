#ifndef ORPG_GAMEENGINE_EVENTSSTRUCTS_H
#define ORPG_GAMEENGINE_EVENTSSTRUCTS_H


#include <string>
#include "ISystem.h"

enum EventType{
    ENGINE_TEST,
    AUDIO_TEST,
    RENDER_TEST,
    ERROR_TEST,
    ERRNO_TEST
    //TBA
};

struct EngineTestEvent{
    const EventType type=ENGINE_TEST;
    const ISystem* src;
    int var;
    std::string data;
    const std::string msg = "You should not be seeing this, contact developer";
};

struct AudioTestEvent{
    const EventType type=AUDIO_TEST;
    const ISystem* src;
    float pos[2];
    std::string fileName;
    const std::string msg = "You should not be seeing this, contact developer";
};

#endif //ORPG_GAMEENGINE_EVENTSSTRUCTS_H
