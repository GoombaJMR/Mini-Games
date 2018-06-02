////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------//
////--------------------------------FIERY-TRIANGLE------------------------------////
//////------------------------------------------------------------------------//////
////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <utility>
#include <random>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------//
////------------------------------CLASS-DEFINITIONS-----------------------------////
//////------------------------------------------------------------------------//////
////////////////////////////////////////////////////////////////////////////////////

class Player {
public:
    void obtainData(string player12);
    
    //ACCESSOR FUNCTIONS
    int getClass();
    int getHP();
    int getHeal();
    int getMove();
    int getStatus();
    int getStrength();
    int getWeakness();
    int getDamageDealt();
    string getMoveName();
    string getName();
    
    //MUTATOR FUNCTIONS
    void setHP(int newHP);
    void setMove(int choice);
    void setPoison();
    void setStrength(int strong);
    void setWeakness(int weak);
    void setDamageDealt(int damage);
    void setMoveName(string moveName);
    void setHeal();
    
private:
    int m_class;
    int m_hp;
    int m_currentMove;
    int m_heal = 1;
    int m_strong;
    int m_weakness;
    int m_move;
    int m_damageDealt;
    bool m_poisoned = false;
    string m_name;
    string m_message;
    string m_moveName;
};

////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------//
////----------------------------------CONSTANTS---------------------------------////
//////------------------------------------------------------------------------//////
////////////////////////////////////////////////////////////////////////////////////

const int FIRE_CLASS  = 1;  //Fire Wizard
const int WATER_CLASS = 2;  //Water Mage
const int GRASS_CLASS = 3;  //Grass Sorcerer
const int FIRE_BLAST  = 4;  //Fire Attack
const int WATER_BLAST = 5;  //Water Attack
const int GRASS_BLAST = 6;  //Grass Attack
const int STRIKE      = 7;  //Physical Attack (5 DAMAGE GUARANTEED)
const int POISON      = 8;  //Lasts for 10 turns (TURN+2 DAMAGE PER TURN)
const int HEAL        = 9;  //Heal 50 HP Once (USES TURN)
const int WEAKTOFIRE  = 10; //Weak to Fire attacks
const int WEAKTOWATER = 11; //Weak to Water attacks
const int WEAKTOGRASS = 12; //Weak to Grass attacks
const int STRONGFIRE  = 13; //Strong to Fire attacks
const int STRONGWATER = 14; //Strong to Water attacks
const int STRONGGRASS = 15; //Strong to Grass attacks

////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------//
////----------------------------FUNCTION-DEFINITIONS----------------------------////
//////------------------------------------------------------------------------//////
////////////////////////////////////////////////////////////////////////////////////

void printInstructions();
void printIntroduction();
int randInt(int min, int max);
void playerMove(Player& player);
int calculateSetDamage(Player attacker, Player receiver);
void calculateDamage(Player& p1, Player& p2, int turn);
void displayResults(Player p1, Player p2, bool& inProgress, bool& win);

////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------//
////----------------------------------INT-MAIN----------------------------------////
//////------------------------------------------------------------------------//////
////////////////////////////////////////////////////////////////////////////////////

int main ()
{
    int turn = 1;
    bool gameInProgress = true;
    bool winner = false;
    string enter;
    Player player1;
    Player player2;
    
    printIntroduction();
    player1.obtainData("[Player 1]");
    player2.obtainData("[Player 2]");
    
    while (gameInProgress)
    {
        cout << "[Turn " << turn << "] ~~ " << player1.getName() << ": " <<
        player1.getHP() << " HP ~~ " << player2.getName() << ": " <<
        player2.getHP() << " HP ~~" << endl;
        
        playerMove(player1);
        playerMove(player2);
        calculateDamage(player1, player2, turn);
        displayResults(player1, player2, gameInProgress, winner);
        
        if(gameInProgress)
            turn++;
    }
    
    if (winner)
    {
        cout << "[Comp] Congratulations player 1, aka " << player1.getName() << ", you have emerged victorious within " << turn << " turns!";
        getline(cin, enter);
        cout << endl << "[Comp] The game has ended now. Hope you enjoyed it too, " << player2.getName() << "!" << endl << endl;
        exit(1);
    }
    
    else
    {
        cout << "[Comp] Congratulations player 2, aka " << player2.getName() << ", you have emerged as the winner within " << turn << " turns!";
        getline(cin, enter);
        cout << endl << "[Comp] The game has ended now. Hope you enjoyed it too, " << player1.getName() << "!";
        exit(1);
    }
}

