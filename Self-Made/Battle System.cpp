//JULIAN'S TURN BASED TEXT-RPG GAME.
#include <iostream>
#include <string>
#include <utility>
#include <random>
#include <cstdlib>
#include <unistd.h>

using namespace std;

//CREATE PLAYER AND ENEMY CLASSES IN ANOTHER DOCUMENT THEN USE IFSTREAM/IOSTREAM//
struct Player {
public:
    string name;
    int HP;
    int MaxHP;
    int MP;
    int MaxMP;
    int ATK;
    int MAT;
    int DEF;
    int AGI;
    int className; //1 for L, 2 for W, 3 for G, 4 for A
    int magUp;   //1 for W, 0 for ALL OTHER
};

struct Monster {
public:
    string Name;
    int HP;
    int MP;
    int ATK;
    int DEF;
    int AGI;
    int WEAK1;
    int STRONG1;
    int numberOfAttacks;
};

//FUNCTION PROTOTYPES
void battleSystem(string enemy, int enemyHP, int enemyWeak, int enemyStrong, int enemyAttack, int enemyDefense, int enemyAgility, 
                  int& HP, int& maxHP, int& MP, int& maxMP, int& vial, int& baseAttack, int& baseMagic, int& baseDefense, int& baseAgility, int& level, int exp, 
                  string yourName, string yourClass, int& total, int magUp);

void playerTurn(string enemy, int& enemyHP, int enemyWeak, int enemyStrong, int enemyAttack, int enemyDefense, int enemyAgility, 
                  int& HP, int& maxHP, int& MP, int& maxMP, int& vial, int& baseAttack, int& baseMagic, int& baseDefense, int& baseAgility, int& level, int exp, 
                  string yourName, string yourClass, int magUp);

void enemyTurn(string enemy, int& HP, int enemyAttack, int enemyDefense, int baseDefense);

void levelUp(int& level, int& total, int& maxHP, int& maxMP, int& baseAttack, int& baseMagic, int& baseDefense, int& baseAgility);

void help();

void gameOver();

int randInt(int min, int max);

