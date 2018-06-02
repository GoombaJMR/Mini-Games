//KyleKart
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

using namespace std;

////---------------------------------------////
//-----------------CONSTANTS-----------------//
////---------------------------------------////
int const ROWS = 19;
int const COLUMNS = 19;
int const MAX_ITEMS = 3;
int const MAX_ITEMS_MAP = 19;
int const MAX_TIRES = 40;
int const WEED = 1;
int const SPIKE = 2;
int const CHAIN = 3;

////---------------------------------------////
//-----------------CLASS-DEF-----------------//
////---------------------------------------////
class Player
{
public:
    //CONSTRUCTORS
    Player(string nm, int p, char icon); //Implementation below class
    
    //ACCESSORS
    int getRow()            { return m_row; }
    int getCol()            { return m_col; }
    int getItem()			{ return m_item[0]; }
    int getWeedCount()		{ return m_weedCount; }
    bool isWeeded()			{ return m_weeded; }
    bool isSpiked()			{ return m_spiked; }
    bool isChained()		{ return m_chained; }
    char getIcon()          { return m_display; }
    string getName()        { return m_name; }
    
    //MUTATORS
    void setRow(int updated) { m_row = updated; }
    void setCol(int updated) { m_col = updated; }
    void unSetWeed()		 { m_weeded = false; }
    void unSetSpike()		 { m_spiked = false; }
    void unSetChain()	 	 { m_chained = false; }
    void setDis(char display) { m_display = display; }
    void reduceItem();
    
    //OTHER
    
private:
    int m_row;
    int m_col;
    int m_item[3];
    int m_weedCount;
    int m_spikeCount;

    bool m_weeded;
    bool m_spiked;
    bool m_chained;

    char m_display;
    string m_name;

    struct ItemList
    {
        int m_item;
        ItemList* next;
    };
    ItemList* head;
};

Player::Player(string nm, int p, char icon)
{
    //Player Name
    m_name = nm;
    
    //If Player 1, place in bottom left
    if (p == 1)
    {
        m_row = ROWS-2;
        m_col = 1;
        m_display = '1';
    }
    //Else Player 2, place in bottom right
    else if (p == 2)
    {
        m_row = ROWS-2;
        m_col = COLUMNS-2;
        m_display = '2';
    }
}

Player::reduceItem()
{
	for (int i = 0; i < 2; i++)
		m_item[i] = m_item[i+1];
	m_item[2] = 0;
}

void setWeed()			 
{ 
	m_weeded = true;
	
}
void setSpike()			 
{ 
	m_spiked = true; 
}
void setChain()			 
{ 
	m_chained = true; 
}

////---------------------------------------////
//-----------------PROTOTYPE-----------------//
////---------------------------------------////
void drawGrid(Player p1, Player p2, char grid[ROWS][COLUMNS]);
void drawGridMap(Player p1, Player p2, char grid[ROWS][COLUMNS]);
void drawGridPoints(Player p1, Player p2, char grid[ROWS][COLUMNS]);
void placeRandomItems(char grid[ROWS][COLUMNS]);
void displayGrid(Player p1, Player p2, char grid[ROWS][COLUMNS]);
string findName(int num);
bool playerTurn(Player& move, Player& opponent, char grid[ROWS][COLUMNS]);
void playerInput(Player& move, char grid[ROWS][COLUMNS]);
int randInt(int min, int max);

////---------------------------------------////
//-----------------INT-MAIN------------------//
////---------------------------------------////
int main () {
    //BASIC VARIABLE INITIALIZATION
    int p_1 = 1;
    int p_2 = 2;
    int tempBool = false;

    //PLAYER INITIALIZATION
    Player p1(findName(p_1), p_1, '1');
    Player p2(findName(p_2), p_2, '2');
    
    char battleGrid[ROWS][COLUMNS];
    drawGrid(p1, p2, battleGrid);
    
    while (!tempBool)
    {
        playerTurn(p1, p2, battleGrid);
        system("clear");
        playerTurn(p2, p1, battleGrid);
        system("clear");
    }
}

