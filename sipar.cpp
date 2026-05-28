#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <windows.h>
#include <ctime>
#include <cmath>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setPos(int x, int y) {
    COORD c;
    c.X = (short)(40 + x);
    c.Y = (short)(12 - y);
    SetConsoleCursorPosition(hConsole, c);
}
void setColor(int color) { SetConsoleTextAttribute(hConsole, color); }
// colors and visuals ae added using claude and deepseek
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void clearScreen() {
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

// ---------------- FRONT PAGE MENU ----------------
bool showFrontPage() {
    clearScreen();
    hideCursor();

    int cursorX = 0;
    int cursorY = 0;

    string menuOptions[3] = {
        "START MISSION",
        "INSTRUCTIONS",
        "EXIT SYSTEM"
    };

    int selectedOption = 0;
    int lastOption = -1;
    int lastCursorX = -1;
    int lastCursorY = -1;

    while (true) {
        // Only redraw if something changed
        if (lastOption != selectedOption || lastCursorX != cursorX || lastCursorY != cursorY) {

            // Draw border (only once)
            if (lastOption == -1) {
                // Fill entire background with gray (background color code: 112 = gray background with black text)
                // Gray background = 112 (7*16 = 112, where 7 is gray background)
                COORD fillPos;
                for (int y = 0; y < 25; y++) {
                    for (int x = 0; x < 80; x++) {
                        fillPos.X = x;
                        fillPos.Y = y;
                        SetConsoleCursorPosition(hConsole, fillPos);
                        setColor(112); // Gray background with black text
                        cout << " ";
                    }
                }

                // Draw black border
                setColor(112); // Gray background with black text
                for (int i = 0; i < 80; i++) {
                    COORD c;
                    c.X = i; c.Y = 0;
                    SetConsoleCursorPosition(hConsole, c);
                    cout << "=";
                    c.Y = 24;
                    SetConsoleCursorPosition(hConsole, c);
                    cout << "=";
                }

                for (int i = 1; i < 24; i++) {
                    COORD c;
                    c.X = 0; c.Y = i;
                    SetConsoleCursorPosition(hConsole, c);
                    cout << "||";
                    c.X = 78;
                    SetConsoleCursorPosition(hConsole, c);
                    cout << "||";
                }

                // Title with white text on gray background
                COORD titlePos;
                titlePos.X = 20; titlePos.Y = 5;
                SetConsoleCursorPosition(hConsole, titlePos);
                setColor(112); // Gray background with black text
                cout << "+===================================+";
                titlePos.Y = 6;
                SetConsoleCursorPosition(hConsole, titlePos);
                cout << "|  SIPAR DEFENSE COMMAND SYSTEM   |";
                titlePos.Y = 7;
                SetConsoleCursorPosition(hConsole, titlePos);
                cout << "+===================================+";

                // Instructions at bottom (only once)
                COORD instrPos;
                instrPos.X = 15; instrPos.Y = 20;
                SetConsoleCursorPosition(hConsole, instrPos);
                setColor(112); // Gray background with black text
                cout << "Use [W/S] to navigate | Press [SPACE] to select";
            }

            // Menu options - redraw only changed ones
            if (lastOption != selectedOption || lastOption == -1) {
                for (int i = 0; i < 3; i++) {
                    COORD optPos;
                    optPos.X = 30; optPos.Y = 11 + i * 2;
                    SetConsoleCursorPosition(hConsole, optPos);

                    if (i == selectedOption) {
                        setColor(240); // Black background with bright white text (inverted)
                        cout << ">>> " << menuOptions[i] << " <<<";
                    } else {
                        setColor(112); // Gray background with black text
                        cout << "    " << menuOptions[i] << "    ";
                    }
                }
            }

            // Clear old cursor position
            if (lastCursorX != -1) {
                COORD oldPos;
                oldPos.X = 5 + lastCursorX;
                oldPos.Y = 10 + lastCursorY;
                SetConsoleCursorPosition(hConsole, oldPos);
                setColor(112); // Gray background
                cout << " ";
            }

            // Draw moveable cursor
            COORD cursorPos;
            cursorPos.X = 5 + cursorX;
            cursorPos.Y = 10 + cursorY;
            SetConsoleCursorPosition(hConsole, cursorPos);
            setColor(124); // Gray background with red text
            cout << "@";

            // Moveable cursor display
            COORD instrPos;
            instrPos.X = 25; instrPos.Y = 22;
            SetConsoleCursorPosition(hConsole, instrPos);
            setColor(112); // Gray background with black text
            cout << "Cursor Position: X=" << cursorX << " Y=" << cursorY << "  ";

            lastOption = selectedOption;
            lastCursorX = cursorX;
            lastCursorY = cursorY;
        }

        // menu keh liye input wagaira
        if (GetAsyncKeyState('W') & 0x8000) {
            selectedOption = (selectedOption - 1 + 3) % 3;
            cursorY = max(-5, cursorY - 1);
            Sleep(200);
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            selectedOption = (selectedOption + 1) % 3;
            cursorY = min(10, cursorY + 1);
            Sleep(200);
        }
        if (GetAsyncKeyState('A') & 0x8000) {
            cursorX = max(-5, cursorX - 1);
            Sleep(100);
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            cursorX = min(65, cursorX + 1);
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            Sleep(200);
            if (selectedOption == 0) {
                return true; // Starting mission
            } else if (selectedOption == 1) {
                // instrctions show krna keh liye
                clearScreen();
                setColor(11);
                COORD instrDetailPos;
                instrDetailPos.X = 10; instrDetailPos.Y = 5;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                cout << "=== INSTRUCTIONS ===";
                instrDetailPos.Y = 7;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                setColor(12); cout << "X = Enemy Missile (High Priority)";
                instrDetailPos.Y = 8;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                setColor(11); cout << ". = Enemy Drone (Medium Priority)";
                instrDetailPos.Y = 9;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                setColor(10); cout << "<O> = Friendly Unit (Do Not Shoot!)";
                instrDetailPos.Y = 10;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                setColor(9); cout << "| = Defense Line (Protect This!)";
                instrDetailPos.Y = 12;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                setColor(14); cout << "Press [SPACE] to fire missiles";
                instrDetailPos.Y = 13;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                cout << "Press [E] to exit mission";
                instrDetailPos.Y = 16;
                SetConsoleCursorPosition(hConsole, instrDetailPos);
                setColor(7); cout << "Press any key to return...";
                while (!GetAsyncKeyState(VK_SPACE)) Sleep(50);
                Sleep(300);
                clearScreen();
                lastOption = -1; // Force full redraw
            } else if (selectedOption == 2) {
                return false; // Exit
            }
        }

        Sleep(50);
    }
}

struct Target {
    int id;
    float x, y;
    bool isHostile;
    bool destroyed;
    char symbol;
    int risk;
    void evaluate() {
        float dist = sqrt(x * x + y * y);
        risk = (isHostile ? 55 : 0) + (int)(120 / (dist + 1));
    }
};

// BST use kia hai takeh drone aur missile alag alag hoon priority base pr
class Node {
public:
    Target data;
    Node* left;
    Node* right;
    Node(Target t) { data = t; left = NULL; right = NULL; }
};

class BST {
public:
    Node* root;
    BST() { root = NULL; }

    Node* insert(Node* node, Target t) {
        if (!node) return new Node(t);
        if (t.risk < node->data.risk) node->left = insert(node->left, t);
        else node->right = insert(node->right, t);
        return node;
    }

    void insert(Target t) { root = insert(root, t); }

    Node* findPriority(Node* node, char sym) {
        if (!node) return NULL;
        if (node->data.isHostile && !node->data.destroyed && node->data.symbol == sym) return node;
        Node* left = findPriority(node->left, sym);
        if (left) return left;
        return findPriority(node->right, sym);
    }

    Node* findPriority(char sym) { return findPriority(root, sym); }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left); clear(node->right);
        delete node;
    }
    void clear() { clear(root); root = NULL; }
};

