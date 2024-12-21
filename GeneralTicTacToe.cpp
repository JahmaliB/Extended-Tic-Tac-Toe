#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int MAX_ROWS = 13;
const int MAX_COLS = 16;

//==========
// Struct ||
//==========
struct GameInfo
{
    int numPlayers;
};

struct PlayerInfo
{
    string fullname, firstName, lastName;
    char currentPlayerPiece;
    int wins, losses, draws;
};

struct BoardInfo
{
    int numRows;
    int numCols;
};

//==========================================
// function to determine if name is valid ||
//==========================================
bool nameValidation(string& fullName);

//=====================================================
// capitalize First Characted in first and last name ||
//=====================================================
string capitalization(string& fullName);

//===========================================================
// function to check if numrows and numcols is and integer ||
//===========================================================
bool isInteger(const string& str);

//============================
//convert the string to int ||
//============================
int stringToInt(const string& str);

//================================
// initialize board with spaces ||
//===============================-
void initializeBoard(char board[MAX_ROWS][MAX_COLS], BoardInfo& boardInfo);

//================
//Board Drawing ||
//================
void displayBoard(char board[MAX_ROWS][MAX_COLS], BoardInfo& boardInfo, char currentPlayerPiece);

//=======================
//function to checkwin ||
//=======================
bool checkWin(char board[MAX_ROWS][MAX_COLS], BoardInfo& boardInfo, char currentPlayerPiece);

//=================
// Draw Function ||
//=================
bool isDraw(BoardInfo& boardInfo, char board[MAX_ROWS][MAX_COLS]);

//===========================
// checks if move is valid ||
//===========================
bool isValidMove(int row, int col, int numRows, int numCols, char board[MAX_ROWS][MAX_COLS]);

//======================
// Gather Player Move ||
//======================
char makeMove(PlayerInfo players[], BoardInfo& boardInfo, char board[MAX_ROWS][MAX_COLS], int currentPlayer);

//================================================================
//displays game stats (wins loses, draws, and number of games)  ||
//================================================================
void displayStats(PlayerInfo players[], int numGames, GameInfo gameInfo, string winner);

//=======================================
// ask user if they want to play again ||
//=======================================
char redo();