//MAIN FUNCTION
int main () {
    Player Main;
    Player Landsknecht;
    Player Wizard;
    Player Guardian;
    Player Assassin;
    Monster Slime;
    Monster Giant;
    Monster Eagle;
    Monster ZombieMob;
    
    //INITIALIZING PLAYER CLASS BASE STATISTICS
    Landsknecht.HP = 120;     Landsknecht.MaxHP = 120;      Landsknecht.MP = 60;    Landsknecht.MAT = 18;                 
    Landsknecht.MaxMP = 60;   Landsknecht.ATK = 35;         Landsknecht.DEF = 20;
    Landsknecht.AGI = 22;     Landsknecht.className = 1;    Landsknecht.magUp = 0;
    
    Wizard.HP = 80;           Wizard.MaxHP = 80;            Wizard.MP = 90;         Wizard.MAT = 30;
    Wizard.MaxMP = 90;        Wizard.ATK = 12;              Wizard.DEF = 14;
    Wizard.AGI = 18;          Wizard.className = 2;         Wizard.magUp = 1;
    
    Guardian.HP = 170;        Guardian.MaxHP = 170;         Guardian.MP = 30;       Guardian.MAT = 20;
    Guardian.MaxMP = 30;      Guardian.ATK = 24;            Guardian.DEF = 30;
    Guardian.AGI = 15;        Guardian.className = 3;       Guardian.magUp = 0;
    
    Assassin.HP = 100;        Assassin.MaxHP = 100;         Assassin.MP = 30;       Assassin.MAT = 23;
    Assassin.MaxMP = 30;      Assassin.ATK = 27;            Assassin.DEF = 16;
    Assassin.AGI = 35;        Assassin.className = 4;       Assassin.magUp = 0;

    //INITIALIZING MONSTER CLASS STATISTICS
    Slime.Name = "Slime";
    Slime.HP = 120;
    Slime.MP = 0;
    Slime.ATK = 20;
    Slime.DEF = 10;
    Slime.AGI = 10;
    Slime.WEAK1 = 1;    //WEAK TO FIRE
    Slime.STRONG1 = 2;  //STRONG AGAINST ICE
    Slime.numberOfAttacks = 1;

    Giant.Name = "Giant";
    Giant.HP = 220;
    Giant.MP = 40;
    Giant.ATK = 30;
    Giant.DEF = 22;
    Giant.AGI = 20;
    Giant.WEAK1 = 3;    //WEAK TO LIGHTNING
    Giant.STRONG1 = 1;  //STRONG AGAINST FIRE
    Slime.numberOfAttacks = 1;

    Eagle.Name = "Eagle";
    Eagle.HP = 250;
    Eagle.MP = 60;
    Eagle.ATK = 34;
    Eagle.DEF = 20;
    Eagle.AGI = 30;
    Eagle.WEAK1 = 3;    //WEAK TO LIGHTNING
    Eagle.STRONG1 = 1;  //STRONG AGAINST FIRE
    Eagle.numberOfAttacks = 1;

    ZombieMob.Name = "Zombie Mob";
    ZombieMob.HP = 700;
    ZombieMob.MP = 0;
    ZombieMob.ATK = 20;
    ZombieMob.DEF = 15;
    ZombieMob.AGI = 15;
    ZombieMob.WEAK1 = 1;
    ZombieMob.STRONG1 = 3;
    ZombieMob.numberOfAttacks = 3;
    
    //VARIABLE INITIALIZATION (DONT FORGET MONEY)
    string enter;
    char yesno;
    string yourName;
    string classNameDisplayed;
    char classChoice;
    int potions = 3;
    int level = 1;
    int totalEXP = 0;
    
    cout << "[Creator] What is your name, young one? ";
    
    labelname:
    getline(cin, yourName);

    if (yourName == "") {
    	cout << "[Creator] Sorry, I didn't quite get that. Can you say it again?" << endl;
    	cout << "[You] It's... ";
    	goto labelname;
    }

    cout << "[Creator] Very well, " << yourName << ", continue through this game by pressing the [Enter] key.";
    getline(cin, enter);

    cout << "[Creator] Please select choices by typing the first letter of the option."; 
    getline(cin, enter);

    cout << "[Creator] For example, if you want to be a swordsman, you would type S (or s), then the [Enter] key.";
    getline(cin, enter);
    
    cout << endl;
    cout << "[Creator] First, choose your class (Landsknecht, Wizard, Guardian, Assassin, ?): ";
    
    labelstart:
    cin >> classChoice;
    
    switch (classChoice) {
        case 'l':
        case 'L':
            cout << "You chose the Landsknecht class!" << endl << endl;
            Main = Landsknecht;
            break;
        case 'w':
        case 'W':
            cout << "You chose the Wizard class!" << endl << endl;
            getline(cin, enter);
            Main = Wizard;
            break;
        case 'g':
        case 'G':
            cout << "You chose the Guardian class!" << endl << endl;
            getline(cin, enter);
            Main = Guardian;
            break;
        case 'a':
        case 'A':
            cout << "You chose the Assassin class!" << endl << endl;
            getline(cin, enter);
            Main = Assassin;
            break;
        case '?':
        	cout << endl << "[Creator] Landsknechts are reliable attackers with well rounded defense and agility." << endl;
        	getline(cin, enter); //THIS ONE GETS IGNORED
        	cout << "[Creator] They start off with good amounts of HP and MP, making 'em the best option for beginners.";
            cout << "[Creator] Main Tags: Fun to play with, not too hard to use, balanced class.";
        	getline(cin, enter);
        	cout << endl << "[Creator] Wizards are strong mages with more MP and can deal good magic damage." << endl;
        	cout << "[Creator] Its defenses are lower, but increased magic ATK makes up for it.";
            cout << "[Creator] Main Tags: Hard but fun to use, low defense, magic glass cannon (high MAT).";
        	getline(cin, enter);
        	cout << endl << "[Creator] Guardians are tanks that have a lot of HP but little MP." << endl;
        	cout << "[Creator] A slow class to play with due to low agility, but pays off with its high HP.";
            cout << "[Creator] Main Tags: Good for beginners, high defense, deals decent damage.";
        	getline(cin, enter);
        	cout << endl << "[Creator] Assassins are a sneaky class with lowered HP, MP, and DEF stats but high agility and reasonable attack." << endl;
        	cout << "[Creator] Its agility makes escaping easier, and has a higher likelihood of attacking first during battle.";
            cout << "[Creator] Main Tags: Very hard to use, high base critical hit rate, easier for escaping.";
        	getline(cin, enter);
        	cout << endl;
        	cout << "[Creator] Now then... your class? " << endl;
        	cout << "[" << yourName << "] Yeah... I choose to be the ";
        	goto labelstart;
        	break;
        default:
            cout << "[Creator] You failed to choose a class. Try again." << endl;
            getline(cin, enter);
            goto labelstart;
    }

    Main.name = yourName;

    if (Main.className == 1)
    	classNameDisplayed = "Landsknecht";
    else if (Main.className == 2)
    	classNameDisplayed = "Wizard";
    else if (Main.className == 3)
    	classNameDisplayed = "Guardian";
    else if (Main.className == 4)
    	classNameDisplayed = "Assassin";
    
    //STORY PART 1
    
    cout << "[Creator] Let's go over the battle system." << endl << endl;
    getline(cin, enter);
    
    cout << "[Tutorial] Select options by typing the first letter of the command.";
    getline(cin, enter);
    
    cout << "[Tutorial] If you want to [Attack], type A (or a) then press enter.";
    getline(cin, enter);
    
    cout << "[Tutorial] Let's see if you can defeat a basic slime. Good luck!" << endl;
    getline(cin, enter);
    
    battleSystem(Slime.Name, Slime.HP, Slime.WEAK1, Slime.STRONG1, Slime.ATK, Slime.DEF, Slime.AGI, Main.HP, Main.MaxHP, Main.MP, Main.MaxMP, potions, Main.ATK, Main.MAT, Main.DEF, Main.AGI, level, 300, yourName, classNameDisplayed, totalEXP, Main.magUp);

    cout << endl << "[Tutorial] Great Job! Let's see if you can beat a stronger enemy, like a giant.";
    getline(cin, enter);

    cout << "[Creator] Would you like to heal (Y/N)?: ";
    cin >> yesno;

    switch (yesno) {
        case 'y':
        case 'Y':
            cout << "[Creator] Very well...";
            getline(cin, enter);
            Main.HP = Main.MaxHP;
            Main.MP = Main.MaxMP;
            cout << "You've healed!";
            getline(cin, enter);
            break;
        case 'n':
        case 'N':
            cout << "[Creator] Understood...";
            getline(cin, enter);
            break;
        default:
            cout << "[Creator] You failed to choose... starting the battle without healing.";
            getline(cin, enter);
    }

    cout << "Let the battle begin!" << endl;
    getline(cin, enter);

    battleSystem(Giant.Name, Giant.HP, Giant.WEAK1, Giant.STRONG1, Giant.ATK, Giant.DEF, Giant.AGI, Main.HP, Main.MaxHP, Main.MP, Main.MaxMP, potions, Main.ATK, Main.MAT, Main.DEF, Main.AGI, level, 750, yourName, classNameDisplayed, totalEXP, Main.magUp);

    //TUTORIAL END SEQUENCE
    cout << endl;
    cout << "[Julian] Looks like you got the hang of how the battle system works!";
    getline(cin, enter);

    cout << "[Julian] It'll take some time, but maybe a longer version of this game will be made!";
    getline(cin, enter);

    cout << "[Julian] Like... one with a basic story and stuff.";
    getline(cin, enter);

    cout << "[Julian] Well either way, until next time ^_^. -Julian.";
    getline(cin, enter);

    cout << endl;

    exit(0);
}