// Sipar
class SiparSystem {
private:
    vector<Target> allTargets;
    vector<string> history;
    queue<Target> waveQueue;
    BST activeHostiles;
    char missileBar[20];         // ammo bar (array)
    int missiles;
    int breaches;

    void boomAnimation(Target& t) {
        int tx = (int)t.x;
        int ty = (int)t.y / 2;
        char frames[4] = { '*', '#', '@', '*' };
        int colors[4] = { 14, 12, 6, 14 };
        for (int i = 0; i < 4; i++) {
            setPos(tx, ty);
            setColor(colors[i]);
            cout << frames[i];
            Sleep(150);
            setPos(tx, ty);
            cout << " ";
        }
        setPos(tx, ty);
        setColor(8);
        cout << "N";
    }

public:
    SiparSystem() {
        srand((unsigned)time(0));
        missiles = 15;
        breaches = 0;
        for (int i = 0; i < 20; i++) missileBar[i] = '|';
    }

    void initWave() {
        // preload queue targets
        Target t1{ 301, 35, 10, true, false, 'X' }; t1.evaluate();
        Target t2{ 302, 40, -8, true, false, '.' }; t2.evaluate();
        Target t3{ 303, 25, 6, true, false, 'X' }; t3.evaluate();
        Target t4{ 304, 30, -12, true, false, '.' }; t4.evaluate();
        Target t5{ 305, 0, -20, false, false, 'O' }; t5.evaluate();
        Target t6{ 306, 45, 5, true, false, 'X' }; t6.evaluate();
        Target t7{ 307, 50, -6, true, false, '.' }; t7.evaluate();
        waveQueue.push(t1); waveQueue.push(t2);
        waveQueue.push(t3); waveQueue.push(t4);
        waveQueue.push(t5); waveQueue.push(t6);
        waveQueue.push(t7);
    }

