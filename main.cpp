#include <bits/stdc++.h>
using namespace std;
#include <windows.h>

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void print_welcome()
{
    std::cout << " W   W  EEEEE  L      CCCC  OOO   M      M  EEEEE\n";
    std::cout << " W   W  E      L     C     O   O  M M  M M  E    \n";
    std::cout << " W W W  EEEE   L     C     O   O  M  M   M  EEEE \n";
    std::cout << " WW WW  E      L     C     O   O  M      M  E    \n";
    std::cout << " W   W  EEEEE  LLLLL  CCCC  OOO   M      M  EEEEE\n";
}
map<char, string> pieceSymbols = {
    {'p', "♟"},
    {'r', "♜"},
    {'n', "♞"},
    {'b', "♝"},
    {'q', "♛"},
    {'k', "♚"},
    {'P', "♙"},
    {'R', "♖"},
    {'N', "♘"},
    {'B', "♗"},
    {'Q', "♕"},
    {'K', "♔"},
    {'0', "\u00B7"}};
vector<pair<char, string>> conversion = {
    {'p', "Pawn"},
    {'r', "Rook"},
    {'n', "Knight"},
    {'b', "Bishop"},
    {'q', "Queen"},
    {'k', "King"},
    {'P', "Pawn"},
    {'R', "Rook"},
    {'K', "Knight"},
    {'B', "Bishop"},
    {'Q', "Queen"},
    {'K', "King"}};
bool check_valid_piece_type(char ch)
{
    for (auto itr : conversion)
    {
        if (ch == itr.first || ch == toupper(itr.first))
        {
            return true;
        }
    }
    return false;
}
class Piece
{
public:
    bool Is_white(char ch)
    {
        return isupper(ch);
    }
    bool bound_validation(int cur_x, int cur_y, int new_x, int new_y)
    {
        if (new_x == cur_x && new_y == cur_y)
            return false;
        if (!(new_x >= 0 && new_y >= 0 && new_x < 8 && new_y < 8 && cur_x >= 0 && cur_y >= 0 && cur_x < 8 && cur_y < 8))
            return false;
        return true;
    }
    pair<int, int> find_cordinate(vector<vector<char>> &board, char ch)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] == ch)
                    return {i, j};
            }
        }
        return {-1, -1};
    }
};
class Pawn : public Piece
{
public:
    bool isvalid(vector<vector<char>> &board, int cur_x, int cur_y, int new_x, int new_y)
    {
        if (!bound_validation(cur_x, cur_y, new_x, new_y))
            return false;

        char type = board[cur_x][cur_y];
        if (Is_white(type))
        {

            if (new_x == cur_x - 1 && new_y == cur_y && board[new_x][new_y] == '0')
            {
                return true;
            }

            if (new_x == cur_x - 2 && new_y == cur_y && cur_x == 6 &&
                board[cur_x - 1][cur_y] == '0' && board[new_x][new_y] == '0')
            {
                return true;
            }

            if (new_x == cur_x - 1 && abs(new_y - cur_y) == 1 && islower(board[new_x][new_y]))
            {
                return true;
            }
        }
        else
        {

            if (new_x == cur_x + 1 && new_y == cur_y && board[new_x][new_y] == '0')
            {
                return true;
            }

            if (new_x == cur_x + 2 && new_y == cur_y && cur_x == 1 &&
                board[cur_x + 1][cur_y] == '0' && board[new_x][new_y] == '0')
            {
                return true;
            }

            if (new_x == cur_x + 1 && abs(new_y - cur_y) == 1 && isupper(board[new_x][new_y]))
            {
                return true;
            }
        }
        return false;
    }

    bool can_promote(char type, int x)
    {
        return (Is_white(type) && x == 0) || (!Is_white(type) && x == 7);
    }

    void promote(vector<vector<char>> &board, int x, int y)
    {
        char type = board[x][y];
        if (can_promote(type, x))
        {
            cout << "You can promote your pawn!\n";
            cout << "Enter the first letter of the piece you want to promote to (e.g., R for Rook):\n";
            while (true)
            {
                char temp;
                cin >> temp;
                if (check_valid_piece_type(temp))
                {
                    board[x][y] = Is_white(type) ? toupper(temp) : tolower(temp);
                    break;
                }
                else
                {
                    cout << "Invalid input. Try again.\n";
                }
            }
        }
    }

