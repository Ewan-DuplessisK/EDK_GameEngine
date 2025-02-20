#ifndef ORPG_GAMEENGINE_MESSAGEBUS_H
#define ORPG_GAMEENGINE_MESSAGEBUS_H
#include <queue>
#include <map>
#include <string>
#include "EventsStructs.h"
#include "ISystem.h"
using namespace std;
#define MESSAGES_PER_FRAME 124

struct Message{EventType type; void* addr;};

class MessageBus {

private:
    MessageBus();
    queue<Message>msgQueue;
    std::map<EventType,std::vector<ISystem*>> ListenersLists;
    int immediateMessagesThisFrame = 0;
public:
    static MessageBus& getInstance(){
        static MessageBus instance;
        return instance;
    };
    void postMessage(EventType type, void* addr);
    void postImmediateMessage(EventType typ, void* addr);
    void handleQueue();
    MessageBus(MessageBus const&)=delete;
    void operator=(MessageBus const&)=delete;
    bool addListener(EventType type,ISystem* sys);
};


#endif //ORPG_GAMEENGINE_MESSAGEBUS_H