    int countHostiles() {
        int count = 0;
        for (auto& t : allTargets) {
            if (t.isHostile && !t.destroyed) count++;
        }
        return count;
    }

    void deployWave() {
        if (!waveQueue.empty() && countHostiles() < 6) {
            Target t = waveQueue.front(); waveQueue.pop();
            allTargets.push_back(t);
        }
    }

    void rebuildBST() {
        activeHostiles.clear();
        for (auto& t : allTargets) {
            if (t.isHostile && !t.destroyed) {
                activeHostiles.insert(t);
            }
        }
    }

    void updatePositions() {
        for (auto& t : allTargets) {
            if (!t.destroyed) {
                if (t.isHostile) t.x -= 1;
                else if (t.symbol == 'O') t.y += (rand() % 3 - 1);
            }
        }
    }

    void draw() {
        for (auto& t : allTargets) {
            setPos((int)t.x, (int)t.y / 2);
            if (t.destroyed) { setColor(8); cout << "N"; }
            else if (t.isHostile) { setColor(12); cout << t.symbol; }
            else { setColor(10); cout << "<O>"; }
        }
    }

    void fire() {
        if (missiles <= 0) {
            setPos(-20, -12); setColor(12);
            cout << "Not enough stock!";
            Sleep(700);
            return;
        }

        Node* threat = activeHostiles.findPriority('X');
        if (!threat) threat = activeHostiles.findPriority('.');

        if (threat) {
            missiles--;
            missileBar[missiles] = ' '; // update ammo bar
            setPos(-25, -12); setColor(14); cout << "[DEFENSE SYSTEM] → LOCKED ON"; Sleep(400);
            setPos(-25, -11); cout << "[MISSILE LAUNCH] → IMPACT CONFIRMED"; Sleep(400);
            setPos(-25, -10); cout << "[TARGET DESTROYED]"; Sleep(400);

            for (auto& t : allTargets) {
                if (t.id == threat->data.id) {
                    boomAnimation(t);
                    t.isHostile = false;
                    t.destroyed = true;
                    history.push_back("Neutralized: " + to_string(t.id));
                    break;
                }
            }
        }
        else {
            missiles--;
            missileBar[missiles] = ' ';
            setPos(-20, -12); setColor(11);
            cout << "You targeted non-hostile target <O>";
            Sleep(700);
        }
    }