//=================
// Main Function ||
//=================
int main () 
{
    GameInfo gameInfo;
    BoardInfo boardInfo;
    PlayerInfo players[7];
    char board[MAX_ROWS][MAX_COLS], currentPlayerPiece = 'X', again;
    int currentPlayer = 2, numGames = 0, tempIndex = -1;
    string nextPlayer, winner, numPlayersStr;

    for (int index = 0; index < 7; index++) 
    {
        players[index].wins = 0;
        players[index].losses = 0;
        players[index].draws = 0;
    }

    cout << "\n\t\t Welcome to Extended Tic Tac Toe" << endl;

    while (true) 
    {
        cout << "\nHow many players will be playing (between 3 - 7 players): ";
        getline(cin, numPlayersStr);

        bool isValid = true;

        while (numPlayersStr.length() == 0) 
        {
            isValid = false;
            break;
        }

        for (char c : numPlayersStr) 
        {
            if (!isdigit(c)) 
            {
                isValid = false;
                break;
            }
        }

        if (isValid) 
        {
            gameInfo.numPlayers = stoi(numPlayersStr);
            if (gameInfo.numPlayers >= 3 && gameInfo.numPlayers <= 7) 
            {
                break;
            }
        }

        cout << "\nInvalid input. Please enter a valid number between 3 and 7. ";
    }

    cout << endl;
    for (int index = 0; index < gameInfo.numPlayers; index++) 
    {
        cout << "Player " << index + 1 << ", enter your first and last name (seperated by spaces): " ;
        getline (cin, players[index].fullname);

        while (!nameValidation(players[index].fullname)) 
        {
            cout << "\nInvalid Name!" <<endl << "Player " << index + 1 << 
            " please enter your first and last name (alphabet character ONLY and seperated by spaces): ";
            getline (cin, players[index].fullname);
        }        
        capitalization(players[index].fullname);
        int Pos = players[index].fullname.find(' ');
        players[index].firstName = players[index].fullname.substr(0, Pos);
        players[index].lastName = players[index].fullname.substr(Pos + 1);
        players[index].currentPlayerPiece = 'a' + index;
    }

    while (true) 
    {
        cout << "\nPlease enter the dimension of the board (between 4 by 4 - 13 by 16). " << endl;
        cout << "Enter the number of rows -> ";
        string numRowsStr;
        cin >> numRowsStr;

        cout << "Enter the number of columns -> ";
        string numColsStr;
        cin >> numColsStr;

        if (isInteger(numRowsStr) && isInteger(numColsStr)) 
        {
            boardInfo.numRows = stringToInt(numRowsStr);
            boardInfo.numCols = stringToInt(numColsStr);

            if (boardInfo.numRows >= 4 && boardInfo.numCols >= 4 && boardInfo.numRows <= MAX_ROWS && boardInfo.numCols <= MAX_COLS) 
            {
                break;
            }
        }

        cout << "\nInvalid Dimensions. Enter the dimension again." << endl;
    }
        

    do 
    {
        if (again == 'Y' || again == 'y') 
        {
            winner = 'x';
            cout << "Please enter the dimension of the board." <<endl;
            cout << "Enter the number of rows -> ";
            cin >> boardInfo.numRows;
            cout << "Enter the number of columns -> ";
            cin >> boardInfo.numCols;

            while (boardInfo.numRows < 4 || boardInfo.numCols < 4 || boardInfo.numRows > MAX_ROWS || boardInfo.numCols > MAX_COLS) 
            {
                cout << "\n The board has to be 4 by 4 or larger. Enter the dimension again.";
                cout << "Enter the number of rows -> ";
                cin >> boardInfo.numRows;
                cout << "Enter the number of columns -> ";
                cin >> boardInfo.numCols;
            }
        }

        initializeBoard(board, boardInfo);
        displayBoard(board, boardInfo, currentPlayerPiece);
        numGames++;

        if (numGames > 1 && tempIndex != -1)  
        {
            currentPlayer = (tempIndex + 1) % gameInfo.numPlayers;                        
        } 
        else if (numGames > 1 && isDraw(boardInfo, board)) 
        {
            currentPlayer = (tempIndex + 1) % gameInfo.numPlayers;                        
        }

        while (true) 
        {
            if (currentPlayer >= gameInfo.numPlayers) 
            {
                currentPlayer = 0;
            } 

            currentPlayerPiece = makeMove(players, boardInfo, board, currentPlayer);
            displayBoard(board, boardInfo, currentPlayerPiece);

            if (isDraw(boardInfo, board)) 
            {
                tempIndex = currentPlayer;
                for (int i = 0; i < gameInfo.numPlayers; i++)
                    {
                        players[i].draws++;
                    }
                displayStats(players, numGames, gameInfo, winner);
                break;
            }

            if (checkWin(board, boardInfo, currentPlayerPiece)) 
            {
                tempIndex = currentPlayer;
                winner = players[currentPlayer].fullname;
                for (int i = 0; i < gameInfo.numPlayers; i++) 
                {
                    if (winner != players[i].fullname) 
                    {
                        players[i].losses++;
                    }
                }

                displayBoard (board, boardInfo, currentPlayerPiece);
                cout << "The winner is " << winner << "! \n";
                displayStats(players, numGames, gameInfo, winner);
                break;
            }
            currentPlayer++;
        }
        again = redo();

    } while (again == 'Y' || again == 'y');

    cout << "\t\tGood Bye! See you soon!";
}

bool nameValidation(string& fullName) 
{
    bool foundFirstName = false;
    bool foundLastName = false;
    bool foundSpace = false;

    for (char c : fullName) 
    {
        if (isalpha(c)) 
        {
            if (!foundFirstName) 
            {
                foundFirstName = true;
            } 
            else if (foundSpace) 
            {
                return true;
            }
        } 
        else if (isspace(c)) 
        {
            if (!foundFirstName) 
            {
                continue;
            } 
            else 
            {
                foundSpace = true;
            }
        } 
        else 
        {
            return false;
        }
    }
    return false;
}

string capitalization (string& fullName) 
{
    for (int i = 0; i < fullName.length(); i++) 
    {
        if (i == 0)
		{
			fullName[i] = toupper(fullName[i]);
		}
		else if (fullName[i - 1] == ' ')
		{
			fullName[i] = toupper(fullName[i]);
		}
    }
    return fullName;
}

bool isInteger(const string& str) 
{
    for (char c : str) 
    {
        if (!isdigit(c)) 
        {
            return false;
        }
    }
    return true;
}