void battleSystem(string enemy, int enemyHP, int enemyWeak, int enemyStrong, int enemyAttack, int enemyDefense, int enemyAgility, int& HP, int& maxHP, int& MP, int& maxMP, int& vial, int& baseAttack, int& baseMagic, int& baseDefense, int& baseAgility, int& level, int exp, string yourName, string yourClass, int& total, int magUp) {
    string _enter;
    string _choice;
    string specialClassNameDisplayed = yourClass;
    int turnCounter = 1;
    int enemyInitialHP = enemyHP;
    bool enemyIsAlive = true;
    bool escaped = false;
    
    while (enemyIsAlive) {
        
        //STATUS
        cout << "[Turn " << turnCounter << "] Current Status: " << HP << "/" << maxHP << " HP | " << MP << "/" << maxMP << " MP | " << vial << " Potions" << endl;
        cout << "         " << enemy << "'s Status: " << enemyHP << "/" << enemyInitialHP << " HP";
        cout << endl << endl;
        
        if (baseAgility >= enemyAgility) {
            
            playerTurn(enemy, enemyHP, enemyWeak, enemyStrong, enemyAttack, enemyDefense, enemyAgility, HP, maxHP, MP, maxMP, vial, baseAttack, baseMagic, baseDefense, baseAgility, level, exp, yourName, specialClassNameDisplayed, magUp);
            
            if (enemyHP <= 0) {
                break;
            }
            
            enemyTurn(enemy, HP, enemyAttack, enemyDefense, baseDefense);
        }
        
        else {
            
            enemyTurn(enemy, HP, enemyAttack, enemyDefense, baseDefense);
            playerTurn(enemy, enemyHP, enemyWeak, enemyStrong, enemyAttack, enemyDefense, enemyAgility, HP, maxHP, MP, maxMP, vial, baseAttack, baseMagic, baseDefense, baseAgility, level, exp, yourName, specialClassNameDisplayed, magUp);
            
            if (enemyHP <= 0) {
                break;
            }
        }
        
        if (escaped == true) {
            break;
        }
        
        cout << endl;
        turnCounter++;
        
    }
    
    if (escaped == false) {
    	cout << "You have successfully defeated the " << enemy << "!";
    	getline(cin, _enter);
    
    
    	cout << "You gained " << exp << " EXP";
    	getline(cin, _enter);
    
    	//LEVEL UP SYSTEM
        total += exp;
        levelUp(level, total, maxHP, maxMP, baseAttack, baseMagic, baseDefense, baseAgility);
    }
}

