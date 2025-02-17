#ifndef ORPG_GAMEENGINE_CONSOLESYSTEM_H
#define ORPG_GAMEENGINE_CONSOLESYSTEM_H
#include "ISystem.h"
#include "EventsStructs.h"
#include <imgui.h>
#include <string>
#include <vector>
#include <map>

class ConsoleSystem : public ISystem{

public:
    ConsoleSystem();
    void ExecCommand(char* command_line);
    void Draw(const char* title, bool* p_open);
    std::vector<std::string>getCommandList(){return commandList;}
    void LogAdd(std::string str){msgLog.emplace_back(str);}

private:
    void handleMessage(EventType type,void* eventPtr) override;
    std::vector<std::string> msgLog={};
    std::vector<std::string> commandList={};
    std::map<EventType,std::string> msgTypeToString = {
            {ENGINE_TEST,"ENGINE_TEST"},
            {AUDIO_TEST,"AUDIO_TEST"},
            {RENDER_TEST,"RENDER_TEST"},
            {ERROR_TEST,"ERROR_TEST"},
            {ERRNO_TEST,"ERRNO_TEST"}
    };
    std::map<std::string,EventType> stringToMsgType = {
            {"ENGINE_TEST",ENGINE_TEST},
            {"AUDIO_TEST",AUDIO_TEST},
            {"RENDER_TEST",RENDER_TEST},
            {"ERROR_TEST",ERROR_TEST},
            {"ERRNO_TEST",ERRNO_TEST}
    };
};


#endif //ORPG_GAMEENGINE_CONSOLESYSTEM_H