int stringToInt(const string& str) 
{
    int result = 0;
    for (char c : str) 
    {
        result = result * 10 + (c - '0');
    }
    return result;
}

void initializeBoard (char board[MAX_ROWS][MAX_COLS], BoardInfo& boardInfo) 
{
    for (int r = 0; r < boardInfo.numRows; r++)
    {
        for (int c = 0; c < boardInfo.numCols; c++)
        {
            board[r][c] = ' ';
        }
    }
}

void displayBoard (char board[MAX_ROWS][MAX_COLS], BoardInfo& boardInfo, char currentPlayerPiece)
{    
    cout << endl;
    cout << "  ";
    for (int i = 1; i <= boardInfo.numCols; i++)
    {
        if (i < 10) 
        {
            cout << "  " << i << " ";
        } 
        else 
        {
            cout << "  " << i << "";
        }
    }
    cout << endl;


    cout << "  ";
    for (int i = 1; i <= boardInfo.numCols; i++)
    {
        cout << " ---";
    }
    cout <<endl;

    for (int r = 0; r < boardInfo.numRows; r++)
    {
        char displayLetter = 'A' + r;
        cout << displayLetter << " | " ;

        for (int c = 0; c < boardInfo.numCols; c++)
        {
            cout << board[r][c] << " | ";
        }
        cout <<displayLetter << endl;

        if (r < boardInfo.numRows - 1)
        {
            cout << "   ---";
            for (int i = 1; i < boardInfo.numCols; i++)
            {
                cout << " ---";
            }
            cout << " " << endl;
        }
    }

    cout << "  ";
    for (int i = 1; i <= boardInfo.numCols; i++)
    {
        cout << " ---";
    }
    cout << endl;

    cout << "  ";
    for (int i = 1; i <= boardInfo.numCols; i++)
    {
        if (i < 10) 
        {
            cout << "  " << i << " ";
        } 
        else 
        {
            cout << "  " << i << "";
        }
    }
    cout << endl << endl;
 

}

bool checkWin(char board[MAX_ROWS][MAX_COLS], BoardInfo& boardInfo, char currentPlayerPiece)
{
    bool hasWin = false;

    for (int r = 0; r < boardInfo.numRows; r++)
    {
        int consecutiveCount = 0;
        for (int c = 0; c < boardInfo.numCols; c++)
        {
            if (board[r][c] == currentPlayerPiece)
            {
                consecutiveCount++;
                if (consecutiveCount >= 3 || consecutiveCount >= 5)
                {
                    for (int i = c - consecutiveCount + 1; i <= c; i++)
                    {
                        if (board[r][i] != toupper(board[r][i]))
                        {
                            board[r][i] = toupper(board[r][i]);
                        }
                    }
                    hasWin = true;
                }
            }
            else
            {
                consecutiveCount = 0;
            }
        }
    }

    for (int c = 0; c < boardInfo.numCols; c++)
    {
        int consecutiveCount = 0;
        for (int r = 0; r < boardInfo.numRows; r++)
        {
            if (board[r][c] == currentPlayerPiece)
            {
                consecutiveCount++;
                if (consecutiveCount >= 3 || consecutiveCount >= 5)
                {
                    for (int i = r - consecutiveCount + 1; i <= r; i++)
                    {
                        if (board[i][c] != toupper(board[i][c]))
                        {
                            board[i][c] = toupper(board[i][c]);
                        }
                    }
                    hasWin = true;
                }
            }
            else
            {
                consecutiveCount = 0;
            }
        }
    }

    for (int r = 0; r < boardInfo.numRows; r++)
    {
        for (int c = 0; c < boardInfo.numCols; c++)
        {
            int consecutiveCount = 0;

            for (int i = 0; i < 4; i++)
            {
                int newRow = r + i;
                int newCol = c + i;

                if (newRow >= 0 && newRow < boardInfo.numRows && newCol >= 0 && newCol < boardInfo.numCols &&
                    board[newRow][newCol] == currentPlayerPiece)
                {
                    consecutiveCount++;
                    if (consecutiveCount >= 3 || consecutiveCount >= 5) // Modify to 4 for a win with 4 consecutive pieces
                    {
                        for (int j = 0; j < i + 1; j++)
                        {
                            if (board[r + j][c + j] != toupper(board[r + j][c + j]))
                            {
                                board[r + j][c + j] = toupper(board[r + j][c + j]);
                            }
                        }
                        hasWin = true;
                    }
                }
                else
                {
                    consecutiveCount = 0;
                }
            }
        }
    }

    for (int r = 0; r < boardInfo.numRows; r++)
    {
        for (int c = 0; c < boardInfo.numCols; c++)
        {
            int consecutiveCount = 0;
            for (int i = 0; i < 4; i++)
            {
                int newRow = r + i;
                int newCol = c - i;
                if (newRow >= 0 && newRow < boardInfo.numRows && newCol >= 0 && newCol < boardInfo.numCols &&
                    board[newRow][newCol] == currentPlayerPiece)
                {
                    consecutiveCount++;
                    if (consecutiveCount >= 3 || consecutiveCount >= 5)
                    {
                        for (int j = 0; j < i + 1; j++)
                        {
                            if (board[r + j][c - j] != toupper(board[r + j][c - j]))
                            {
                                board[r + j][c - j] = toupper(board[r + j][c - j]);
                            }
                        }
                        hasWin = true;
                    }
                }
                else
                {
                    consecutiveCount = 0;
                }
            }
        }
    }

    return hasWin;
}