////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------//
////-----------------------MEMBER-FUNCTION-IMPLEMENTATIONS----------------------////
//////------------------------------------------------------------------------//////
////////////////////////////////////////////////////////////////////////////////////

int Player::getClass() {
    return m_class;
}

int Player::getHP() {
    return m_hp;
}

string Player::getName() {
    return m_name;
}

int Player::getMove() {
    return m_move;
}

int Player::getHeal() {
    return m_heal;
}

int Player::getStatus() {
    return m_poisoned;
}

string Player::getMoveName() {
    return m_moveName;
}

int Player::getStrength() {
    return m_strong;
}

int Player::getWeakness() {
    return m_weakness;
}

int Player::getDamageDealt() {
    return m_damageDealt;
}

void Player::setHP(int newHP) {
    m_hp = newHP;
}

void Player::setMove(int choice) {
    m_move = choice;
}

void Player::setPoison() {
    m_poisoned = !m_poisoned;
}

void Player::setStrength(int strong) {
    m_strong = strong;
}

void Player::setWeakness(int weak) {
    m_weakness = weak;
}

void Player::setDamageDealt(int damage) {
    m_damageDealt = damage;
}

void Player::setMoveName(string moveName) {
    m_moveName = moveName;
}

void Player::setHeal() {
    m_heal = 0;
}

////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------//
////--------------------------FUNCTION-IMPLEMENTATIONS--------------------------////
//////------------------------------------------------------------------------//////
////////////////////////////////////////////////////////////////////////////////////

void Player::obtainData(string player12)
{
    string name = "";
    string enter = "";
    string className = "";
    string answer = "";
labela:
    cout << "[Comp] What is your name " << player12 << "? ";
    getline(cin, name);
    
    m_name = name;
    m_hp = 100;
    
    cout << "[Comp] Very well, " << name << ". Your class (F, W, G)? ";
    getline(cin, className);
    if (className == "F" || className == "f")
    {
        m_class = FIRE_CLASS;
        className = "Fire Wizard";
        m_weakness = WEAKTOWATER;
        m_strong = STRONGGRASS;
    }
    else if (className == "W" || className == "w")
    {
        m_class = WATER_CLASS;
        className = "Water Mage";
        m_weakness = WEAKTOGRASS;
        m_strong = STRONGFIRE;
    }
    else if (className == "G" || className == "g")
    {
        m_class = GRASS_CLASS;
        className = "Grass Sorcerer";
        m_weakness = WEAKTOFIRE;
        m_strong = STRONGWATER;
    }
    else
    {
        cout << "[Comp] You did not choose a class properly. Going to start: ";
        getline(cin, enter);
        goto labela;
    }
    
    cout << "[Comp] Let me double check..." << endl;
    cout << "[Comp] Your name is " << name << " and you are a " << className << ", right? (Y/N) ";
    getline(cin, answer);
    if (answer == "Y" || answer == "y" || answer == "")
    {
        cout << "[Comp] Okay, good luck to you!" << endl;
        getline(cin, enter);
        system("clear");
    }
    else
    {
        cout << "[Comp] Alright, let us redo this then: ";
        getline(cin, enter);
        cout << endl;
        goto labela;
    }
    
}

void playerMove(Player& player)
{
    string choice;
    string enter;
    
labelb:
    cout << "[" << player.getName() << "] Please select a move (F, W, G, S, P, H): ";
    getline(cin, choice);
    
    if (choice == "F" || choice == "f")
        player.setMove(FIRE_BLAST);
    
    else if (choice == "W" || choice == "w")
        player.setMove(WATER_BLAST);
    
    else if (choice == "G" || choice == "g")
        player.setMove(GRASS_BLAST);
    
    else if (choice == "S" || choice == "s")
        player.setMove(STRIKE);
    
    else if (choice == "P" || choice == "p")
        player.setMove(POISON);
    
    else if (choice == "H" || choice == "h")
    {
        if (player.getHeal() == 0)
        {
            cout << "You can no longer heal. Try another option...";
            cout << endl;
            goto labelb;
        }
        player.setMove(HEAL);
        player.setHeal();
    }
    else
    {
        cout << "[Comp] You entered an incorrect command. Try again...";
        getline(cin, enter);
        cout << endl;
        goto labelb;
    }
    system("clear");
}

