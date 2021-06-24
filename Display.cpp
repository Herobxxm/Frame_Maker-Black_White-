#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

COORD StartOfScreen = {0, 0};

void color_text(int color, string text) // color = 7 white  color = 12 red
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << text << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void set_cursor_pos(COORD c) // set curser
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

COORD get_cursor_pos() // get curser
{
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
        printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
    COORD Pos;
    Pos.X = screenBufferInfo.dwCursorPosition.X;
    Pos.Y = screenBufferInfo.dwCursorPosition.Y;
    return Pos;
}

void clearScreen()
{
    set_cursor_pos(StartOfScreen);
    for (int i = 0; i < 43; i++)
        cout << "                                                                                                           " << endl;
    set_cursor_pos(StartOfScreen);
}

void runVideo(string Path)
{
    ifstream File;
    File.open(Path);
    if (!File)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << endl << "Unable to open file.";
        Sleep(1500);
        return;
    }
    else
    {
        clearScreen();
        string line;
        string print = "";
        bool GG = false;
        while (getline(File, line))
        {
            if (line == "nextFrame"){
                clearScreen();
                cout << print;
                print = "";
                Sleep(20); // Adjust your frame rate here.
                GG = false;
            }
            else
            {
                for (auto x : line)
                {
                    if(x == '0')   
                        print += " ";
                    else if (x == '1')
                        print += "X"; // Adjust your output here
                }
                print += "\n";
            }
        }
    }
}

int main()
{
    while (true)
    {
        clearScreen();
        string File;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Write your .txt here plese:";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        getline(cin, File);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        runVideo(File);
    }
}
