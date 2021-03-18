#include <iostream>
#include <time.h>
#include <vector>
//tic tac toe
using namespace std;

char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
char player = ' ';
char computer = ' ';

int currentPlayer = 0; //0 = player, 1=comp
int winner = -1;

bool isCompleted = false;

vector<int> each_digit(int x)
{
  vector<int> digit;
  while(x > 0) {
    digit.push_back(x % 10);
    x /= 10;
  }
  return digit;
}

void checkIsCompleted() {
  for(auto& x : board) {
    if(x == '-') {
      isCompleted = false;
      return;
    }
  }
  isCompleted = true;
}

void checkWinner() {
  //123,456,789,147,258,369,159,357
  //012,345,678,036,147,258,048,246
  vector<int> pattern = {123,456,789,147,258,369,159,357}; // to do minus by one
  for(auto& x : pattern) {
    vector<int> digits = each_digit(x);
    //minus by one
    for(auto& i : digits) {
      i--;
    }
    
    if(board[digits[0]] == board[digits[1]] && board[digits[0]] == board[digits[2]] && board[digits[0]] != '-') {
      winner = board[digits[0]] == player ? 0 : 1;
      isCompleted = true;
      return;
    }
  }
}

void printBoard() {
  printf("_______\n");
  printf("|%c|%c|%c|\n|%c|%c|%c|\n|%c|%c|%c|\n",board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);
  printf("¯¯¯¯¯¯¯\n");
}

void computerStep() {
  if(isCompleted)
    return;
  //pure random, not ai btw
  int pos = rand() % 9;
  do {
    pos = rand() % 9;
  } while(board[pos] != '-');
  board[pos] = computer;
}

bool takeAStep() {
  int n = 0;
  cout << "Take a step : " << endl;
  cin >> n;
  n--;
  if(board[n] != '-')
    return false;

  board[n] = player;
  return true;
}

void mainTicTacToe() {
  while(!isCompleted) {
    if(currentPlayer){
      cout << "Computer turn\n";
      computerStep();
    }
    else {
      bool isOK = takeAStep();
      if(!isOK) {
        cout << "Invalid Step\n";
        continue;
      }
    }
    currentPlayer = currentPlayer ? 0 : 1;
    printBoard();
    checkIsCompleted();
    checkWinner();
  }
  if(winner == -1)
    cout << "Draw !" << endl;
  else
  cout << "Winner : " << (winner == 0 ? "Player": "Computer") << endl;
}

int main() {
    srand(time(NULL));
    
    while(player == ' ') {
      cout << "Select :\n1. O\n2. X" << endl;
      int p = 0;
      cin >> p;
      switch(p) {
        case 1:
        player = 'O';
        break;
        case 2:
        player = 'X';
        break;
        default:
        cout << "unknown" << endl;
        break;
      }
    }

  computer = player == 'O' ? 'X' : 'O';
      currentPlayer = player == 'O' ? 1 : 0;
  cout << (currentPlayer == 1 ? "Computer" : "Player") << " goes first.\n";
    printBoard();
  mainTicTacToe();
    return 0;
}