int calculateSetDamage(Player attacker, Player receiver)
{
    //If attacker is strong against the receiver
    if ((receiver.getWeakness() == WEAKTOGRASS && attacker.getStrength() == STRONGWATER  ) //Attacker is grass type, receiver is water type
        || (receiver.getWeakness() == WEAKTOWATER && attacker.getStrength() == STRONGFIRE   ) //Attacker is water type, receiver is fire type
        || (receiver.getWeakness() == WEAKTOFIRE  && attacker.getStrength() == STRONGGRASS )) //Attacker is fire type, receiver is grass type
        receiver.setDamageDealt(15); //Receiver takes a lot of damage due to class weakness
    
    //Else if attack is neutral against the receiver
    else if ((receiver.getWeakness() == WEAKTOGRASS && attacker.getStrength() == STRONGFIRE ) //Attacker is same type as receiver (water)
             ||  (receiver.getWeakness() == WEAKTOWATER && attacker.getStrength() == STRONGGRASS    ) //Attacker is same type as receiver (fire)
             ||  (receiver.getWeakness() == WEAKTOFIRE && attacker.getStrength() == STRONGWATER    )) //Attacker is same type as receiver (grass)
        receiver.setDamageDealt(10);
    
    //Else if attack is weak against the receiver
    else if ((receiver.getWeakness() == WEAKTOGRASS && attacker.getStrength() == STRONGGRASS ) //Attacker is water type, receiver is water type
             ||  (receiver.getWeakness() == WEAKTOWATER && attacker.getStrength() == STRONGWATER     ) //Attacker is fire type, receiver is fire type
             ||  (receiver.getWeakness() == WEAKTOFIRE && attacker.getStrength() == STRONGFIRE      )) //Attacker is grass type, receiver is grass type
        receiver.setDamageDealt(5);
    
    return receiver.getDamageDealt();
}

void calculateDamage(Player& p1, Player& p2, int turn)
{
    //SETTING LOCAL FUNCTION VARIABLES
    string enter;
    int p1CurrentHP = p1.getHP();
    int p2CurrentHP = p2.getHP();
    int damageDoneToP1 = calculateSetDamage(p2, p1);
    int damageDoneToP2 = calculateSetDamage(p1, p2);
    
    //PLAYER ONE INDIVIDUAL MOVES
    if (p1.getMove() == STRIKE)
    {
        damageDoneToP2 = 10; 
        p1.setMoveName("struck their opponent!");
    }
    
    
    if (p1.getMove() == POISON)
    {
        if (p2.getStatus())
        {
            damageDoneToP2 = 0;
            p1.setMoveName("tried to and failed to poison the already poisoned enemy!");
        }
        else
        {
            damageDoneToP2 = 0;
            p2.setPoison();
            p1.setMoveName("poisoned their opponent!");
        }
    }
    
    if (p1.getMove() == HEAL)
    {
        p1CurrentHP += 50;
        damageDoneToP2 = 0;
        //Heal from poison
        if (p1.getStatus())
            p1.setPoison();
        p1.setMoveName("healed themselves!");
    }
    
    //PLAYER TWO INDIVIDUAL MOVES
    if (p2.getMove() == HEAL)
    {
        p2CurrentHP += 50;
        damageDoneToP1 = 0;
        if (p2.getStatus())
            p2.setPoison();
        p2.setMoveName("healed themselves!");
    }
    
    if (p2.getMove() == POISON)
    {
        if (p1.getStatus())
        {
            damageDoneToP1 = 0;
            p2.setMoveName("tried to and failed to poison the already poisoned enemy!");
        }
        else
        {
            damageDoneToP1 = 0;
            p1.setPoison();
            p2.setMoveName("poisoned their opponent!");
        }
    }
    
    if (p2.getMove() == STRIKE) 
    {
        damageDoneToP1 = 10; 
        p2.setMoveName("struck their opponent!");
    }
    
    //TYPE COMPARISON MOVES
    if (p1.getMove() == FIRE_BLAST)
        p1.setMoveName("used Fire Blast!");
    else if (p1.getMove() == WATER_BLAST)
        p1.setMoveName("used Water Blast!");
    else if (p1.getMove() == GRASS_BLAST)
        p1.setMoveName("used Grass Blast!");

    if (p2.getMove() == FIRE_BLAST)
        p2.setMoveName("used Fire Blast!");
    else if (p2.getMove() == WATER_BLAST)
        p2.setMoveName("used Water Blast!");
    else if (p2.getMove() == GRASS_BLAST)
        p2.setMoveName("used Grass Blast!");
    
    if (p1.getMove() == FIRE_BLAST && p2.getMove() == WATER_BLAST)
    {
        damageDoneToP1 += 5;  damageDoneToP2 -= 5;
    }
    
    else if (p1.getMove() == FIRE_BLAST && p2.getMove() == GRASS_BLAST)
    {
        damageDoneToP1 -= 10;  damageDoneToP2 += 10;
    }
    
    else if (p1.getMove() == WATER_BLAST && p2.getMove() == FIRE_BLAST)
    {
        damageDoneToP1 -= 10;  damageDoneToP2 += 10;
    }
    
    else if (p1.getMove() == WATER_BLAST && p2.getMove() == GRASS_BLAST)
    {
        damageDoneToP1 += 5;  damageDoneToP2 -= 5;
    }
    
    else if (p1.getMove() == GRASS_BLAST && p2.getMove() == FIRE_BLAST)
    {
        damageDoneToP1 += 5;  damageDoneToP2 -= 5;
    }
    
    else if (p1.getMove() == GRASS_BLAST && p2.getMove() == WATER_BLAST)
    {
        damageDoneToP1 -= 10;  damageDoneToP2 += 10;
    }

    //IFs for OTHER THREE MOVES. Don't forget poison
    
    if (p1.getStatus())
        damageDoneToP1 += (turn + 2); //Algorithm may be off but it works for now
    if (p2.getStatus())
        damageDoneToP2 += (turn + 2);
    
    p1.setDamageDealt(damageDoneToP2);
    p2.setDamageDealt(damageDoneToP1);
    
    p1CurrentHP -= damageDoneToP1;
    p2CurrentHP -= damageDoneToP2;

    if (p1CurrentHP <= 0)
    {
        if (p1CurrentHP <= 0 && p2CurrentHP <= 0)
        {
            if (p1CurrentHP > p2CurrentHP)
                p1CurrentHP = 1;
            else if (p1CurrentHP < p2CurrentHP)
                p2CurrentHP = 1;
            else
            {
                cout << "[DRAW]: Game has ended in a draw. Play another match!";
                getline(cin, enter);
                cout << endl;
                exit(1);
            }   
        }
        else
            p1CurrentHP = 0;
    }
    if (p2CurrentHP <= 0)
    {
        if (p1CurrentHP <= 0 && p2CurrentHP <= 0)
        {
            if (p1CurrentHP > p2CurrentHP)
                p1CurrentHP = 1;
            else if (p1CurrentHP < p2CurrentHP)
                p2CurrentHP = 1;
            else
            {
                cout << "[DRAW]: Game has ended in a draw. Play another match!";
                getline(cin, enter);
                cout << endl;
                exit(1);
            }   
        }
        else
            p2CurrentHP = 0;
    }

    p1.setHP(p1CurrentHP);
    p2.setHP(p2CurrentHP);
}