    void monitorBase() {
        for (auto& t : allTargets) {
            if (t.isHostile && !t.destroyed && t.x <= -40) {
                setPos(-25, -12); setColor(9);
                if (t.symbol == 'X') cout << "Enemy missile hit our base!";
                else if (t.symbol == '.') cout << "A hostile drone entered our base!";
                Sleep(700);
                t.isHostile = false; t.destroyed = true;
                breaches++;
            }
        }
    }

    void printHistory() {
        setPos(-38, 10); setColor(7);
        cout << "LOG: ";
        for (auto& h : history) cout << h << " | ";
    }

    void printMissiles() {
        setPos(30, -12); setColor(11);
        cout << "Missiles: " << missiles << " ";
        cout << "[";
        for (int i = 0; i < 20; i++) cout << missileBar[i];
        cout << "]";
    }

    void drawBaseLine() {
        setColor(9);
        for (int j = -12; j <= 12; j++) {
            setPos(-40, j);
            cout << "|";
        }
    }

    void printManual() {
        setPos(-38, -14);
        setColor(12); cout << "X=Missile  ";
        setColor(11); cout << ".=Drone  ";
        setColor(10); cout << "<O>=Friendly  ";
        setColor(14); cout << "HQ=Base  ";
        setColor(9);  cout << "Line=Defense  ";
        setColor(8);  cout << "N=Neutralized";
    }

    int getNeutralizedCount() {
        int count = 0;
        for (auto& t : allTargets) if (t.destroyed) count++;
        return count;
    }

    int getBreaches() { return breaches; }
    int getRemainingMissiles() { return missiles; }


}; //close SiparSystem

