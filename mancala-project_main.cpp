#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;


void displayInstructions()
{
    cout << "\n-----Explination and Instuctions-----\n";
    cout << "The game board will display whenever you are prompted to choose a pocket.\n";
    cout << "Each pocket, including the players' stores, have a corresponding number.\n";
    cout << "Player One's store (on the left) is pocket 0. Player Two's store (on the right) is pocket 7.\n";
    cout << "The numbering of the pockets is accending counter clockwise.\n";
    cout << "This means that Player One's pockets are 11, 12, 13, 1, 2, and 3\n";
    cout << "Player Two's pockets are 4, 5, 6, 8, 9, and 10.\n";
    cout << "To play, you will input the number of the pocket you wish to pick up.\n";
    cout << "If you get an extra turn, you will be prompted to choose another pocket.\n\n";
}


void displayBoard(const vector<int> numStones)
{
    int length = 20;
    
    for(int i = 0; i <= (length * 2); ++i)
    {
        cout << "-";
    }
    cout << endl;
    
    cout << "|    | ";
    for(int i = 5; i >= 0; --i)
    {
        int pckt = i + 8;
        cout << setfill('0') << setw(2) << numStones.at(pckt) << " | ";
    }
    cout << "   |";
    cout << endl;
    
    cout << "| " << setfill('0') << setw(2) << numStones.at(0) << " |";
    for(int i = 0; i <= 28; ++i)
    {
        cout << "-";
    }
    cout << "| " << setfill('0') << setw(2) << numStones.at(7) << " |";
    cout << endl;
    
    cout << "|    | ";
    for(int i = 1; i <= 6; ++i)
    {
        int pckt = i;
        cout << setfill('0') << setw(2) << numStones.at(pckt) << " | ";
    }
    cout << "   |";
    cout << endl;
    
    for(int i = 0; i <= (length * 2); ++i)
    {
        cout << "-";
    }
    cout << endl;
}


void choosePocket(vector<int>& numStones, int& choice, const int turnCount)
{
    bool validChoice = false;
    bool invalidChoice;
    
    while (validChoice == false){
        cout << "Choose a pocket: ";
        cin >> choice;
        
        // Valid choice?
        if (turnCount%2 == 1){
            if (choice!=11 && choice!=12 && choice!=13  &&  choice!=1 && choice!=2 && choice!=3){
                invalidChoice = true;
            }
            else {
                invalidChoice = false;
            }
        }
        else if (turnCount%2 == 0){
            if (choice!=4 && choice!=5 && choice!=6  &&  choice!=8 && choice!=9 && choice!=10){
                invalidChoice = true;
            }
            else {
                invalidChoice = false;
            }
        }
        else {
            cout << "ERROR\n";
        }
        
        // Invalid choice
        if (invalidChoice == true){
            cout << "Invalid choice. Choose again.\n";
        }
        // Empty pocket
        else if (numStones.at(choice) == 0){
            cout << "Empty pocket. Choose again.\n";
        }
        else {
            validChoice = true;
        }
    }
}