void displayResults(Player p1, Player p2, bool& inProgress, bool& win)
{
    string enter;
    system("clear");
    
    cout << "[" << p1.getName() << "] " << p1.getMoveName() << endl;
    cout << "[" << p2.getName() << "] " << p2.getMoveName() << endl;
    
    if (p1.getStatus())
        cout << endl << "[" << p1.getName() << "] is poisoned!" << endl;
    if (p2.getStatus())
        cout << endl << "[" << p2.getName() << "] is poisoned!";
    
    cout << endl << endl;
    cout << "[" << p1.getName() << "] has taken " << p2.getDamageDealt() << " damage and now has " << p1.getHP() << " HP left!";
    cout << endl << "[" << p2.getName() << "] has taken " << p1.getDamageDealt() << " damage and now has " << p2.getHP() << " HP left!";
    getline(cin, enter);
    
    if (p1.getHP() == 0 && p2.getHP() == 0)
    {
        cout << endl << "[Comp] Stop! The game has ended!";
        getline(cin, enter);
        cout << endl;
        if (p1.getDamageDealt() > p2.getDamageDealt())
            win = true;
        if (p1.getHP() < p2.getHP())
            win = false;
    }
    
    else if (p1.getHP() <= 0 || p2.getHP() <= 0)
    {
        cout << endl << "[Comp] Stop! The game has ended!";
        getline(cin, enter);
        cout << endl;
        inProgress = false;
        if (p1.getHP() <= 0)
            win = false;
        if (p2.getHP() <= 0)
            win = true;
    }
    
    
    
    system("clear");
}

