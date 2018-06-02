//JULIAN'S FIRST C++ GAME//


//Libraries
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

using namespace std;

//Function Prototypes
int humanTurn(int humanTotalScore, string name);
int randInt(int min, int max);
//int humanTwoTurn(int humanTwoTotalScore);
void printRules();

int main()
{
    int humanScore1;
    int humanScore2;
    string name1;
    string name2;

    string enter;
    string response1;
    
    cout << "Welcome to Julian's first multiplayer game." << endl;
    
    cout << "Please write player 1's name: ";
    getline(cin, name1);

    cout << "Please write player 2's name: ";
    getline(cin, name2);
    
    cout << "Hello " << name1 << " and " << name2 << "!" << endl;
    
    cout << "The rules go as follows (enter to continue): ";
    getline(cin, enter);
    
    printRules();
    
    labela:
    cout << "Would you like me to repeat the instructions (Y/N): \n";
    getline(cin, response1);
    
    if (response1 == "N" || response1 == "n" || response1 == "")
    {
        cout << "Let us begin!" << endl;
        
        while (humanScore1 < 100 || humanScore2 < 100) {
            humanScore1 = humanTurn(humanScore1, name1);
            cout << endl;
            cout << name1 << "'s Current Score: " << humanScore1 << endl;
            cout << name2 << "'s Current Score: " << humanScore2 << endl;
            getline(cin, enter);
            
            if (humanScore1 >= 100)
            {
                cout << "You won! Congratulations " << name1 << " >o<!" << endl;
                cout << "Quit program by pressing enter." << endl;
                getline(cin, enter);
                exit(1);
            }

            humanScore2 = humanTurn(humanScore2, name2);
            cout << name1 << "'s Current Score: " << humanScore1 << endl;
            cout << name2 << "'s Current Score: " << humanScore2 << endl;
            getline(cin, enter);
            
            if (humanScore2 >= 100)
            {
                cout << "You won! Congratulations " << name2 << " ^_^!" << endl;
                cout << "Quit program by pressing enter." << endl;
                getline(cin, enter);
                exit(1);
            }
        }
    }
    else if (response1 == "Y" || response1 == "y")
    {
        printRules();
        goto labela;
    }
    
}

int humanTurn(int humanTotalScore, string name)
{
    int firstRoll = 0;
    int totalScore = 0;
    string enter;
    char choice;
    
    label0:
    cout << name << ": Roll or hold the die (R/H): ";
    cin >> choice;
    
    if (choice == 'R' || choice == 'r')
    {
        firstRoll = 0;
        label1:
        firstRoll = randInt(1, 6);
        
        cout << name << " rolled a " << firstRoll << "!" << endl;
        
        switch (firstRoll)
        {
            case 1:
                totalScore = 0;
                cout << "The 1 made you lose all your non-banked points!" << endl;
                getline(cin, enter);
                cout << "You have a total of " << humanTotalScore << " points (banked)." << endl;
                return humanTotalScore;
                break;
            case 2:
                totalScore += 2;
                cout << "You earned 2 points, with a total of " << totalScore << " to bank. ";
                getline(cin, enter);
                break;
            case 3:
                totalScore += 3;
                cout << "You earned 3 points, with a total of " << totalScore << " to bank. ";
                getline(cin, enter);
                break;
            case 4:
                totalScore += 4;
                cout << "You earned 4 points, with a total of " << totalScore << " to bank. ";
                getline(cin, enter);
                break;
            case 5:
                totalScore += 5;
                cout << "You earned 5 points, with a total of " << totalScore << " to bank. ";
                getline(cin, enter);
                break;
            case 6:
                totalScore += 6;
                cout << "You earned 6 points, with a total of " << totalScore << " to bank. ";
                getline(cin, enter);
                break;
            default:
                cout << "Something wrong happened... ending game." << endl;
                exit(1);
                break;
        }
        if (totalScore >= 2)
        {
            cout << " Roll or Hold? (R/H): ";
            cin >> choice;
            
            if (choice == 'H' || choice == 'h')
            {
                humanTotalScore += totalScore;
                cout << name << " has banked their stash of points." << endl;
                getline(cin, enter);
                return humanTotalScore;
            }
            else if (choice == 'R' || choice == 'r')
                goto label1;
        }
        else
        {
            cout << "Rolling... (press enter)" << endl;
            getline(cin, enter);
            goto label1;
        }
    }
    else if ((choice == 'H' || choice == 'h') && totalScore == 0)
    {
        cout << "Sorry, you can't bank 0 points..." << endl;
        return 0;
    }
    else
    {
        cout << "Something went wrong..." << endl;
        exit(1);
        return 0;
    }
    return 0;
}

void printRules()
{
    string enter;
    
    cout << "If you roll the die and score between 2 and 6,\n";
    cout << "You will have the opportunity to roll to get more points.";
    getline(cin, enter);
    cout << "You can also hold and bank the current number of points you have rolled.";
    getline(cin, enter);
    cout << "However, if you roll a 1 then you lose the points" << endl;
    cout << "you have accummulated without banking.";
    getline(cin, enter);
}

int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
