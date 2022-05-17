#include <iostream>
#include <vector>
#include <deque>

#include "Windows.h"

#include <vector>
#include <chrono>
#include <set>
#include <thread>


namespace Position {

    const int x = 0;
    const int y = 0;

}


int main() {

    std::vector<std::pair<int, int>> CursorLogs;
    bool Not = false;

    while (true) {
        POINT p;
        GetCursorPos(&p);

        std::cout << p.x << " ";
        std::cout << p.y << std::endl;

        CursorLogs.emplace_back(p.x, p.y);

        // Check on couple
        if (CursorLogs.size() == 10) {
            size_t count = 0;

            for (const auto el : CursorLogs) {
                if (el == CursorLogs[9]) {
                    count++;
                }
            }

            if (count >= 5) {
                std::cout << "Wait" << std::endl;
                std::set < std::pair<int, int>> MoveDetect;
                ShowCursor(FALSE); // Hide cursor

                while (MoveDetect.size() < 2) {
                    POINT p;
                    GetCursorPos(&p);
                    MoveDetect.emplace(p.x, p.y);
                    std::cout << "Not activity" << std::endl;

                }
                MoveDetect.clear();

                // Time to set in position
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));

                POINT p;
                GetCursorPos(&p);

                std::pair<int, int> SetCurrently{ p.x, p.y };

                // Chech cursor position
                if (SetCurrently.first == Position::x && SetCurrently.second == Position::y) {
                    std::cout << "Accecs" << std::endl; CursorLogs.clear();  ShowCursor(TRUE);
                    system("clear");
                }
                else {
                    // Some bad
                    std::cout << "Access denied" << std::endl;
                    CursorLogs.clear(); // Comment out in release

                    //
                }

            }
            else { CursorLogs.clear(); }


        }



        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }



}