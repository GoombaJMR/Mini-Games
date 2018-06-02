//CHOICE
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

using namespace std;

int ROWCOUNT = 5;
int COLCOUNT = 5;

class Board;
class Piece;

class Game
{
public:
    Game(int rows, int cols, int spots);
    int getRow() { return m_rows; }
    int getCol() { return m_cols; }
    Piece* play(Piece p, Board b);
    
private:
    int m_rows;
    int m_cols;
    int m_boostSpots;
};

class Board
{
public:
    Board(Game& game, Piece& piece);
    ~Board();
    void placePiece();
    void placeFinish();
    void display();
    bool checkNext(int move, bool& p1win, bool& p2win);
    
private:
    Game& m_game;
    Piece& m_piece;
    char** m_board;
};

class Piece
{
public:
    Piece(string p1, string p2, Game g);
    string getP1() { return m_p1; }
    string getP2() { return m_p2; }
    int getPRows() { return p_row; }
    int getPCols() { return p_col; }
    void setPRows(int row) { p_row = row; }
    void setPCols(int col) { p_col = col; }
    char getSymbol() { return m_symbol; }
    int makeMove(string player);
    int move(int& direction);
    
private:
    int p_row;
    int p_col;
    char m_symbol;
    string m_p1;
    string m_p2;
};

//-------------------------------------------------//
//-------GAME--------------------------------------//
//-------------------------------------------------//
Game::Game(int rows, int cols, int spots) : m_rows(rows), m_cols(cols), m_boostSpots(spots) {}

Piece* Game::play(Piece p, Board b)
{
    int turn = 1;
    bool p1win = false, p2win = false;
    int p1 = 0, p2 = 0, total = 0;
    while (!p1win && !p2win)
    {
        cout << "[TURN " << turn << "!]" << endl << endl;
        b.display();
        p1 = p.makeMove(p.getP1());
        system("clear");
        b.display();
        p2 = p.makeMove(p.getP2());
        total = p1 + p2;
        b.checkNext(p.move(total), p1win, p2win);
        turn++;
    }
    
    b.display();
    if (p1win)
        cout << "Congrats " << p.getP1() << ", you won!" << endl;
    else
        cout << "Great job " << p.getP2() << ", you won!!" << endl;
    exit(1);
}

