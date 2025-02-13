#pragma once
#include <string>
#include <fstream>
#include <windows.h>
#include <ShlObj.h>

namespace Connection {
    std::string lastmessage = "no_message_found";

    std::string GetFilePath() {
        char path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
            return std::string(path) + "\\ExecutionManager.txt";
        }
        return "";
    }

    std::string ReadFileContent() {
        std::ifstream file(GetFilePath());
        if (!file.is_open()) return "file_not_found";

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return content;
    }

    void CreateConnection() {
        lastmessage = ReadFileContent();
    }

    std::string GetLastMessage() {
        lastmessage = ReadFileContent();
        return lastmessage;
    }

    void Reset() {
        std::ofstream file(GetFilePath(), std::ios::trunc);
        if (file.is_open()) {
            file.close();
            lastmessage = "no_message_found";
        }
    }

    bool AlreadyRead() {
        std::string current = ReadFileContent();
        return lastmessage == current;
    }
}