// MAIN
int main() {
    hideCursor();

    // Show front page menu using deepseek
    bool startMission = showFrontPage();

    if (!startMission) {
        clearScreen();
        setColor(11);
        cout << "\n\n\tSystem shutdown. Goodbye.\n\n";
        return 0;
    }

    SiparSystem sipar;
    int frame = 0;

    Sleep(1000);
    clearScreen();
    setColor(11);
    cout << "\n\n\t[ INITIALIZING DEFENSE SYSTEMS... ]\n";
    Sleep(2000);

    sipar.initWave();

    while (frame < 80) {
        clearScreen();
        sipar.rebuildBST();   // keep BST in sync

        setColor(11);
        cout << "------------------------------------------------------------\n";
        cout << " SIPAR RADAR ENGINE | PULSE: " << frame << "\n";
        cout << "------------------------------------------------------------\n";

        setPos(0, 0); setColor(14); cout << "[HQ]";

        if (frame % 10 == 0) sipar.deployWave();

        sipar.updatePositions();
        sipar.draw();
        sipar.printHistory();
        sipar.printMissiles();
        sipar.drawBaseLine();
        sipar.printManual();
        sipar.monitorBase();

        if (GetAsyncKeyState(VK_SPACE) & 0x8000) sipar.fire();
        if (GetAsyncKeyState('E') & 0x8000) break;

        setPos(-38, -10); setColor(8);
        cout << ">> STATUS: Scanning... Press [SPACE] to fire | Press E to exit";

        Sleep(500); // Increased from 300 to reduce pulse speed
        frame++;
    }

    clearScreen();

    // Create a visual end screen
    setColor(112); // Gray background
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            COORD fillPos;
            fillPos.X = x;
            fillPos.Y = y;
            SetConsoleCursorPosition(hConsole, fillPos);
            cout << " ";
        }
    }

    // Draw border
    setColor(112);
    for (int i = 0; i < 80; i++) {
        COORD c;
        c.X = i; c.Y = 0;
        SetConsoleCursorPosition(hConsole, c);
        cout << "=";
        c.Y = 24;
        SetConsoleCursorPosition(hConsole, c);
        cout << "=";
    }

    for (int i = 1; i < 24; i++) {
        COORD c;
        c.X = 0; c.Y = i;
        SetConsoleCursorPosition(hConsole, c);
        cout << "||";
        c.X = 78;
        SetConsoleCursorPosition(hConsole, c);
        cout << "||";
    }

    COORD pos;

    // Title
    pos.X = 25; pos.Y = 3;
    SetConsoleCursorPosition(hConsole, pos);
    setColor(112);
    cout << "===== DEFENSE SUMMARY =====";

    // Stats
    pos.X = 30; pos.Y = 7;
    SetConsoleCursorPosition(hConsole, pos);
    setColor(112);
    cout << "Missiles Remaining: " << sipar.getRemainingMissiles();

    pos.X = 30; pos.Y = 9;
    SetConsoleCursorPosition(hConsole, pos);
    cout << "Hostiles Neutralized: " << sipar.getNeutralizedCount();

    pos.X = 30; pos.Y = 11;
    SetConsoleCursorPosition(hConsole, pos);
    cout << "Breaches: " << sipar.getBreaches();

    // Mission Result
    if (sipar.getBreaches() == 0) {
        // SUCCESS - Green background
        pos.X = 20; pos.Y = 15;
        SetConsoleCursorPosition(hConsole, pos);
        setColor(32); // Green background with black text
        cout << "                                        ";
        pos.Y = 16;
        SetConsoleCursorPosition(hConsole, pos);
        cout << "     MISSION SUCCESSFUL: BASE SECURED    ";
        pos.Y = 17;
        SetConsoleCursorPosition(hConsole, pos);
        cout << "                                        ";

        // ASCII art for success
        pos.X = 35; pos.Y = 19;
        SetConsoleCursorPosition(hConsole, pos);
        setColor(112);
        cout << "  ___  ";
        pos.X = 35; pos.Y = 20;
        SetConsoleCursorPosition(hConsole, pos);
        cout << " /   \\ ";
        pos.X = 35; pos.Y = 21;
        SetConsoleCursorPosition(hConsole, pos);
        cout << " \\___/ ";
    }
    else {
        // FAILED - Red background
        pos.X = 20; pos.Y = 15;
        SetConsoleCursorPosition(hConsole, pos);
        setColor(64); // Red background with black text
        cout << "                                        ";
        pos.Y = 16;
        SetConsoleCursorPosition(hConsole, pos);
        cout << "    MISSION FAILED: BASE COMPROMISED    ";
        pos.Y = 17;
        SetConsoleCursorPosition(hConsole, pos);
        cout << "                                        ";

        // ASCII art for failure
        pos.X = 35; pos.Y = 19;
        SetConsoleCursorPosition(hConsole, pos);
        setColor(112);
        cout << "  ___  ";
        pos.X = 35; pos.Y = 20;
        SetConsoleCursorPosition(hConsole, pos);
        cout << " /   \\ ";
        pos.X = 35; pos.Y = 21;
        SetConsoleCursorPosition(hConsole, pos);
        cout << "  \\_/  ";
    }

    // Press any key to exit
    pos.X = 25; pos.Y = 23;
    SetConsoleCursorPosition(hConsole, pos);
    setColor(112);
    cout << "Press any key to exit...";

    // Wait for key press
    while (true) {
        for (int key = 0; key < 256; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
                Sleep(200);
                return 0;
            }
        }
        Sleep(50);
    }
}
