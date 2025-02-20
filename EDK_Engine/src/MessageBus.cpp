#include <iostream>
#include "MessageBus.h"

MessageBus::MessageBus(){}

void MessageBus::postMessage(EventType type, void* addr) {
    msgQueue.push({type,addr});
}

void MessageBus::postImmediateMessage(EventType type, void* addr) {
    for(ISystem* system : ListenersLists[type]){
        system->handleMessage(type,addr);
    }
}

void MessageBus::handleQueue() {
    int i=0;
    while(i<MESSAGES_PER_FRAME && !msgQueue.empty()){
        Message msg = msgQueue.front();
        for(ISystem* system : ListenersLists[msg.type]){
            system->handleMessage(msg.type,msg.addr);
        }
        msgQueue.pop();
        i++;
    }
}

bool MessageBus::addListener(EventType type,ISystem* sys){
    if(ListenersLists.find(type)==ListenersLists.end()){
        /*std::cerr<<"MessageBus::addListener : call for unknown type"<<std::endl;
        return false;*/
        ListenersLists[type] = {};
    }
    ListenersLists.at(type).emplace_back(sys);
    if(std::find(ListenersLists.at(type).begin(),ListenersLists.at(type).end(),sys)==ListenersLists.at(type).end()){
        std::cerr<<"MessageBus::addListener : emplace_back failed"<<std::endl;
        return false;
    }else return true;

}