    bool move(vector<vector<char>> &board, int cur_x, int cur_y, int new_x, int new_y)
    {
        cout << "Pawn is moving...\n";
        char type = board[cur_x][cur_y];
        if (isvalid(board, cur_x, cur_y, new_x, new_y))
        {
            board[new_x][new_y] = type;
            board[cur_x][cur_y] = '0';
            if (can_promote(type, new_x))
            {
                promote(board, new_x, new_y);
            }
            return true;
        }
        return false;
    }

    vector<pair<int, int>> get_moves(vector<vector<char>> &board, int cur_x, int cur_y)
    {
        char type = board[cur_x][cur_y];
        int direction = Is_white(type) ? -1 : 1;
        vector<pair<int, int>> moves;

        if (cur_x + direction >= 0 && cur_x + direction < 8 && board[cur_x + direction][cur_y] == '0')
        {
            moves.push_back({cur_x + direction, cur_y});
        }

        if ((Is_white(type) && cur_x == 6) || (!Is_white(type) && cur_x == 1))
        {
            if (board[cur_x + direction][cur_y] == '0' && board[cur_x + 2 * direction][cur_y] == '0')
            {
                moves.push_back({cur_x + 2 * direction, cur_y});
            }
        }

        if (cur_y > 0 && cur_x + direction >= 0 && cur_x + direction < 8)
        {
            if ((Is_white(type) && islower(board[cur_x + direction][cur_y - 1])) ||
                (!Is_white(type) && isupper(board[cur_x + direction][cur_y - 1])))
            {
                moves.push_back({cur_x + direction, cur_y - 1});
            }
        }
        if (cur_y < 7 && cur_x + direction >= 0 && cur_x + direction < 8)
        {
            if ((Is_white(type) && islower(board[cur_x + direction][cur_y + 1])) ||
                (!Is_white(type) && isupper(board[cur_x + direction][cur_y + 1])))
            {
                moves.push_back({cur_x + direction, cur_y + 1});
            }
        }

        return moves;
    }
};
class Rook : public Piece
{
public:
    bool isvalid(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {
        if (!bound_validation(cur_x, cur_y, new_x, new_y))
            return false;

        if (cur_x != new_x && cur_y != new_y)
            return false;
        if (cur_x == new_x)
        {
            int start = min(cur_y, new_y) + 1;
            int end = max(cur_y, new_y);
            for (int i = start; i < end; ++i)
            {
                if (board[cur_x][i] != '0')
                    return false;
            }
        }
        else if (cur_y == new_y)
        {
            int start = min(cur_x, new_x) + 1;
            int end = max(cur_x, new_x);
            for (int i = start; i < end; ++i)
            {
                if (board[i][cur_y] != '0')
                    return false;
            }
        }
        if (board[new_x][new_y] == '0')
            return true;
        if (islower(board[cur_x][cur_y]) == islower(board[new_x][new_y]))
            return false;

        return true;
    }

    bool move(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {
        char type = board[cur_x][cur_y];
        if (isvalid(board, new_x, new_y, cur_x, cur_y))
        {
            board[new_x][new_y] = type;
            board[cur_x][cur_y] = '0';
            return true;
        }
        return false;
    }

    vector<pair<int, int>> get_moves(vector<vector<char>> &board, int cur_x, int cur_y)
    {
        vector<pair<int, int>> moves;
        char type = board[cur_x][cur_y];

        for (int i = cur_y + 1; i < 8; ++i)
        {
            if (board[cur_x][i] == '0')
                moves.push_back({cur_x, i});
            else if (islower(type) != islower(board[cur_x][i]))
            {
                moves.push_back({cur_x, i});
                break;
            }
            else
                break;
        }

        for (int i = cur_y - 1; i >= 0; --i)
        {
            if (board[cur_x][i] == '0')
                moves.push_back({cur_x, i});
            else if (islower(type) != islower(board[cur_x][i]))
            {
                moves.push_back({cur_x, i});
                break;
            }
            else
                break;
        }

        for (int i = cur_x + 1; i < 8; ++i)
        {
            if (board[i][cur_y] == '0')
                moves.push_back({i, cur_y});
            else if (islower(type) != islower(board[i][cur_y]))
            {
                moves.push_back({i, cur_y});
                break;
            }
            else
                break;
        }

        for (int i = cur_x - 1; i >= 0; --i)
        {
            if (board[i][cur_y] == '0')
                moves.push_back({i, cur_y});
            else if (islower(type) != islower(board[i][cur_y]))
            {
                moves.push_back({i, cur_y});
                break;
            }
            else
                break;
        }

        return moves;
    }
};
class Knight : public Piece
{
public:
    Knight() {}

    bool isvalid(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {

        if (!bound_validation(cur_x, cur_y, new_x, new_y))
            return false;

        if (!((abs(new_x - cur_x) == 2 && abs(new_y - cur_y) == 1) ||
              (abs(new_x - cur_x) == 1 && abs(new_y - cur_y) == 2)))
            return false;

        return board[new_x][new_y] == '0' ||
               islower(board[new_x][new_y]) != islower(board[cur_x][cur_y]);
    }

    bool move(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {
        char type = board[cur_x][cur_y];
        if (isvalid(board, new_x, new_y, cur_x, cur_y))
        {
            board[new_x][new_y] = type;
            board[cur_x][cur_y] = '0';
            return true;
        }
        return false;
    }

    vector<pair<int, int>> get_moves(vector<vector<char>> &board, int cur_x, int cur_y)
    {
        vector<pair<int, int>> moves;
        vector<pair<int, int>> offsets = {
            {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

        for (auto offset : offsets)
        {
            int new_x = cur_x + offset.first;
            int new_y = cur_y + offset.second;

            if (isvalid(board, new_x, new_y, cur_x, cur_y))
            {
                moves.push_back({new_x, new_y});
            }
        }
        return moves;
    }
};
class Bishop : public Piece
{
public:
    bool isvalid(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {
        if (!bound_validation(cur_x, cur_y, new_x, new_y))
            return false;

        if (abs(cur_x - new_x) != abs(cur_y - new_y))
            return false;

        int dx = (new_x > cur_x) ? 1 : -1;
        int dy = (new_y > cur_y) ? 1 : -1;

        for (int i = 1; i < abs(new_x - cur_x); ++i)
        {
            if (board[cur_x + i * dx][cur_y + i * dy] != '0')
                return false;
        }

        return board[new_x][new_y] == '0' ||
               islower(board[new_x][new_y]) != islower(board[cur_x][cur_y]);
    }

    bool move(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {
        char type = board[cur_x][cur_y];
        if (isvalid(board, new_x, new_y, cur_x, cur_y))
        {
            board[new_x][new_y] = type;
            board[cur_x][cur_y] = '0';
            return true;
        }
        return false;
    }

    vector<pair<int, int>> get_moves(vector<vector<char>> &board, int cur_x, int cur_y)
    {
        vector<pair<int, int>> moves;
        char type = board[cur_x][cur_y];

        int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        for (auto direction : directions)
        {
            for (int i = 1; i < 8; ++i)
            {
                int new_x = cur_x + i * direction[0];
                int new_y = cur_y + i * direction[1];

                if (!bound_validation(cur_x, cur_y, new_x, new_y))
                    break;

                if (board[new_x][new_y] == '0')
                    moves.push_back({new_x, new_y});
                else if (islower(board[new_x][new_y]) != islower(type))
                {
                    moves.push_back({new_x, new_y});
                    break;
                }
                else
                {
                    break;
                }
            }
        }

        return moves;
    }
};
class Queen : public Bishop, public Rook
{
public:
    bool isvalid(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {
        if (!Bishop::bound_validation(cur_x, cur_y, new_x, new_y))
            return false;

        if (new_x == cur_x || new_y == cur_y)
            return Rook::isvalid(board, new_x, new_y, cur_x, cur_y);
        else if (abs(cur_x - new_x) == abs(cur_y - new_y))
            return Bishop::isvalid(board, new_x, new_y, cur_x, cur_y);

        return false;
    }

    bool move(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y)
    {
        char type = board[cur_x][cur_y];
        if (isvalid(board, new_x, new_y, cur_x, cur_y))
        {
            board[new_x][new_y] = type;
            board[cur_x][cur_y] = '0';
            return true;
        }
        return false;
    }

    vector<pair<int, int>> get_moves(vector<vector<char>> &board, int cur_x, int cur_y)
    {
        vector<pair<int, int>> moves;

        vector<pair<int, int>> rook_moves = Rook::get_moves(board, cur_x, cur_y);
        vector<pair<int, int>> bishop_moves = Bishop::get_moves(board, cur_x, cur_y);

        moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());
        moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());

        return moves;
    }
};
class King : public Piece
{
public:
    bool Is_In_Check(vector<vector<char>> &board, int cur_x, int cur_y)
    {
        vector<pair<int, int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        auto check_line_of_sight = [&](int x, int y, int dx, int dy, char threat1, char threat2)
        {
            while (true)
            {
                x += dx;
                y += dy;
                if (!bound_validation(x, y, 0, 0))
                    break;
                if (board[x][y] != '0')
                {
                    char piece = board[x][y];
                    if (islower(board[cur_x][cur_y]) != islower(piece) && (toupper(piece) == threat1 || toupper(piece) == threat2))
                        return true;
                    break;
                }
            }
            return false;
        };

        for (const auto &dir : directions)
        {
            if (check_line_of_sight(cur_x, cur_y, dir.first, dir.second, 'R', 'Q') ||
                check_line_of_sight(cur_x, cur_y, dir.first, dir.second, 'B', 'Q'))
                return true;
        }

        vector<pair<int, int>> knight_moves = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        for (const auto &move : knight_moves)
        {
            int new_x = cur_x + move.first, new_y = cur_y + move.second;
            if (bound_validation(new_x, new_y, 0, 0) && board[new_x][new_y] == ((islower(board[cur_x][cur_y]) ? 'N' : 'n')))
                return true;
        }
        int direction = islower(board[cur_x][cur_y]) ? 1 : -1;
        if ((bound_validation(cur_x + direction, cur_y + 1, 0, 0) &&
             board[cur_x + direction][cur_y + 1] == (islower(board[cur_x][cur_y]) ? 'P' : 'p')) ||
            (bound_validation(cur_x + direction, cur_y - 1, 0, 0) &&
             board[cur_x + direction][cur_y - 1] == (islower(board[cur_x][cur_y]) ? 'P' : 'p')))
            return true;

        vector<pair<int, int>> king_moves = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
        for (const auto &move : king_moves)
        {
            int new_x = cur_x + move.first, new_y = cur_y + move.second;
            if (bound_validation(new_x, new_y, 0, 0) &&
                board[new_x][new_y] == (islower(board[cur_x][cur_y]) ? 'K' : 'k'))
                return true;
        }

        return false;
    }

    bool isvalid(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y, bool Can_castel)
    {
        if (!bound_validation(cur_x, cur_y, new_x, new_y))
            return false;
        if (islower(board[new_x][new_y]) == islower(board[cur_x][cur_y]) && board[new_x][new_y] != '0')
            return false;
        if (abs(new_y - cur_y) == 2 && cur_x == new_x && !Is_In_Check(board, cur_x, cur_y))
        {
            return validate_castling(board, cur_x, cur_y, new_y, Can_castel);
        }
        char ch = board[new_x][new_y];
        board[new_x][new_y] = board[cur_x][cur_y];
        board[cur_x][cur_y] = '0';
        if (abs(new_x - cur_x) <= 1 && abs(new_y - cur_y) <= 1 && !Is_In_Check(board, new_x, new_y))
        {
            board[cur_x][cur_y] = board[new_x][new_y];
            board[new_x][new_y] = ch;
            return true;
        }
        board[cur_x][cur_y] = board[new_x][new_y];
        board[new_x][new_y] = ch;
        return false;
    }

    bool validate_castling(vector<vector<char>> &board, int cur_x, int cur_y, int new_y, bool Can_castel)
    {
        if (!Can_castel)
            return false;
        int rook_y = (new_y > cur_y) ? 7 : 0;
        for (int i = min(cur_y, rook_y) + 1; i < max(cur_y, rook_y); ++i)
        {
            if (board[cur_x][i] != '0')
                return false;
        }
        return true;
    }

    bool move(vector<vector<char>> &board, int new_x, int new_y, int cur_x, int cur_y, bool Can_Castel)
    {
        if (!isvalid(board, new_x, new_y, cur_x, cur_y, Can_Castel))
            return false;
        char type = board[cur_x][cur_y];
        board[new_x][new_y] = type;
        board[cur_x][cur_y] = '0';
        if (abs(new_y - cur_y) == 2)
        {
            int rook_y = (new_y > cur_y) ? 7 : 0;
            int rook_new_y = (new_y > cur_y) ? new_y - 1 : new_y + 1;
            board[cur_x][rook_new_y] = board[cur_x][rook_y];
            board[cur_x][rook_y] = '0';
        }

        return true;
    }

    vector<pair<int, int>> get_moves(vector<vector<char>> &board, int cur_x, int cur_y, bool Can_castel)
    {
        vector<pair<int, int>> moves;

        vector<pair<int, int>> king_moves = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
        for (const auto &move : king_moves)
        {
            int new_x = cur_x + move.first, new_y = cur_y + move.second;
            if (isvalid(board, new_x, new_y, cur_x, cur_y, Can_castel))
                moves.push_back({new_x, new_y});
        }

        if (validate_castling(board, cur_x, cur_y, cur_y + 2, Can_castel))
            moves.push_back({cur_x, cur_y + 2});
        if (validate_castling(board, cur_x, cur_y, cur_y - 2, Can_castel))
            moves.push_back({cur_x, cur_y - 2});

        return moves;
    }
};
class Scoreboard
{
    map<string, int> player1_freq;
    map<string, int> player2_freq;

public:
    string player1;
    string player2;
    pair<int, int> cor_1 = {0, 4};
    pair<int, int> cor_2 = {7, 4};
    Scoreboard()
    {
        print_welcome();
        cout << endl;
        cout << "PLEASE ENTER YOUR NAME(player1) \n";
        cin >> player1;
        cout << "PLEASE ENTER YOUR NAME(player2) \n";
        cin >> player2;
        clear_screen();
        for (auto itr : pieceSymbols)
        {
            if (itr.first > 'a')
                player1_freq[itr.second] = 0;
            else if (itr.first != '0')
                player2_freq[itr.second] = 0;
        }
    }

public:
    void set_freq_player1(char ch)
    {
        player1_freq[pieceSymbols[ch]]++;
    }
    void set_freq_player2(char ch)
    {
        player2_freq[pieceSymbols[ch]]++;
    }
    void display_freq_player1()
    {
        cout << "the score of " << player1 << " is\n";
        cout << "========== SCOREBOARD ========== \n";
        for (auto itr : player1_freq)
        {
            cout << itr.first << " x " << itr.second << "  ";
        }
        cout << endl;
    }
    void display_freq_player2()
    {
        cout << "the score of " << player2 << " is\n";
        cout << "========== SCOREBOARD ========== \n";
        for (auto itr : player2_freq)
        {
            cout << itr.first << " x " << itr.second << "  ";
        }
        cout << endl;
    }
    void overall_scoreboard()
    {
        cout << "========================== SCOREBOARD =========================== \n"
             << player1 << " : ";
        for (auto itr : player1_freq)
        {
            cout << itr.first << " x " << itr.second << "  ";
        }
        cout << endl;
        cout << player2 << " : ";
        for (auto itr : player2_freq)
        {
            cout << itr.first << " x " << itr.second << "  ";
        }
        cout << endl;
        cout << "====================================================================\n";
    }
    bool isDrawInsufficientMaterial()
    {
        // Initial counts for each piece
        int totalPawns = 8, totalRooks = 2, totalKnights = 2, totalBishops = 2, totalQueens = 1;

        // Calculate remaining pieces for each player
        int p1Pawns = totalPawns - player1_freq[(pieceSymbols['P'])];
        int p2Pawns = totalPawns - player2_freq[(pieceSymbols['p'])];
        int p1Rooks = totalRooks - player1_freq[(pieceSymbols['R'])];
        int p2Rooks = totalRooks - player2_freq[(pieceSymbols['r'])];
        int p1Knights = totalKnights - player1_freq[(pieceSymbols['N'])];
        int p2Knights = totalKnights - player2_freq[(pieceSymbols['n'])];
        int p1Bishops = totalBishops - player1_freq[(pieceSymbols['B'])];
        int p2Bishops = totalBishops - player2_freq[(pieceSymbols['b'])];
        int p1Queens = totalQueens - player1_freq[(pieceSymbols['Q'])];
        int p2Queens = totalQueens - player2_freq[(pieceSymbols['q'])];

        if (p1Pawns > 0 || p2Pawns > 0 || p1Rooks > 0 || p2Rooks > 0 || p1Queens > 0 || p2Queens > 0)
        {
            return false;
        }

        int p1MinorPieces = p1Knights + p1Bishops;
        int p2MinorPieces = p2Knights + p2Bishops;

        if (p1MinorPieces == 0 && p2MinorPieces == 0)
            return true;

        if ((p1MinorPieces == 1 && p1Knights == 1 && p2MinorPieces == 0) ||
            (p2MinorPieces == 1 && p2Knights == 1 && p1MinorPieces == 0))
        {
            return true;
        }

        if ((p1MinorPieces == 1 && p1Bishops == 1 && p2MinorPieces == 0) ||
            (p2MinorPieces == 1 && p2Bishops == 1 && p1MinorPieces == 0))
        {
            return true;
        }

        if (p1MinorPieces == 1 && p2MinorPieces == 1 && p1Bishops == 1 && p2Bishops == 1)
        {
            return true;
        }

        return false;
    }
};
class chess_board
{
public:
    vector<vector<char>> board;
    Pawn my_pawn = Pawn();
    Rook my_rook = Rook();
    Bishop my_bishop = Bishop();
    Queen my_queen = Queen();
    King my_king = King();
    Knight my_knight = Knight();
    chess_board()
    {
        board.resize(8, vector<char>(8, '0'));
        board[0] = {'r', 'b', 'n', 'q', 'k', 'b', 'n', 'r'};
        board[1] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};
        board[6] = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};
        board[7] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    }
    void display_board(vector<vector<char>> &boards)
    {
        for (auto itr : boards)
        {
            for (auto it : itr)
            {
                cout << " " << pieceSymbols[it] << " ";
            }
            cout << endl;
        }
    }
    bool checkmate(vector<vector<char>> &board, bool white, int x_cor, int y_cor, bool Can_Castel)
    {
        char piece = board[x_cor][y_cor];
        vector<pair<int, int>> moves = my_king.get_moves(board, x_cor, y_cor, Can_Castel);

        for (auto itr : moves)
        {
            int new_x = itr.first;
            int new_y = itr.second;
            char destination_piece = board[new_x][new_y];

            board[new_x][new_y] = piece;
            board[x_cor][y_cor] = '0';

            if (!my_king.Is_In_Check(board, new_x, new_y))
            {

                board[x_cor][y_cor] = piece;
                board[new_x][new_y] = destination_piece;
                return false;
            }

            board[x_cor][y_cor] = piece;
            board[new_x][new_y] = destination_piece;
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (white == (islower(board[i][j]) > 0))
                {
                    vector<pair<int, int>> moves;
                    char piece = board[i][j];
                    int x = i, y = j;

                    switch (tolower(piece))
                    {
                    case 'r':
                        moves = my_rook.get_moves(board, x, y);
                        break;
                    case 'b':
                        moves = my_bishop.get_moves(board, x, y);
                        break;
                    case 'n':
                        moves = my_knight.get_moves(board, x, y);
                        break;
                    case 'q':
                        moves = my_queen.get_moves(board, x, y);
                        break;
                    case 'p':
                        moves = my_pawn.get_moves(board, x, y);
                        break;
                    default:
                        continue;
                    }

                    for (auto itr : moves)
                    {
                        int new_x = itr.first;
                        int new_y = itr.second;
                        char destination_piece = board[new_x][new_y];

                        board[new_x][new_y] = piece;
                        board[x][y] = '0';

                        if (!my_king.Is_In_Check(board, x_cor, y_cor))
                        {
                            board[x][y] = piece;
                            board[new_x][new_y] = destination_piece;
                            return false;
                        }
                        board[x][y] = piece;
                        board[new_x][new_y] = destination_piece;
                    }
                }
            }
        }

        return true;
    }
};
pair<int, int> convertToCoordinate(const string &command)
{

    if (command.size() != 2)
        return {-1, -1};

    char letter = command[0];
    int number = command[1] - '1';
    int xCoordinate = letter - 'a';
    if (number >= 0 && number < 8 && xCoordinate >= 0 && xCoordinate < 8)
    {
        return {number, xCoordinate};
    }
    return {-1, -1};
}
vector<pair<int, int>> input_cordinates(vector<vector<char>> &board, bool white)
{
    vector<pair<int, int>> coordinates(2);
    int cur_x, cur_y;
    while (true)
    {
        cout << "Enter the coordinate of the piece you want to move (e.g., 'e2'): ";
        string start_input;
        cin >> start_input;
        auto start_cordinate = convertToCoordinate(start_input);
        if (start_cordinate.first != -1 && start_cordinate.second != -1)
        {
            if (board[start_cordinate.first][start_cordinate.second] == '0')
                cout << "The selected cell is empty.\n";
            else if ((islower(board[start_cordinate.first][start_cordinate.second]) > 0) != white)
                cout << "You selected an enemy piece.\n";
            else
            {
                coordinates[0] = start_cordinate;
                cur_x = start_cordinate.first;
                cur_y = start_cordinate.second;
                break;
            }
        }
        cout << "Invalid input! Try again.\n";
    }
    while (true)
    {
        cout << "Enter the destination coordinate where you want to move your " << pieceSymbols[board[cur_x][cur_y]] << " (e.g., 'e4'): ";
        string end_input;
        cin >> end_input;
        auto end_cordinate = convertToCoordinate(end_input);

        if (end_cordinate.first != -1 && end_cordinate.second != -1)
        {
            if ((islower(board[end_cordinate.first][end_cordinate.second]) == islower(board[cur_x][cur_y])) && board[end_cordinate.first][end_cordinate.second] != '0')
            {
                cout << "The destination is occupied by your own piece.\n";
            }
            else
            {
                coordinates[1] = end_cordinate;
                break;
            }
        }
        cout << "Invalid input! Try again.\n";
    }
    return coordinates;
}

void play()
{

    auto scoreboard = new Scoreboard();
    auto my_board = new chess_board();
    auto my_pawn = new Pawn();
    auto my_rook = new Rook();
    auto my_bishop = new Bishop();
    auto my_queen = new Queen();
    auto my_king = new King();
    auto my_knight = new Knight();
    bool white = true;
    auto board = my_board->board;
    int check_pawn_movement = 0;
    bool game_is_on = true;
    bool player1_can_castel = true;
    bool player2_can_castel = true;
    clear_screen();
    while (game_is_on)
    {
        bool check_on_white = my_king->Is_In_Check(board, scoreboard->cor_1.first, scoreboard->cor_1.second);
        bool check_on_black = my_king->Is_In_Check(board, scoreboard->cor_2.first, scoreboard->cor_2.second);
        bool checkmate_on_white = my_board->checkmate(board, true, scoreboard->cor_1.first, scoreboard->cor_1.second, white ? player1_can_castel : player2_can_castel);
        bool checkmate_on_black = my_board->checkmate(board, false, scoreboard->cor_2.first, scoreboard->cor_2.second, white ? player1_can_castel : player2_can_castel);
        if (white)
        {
            if (check_on_white)
            {
                cout << "Invalid move, your king is in check!\n";
            }
            else if (check_on_black)
            {
                if (checkmate_on_black)
                {
                    game_is_on = false;
                    cout << "CHECKMATE ON BLACK AND THE WINNER IS " << scoreboard->player1 << endl;
                    continue;
                }
                cout << scoreboard->player2 << ", your king is in check.\n";
            }
        }
        else
        {
            if (check_on_black)
            {
                cout << "Invalid move, your king is in check!\n";
            }
            else if (check_on_white)
            {
                if (checkmate_on_white)
                {
                    game_is_on = false;
                    cout << "CHECKMATE ON BLACK AND THE WINNER IS " << scoreboard->player2 << endl;
                    continue;
                }
                cout << scoreboard->player1 << ", your king is in check.\n";
            }
        }
        check_pawn_movement++;
        if (white)
            cout << scoreboard->player1 << ", it's your turn.\n";
        else
            cout << scoreboard->player2 << ", it's your turn.\n";

        my_board->display_board(board);

        cout << "Available commands:\n"
             << "1) View overall scoreboard -> 'Score'\n"
             << "2) View your scoreboard -> 'MyScore'\n"
             << "3) Continue game -> 'Continue or yes'\n";

        string command;
        while (true)
        {
            cin >> command;
            if (command == "Score")
                scoreboard->overall_scoreboard();
            else if (command == "MyScore")
                white ? scoreboard->display_freq_player1() : scoreboard->display_freq_player2();
            else if (command == "Continue" || command == "yes")
                break;
            else
                cout << "Invalid input! Try again.\n";

            cout << "Enter command again: ";
        }

        cout << "Do you wish to know the possible moves of any of your pieces?\n"
             << "If yes, enter 'yes'; otherwise, enter 'no': ";
        while (true)
        {
            string move_check;
            cin >> move_check;
            if (move_check == "no")
                break;
            cout << "Enter the location of the piece whose moves you want to know in chess notation (e.g., e2): ";
            string location;
            cin >> location;

            auto coordinate = convertToCoordinate(location);
            int x = coordinate.first, y = coordinate.second;

            char piece = board[x][y];
            if ((islower(piece) != 0) != white)
            {
                cout << "You selected an invalid piece. Try again.\n";
                continue;
            }

            vector<pair<int, int>> moves;
            switch (tolower(piece))
            {
            case 'r':
                moves = my_rook->get_moves(board, x, y);
                break;
            case 'b':
                moves = my_bishop->get_moves(board, x, y);
                break;
            case 'n':
                moves = my_knight->get_moves(board, x, y);
                break;
            case 'q':
                moves = my_queen->get_moves(board, x, y);
                break;
            case 'p':
                moves = my_pawn->get_moves(board, x, y);
                break;
            case 'k':
                moves = my_king->get_moves(board, x, y, white ? player1_can_castel : player2_can_castel);
                break;
            default:
                cout << "Unknown piece type!\n";
                continue;
            }

            if (moves.empty())
            {
                cout << "No valid moves for the selected piece.\n";
            }
            else
            {
                cout << "Possible moves: ";
                for (auto move : moves)
                {
                    char ch = 'a';
                    ch = ch + move.second;
                    cout << ch << move.first + 1 << " ";
                }
                cout << endl;
            }
            cout << "if you don't want to know moves of your piece then enter no \nor if you want to play your next move then enter anything else" << endl;
        }

        pair<int, int> start_cor, end_cor;
        auto getcordinate = input_cordinates(board, white);
        start_cor = getcordinate[0];
        end_cor = getcordinate[1];
        int cur_x = start_cor.first, cur_y = start_cor.second;
        int new_x = end_cor.first, new_y = end_cor.second;
        char piece = board[cur_x][cur_y];
        char ending_piece = board[new_x][new_y];
        bool move_is_done = false;
        auto temp = board;

        clear_screen();

        switch (tolower(piece))
        {
        case 'r':
            move_is_done = my_rook->move(board, new_x, new_y, cur_x, cur_y);
            if (move_is_done)
                white ? player1_can_castel = false : player2_can_castel = false;
            break;
        case 'b':
            move_is_done = my_bishop->move(board, new_x, new_y, cur_x, cur_y);
            break;
        case 'n':
            move_is_done = my_knight->move(board, new_x, new_y, cur_x, cur_y);
            break;
        case 'q':
            move_is_done = my_queen->move(board, new_x, new_y, cur_x, cur_y);
            break;
        case 'p':
            move_is_done = my_pawn->move(board, cur_x, cur_y, new_x, new_y);
            if (move_is_done)
            {
                check_pawn_movement = 0;
            }
            break;
        case 'k':
            move_is_done = my_king->move(board, new_x, new_y, cur_x, cur_y, white ? player1_can_castel : player2_can_castel);
            if (move_is_done)
            {
                white ? player1_can_castel = false : player2_can_castel = false;
                white ? scoreboard->cor_1 = {new_x, new_y} : scoreboard->cor_2 = {new_x, new_y};
            }
            break;
        default:
            cout << "Unknown piece type!\n";
        }
        check_on_white = my_king->Is_In_Check(board, scoreboard->cor_1.first, scoreboard->cor_1.second);
        check_on_black = my_king->Is_In_Check(board, scoreboard->cor_2.first, scoreboard->cor_2.second);
        checkmate_on_white = my_board->checkmate(board, true, scoreboard->cor_1.first, scoreboard->cor_1.second, white ? player1_can_castel : player2_can_castel);
        checkmate_on_black = my_board->checkmate(board, false, scoreboard->cor_2.first, scoreboard->cor_2.second, white ? player1_can_castel : player2_can_castel);

        // draw Conditions

        // Fifty move rule
        if (check_pawn_movement >= 50)
        {
            game_is_on = false;
            cout << "FIFTY MOVE RULE , dRAW " << endl;
            continue;
        }
        // Stalemate draw
        if (white && checkmate_on_white && !check_on_white)
        {
            game_is_on = false;
            cout << "As the white has no legal moves , the match is a draw" << endl;
            continue;
        }
        if (!white && checkmate_on_black && !check_on_black)
        {
            game_is_on = false;
            cout << "As the black has no legal moves , the match is a draw" << endl;
            continue;
        }
        // Insufficiant matirial
        if (scoreboard->isDrawInsufficientMaterial())
        {
            game_is_on = false;
            cout << "Draw , Due to Insufficient Material " << endl;
            continue;
        }
        // checking if the move is done or not
        if (!move_is_done)
        {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        // checking for checkmate
        if (white)
        {
            if (check_on_white)
            {
                move_is_done = false;
                board = temp;
                cout << "Invalid move, your king is in check!\n";
            }
            else if (check_on_black)
            {
                if (checkmate_on_black)
                {
                    game_is_on = false;
                    cout << "CHECKMATE ON BLACK AND THE WINNER IS " << scoreboard->player1 << endl;
                    continue;
                }
                cout << scoreboard->player2 << ", your king is in check.\n";
            }
        }
        else
        {
            if (check_on_black)
            {
                move_is_done = false;
                board = temp;
                cout << "Invalid move, your king is in check!\n";
            }
            else if (check_on_white)
            {
                if (checkmate_on_white)
                {
                    game_is_on = false;
                    cout << "CHECKMATE ON BLACK AND THE WINNER IS " << scoreboard->player2 << endl;
                    continue;
                }
                cout << scoreboard->player1 << ", your king is in check.\n";
            }
        }

        // updating the score of the players
        if (move_is_done)
        {
            white = !white;
            if (ending_piece != '0')
            {
                if (white)
                    scoreboard->set_freq_player1(ending_piece);
                else
                    scoreboard->set_freq_player2(ending_piece);
            }
        }
    }
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    play();
}