////---------------------------------------////
//-----------------FUNCTIONS-----------------//
////---------------------------------------////
void drawGrid(Player p1, Player p2, char grid[ROWS][COLUMNS])
{
    drawGridMap(p1, p2, grid);
    drawGridPoints(p1, p2, grid);
    placeRandomItems(grid);
}

void drawGridMap(Player p1, Player p2, char grid[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
        {
            if (j == 0 && i != 0)
                grid[i][j] = '|';
            else if (j == COLUMNS-1 && i != 0)
                grid[i][j] = '|';
            else if (i == ROWS-1)
                grid[i][j] = '~';
            else if ((i == 0 && j != 0) && (i == 0 && j != COLUMNS-1))
                grid[i][j] = '_';
            else if ((i == 0 && j == 0) || (i == 0 && j == COLUMNS-1))
                grid[i][j] = ' ';
            else
                grid[i][j] = ' ';
        }
    grid[p1.getRow()][p1.getCol()] = p1.getIcon();
    grid[p2.getRow()][p2.getCol()] = p2.getIcon();
}

void drawGridPoints(Player p1, Player p2, char grid[ROWS][COLUMNS])
{
    int HALF = COLUMNS/2;
    grid[1][HALF] = 'F';
    p1.setDis('1');
    p1.setDis('2');
}

void displayGrid(char grid[ROWS][COLUMNS])
{
	cout << "  ";
	
	for (int j = 0; j < COLUMNS; j++)
	{
		cout << j;
	}

    for (int i = 0; i < ROWS; i++)
    {
    	cout << i << " ";
        for (int j = 0; j < COLUMNS; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

void placeRandomItems(char grid[ROWS][COLUMNS])
{
    int itemCounter = 0;
    while (itemCounter <= MAX_ITEMS_MAP)
    {
        int magicRow = 0;
        int magicCol = 0;
        
        magicRow = randInt(2, ROWS-1);
        magicCol = randInt(2, COLUMNS-1);
        
        if (grid[magicRow-1][magicCol-1] == ' ')
        {
            grid[magicRow-1][magicCol-1] = '!';
            //Function to determine the item
            itemCounter++;
        }
    }
    
    int tireCounter = 0;
    while (tireCounter <= MAX_TIRES)
    {
        int tireRow = 0;
        int tireCol = 0;
        
        tireRow = randInt(2, ROWS-1);
        tireCol = randInt(2, COLUMNS-1);
        
        if (grid[tireRow-1][tireCol-1] == ' ')
        {
            grid[tireRow-1][tireCol-1] = 'o';
            tireCounter++;
        }
    }
    
    //RISK: What if it blocks the way for the player? Likelihood < 2.5% so...
}

bool playerTurn(Player& move, Player& opponent, char grid[ROWS][COLUMNS])
{
    displayGrid(grid);

    playerInput(move, grid);
    
    
    
    
    
    return true;
}

void playerInput(Player& move, char grid[ROWS][COLUMNS])
{
    goomba:
    char choice;
    cout << "[ Please input your command " << move.getName() << "-san ]" << endl;
    cout << "[-------------------------------------------]" << endl;
    cout << "(----N--Move-UP-------------S--Move-DOWN----)" << endl;
    cout << "{----W--Move-LEFT-----------E--Move-RIGHT---}" << endl;
    cout << "(----I--USE-ITEM----------------------------)" << endl;
    cout << "[-------------------------------------------]" << endl;
    cout << "Your Input: ";
    cin >> choice;
    switch (choice) {
        case 'n':
        case 'N':
            if (grid[move.getRow()-1][move.getCol()] == 'o'
             || grid[move.getRow()-1][move.getCol()] == '_')
                {
                    cout << "You cannot move forward. Try again." << endl;
                    displayGrid(grid);
                    goto goomba;
                }
            else if (grid[move.getRow()-1][move.getCol()] == '!')
                {
                    //RANDOM ITEM FUNCTION
                    //ADD DATA NODE FOR PLAYER
                    //LINKED LISTS
                }
            else if (grid[move.getRow()-1][move.getCol()] == '1'
             ||      grid[move.getRow()-1][move.getCol()] == '2')
                {
                    cout << "You cannot move into another player. Try again." << endl;
                    displayGrid(grid);
                    goto goomba;
                }
            else
                {
                    grid[move.getRow()][move.getCol()] = ' ';
                    move.setRow(move.getRow()-1);
                    grid[move.getRow()][move.getCol()] = move.getIcon();
                    cout << "You have moved up." << endl;
                }
            break;
        
        case 's':
        case 'S':
            if (grid[move.getRow()+1][move.getCol()] == 'o'
                || grid[move.getRow()+1][move.getCol()] == '~')
            {
                cout << "You cannot move backward. Try again." << endl;
                displayGrid(grid);
                goto goomba;
            }
            else if (grid[move.getRow()+1][move.getCol()] == '!')
            {
                //RANDOM ITEM FUNCTION
                //ADD DATA NODE FOR PLAYER
                //LINKED LISTS
            }
            else if (grid[move.getRow()+1][move.getCol()] == '1'
                     ||      grid[move.getRow()+1][move.getCol()] == '2')
            {
                cout << "You cannot move into another player. Try again." << endl;
                displayGrid(grid);
                goto goomba;
            }
            else
            {
                grid[move.getRow()][move.getCol()] = ' ';
                move.setRow(move.getRow()+1);
                grid[move.getRow()][move.getCol()] = move.getIcon();
                cout << "You have moved down." << endl;
            }
            break;
        
        case 'w':
        case 'W':
            if (grid[move.getRow()][move.getCol()-1] == 'o'
                || grid[move.getRow()][move.getCol()-1] == '|')
            {
                cout << "You cannot move left. Try again." << endl;
                displayGrid(grid);
                goto goomba;
            }
            else if (grid[move.getRow()][move.getCol()-1] == '!')
            {
                //RANDOM ITEM FUNCTION
                //ADD DATA NODE FOR PLAYER
                //LINKED LISTS
            }
            else if (grid[move.getRow()][move.getCol()-1] == '1'
                     ||      grid[move.getRow()][move.getCol()-1] == '2')
            {
                cout << "You cannot move into another player. Try again." << endl;
                displayGrid(grid);
                goto goomba;
            }
            else
            {
                grid[move.getRow()][move.getCol()] = ' ';
                move.setCol(move.getCol()-1);
                grid[move.getRow()][move.getCol()] = move.getIcon();
                cout << "You have moved left" << endl;
            }
            break;
            
        case 'e':
        case 'E':
            if (grid[move.getRow()][move.getCol()+1] == 'o'
                || grid[move.getRow()][move.getCol()+1] == '|')
            {
                cout << "You cannot move right. Try again." << endl;
                displayGrid(grid);
                goto goomba;
            }
            else if (grid[move.getRow()][move.getCol()+1] == '!')
            {
                //RANDOM ITEM FUNCTION
                //ADD DATA NODE FOR PLAYER
                //LINKED LISTS
            }
            else if (grid[move.getRow()][move.getCol()+1] == '1'
                     ||      grid[move.getRow()][move.getCol()+1] == '2')
            {
                cout << "You cannot move into another player. Try again." << endl;
                displayGrid(grid);
                goto goomba;
            }
            else
            {
                grid[move.getRow()][move.getCol()] = ' ';
                move.setCol(move.getCol()+1);
                grid[move.getRow()][move.getCol()] = move.getIcon();
                cout << "You have moved right" << endl;
            }
            break;
        
        case 'i':
        case 'I':
            
            break;

        default:
            cout << "You did not input a proper move." << endl << endl;
            goto goomba;
            break;
    }
    //INCOMPLETE
}

string findName(int num)
{
    string nm;
    cout << "What is your name, player " << num << "? ";
    getline(cin, nm);
    return nm;
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