void turn(vector<int>& numStones, int& turnCount)
{
    bool turnContinue = true;
    bool makeChoice = true;
    int choice;
    int lastPocket;
    
    ++turnCount;
    cout << "\nTurn " << turnCount << endl;
    
    // Who's turn
    if (turnCount%2 == 1){
        cout << "Player One's Turn\n";
    }
    else if (turnCount%2 == 0){
        cout << "Player Two's Turn\n";
    }
    else {
        cout << "*Player Turn ERROR*\n";
    }
    
    // Turn loop
    while (turnContinue == true){
        // Setting choice
        if (makeChoice == true){
            displayBoard(numStones);
            choosePocket(numStones, choice, turnCount);
        }
        else {
            cout << "Picking up opposite side\n";
            choice = 14 - lastPocket;
        }
        
        
        // Process turn
        int skip = 0;
        int hand = numStones.at(choice);
        numStones.at(choice) = 0;
        
        for (int x = 1; x <= hand+skip; x++){
            // reset count-up
            if (choice+x == 14){
                choice = choice - 14;
                //cout << "reset count-up.\n";
            }
            
            // If normal
            if (choice+x != 0 && choice+x != 7){
                numStones.at(choice+x) ++;
                cout << "Placed a stone at " << choice+x << ".\n";
            }
            // If store
            else {
                // Player One skip Player Two's store
                if (turnCount%2 == 1  &&  choice+x == 7){
                    cout << "Skipped " << choice+x << ".\n";
                    skip++;
                }
                // Player Two skip Player One's store
                else if (turnCount%2 == 0  &&  choice+x== 0){
                    cout << "Skipped " << choice+x << ".\n";
                    skip++;
                }
                // False alarm
                else {
                    numStones.at(choice+x+skip) ++;
                    cout << "Placed a stone in " << choice+x << ".\n";
                }
            }
            
            lastPocket = choice+x;
        }
        
        
        // Another turn?
            // Player 1
        if (turnCount%2 == 1){
            // Own store
            if (lastPocket == 0){
                turnContinue = true;
                makeChoice = true;
                cout << "Ended in store. Go again.\n";
            }
            // Empty pocket
            else if (numStones.at(lastPocket) == 1){
                // Player One's side
                if (lastPocket == 1 || lastPocket == 2 || lastPocket == 3 || lastPocket == 11 || lastPocket == 12 || lastPocket == 13){
                    // Opposite side isn't empty
                    if (numStones.at(14-lastPocket) > 0){
                        // This is when the last pocket is empty, it's player one's turn, last pocket was on player one's side, and the opposite side isn't empty.
                        turnContinue = true;
                        makeChoice = false;
                        cout << "Ended in empty pocket on your side. Use opposite pocket\n";
                    }
                    else {
                        turnContinue = false;
                        cout << "Ending turn.\n";
                    }
                }
                else {
                    turnContinue = false;
                    cout << "Ending turn.\n";
                }
            }
            // Else
            else {
                turnContinue = false;
                cout << "Ending turn.\n";
            }
            
            if (numStones.at(1) + numStones.at(2) + numStones.at(3) + numStones.at (11) + numStones.at(12) + numStones.at(13) == 0){
                turnContinue = false;
            }
        }
            // Player 2
        if (turnCount%2 == 0){
            // Own store
            if (lastPocket == 7){
                turnContinue = true;
                makeChoice = true;
                cout << "Ended in store. Go again.\n";
            }
            // Empty pocket
            else if (numStones.at(lastPocket) == 1){
                // Player Two's side
                if (lastPocket == 4 || lastPocket == 5 || lastPocket == 6 || lastPocket == 8 || lastPocket == 9 || lastPocket == 10){
                    // Opposite side isn't empty
                    if (numStones.at(14-lastPocket) > 0){
                        // This is when the last pocket is empty, it's player one's turn, last pocket was on player one's side, and the opposite side isn't empty.
                        turnContinue = true;
                        makeChoice = false;
                        cout << "Ended in empty pocket on your side. Use opposite pocket\n";
                    }
                    else {
                        turnContinue = false;
                        cout << "Ending turn.\n";
                    }
                }
                else {
                    turnContinue = false;
                    cout << "Ending turn.\n";
                }
            }
            // Else
            else {
                turnContinue = false;
                cout << "Ending turn.\n";
            }
            if (numStones.at(4) + numStones.at(5) + numStones.at(6) + numStones.at (8) + numStones.at(9) + numStones.at(10) == 0){
                turnContinue = false;
            }
        }
    }
}


void game(vector<int>& numStones, int& turnCount)
{
    bool c = true;
    while (c == true)
    {
        turn(numStones, turnCount);
        // When game is over (both sides are empty)
        if (numStones.at(1) + numStones.at(2) + numStones.at(3) + numStones.at(4) + numStones.at(5) + numStones.at(6)
          + numStones.at(8) + numStones.at(9) + numStones.at(10)+ numStones.at(11)+ numStones.at(12)+ numStones.at(13) ==  0){
            c = false;
        }
    }
}


int main()
{
    // Variables
    vector<int> numStones (14,4);
    numStones.at(0) = 0;
    numStones.at(7) = 0;

    int turnCount = 0;
    
    cout << "Time to play Mancala!\n";
    displayInstructions();
    game(numStones, turnCount);
    
    // Game Over
    cout << "\n \n----------Game Over----------\n";
    if (numStones.at(0) > numStones.at(7)){
        cout << "Player One Wins with " << numStones.at(0) << " points!\n";
    }
    if (numStones.at(0) < numStones.at(7)){
        cout << "Player Two Wins with " << numStones.at(7) << " points!\n";
    }
    if (numStones.at(0) == numStones.at(7)){
        cout << "It's a tie with " << numStones.at(0) << " points!\n";
    }
    cout << "Thank you for playing!\n";

    return 0;
}