//-------------------------------------------------//
//-------BOARD-------------------------------------//
//-------------------------------------------------//
Board::Board(Game& game, Piece& piece) : m_game(game), m_piece(piece)
{
    int rows = game.getRow();
    int cols = game.getCol();
    m_board = new char*[rows];
    for (int i = 0; i < rows; i++)
        m_board[i] = new char[cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m_board[i][j] = '.';
    placePiece();
    placeFinish();
}

Board::~Board()
{
    for (int i = 0; i < m_game.getRow(); i++)
        delete m_board[i];
    delete [] m_board;
}

void Board::placeFinish()
{
    int rowPosition = m_game.getRow() - 1;
    int colPosition = m_game.getCol() - 1;
    m_board[0][0] = '1';
    m_board[rowPosition][colPosition] = '2';
}

void Board::placePiece()
{
    int rowPositionF = m_game.getRow() / 2;
    int colPositionF = m_game.getCol() / 2;
    m_board[rowPositionF][colPositionF] = 'X';
}

void Board::display()
{
    for (int i = 0; i < m_game.getRow(); i++)
    {
        for (int j = 0; j < m_game.getCol(); j++)
        {
            cout << m_board[i][j];
            cout << "          ";
        }
        cout << endl << endl << endl << endl << endl << endl;
    }
}

bool Board::checkNext(int move, bool& p1win, bool& p2win)
{
    switch (move)
    {
        case 0: //NO MOVE
            cout << "You did not move." << endl;
            return true;
            break;
        case 1: //NORTH
            if (m_piece.getPRows() <= 0)
            {
                cout << "You were not able to move." << endl;
                return true;
            }
            if (m_board[m_piece.getPRows()-1][m_piece.getPCols()] != '.' && m_board[m_piece.getPRows()-1][m_piece.getPCols()] != '1' && m_board[m_piece.getPRows()-1][m_piece.getPCols()] != '2') {
                cout << "You were not able to move." << endl;
                return true;
            }
            
            if (m_board[m_piece.getPRows()-1][m_piece.getPCols()] == '1')
                p1win = true;
            if (m_board[m_piece.getPRows()-1][m_piece.getPCols()] == '2')
                p2win = true;
            
            m_board[m_piece.getPRows()][m_piece.getPCols()] = '.';
            m_piece.setPRows(m_piece.getPRows()-1);
            m_board[m_piece.getPRows()][m_piece.getPCols()] = 'X';
            cout << "You have moved up." << endl;
            break;
        case 2: //EAST
            if (m_piece.getPCols() >= COLCOUNT-1)
            {
                cout << "You were not able to move." << endl;
                return true;
            }
            if (m_board[m_piece.getPRows()][m_piece.getPCols()+1] != '.' && m_board[m_piece.getPRows()][m_piece.getPCols()+1] != '1' && m_board[m_piece.getPRows()][m_piece.getPCols()+1] != '2') {
                cout << "You were not able to move." << endl;
                return true;
            }
            
            if (m_board[m_piece.getPRows()][m_piece.getPCols()+1] == '1')
                p1win = true;
            if (m_board[m_piece.getPRows()][m_piece.getPCols()+1] == '2')
                p2win = true;
            
            m_board[m_piece.getPRows()][m_piece.getPCols()] = '.';
            m_piece.setPCols(m_piece.getPCols()+1);
            m_board[m_piece.getPRows()][m_piece.getPCols()] = 'X';
            cout << "You have moved right." << endl;
            break;
        case 3: //SOUTH
            if (m_piece.getPRows() >= ROWCOUNT-1)
            {
                cout << "You were not able to move." << endl;
                return true;
            }
            if ((m_board[m_piece.getPRows()+1][m_piece.getPCols()] != '.' && m_board[m_piece.getPRows()+1][m_piece.getPCols()] != '1' && m_board[m_piece.getPRows()+1][m_piece.getPCols()] != '2')
                || m_piece.getPRows()+1 > ROWCOUNT) {
                cout << "You were not able to move." << endl;
                return true;
            }
            
            if (m_board[m_piece.getPRows()+1][m_piece.getPCols()] == '1')
                p1win = true;
            if (m_board[m_piece.getPRows()+1][m_piece.getPCols()] == '2')
                p2win = true;
            
            m_board[m_piece.getPRows()][m_piece.getPCols()] = '.';
            m_piece.setPRows(m_piece.getPRows()+1);
            m_board[m_piece.getPRows()][m_piece.getPCols()] = 'X';
            cout << "You have moved down." << endl;
            break;
        case 4: //WEST
            if (m_piece.getPCols() <= 0)
            {
                cout << "You were not able to move." << endl;
                return true;
            }
            if ((m_board[m_piece.getPRows()][m_piece.getPCols()-1] != '.' && m_board[m_piece.getPRows()][m_piece.getPCols()-1] != '1' && m_board[m_piece.getPRows()][m_piece.getPCols()-1] != '2')
                || m_piece.getPCols()-1 < 0) {
                cout << "You were not able to move." << endl;
                return true;
            }
            
            if (m_board[m_piece.getPRows()][m_piece.getPCols()-1] == '1')
                p1win = true;
            if (m_board[m_piece.getPRows()][m_piece.getPCols()-1] == '2')
                p2win = true;
            
            
            m_board[m_piece.getPRows()][m_piece.getPCols()] = '.';
            m_piece.setPCols(m_piece.getPCols()-1);
            m_board[m_piece.getPRows()][m_piece.getPCols()] = 'X';
            cout << "You have moved left." << endl;
            break;
    }
    return true;
    
}

//-------------------------------------------------//
//-------PIECE-------------------------------------//
//-------------------------------------------------//
Piece::Piece(string p1, string p2, Game g) : m_p1(p1), m_p2(p2), p_row(g.getRow()/2), p_col(g.getCol()/2) {}

int Piece::makeMove(string player)
{
goomba:
    int value = 0;
    cout << "---------------LEGEND---------------" << endl;
    cout << "0 = NO MOVE || 1 = NORTH || 2 = EAST" << endl;
    cout << "----------- || 3 = SOUTH || 4 = WEST" << endl;
    cout << "------------------------------------" << endl;
    cout << "Choose a direction to move (" << player << "): ";
    cin >> value;
    
    if (value > 4)
    {
        cout << "Please do not choose a number greater than 4" << endl;
        goto goomba;
    }
    
    cout << endl;
    return value;
}

int Piece::move(int& direction)
{
    int mv = direction % 5;
    cout << direction << " % 5 is equal to " << mv << endl;
    return mv;
}

//-------------------------------------------------//
//-------PROTOTYPES--------------------------------//
//-------------------------------------------------//
void waitForEnter();
void printInstructions();
string getName(int player);


//-------------------------------------------------//
//-------IMPLEMENTATION-AND-MAIN-------------------//
//-------------------------------------------------//
int main ()
{
    cout << "----------------------------------------------------" << endl;
    cout << "--------WELCOME-TO-CHOICE--A-GAME-OF-OPTIONS--------" << endl;
    cout << "----------------------------------------------------" << endl;
    
    string p1 = getName(1);
    string p2 = getName(2);
    
    Game gameApple(ROWCOUNT, COLCOUNT, 5);
    Piece gamePiece(p1, p2, gameApple);
    Board gameBoard(gameApple, gamePiece);
    
    printInstructions();
    
    gameApple.play(gamePiece, gameBoard);
    
}

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

string getName(int player)
{
    string name;
    cout << "Player " << player << "'s name: ";
    getline(cin, name);
    return name;
}

void printInstructions()
{
    cout << "----INSTRUCTIONS----" << endl;
    cout << "1. Players take turns inputting a number from 0 - 4." << endl;
    cout << "2. Each number represents a cardinal direction." << endl;
    cout << "3. The sum of the two numbers are used to determine the direction moved!" << endl;
    cout << "4. This process repeats until the piece reaches either P1 or P2's winning space." << endl;
    waitForEnter();
    cout << "----NOTES----" << endl;
    cout << "1. If the sum is above 4, then we modulo the value by 5 to find the direction." << endl;
    cout << "2. 0 => NO MOVE, 1 => NORTH, 2 => EAST, 3 => SOUTH, 4 => WEST." << endl;
    //More about potential items?
    waitForEnter();
    cout << "----EXAMPLES----" << endl;
    cout << "a. P1 chooses 3, P2 chooses 1... Sum is 4 so the piece moves WEST by one." << endl;
    cout << "b. P1 chooses 1, P2 chooses 4... Sum is 5, 5 % 5 = 0, so the piece DOES NOT MOVE." << endl;
    cout << "c. P1 chooses 4, P2 chooses 3... Sum is 7, 7 % 5 = 2, so the piece moves EAST by one." << endl << endl;
    cout << "----LET CHOICE BEGIN!----";
    waitForEnter();
}
