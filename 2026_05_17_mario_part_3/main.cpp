#include <iostream>
#include <windows.h>
#include "Level.hpp"

int main() {
    const int windowWidth = 80;
    const int windowHeight = 25;

    Level gameLevel(windowWidth, windowHeight);

    gameLevel.render(); 

    do {
        bool needRender = gameLevel.update(); 
        
        if (needRender) {
            gameLevel.render();
        }

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}