bool isDraw(BoardInfo& boardInfo, char board[MAX_ROWS][MAX_COLS]) 
{
    for (int r = 0; r < boardInfo.numRows; r++) 
    {
        for (int c = 0; c < boardInfo.numCols; c++) 
        {
            if (board[r][c] == ' ') 
            {
                return false;
            }
        }
    }
    return true;
}

bool isValidMove(int row, int col, int numRows, int numCols, char board[MAX_ROWS][MAX_COLS])
{
    // Check if the specified coordinates are within the board boundaries
    if (row < 0 || row >= numRows || col < 0 || col >= numCols)
    {
        return false;
    }

    // Check if the cell is already occupied
    if (board[row][col] != ' ')
    {
        return false;
    }

    return true;
}

char makeMove(PlayerInfo players[], BoardInfo& boardInfo, char board[MAX_ROWS][MAX_COLS], int currentPlayer)
{
    string mark;
    int row, col;

    while (true)
    {
        cout << players[currentPlayer].firstName << " (" << players[currentPlayer].currentPlayerPiece 
        << ") enter the coordinates you wish to mark (Ex: A5, D2, m7, e5): ";
        cin >> mark;

        row = toupper(mark[0]) - 'A';
        col = mark[1] - '0' - 1;

        if (isValidMove(row, col, boardInfo.numRows, boardInfo.numCols, board))
        {
            board[row][col] = players[currentPlayer].currentPlayerPiece;
            return players[currentPlayer].currentPlayerPiece; 
        }
        else
        {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

void displayStats (PlayerInfo players[], int numGames, GameInfo gameInfo, string winner) 
{    
    int maxLength = 0;
    for (int i = 0; i < gameInfo.numPlayers; i++) 
    {
        int nameLength = players[i].fullname.length();
        if (nameLength > maxLength) 
        {
            maxLength = nameLength;
        }
    }

    string space(maxLength, ' ');

    cout << "Total game played = " <<numGames <<endl <<endl;

    cout << string(maxLength, ' ') << "  ------ ------ ------" <<endl;
    cout << string(maxLength, ' ') << " |  WIN | LOSS | DRAW |" <<endl;
    cout << string(maxLength, ' ') << "  ------ ------ ------" <<endl;

    for (int i = 0; i < gameInfo.numPlayers; i++) 
    {
        if (winner == players[i].fullname) 
        {
            players[i].wins++;
        }

        if (players[i].fullname.length() == maxLength) 
        {
            cout <<" " << players[i].fullname << "|    " << players[i].wins << " |    " 
                << players[i].losses << " |    " << players[i].draws << " | " << endl;
            cout << string(maxLength, ' ') << "  ------ ------ ------" <<endl;

        } 
        else 
        {
            cout << string(maxLength - players[i].fullname.length(), ' ') <<" " << players[i].fullname << "|    " 
                << players[i].wins << " |    " << players[i].losses << " |    " << players[i].draws << " | " << endl;
            cout << string(maxLength, ' ') << "  ------ ------ ------" <<endl;
        }

    }

}

char redo() 
{
    char answer;
    cout << "\nWould you like to play again? Y or N: ";
    cin >> answer;
    cin.ignore();
    cout << endl;

    while (answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n') 
    {
        cout << "Enter a Y/y or N/n ";
        cin >> answer;
        cin.ignore();
        cout <<endl;
    }
    return answer;
}
