#include <bits/stdc++.h>
using namespace std;

const int N = 3;

void printBoard(vector<vector<char>>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j];
            if (j < N - 1) cout << " | ";
        }
        cout << "\n";
        if (i < N - 1) cout << "---------\n";
    }
    cout << "\n";
}


char checkWin(vector<vector<char>>& board) {

    for (int i = 0; i < N; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }

    for (int j = 0; j < N; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return board[0][j];
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' '; 
}

bool isFull(vector<vector<char>>& board) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

int minimax(vector<vector<char>>& board, bool isMaximizing) {
    char winner = checkWin(board);
    if (winner == 'O') return 1;   
    if (winner == 'X') return -1;  
    if (isFull(board)) return 0;  

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, false);
                    board[i][j] = ' ';
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(board, true);
                    board[i][j] = ' ';
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

pair<int, int> bestMove(vector<vector<char>>& board) {
    int bestScore = -1000;
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(board, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}

int main() {
    vector<vector<char>> board(N, vector<char>(N, ' '));
    cout << "Welcome to Tic-Tac-Toe! You are X, AI is O.\n\n";
    printBoard(board);

    while (true) {
        int row, col;
        cout << "Enter your move (row and column 0-2): ";
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = 'X';

        if (checkWin(board) == 'X') {
            printBoard(board);
            cout << "You win!\n";
            break;
        }
        if (isFull(board)) {
            printBoard(board);
            cout << "It's a tie!\n";
            break;
        }

        pair<int, int> aiMove = bestMove(board);
        board[aiMove.first][aiMove.second] = 'O';
        cout << "AI plays:\n";
        printBoard(board);

        if (checkWin(board) == 'O') {
            cout << "AI wins!\n";
            break;
        }
        if (isFull(board)) {
            cout << "It's a tie!\n";
            break;
        }
    }

    return 0;
}