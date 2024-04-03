#include <iostream>
#include <string>
#include <random>

void generateRandomNumber(int& result) {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution for integers between 1 and 3
    std::uniform_int_distribution<int> distribution(1, 3);

    // Generate a random number
    result = distribution(gen);
};


class RockPaperScissors {
public:
    int botPlayStyle; // 1 for aggro, 2 for soft, 3 for random
    int botMove;
    int playerMove;
    bool activeGameStatus = false;
    int turnNo = 0;

    void startGame(){
        activeGameStatus = true;
        turnNo = 1;
        std::cout << "Welcome to RockPaperScissors!" << std::endl;
        playerTurn();
    };

    void endGame(){
        activeGameStatus = false;
        std::cout << "Game Over!" << std::endl;
    }

    void evalTurn(){
        if (playerMove == botMove){
            std::cout << "Draw! Try again!" << std::endl;
            playerTurn();
        } else if (playerMove == 1 && botMove == 2){
            std::cout << "Paper beats Rock - Bot WINS!" << std::endl;
            endGame();
        } else if (playerMove == 1 && botMove == 3){
            std::cout << "Rock beats Scissors - You WIN!" << std::endl;
            endGame();
        } else if (playerMove == 2 && botMove == 1){
            std::cout << "Paper beats Rock - You WIN!" << std::endl;
            endGame();
        } else if (playerMove == 2 && botMove == 3){
            std::cout << "Scissors beats Paper - Bot WINS!" << std::endl;
            endGame();
        } else if (playerMove == 3 && botMove == 1){
            std::cout << "Rock beats Scissors - Bot WINS!" << std::endl;
            endGame();
        } else if (playerMove == 3 && botMove == 2){
            std::cout << "Scissors beats Paper - You WIN!" << std::endl;
            endGame();
        };
    };

    void playerTurn(){
        std::string playerInput;
        bool validInput;
        while (!validInput){
            std::cout << "Pick one: [R]ock [P]aper [S]cissors -> ";
            std::cin  >> playerInput;
            if (playerInput == "r" || playerInput == "R"){
                std::cout << "You picked Rock!" << std::endl;
                playerMove = 1;
                validInput = true;
            } else if (playerInput == "p" || playerInput == "P"){
                std::cout << "You picked Paper!" << std::endl;
                playerMove = 2;
                validInput = true;
            } else if (playerInput == "s" || playerInput == "S"){
                std::cout << "You picked Scissors!" << std::endl;
                playerMove = 3;
                validInput = true;
            } else {
                std::cout << "Incorrect Input!" << std::endl;
            }
        };
        turnNo++;
        botTurn();
    };

    void botPlaysRandom(){
        int num;
        generateRandomNumber(num);
        switch (num) {
            case 1:
                std::cout << "Bot plays Rock!" << std::endl;
                botMove = 1;
            break;
            case 2:
                std::cout << "Bot plays Paper!" << std::endl;
                botMove = 2;
            break;
            case 3:
                std::cout << "Bot plays Scissors!" << std::endl;
                botMove = 3;
            break;
        };
    };

    void botTurn(){
        if (turnNo == 2){
            if (botPlayStyle == 1){
                std::cout << "Bot plays Rock!" << std::endl;
                botMove = 1;
            } else if (botPlayStyle == 2){
                std::cout << "Bot plays Paper!" << std::endl;
                botMove = 2;
            } else if (botPlayStyle == 3){
                botPlaysRandom();
            };
        } else if (turnNo == 4){
            if (botPlayStyle == 1){
                std::cout << "Bot plays Paper!" << std::endl;
                botMove = 2;
            } else if (botPlayStyle == 2){
                switch (playerMove){
                    case 1:
                        std::cout << "Bot plays Scissors!" << std::endl;
                        botMove = 3;
                    break;
                    case 2:
                        std::cout << "Bot plays Rock!" << std::endl;
                        botMove = 1;
                    break;
                    case 3:
                        std::cout << "Bot plays Paper!" << std::endl;
                        botMove = 2;
                    break;
                };
            } else if (botPlayStyle == 3){
                botPlaysRandom();
            };
        } else if (turnNo == 6) {
            if (botPlayStyle == 1){
                switch (playerMove){
                    case 1:
                        std::cout << "Bot plays Paper!" << std::endl;
                        botMove = 2;
                    break;
                    case 2:
                        std::cout << "Bot plays Scissors!" << std::endl;
                        botMove = 3;
                    break;
                    case 3:
                        std::cout << "Bot plays Rock!" << std::endl;
                        botMove = 1;
                    break;
                };
            } else {
                botPlaysRandom();
            };
        } else {
            botPlaysRandom();
        };
        turnNo++;
        evalTurn();
    };
};

int main(int argCount, char* argVector[]){
    RockPaperScissors activeGame;
    if (argCount < 2){
        int rng;
        generateRandomNumber(rng);
        activeGame.botPlayStyle = rng;
    } else {
        std::string arg1 = argVector[1];
        if (arg1 == "aggro"){
            activeGame.botPlayStyle = 1;
        } else if (arg1 == "soft"){
            activeGame.botPlayStyle = 2;
        } else if (arg1 == "random"){
            activeGame.botPlayStyle = 3;
        } else {
            std::cout << "usage: ./RockPaperScissors [aggro | soft | random]" << std::endl;
            std::cout << "leave args empty for a randomized pick between these 3 playstyles" << std::endl;
            return 0;
        };
    };
    activeGame.startGame();
    return 0;
};
