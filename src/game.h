#ifndef GAME_H
#define GAME_H

#include "raylib.h"


const int BOARD_WIDTH = 100;
const int BOARD_HEIGHT = 100;

class Game {
    struct Tile {
        bool isAlive = false;
        
        void onUpdate(int x_, int y_, Tile* board) {
            int neighbors = 0;
            for(int y = y_ - 1; y <= y_ + 1; y++) {
                for(int x = x_ - 1; x <= x_ + 1; x++) {
                    if(!(x < 0 || y < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT)) {
                        if(!(x == x_ && y == y_)) {
                            if(board[x * BOARD_WIDTH + y].isAlive) {
                                neighbors += 1;
                            }
                        }
                    }
                }
            }
            
            if(board[x_ * BOARD_WIDTH + y_].isAlive && (neighbors == 2 || neighbors == 3)) { 
                isAlive = true; 
            } else if(!board[x_ * BOARD_WIDTH + y_].isAlive && neighbors == 3) {
                isAlive = true; 
            } else { 
                isAlive = false; 
            }
            
        }
    };
    
    public:
    Game(int width, int height, char* title, int FPS);
    void Run();
    
    int screenWidth()           { return screenWidth_; }
    int screenHeight()          { return screenHeight_; }
    int FPS()                   { return FPS_; }
    bool Running()              { return running_; }
    void UpdateFPS(int FPS)     { FPS_ = FPS; SetTargetFPS(FPS_); }
    void SetAlive(int x, int y) { board_[x * BOARD_WIDTH + y].isAlive = true; }
    void SetDead(int x, int y)  { board_[x * BOARD_WIDTH + y].isAlive = false; }
    
    private:
    
    int screenWidth_;
    int screenHeight_;
    int scaleX_, scaleY_;
    int FPS_;
    int offset_;
    int frame_;
    
    bool running_;
    bool playing_;
    bool update_;
    bool drawingMode_;
    bool drawing_;
    
    Rectangle playButton_;
    
    Tile *board_, *board2_;
    //Tile* pBoard_;
    
    void Update();
    void HandleInput();
    void UpdateBoard();
    bool CheckCell(int x, int y);
    void DrawUI();
    void DrawBoard(Tile* board);
    void DrawCell(int x, int y, bool isAlive);
    void CloseGame();
    void ToggleCell(int x, int y);
    void TogglePlaying();
    
    int Index(int x, int y);
    
    protected:
};

#endif