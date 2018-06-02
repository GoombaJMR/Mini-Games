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
int humanTurn(int humanTotalScore);
int randInt(int min, int max);
//int humanTwoTurn(int humanTwoTotalScore);
int computerTurn(int computerTotalScore);
void printRules();

int main()
{
    int humanScore;
    int computerScore = 0;
    string name;
    string enter;
    string response1;
    
    cout << "Welcome to PIG." << endl;
    cout << "Please write your first name: ";
    getline(cin, name);
    
    cout << "Hello " << name << "!" << endl;
    cout << "The rules go as follows (enter to continue): ";
    getline(cin, enter);
    
    printRules();
    
    labela:
    cout << "Would you like me to repeat the instructions (Y/N): ";
    getline(cin, response1);
    cout << endl;
    
    if (response1 == "N" || response1 == "n" || response1 == "")
    {
        cout << "Let us begin!" << endl;
        while (humanScore < 100 || computerScore < 100) {
            humanScore = humanTurn(humanScore);
            cout << endl;
            cout << "Your Current Score: " << humanScore << endl;
            cout << "CPU's Current Score: " << computerScore << endl;
            getline(cin, enter);
            if (humanScore >= 100)
            {
                cout << "You won! Congratulations " << name << " >o<!" << endl;
                cout << "Quit program by pressing enter." << endl;
                getline(cin, enter);
                exit(1);
            }
            computerScore = computerTurn(computerScore);
            cout << "CPU's Current Score: " << computerScore << endl;
            cout << "Your Current Score: " << humanScore << endl;
            getline(cin, enter);
            if (computerScore >= 100)
            {
                cout << "You lost! It's okay, " << name << " ..." << endl;
                cout << "Quit program by pressing enter." << endl;
                getline(cin, enter);
                exit(1);
            }
        }
        if (humanScore >= 100)
        {
            cout << "You won! Congratulations " << name << " >o<!" << endl;
            cout << "Quit program by pressing enter." << endl;
            getline(cin, enter);
            exit(1);
        }
        else if (computerScore >= 100)
        {
            cout << "You lost! It's okay, " << name << " ..." << endl;
            cout << "Quit program by pressing enter." << endl;
            getline(cin, enter);
            exit(1);
        }
    }
    else if (response1 == "Y" || response1 == "y")
    {
        printRules();
        goto labela;
    }
    
}

int humanTurn(int humanTotalScore)
{
    int firstRoll = 0;
    int totalScore = 0;
    string enter;
    char choice;
    
    cout << "Roll or hold the die (R/H): ";
    cin >> choice;
    
    if (choice == 'R' || choice == 'r')
    {
        label1:
        firstRoll = randInt(1, 6);
        
        cout << "You rolled a " << firstRoll << "!" << endl;
        
        switch (firstRoll)
        {
            case 1:
                totalScore = 0;
                cout << "The 1 made you lose all your non-banked points!" << endl;
                getline(cin, enter);
                cout << "You now have " << totalScore << " points to bank." << endl;
                cout << "You have a total of " << humanTotalScore << " points (banked)." << endl;
                getline(cin, enter);
                return humanTotalScore;
                break;
            case 2:
                totalScore += 2;
                cout << "You have earned 2 points!" << endl;
                cout << "You now have " << totalScore << " points to bank." << endl;
                getline(cin, enter);
                break;
            case 3:
                totalScore += 3;
                cout << "You have earned 3 points!" << endl;
                cout << "You now have " << totalScore << " points to bank." << endl;
                getline(cin, enter);
                break;
            case 4:
                totalScore += 4;
                cout << "You have earned 4 points!" << endl;
                cout << "You now have " << totalScore << " points to bank." << endl;
                getline(cin, enter);
                break;
            case 5:
                totalScore += 5;
                cout << "You have earned 5 points!" << endl;
                cout << "You now have " << totalScore << " points to bank." << endl;
                getline(cin, enter);
                break;
            case 6:
                totalScore += 6;
                cout << "You have earned 6 points!" << endl;
                cout << "You now have " << totalScore << " points to bank." << endl;
                getline(cin, enter);
                break;
            default:
                cout << "Something wrong happened... ending game." << endl;
                exit(1);
                break;
        }
        if (totalScore >= 2)
        {
            cout << "Roll or Hold? (R/H): ";
            cin >> choice;
            
            if (choice == 'H' || choice == 'h')
            {
                humanTotalScore += totalScore;
                cout << "You have banked your stash of points." << endl;
                getline(cin, enter);
                return humanTotalScore;
            }
            else if (choice == 'R' || choice == 'r')
                goto label1;
            else
            {
                cout << "You did not follow instructions... ending game." << endl;
                exit(1);
            }
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
        cout << "Sorry, you can't bank 0 points... ending game now." << endl;
        exit(1);
        return 0;
    }
    else
    {
        cout << "You didn't follow instructions... ending game now." << endl;
        exit(1);
        return 0;
    }
}

int computerTurn(int computerTotalScore)
{
    int firstRoll = 0;
    int totalScore = 0;
    string enter;
    
    cout << "CPU rolls the dice... (press enter)";
    getline(cin, enter);
    
    labelb:
    firstRoll = randInt(1, 6);
    
    switch (firstRoll)
    {
        case 1:
            totalScore = 0;
            cout << "CPU rolled a 1!" << endl;
            cout << "CPU now has 0 points to bank." << endl;
            cout << "CPU has a total of " << computerTotalScore << " points (banked)." << endl;
            getline(cin, enter);
            return computerTotalScore;
            break;
        case 2:
            totalScore += 2;
            cout << "CPU rolled a 2!" << endl;
            cout << "CPU now has " << totalScore << " points to bank." << endl;
            getline(cin, enter);
            break;
        case 3:
            totalScore += 3;
            cout << "CPU rolled a 3!" << endl;
            cout << "CPU now has " << totalScore << " points to bank." << endl;
            getline(cin, enter);
            break;
        case 4:
            totalScore += 4;
            cout << "CPU rolled a 4!" << endl;
            cout << "CPU now has " << totalScore << " points to bank." << endl;
            getline(cin, enter);
            break;
        case 5:
            totalScore += 5;
            cout << "CPU rolled a 5!" << endl;
            cout << "CPU now has " << totalScore << " points to bank." << endl;
            getline(cin, enter);
            break;
        case 6:
            totalScore += 6;
            cout << "CPU rolled a 6!" << endl;
            cout << "CPU now has " << totalScore << " points to bank." << endl;
            getline(cin, enter);
            break;
        default:
            cout << "CPU made a fatal error... ending game." << endl;
            exit(1);
            break;
    }
    if (totalScore >= randInt(8, 18))
    {
        computerTotalScore += totalScore;
        cout << "CPU decides to bank its points!" << endl;
        getline(cin, enter);
        cout << "CPU now has " << computerTotalScore << " points!" << endl;
        getline(cin, enter);
        return computerTotalScore;
    }
    else
        goto labelb;
    
}

//int humanTwoTurn(int humanTwoTotalScore)

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