void printIntroduction()
{
    string enter;
    string answer;
    cout << "---------------------------------------" << endl;
    cout << "-------Welcome to Fiery Triangle-------" << endl;
    cout << "--------------Julian Rice--------------" << endl;
    cout << "---------------------------------------" << endl;
    getline(cin, enter);
    
    cout << "[Comp] Before we start, would you like to hear a basic overview of this game? (Y/N) ";
    getline(cin, answer);
    
    if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "")
    {
        cout << "[Comp] Very well. Press enter to continue";
        getline(cin, enter);
        printInstructions();
    }
    else
    {
        cout << "[Comp] No? Very well. Press enter to continue";
        getline(cin, enter);
        cout << endl;
    }
    
}

void printInstructions()
{
    string enter;
    string answer;
    cout << "[Comp] First off, you will be able to choose from one of three classes. ";
    getline(cin, enter);
    cout << "[Comp] The Fire Wizard, Water Mage, and Grass Sorcerer. You also start with 100 HP.";
    getline(cin, enter);
    cout << "[Comp] As expected, each class is strong against one other but weak to the third class." << endl << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "----------------------------------------GUIDE-#1---------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "-----------------Fire-Class---deals--->15-damage----to---->Grass-Class-----------------" << endl;
    cout << "-----------------Fire-Class---deals--->10-damage----to---->Fire--Class-----------------" << endl;
    cout << "-----------------Fire-Class---deals--->05-damage----to---->Water-Class-----------------" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    getline(cin, enter);
    cout << endl << "[Comp] <EXAMPLE#1> A Fire Wizard will naturally be weak to the Water Mage and deal little damage ";
    cout << "but will be naturally stronger against the Grass Sorcerer and deal more damage.";
    getline(cin, enter);
    cout << endl << "[Comp] Each class will also be able to use three magic moves: Fire, Water, and Grass blasts.";
    getline(cin, enter);
    cout << "[Comp] The damage you deal with your attack is set between classes, but you can deal more or less damage ";
    cout << "depending on what move your opponent chooses.";
    getline(cin, enter);
    cout << endl << "[Comp] <EXAMPLE#2> A Fire Wizard uses Fire and deals a mere 5 damage to the Water Mage, but ";
    cout << "if Water Mage uses Grass Blast, then the mage then takes an additional bit of damage due to grass losing to fire.";
    getline(cin, enter);
    cout << endl << "[Comp] <EXAMPLE#3> A Water Mage uses Grass and deals heavy damage to a Water Mage, but ";
    cout << "the second Water Mage uses Fire. The first mage's attack is overwhelmed by the Fire Blast and takes more damage than the second Water Mage.";
    getline(cin, enter);
    cout << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "----------------------------------------GUIDE-#2---------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "-----------------Fire-Blast---deals--->+10 damage--against-->Grass-Blast---------------" << endl;
    cout << "-----------------Fire-Blast---deals--->+00 damage--against-->Fire--Blast---------------" << endl;
    cout << "-----------------Fire-Blast---deals--->-05 damage--against-->Water-Blast---------------" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "[Comp] Would you like more examples? ";
    getline(cin, answer);
    
    if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "")
    {
        cout << "[Comp] Alright. Press continue to enter";
        getline(cin, enter);
        //INCOMPLETE
    }
    
    cout << "[Comp] Let's continue. Press continue to enter";
    getline(cin, enter);
    cout << endl;
    cout << "[Comp] Each player also has the option to choose three other moves: Strike (S), Poison (P), and Heal (H)";
    getline(cin, enter);
    cout << endl << "[Comp] STRIKE: Deal 10 damage to your opponent no matter what." << endl;
    cout << "[Comp] POISON: Poisons the opponent, who takes (2 + turn count) amount of damage per turn." << endl;
    cout << "[Comp] HEAL: Can only be used once, heals 50 health and cures poison." << endl;
    getline(cin, enter);
    cout << endl << "[Comp] The main strategy here is [1] exposing your opponent's type weakness,";
    cout << endl << "[Comp] [2] Predicting and countering the move you think they'll use on you.";
    getline(cin, enter);
    cout << "[Comp] It's also important to consider when your opponent will find out about your type, and how to counter their attacks";
    getline(cin, enter);
    cout << "[Comp] The addition of strike, poison, and heal, add new layers of strategy into this (rock-paper-scissors)^2-style game.";
    getline(cin, enter);
    cout << "[Comp] The game is made completely fair with the addition of more/less damage taken by choosing the right Type Blasts.";
    getline(cin, enter);
    cout << "[Comp] So let's get your names! Don't let your opponent see the screen. Yes, take turns passing the computer around.";
    getline(cin, enter);
    cout << endl;
}

int randInt(int min, int max) {
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
