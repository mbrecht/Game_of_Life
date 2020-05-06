////////////////////////////////////////////
//                                        //
//          Game of Life v1.0             //
//           Michael Brecht               //
//                                        //
////////////////////////////////////////////

#include "game.h"

int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 900;
    const int FPS = 60;
    
    Game* game = new Game(screenWidth, screenHeight, "Game Of Life", FPS);
    
    game->SetAlive(2, 1);
    game->SetAlive(2, 2);
    game->SetAlive(2, 3);
    
    game->Run();
    
    return 0;
}