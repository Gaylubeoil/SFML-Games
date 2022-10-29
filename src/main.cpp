#include "Game.hpp"

int main(){
    srand(time(0));

    Game game;

    while(game.getGameOver()){
        game.update();
        game.render();
    }

    return 0;
}