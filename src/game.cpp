#include "game.h"

#include <iostream>
using namespace std;


Game::Game(int width, int height, char* title, int FPS) {
    screenWidth_ = width;
    screenHeight_ = height;
    scaleX_ = (screenWidth_ / BOARD_WIDTH) * 0.9; 
    scaleY_ = (screenHeight_ / BOARD_HEIGHT) * 0.9; 
    board_ = new Tile[BOARD_WIDTH * BOARD_HEIGHT];
    board2_ = new Tile[BOARD_WIDTH * BOARD_HEIGHT];
    running_ = true;
    playing_ = false;
    update_ = false;
    drawing_ = false;
    drawingMode_ = false;
    FPS_ = FPS;
    frame_ = 0;
    
    InitWindow(screenWidth_, screenHeight_, title);
    
    SetTargetFPS(FPS_);
    
    offset_ = (screenWidth_ - (scaleY_ * BOARD_WIDTH)) /2;
    playButton_ = Rectangle{screenWidth_ - 150, 20, 120, 40};
    
}
    
void Game::Run() {
    while(running_) {
        running_ = !WindowShouldClose();
        Update();
        
        if(!(frame_ % 15)) update_ = true;
        
        frame_++;
    }
    CloseGame();
}

void Game::Update() {
    HandleInput();  
    
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawBoard(board_);
    EndDrawing();
    
    if(playing_ && update_) {
        UpdateBoard();
        update_ = false;
    }
}

void Game::HandleInput() {
    int x = (GetMouseX() - offset_) / scaleY_;
    int y = GetMouseY() / scaleY_;
    bool isInPlayArea = ((GetMouseX() > offset_) && GetMouseX() < (offset_ * 2) + (BOARD_WIDTH * scaleX_) && (GetMouseY() > 0) && (GetMouseY() < BOARD_HEIGHT * scaleY_));
    bool isInButtonArea = ((GetMouseX() > playButton_.x) && (GetMouseX() < playButton_.x + playButton_.width) && (GetMouseY() > playButton_.y) && (GetMouseY() < playButton_.y + playButton_.height));
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isInPlayArea) { 
        drawingMode_ = !board_[Index(x, y)].isAlive;
        ToggleCell(x, y
        );
        drawing_ = true;
    }
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && isInPlayArea && drawing_) {
        if(drawingMode_) SetAlive(x, y);
        if(!drawingMode_) SetDead(x, y);
    }
    if(IsMouseButtonUp(MOUSE_LEFT_BUTTON)) { drawing_ = false; }
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isInButtonArea) { TogglePlaying(); }
}

void Game::UpdateBoard() {
    for(int y = 0; y < BOARD_WIDTH; y++) {
        for(int x = 0; x < BOARD_HEIGHT; x++) {
            board2_[Index(x, y)].isAlive = board_[Index(x, y)].isAlive;
        }
    }
    
    for(int y = 0; y < BOARD_WIDTH; y++) {
        for(int x = 0; x < BOARD_HEIGHT; x++) {
            board_[Index(x, y)].onUpdate(x, y, board2_);
        }
    }
}

void Game::DrawBoard(Tile* board) {
    
    for(int x = 0; x < BOARD_WIDTH; x++) {
        for(int y = 0; y < BOARD_HEIGHT; y++) {
            DrawCell(x, y, board[Index(x, y)].isAlive);
        }                
    }
    //Screen Border
    DrawRectangleLines(offset_, 0, BOARD_WIDTH * scaleY_, BOARD_HEIGHT * scaleY_, BLACK);
    //Play Button
    
    DrawUI();
    }

void Game::DrawUI() {
    DrawRectangleLines(playButton_.x, playButton_.y, playButton_.width, playButton_.height, BLACK);
    
    int centerX = playButton_.x + playButton_.width / 2;
    int centerY = playButton_.y + playButton_.height / 2;
    
    if(playing_) {
        DrawRectangle(centerX - 5, playButton_.y + 8, 5, playButton_.height - 13, BLACK);
        DrawRectangle(centerX + 5, playButton_.y + 8, 5, playButton_.height - 13, BLACK);
    } else {
        DrawTriangle(Vector2({centerX, playButton_.y + 5}), Vector2({centerX, playButton_.y + playButton_.height - 5}), Vector2({centerX + 16 , centerY}), BLACK);
    }
    
}

void Game::DrawCell(int x, int y, bool isAlive) {
    if(isAlive) DrawRectangle((x * scaleY_) + offset_, y * scaleY_, scaleY_, scaleY_, BLACK);
}

void Game::CloseGame() {
    delete board_;
    delete board2_;
    CloseWindow();
}

void Game::ToggleCell(int x, int y) {
    board_[Index(x, y)].isAlive = !board_[Index(x, y)].isAlive;
}

void Game::TogglePlaying() { 
    playing_ = !playing_; 
    update_ = true;
    frame_ = 1;
}

int Game::Index(int x, int y) {
    return x * BOARD_WIDTH + y;
}