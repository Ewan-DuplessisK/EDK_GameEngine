#include "ConsoleSystem.h"
#include <iostream>
#include "MessageBus.h"

static void  Strtrim(char* s){ char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

ConsoleSystem::ConsoleSystem(){
    MessageBus::getInstance().addListener(ENGINE_TEST,this);
    commandList={"CLEAR","HELP"};
    for(const auto& commandPair : msgTypeToString){
        commandList.emplace_back(commandPair.second);
    }

}


void ConsoleSystem::ExecCommand(char* command_line){
    string str = command_line;
    string command = str.substr(0,str.find(" "));
    // Process command
    if (command == "CLEAR"){
        msgLog.clear();
    }
    else if (command == "HELP"){
        string cList = "Commands:\n";
        for(string command:commandList){
            cList+=command+"\n";
        }
        msgLog.emplace_back(cList);
    }
    else{
        if(stringToMsgType.find(command)!=stringToMsgType.end()){//if command in string-enum event map
            if(str.find(" ")==str.npos){//if command is a single word
                string err = "Missing parameter(s) for event: ";
                err+=command;
                msgLog.emplace_back(err);
            }
            else{
                string buff = str.substr(str.find(" "));
                buff.erase(0,1);
                int subType = stoi(buff.substr(0,buff.find(" ")));
                if(buff.find(" ")==buff.npos){ //if command is only two words
                    string err = "Missing data for event: ";
                    err+=command +" "+std::to_string(subType);
                    msgLog.emplace_back(err);
                }
                else{
                    buff = buff.substr(buff.find(" "));
                    buff.erase(0,1);
                    //MessageBus::getInstance().postImmediateMessage({stringToMsgType.at(command),subType,buff.data()});
                }
            }
        }
        else{
            string str = "Unknown command: ";
            str.append(command_line);
            msgLog.emplace_back(str);
        }
    }
    // On command input, we scroll to bottom even if AutoScroll==false
    //ScrollToBottom = true;
}

static int InputCallback(ImGuiInputTextCallbackData* data){
    ConsoleSystem* console = (ConsoleSystem*)data->UserData;
    switch (data->EventFlag){
    case ImGuiInputTextFlags_CallbackCompletion:{
        // Locate beginning of current word
        const char* word_end = data->Buf + data->CursorPos;
        const char* word_start = word_end;
        while (word_start > data->Buf){
            const char c = word_start[-1];
            if (c == ' ' || c == '\t' || c == ',' || c == ';')break;
            word_start--;
        }

        // Build a list of candidates
        std::vector<string>candidates={};
        const std::vector<string>commands=console->getCommandList();
        string inputStr = string(data->Buf,data->CursorPos);
        std::transform(inputStr.begin(),inputStr.end(),inputStr.begin(),::toupper);
        for(const string& command : commands){
            if(command.substr(0,data->CursorPos)==inputStr)candidates.emplace_back(command); //use substring to match start of word
        }
        sort(candidates.begin(),candidates.end()); //order alphabetically

        if (candidates.empty()){
            // No match
            //AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
        }
        else if (candidates.size() == 1){
            // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
            data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
            data->InsertChars(data->CursorPos, candidates[0].c_str());
            data->InsertChars(data->CursorPos, " ");
        }
        else{
            // Multiple matches. Complete as much as we can..
            // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
            //TODO fix multi matches
            auto smin = *std::min_element(candidates.begin(), candidates.end(),[] (const std::string& s1, const std::string& s2) {return s1.length() < s2.length(); });
            int i=data->CursorPos;
            char testChar;
            bool noDifference=true;
            while (noDifference && i<smin.length()){
                testChar = candidates[0].at(i);
                std::cout<<testChar<<std::endl;
                for(string candidate:candidates){
                    if(candidate.at(i)!=testChar){
                        noDifference = false;
                    }
                }
                i++;
            }
            data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
            data->InsertChars(data->CursorPos, candidates[0].substr(0,i-1).c_str()); //cut candidates[0] to match length and replace the input


            // List matches
            string strTmp = "Matches: ";
            for(string candidat:candidates){
                strTmp+=candidat+" ";
            }
            console->LogAdd(strTmp);
        }

        break;
    }
    }
    return 0;
}

void ConsoleSystem::Draw(const char* title, bool* p_open){
    char InputBuf[256]={};
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(title, p_open)){
        ImGui::End();
        return;
    }
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Close Console"))
            *p_open = false;
        ImGui::EndPopup();
    }

    /*ImGui::TextWrapped(
            "This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
            "implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
    ImGui::TextWrapped("Enter 'HELP' for help.");*/


    /*if (ImGui::SmallButton("Add Debug Text"))  { AddLog("%d some text", Items.Size); AddLog("some more text"); AddLog("display very important message here!"); }
    ImGui::SameLine();
    if (ImGui::SmallButton("Add Debug Error")) { AddLog("[error] something went wrong"); }
    ImGui::SameLine();
    if (ImGui::SmallButton("Clear"))           { ClearLog(); }
    ImGui::SameLine();*/
    bool copy_to_clipboard = ImGui::SmallButton("Copy");
    //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

    ImGui::Separator();

    // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (ImGui::BeginPopupContextWindow())
            {
                //if (ImGui::Selectable("Clear")) ClearLog();
                ImGui::EndPopup();
            }

            // Display every line as a separate entry so we can change their color or add custom widgets.
            // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
            // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
            // to only process visible items. The clipper will automatically measure the height of your first item and then
            // "seek" to display only items in the visible area.
            // To use the clipper we can replace your standard loop:
            //      for (int i = 0; i < Items.Size; i++)
            //   With:
            //      ImGuiListClipper clipper;
            //      clipper.Begin(Items.Size);
            //      while (clipper.Step())
            //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            // - That your items are evenly spaced (same height)
            // - That you have cheap random access to your elements (you can access them given their index,
            //   without processing all the ones before)
            // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
            // We would need random-access on the post-filtered list.
            // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
            // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
            // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
            // to improve this example code!
            // If your items are of variable height:
            // - Split them into same height items would be simpler and facilitate random-seeking into your list.
            // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
            if (copy_to_clipboard)
                ImGui::LogToClipboard();
            for(string msg : msgLog){
                ImGui::TextUnformatted(msg.c_str());
            }
            /*for (const char* item : Items)
            {
                if (!Filter.PassFilter(item))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                ImVec4 color;
                bool has_color = false;
                if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
                else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
                if (has_color)
                    ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(item);
                if (has_color)
                    ImGui::PopStyleColor();
            }*/
            if (copy_to_clipboard)
                ImGui::LogFinish();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            /*if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                ImGui::SetScrollHereY(1.0f);
            ScrollToBottom = false;*/

            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::Separator();

    // Command-line
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion;
    if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags,&InputCallback, (void*)this)){
        char* s = InputBuf;
        Strtrim(s);
        if (s[0])
            ExecCommand(s);
        //strcpy(s, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    ImGui::End();
}

void ConsoleSystem::handleMessage(EventType type, void* addr){
    string str = "";
    switch (type) {
        case ENGINE_TEST:{
            EngineTestEvent* event = (EngineTestEvent*) addr;
            str += "[" + msgTypeToString.at(event->type) + " : " + event->src->systemType + "(" + to_string(event->src->uID) + ")] ";
            str += "var: " + to_string(event->var) + "  data: " + event->data + "  " + event->msg;
        }
        case AUDIO_TEST:{
            AudioTestEvent* event = (AudioTestEvent*) addr;
            str += "[" + msgTypeToString.at(event->type) + " : " + event->src->systemType + "(" + to_string(event->src->uID) + ")] ";
            str += "Play from (" + to_string(event->pos[0]) + "," + to_string(event->pos[1]) + ") sound: " + event->fileName + "  " + event->msg;
        }
        default:{
            str += "[Unknown] Received unhandled event type, contact developer";
        }
    }
    msgLog.emplace_back(str);
}