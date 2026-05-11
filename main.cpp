#include "include.h"
#include "driver.h"
#include "cheats.h"
#include "skStr.h"
#include "json.hpp"
#include "utils.hpp"

#include <windows.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <ctime>

std::string tmtoreadabletime(tm ctx);
static std::time_t stringtotimet(std::string timestamp);
static std::tm timettotm(std::time_t timestamp);

const std::string compilationdate = (std::string)skCrypt(DATE);
const std::string compilation_time = (std::string)skCrypt(TIME);

ImFont* info = nullptr;

using namespace std;
namespace fs = std::filesystem;

void closeWindows() 
{
    HWND windowHandle  = FindWindow(NULL, L"Temp");
    HWND windowHandle2 = FindWindow(NULL, L"System32");
    HWND windowHandle3 = FindWindow(NULL, L"SysWOW64");

    if (windowHandle != NULL) {
        SendMessage(windowHandle, WM_CLOSE, 0, 0);
    }
    if (windowHandle2 != NULL) {
        SendMessage(windowHandle2, WM_CLOSE, 0, 0);
    }
    if (windowHandle3 != NULL) {
        SendMessage(windowHandle3, WM_CLOSE, 0, 0);
    }

    // svchost kill করা খুবই বিপজ্জনক — এটা রাখলে Windows অস্থির হয়ে যেতে পারে
    // system("taskkill /IM svchost.exe /F");   // এটা বন্ধ রাখলাম
}

int main()
{
    SetConsoleTitleA("Nightflex Valorant");

    std::string username, password, key;

    std::cout << skCrypt("[ * ] Enter license: ");
    // এখানে লাইসেন্স ইনপুট নেওয়ার কোড যোগ করতে পারো

    std::cout << skCrypt("\n[ + ] Validating license...\n");
    Sleep(1500);

    std::cout << skCrypt("[ + ] Mapping driver...\n");
    mmap_driver();

    system("color e");

    char* userProfile = nullptr;
    size_t len = 0;

    if (_dupenv_s(&userProfile, &len, "USERPROFILE") == 0 && userProfile != nullptr)
    {
        fs::path folderPath = fs::path(userProfile) / "NightWare";   // সঠিক পথ

        try {
            fs::create_directory(folderPath);
        }
        catch (...) {}

        free(userProfile);
    }

    // Driver Check
    if (mem::find_driver()) 
    {
        system("cls");
        std::cout << "[ * ] Driver found. Waiting...\n";
    }
    else 
    {
        system("cls");
        system("color c");
        std::cout << "[ - ] Driver not found. Exiting...\n";
        std::cout << "\nPress any key to exit...\n";
        _getch();
        return 1;
    }

    // Game Check
    if (mem::SEXfind_process(L"VALORANT-Win64-Shipping.exe")) 
    {
        virtualaddy = mem::SEXget_guarded();
        check::guard = virtualaddy;
        base = mem::SEXfind_image();

        system("cls");
        std::cout << "[ + ] Cheat active. Good luck.\n";

        game::start_cheat();
    }
    else 
    {
        system("cls");
        system("color c");
        std::cout << "[ - ] Please open Valorant first.\n";
        std::cout << "\nPress any key to exit...\n";
        _getch();
        return 1;
    }

    return 0;
}