void playerTurn(string enemy, int& enemyHP, int enemyWeak, int enemyStrong, int enemyAttack, int enemyDefense, int enemyAgility, int& HP, int& maxHP, int& MP, int& maxMP, int& vial, int& baseAttack, int& baseMagic, int& baseDefense, int& baseAgility, int& level, int exp, string yourName, string yourClass, int magUp) {
    string _enter;
    string _choice;
    int damageDealt;
    int runProbability;
    int runProbabilityLimit = 100;
    double criticalHit;
    bool enemyIsAlive = true;
    bool escaped = false;
    
labela:
    //PLAYER TURN
    cout << "What will you do？ (Attack, Magic, Heal, Run, Status, ?): ";
    getline(cin, _choice);
    
    if (_choice == "?") {
        help();
        goto labela;
    }
    
    if (_choice == "A" || _choice == "a") {
        cout << "[Player] You attacked the " << enemy << ",";
        getline(cin, _enter);
        
        criticalHit = randInt(baseAgility/2, 100);
        
        if (criticalHit >= 90) {
            damageDealt = randInt(baseAttack - (baseAttack/2), baseAttack + (baseAttack/2));
            damageDealt *= 2;
            
            enemyHP -= damageDealt;
            
            cout << "[Player] and critically dealt " << damageDealt << " damage to it!";
            getline(cin, _enter);
        }
        
        else {
            damageDealt = randInt(baseAttack - (baseAttack/3), baseAttack + (baseAttack/3));
            enemyHP -= damageDealt;
            
            cout << "[Player] and dealt " << damageDealt << " damage to it!";
            getline(cin, _enter);
        }
    }
    
    if (_choice == "M" || _choice == "m") { //Possibly add if statements for magic that requires certain levels.
        cout << "What kind? [Fire, Ice, Lightning, Back]: "; //Enemy Weaknesses --> Fire = 1, Ice = 2, Lightning = 3.
        getline(cin, _choice);
        
        if (_choice == "F" || _choice == "f") {
            
            if (MP < 8) {
                cout << "You do not have enough MP!" << endl;
                goto labela;
            }
            
            MP -= 8;
            
            cout << "[Player] You used Fire on the " << enemy << ", ";
            
            if (enemyWeak == 1) {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt *= 2;

                if (magUp == 1) 
                    damageDealt *= 1.5;

                enemyHP -= damageDealt;
                
                cout << "and it was very effective!\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
            
            else if (enemyStrong == 1) {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt *= 0.25;

                if (magUp == 1) 
                    damageDealt *= 1.5;

                enemyHP -= damageDealt;
                
                cout << "and it was not effective...\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
            
            else {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt += (damageDealt * 0.2);

                if (magUp == 1) 
                    damageDealt *= 1.5;
                
                enemyHP -= damageDealt;
                
                cout << "and it was effective.\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
        }
        
        if (_choice == "I" || _choice == "i") {
            
            if (MP < 8) {
                cout << "You do not have enough MP!" << endl;
                goto labela;
            }
            
            MP -= 8;
            
            cout << "[Player] You used Ice on the " << enemy << ", ";
            
            if (enemyWeak == 2) {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt *= 2;

                if (magUp == 1) 
                    damageDealt *= 1.5;

                enemyHP -= damageDealt;
                
                cout << "and it was very effective!\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
            
            else if (enemyStrong == 2) {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt *= 0.25;

                if (magUp == 1) 
                    damageDealt *= 1.5;

                enemyHP -= damageDealt;
                
                cout << "and it was not effective...\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
            
            else {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt += (damageDealt * 0.2);

                if (magUp == 1) 
                    damageDealt *= 1.5;
                
                enemyHP -= damageDealt;
                
                cout << "and it was effective.\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
        }
        
        if (_choice == "L" || _choice == "l") {
            
            if (MP < 8) {
                cout << "You do not have enough MP!" << endl;
                goto labela;
            }
            
            MP -= 8;
            
            cout << "[Player] You used Lightning on the " << enemy << ", ";
            getline(cin, _enter);
            
            if (enemyWeak == 3) {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt *= 2;

                if (magUp == 1) 
                    damageDealt *= 1.5;

                enemyHP -= damageDealt;
                
                cout << "and it was very effective!\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
            
            else if (enemyStrong == 3) {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt *= 0.25;

                if (magUp == 1) 
                    damageDealt *= 1.5;

                enemyHP -= damageDealt;
                
                cout << "and it was not effective...\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
            
            else {
                damageDealt = randInt(baseMagic, baseMagic + (baseMagic/3));
                damageDealt += (damageDealt * 0.2);
                
                if (magUp == 1) 
                    damageDealt *= 1.5;

                enemyHP -= damageDealt;
                
                cout << "and it was effective.\n[Player] You dealt " << damageDealt << " damage to it!";
                getline(cin, _enter);
            }
        }
        
        if (_choice == "B" || _choice == "b") {
            cout << endl;
            goto labela;
        }
        
    }
    
    if (_choice == "H" || _choice == "h") {
        cout << "What kind? [Potions (" << vial << "), Magic, Back]: ";
        getline(cin, _choice);
        
        if (_choice == "P" || _choice == "p") {
            
            if (vial <= 0) {
                cout << "You're out of potions!" << endl;
                goto labela;
            }
            
            HP += 100;
            vial--;
            
            if (HP > maxHP) {
                HP = maxHP;
            }
            
            cout << "[Player] You used a potion and healed!" << endl;
            cout << "[Player] You now have " << HP << " HP";
            getline(cin, _enter);
            
        }
        
        if (_choice == "M" || _choice == "m") {
            
            if (MP <= (maxMP * 0.20)) {
                cout << "You do not have enough MP!" << endl;
                goto labela;
            }
            
            HP += (maxHP * 0.60);
            MP -= (maxMP * 0.20);
            
            if (HP > maxHP) {
                HP = maxHP;
            }
            
            cout << "[Player] You used your staff and healed!" << endl;
            cout << "[Player] You now have " << HP << " HP and " << MP << " MP.";
            getline(cin, _enter);
        }
        
        if (_choice == "B" || _choice == "b") {
            cout << endl;
            goto labela;
        }
    }
    
    if (_choice == "R" || _choice == "r") {
        runProbability = randInt(0, runProbabilityLimit);
        
        if (runProbability <= baseAgility) {
            cout << "[Player] You have successfully escaped." << endl;
            escaped = true;
        }
        
        else {
            cout << "[Player] You failed to escape.";
            runProbabilityLimit -= 15;
        }
        
        getline(cin, _enter);
    }

    if (_choice == "S" || _choice == "s") {
    	cout << "[Name]:  " << yourName << endl;
    	cout << "[Class]: " << yourClass << endl;
    	cout << "[HP]:    " << HP << "/" << maxHP << endl;
    	cout << "[MP]:    " << MP << "/" << maxMP << endl;
    	cout << "[ATK]:   " << baseAttack << endl;
        cout << "[MAT]:   " << baseMagic << endl;
    	cout << "[DEF]:   " << baseDefense << endl;
    	cout << "[AGI]:   " << baseAgility << endl;
    	getline(cin, _enter);
    	goto labela;
    }
}

void enemyTurn(string enemy, int& HP, int enemyAttack, int enemyDefense, int baseDefense) {
    string _enter;
    int enemyDamageDealt;
    
    //ENEMY TURN
    cout << "[Enemy] The " << enemy << " attacks the player.";
    getline(cin, _enter);
    
    enemyDamageDealt = randInt(enemyAttack - (enemyAttack * 0.25), enemyAttack + (enemyAttack * 0.25));
    enemyDamageDealt = enemyDamageDealt + (enemyAttack*1.5 - baseDefense);
    HP -= enemyDamageDealt;
    
    if (HP <= 0) {
        gameOver();
    }
    
    cout << "[Enemy] You've taken " << enemyDamageDealt << " damage, and now have " << HP << " HP.";
    getline(cin, _enter);
}

void levelUp(int& level, int& total, int& maxHP, int& maxMP, int& baseAttack, int& baseMagic, int& baseDefense, int& baseAgility) {
    string enter;
    static const int experience[] = { 0, 200, 400, 700, 1100, 1500, 2000, 2500, 3200, 4000, 5000 };

    cout << endl;

    while (total >= experience[level]) {
        level++;
        maxHP += 25;
        maxMP += 15;
        baseAttack += randInt(2,5);
        baseMagic  += randInt(2,5);
        baseDefense += randInt(2,5);
        baseAgility += randInt(2,5);
        cout << "You leveled up and are now level " << level << "! Stats have also been increased!" << endl;
    }
}

void help() {
    string enter;
    char option;
    string enterA;
    string enterB;
    
labelb:
    
    cout << "What would you like to know more about? (Attacking, Healing, Escaping, Back): ";
    getline(cin, enter);
    
    if (enter == "A" || enter == "a") {
        cout << "What about attacking? (Fist, Magic): ";
        cin >> option;
        
        switch (option) {
            case 'f':
            case 'F':
                cout << endl << "You use your fists to attack the enemy when selecting the [Attack] command." << endl;
                cout << "There is a small chance you will get a critical hit, doubling your attack." << endl;
                cout << "Critical hits are determined by chance from your agility (AGI) stat." << endl;
                cout << "Using the [Attack] command does not cost MP, and is a reliable option for fighting." << endl;
                getline(cin, enter);
                break;
            case 'm':
            case 'M':
                cout << endl << "There are three elements of magic: Fire, Ice, and Lightning." << endl;
                cout << "They all take 8 MP each time you use it" << endl;
                cout << "The amount of damage you deal using elements depends on magic attack (MAT) and your class." << endl;
                cout << "They are all equally powerful, but deal more damage against certain enemies." << endl;
                cout << "For example, because Fire is effective against slimes, it does way more damage than Ice or Lightning." << endl;
                cout << "Most enemies have weaknesses, so take your time to exploit them!" << endl;
                cout << "Also, some enemies are also strong against certain elements, so beware of that." << endl;
                getline(cin, enter);
                break;
            default:
                cout << "Instructions not followed, going to help screen.";
                getline(cin, enter);
        }
        cout << endl;
        goto labelb;
    }
    
    if (enter == "H" || enter == "H") {
        cout << "What about healing? (Potions, Staff): ";
        cin >> option;
        
        switch (option) {
            case 'p':
            case 'P':
                cout << endl << "You can heal a set amount of HP (100) with potions." << endl;
                cout << "You have limited potions though, so be aware of that.";
                getline(cin, enter);
                break;
            case 's':
            case 'S': 
                cout << endl << "By spending 1/5th of your MP, you can heal yourself with a staff." << endl;
                cout << "It heals 60 percent of your max HP, proving to possibly be more effective than potions.";
                getline(cin, enter);
                break;
            default:
                cout << endl << "Instructions not followed, going to help screen.";
                getline(cin, enter);
        }
        cout << endl << endl;
        goto labelb;
    }
    
    if (enter == "E" || enter == "e") {
        cout << endl << "Your ability to escape a battle depends on your base agility stat." << endl;
        cout << "Each time you fail, your escape chance increases by 10-20 percent." << endl;
        cout << endl;
        goto labelb;
    }
    
    if (enter == "B" || enter == "b") {
        cout << "Understood!" << endl;
        cout << endl;
    }
}

void gameOver() {
    string enter2;
    cout << "You lost all of your HP and died!";
    getline(cin, enter2);
    
    cout << "You can either quit the game or go to the main menu. What will you choose?" << endl;
    cout << "Quit (Q) || Menu (M): ";
    getline(cin, enter2);
    
    if (enter2 == "Q" || enter2 == "q") {
        cout << "Very well, the game is now closing...";
        getline(cin, enter2);
        exit(1);
    }
    
    else if (enter2 == "M" || enter2 == "m") {
        //INCOMPLETE
        cout << "Sorry, this functionality does not work yet. Exiting now...";
        getline(cin, enter2);
        cout << endl;

        exit(1);
    }
    
    else {
        cout << "You didn't select either of the options. Proceeding with the quitting option...";
        getline(cin, enter2);
        exit(1);
    }
}

int randInt(int min, int max) {
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
