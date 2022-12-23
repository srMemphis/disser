#pragma once
#include <FMEngine.h>

class LogWidget
{
public:

    static void Draw(bool* p_open = NULL)
    {
        if (!ImGui::Begin("Log", p_open))
        {
            ImGui::End();
            return;
        }

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Filtering
        //Logger::FilterDisable(Logger::Saverity::Info | Logger::Saverity::Debug);
        Logger::Filter();

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        //Table
        static ImGuiTableFlags tableFlags = ImGuiTableFlags_BordersInnerH;

        if (ImGui::BeginTable("Logger Table", 3, tableFlags))
        {
            ImGui::TableSetupColumn("Saverity", ImGuiTableColumnFlags_WidthFixed, 70.0f);
            ImGui::TableSetupColumn("Time", ImGuiTableColumnFlags_WidthFixed, 80.0f);
            ImGui::TableSetupColumn("Message", ImGuiTableColumnFlags_None);
            //ImGui::TableHeadersRow();

            //// using clipper for large vertical list
            //ImGuiListClipper clipper;
            //clipper.Begin(Logger::GetFilteredMessageCount());
            //while (clipper.Step())
            //{
            //    for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
            //    {   
            //        ImGui::TableNextRow();
            //        auto mess = Logger::GetFilteredMessage(row);
            //        auto len = Logger::GetFilteredMessageLength(row) - Logger::c_SaverityOffset - Logger::c_TimeOffset;
            //        // Saverity
            //        ImGui::TableSetColumnIndex(0);
            //        ImGui::TextUnformatted(mess, mess + Logger::c_SaverityOffset);
            //        mess = mess + Logger::c_SaverityOffset;

            //        // Time
            //        ImGui::TableSetColumnIndex(1);
            //        ImGui::TextUnformatted(mess, mess + Logger::c_TimeOffset);
            //        mess = mess + Logger::c_TimeOffset;

            //        // Message
            //        ImGui::TableSetColumnIndex(2);
            //        ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + ImGui::GetColumnWidth(2));
            //        ImGui::TextUnformatted(mess, mess + len);
            //        ImGui::PopTextWrapPos();
            //    }


            for (int row = 0; row < Logger::GetFilteredMessageCount(); row++)
            {
                ImGui::TableNextRow();
                auto mess = Logger::GetFilteredMessage(row);
                auto len = Logger::GetFilteredMessageLength(row) - Logger::c_SaverityOffset - Logger::c_TimeOffset;
                // Saverity
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted(mess, mess + Logger::c_SaverityOffset);
                mess = mess + Logger::c_SaverityOffset;

                // Time
                ImGui::TableSetColumnIndex(1);
                ImGui::TextUnformatted(mess, mess + Logger::c_TimeOffset);
                mess = mess + Logger::c_TimeOffset;

                // Message
                ImGui::TableSetColumnIndex(2);
                ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + ImGui::GetColumnWidth(2));
                ImGui::TextUnformatted(mess, mess + len);
                ImGui::PopTextWrapPos();
            }

            ImGui::EndTable();
        }





        // Word wrap region
        //ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        //ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        //ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + vMax.x - vMin.x);
        //ImGui::TextUnformatted(Logger::GetFilteredMessage(0), Logger::GetFilteredBufferEnd());
        //ImGui::PopTextWrapPos();




        ImGui::PopStyleVar();

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
        ImGui::End();
    }


private:
    LogWidget() {}
    static bool AutoScroll;  // Keep scrolling if already at the bottom.
};

bool LogWidget::AutoScroll = true;
