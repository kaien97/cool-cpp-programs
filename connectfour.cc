// Connect 4 is played on a 6 x 7 grid
// This program plays Connect 4 against a human player and attempts to win

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int check_winner(int board[][7]);
void drop_token(int col, int player, int (&board)[6][7]);

// returns the row where dropping a chip results in a win, or 0 if not possible
int check_win_possible(int player, int board[][7]) {
  int temp_board[6][7];
  for(int i = 1; i <= 7; i++) {
    copy(&board[0][0], &board[0][0]+6*7, &temp_board[0][0]);
    if (temp_board[0][i-1] == 0) {
      drop_token(i, player, temp_board);
      if (check_winner(temp_board) == player) {
        return i;
      }
    }
  }
  return 0;
}

int check_winner(int board[][7]) {
  for(int i = 0; i < 6; i++ ) {
    for(int j = 0; j < 7; j++ ) {
      if (board[i][j] == 0) continue;
      // Check horizontal win
      if ( j <= 3 ) {
        if (board[i][j] == board[i][j+1] &&
            board[i][j] == board[i][j+2] &&
            board[i][j] == board[i][j+3]) {
          return board[i][j];
        }
      }
      // Check vertical win
      if ( i <= 2 ) {
        if (board[i][j] == board[i+1][j] &&
            board[i][j] == board[i+2][j] &&
            board[i][j] == board[i+3][j]) {
          return board[i][j];
        }
      }
      // check forward diagonal
      if ( i <= 2 && j <= 3) {
        if (board[i][j] == board[i+1][j+1] &&
            board[i][j] == board[i+2][j+2] &&
            board[i][j] == board[i+3][j+3]) {
          return board[i][j];
        }
      }
      // check back diagonal
      if ( i >= 3 && j <= 3) {
        if (board[i][j] == board[i-1][j+1] &&
            board[i][j] == board[i-2][j+2] &&
            board[i][j] == board[i-3][j+3]) {
          return board[i][j];
        }
      }
    }
  }
  return 0;
}

void drop_token(int col, int player, int (&board)[6][7]) {
  for(int i = 5; i >= 0; i--) {
    if (board[i][col-1] == 0) {
      board[i][col-1] = player;
      return;
    }
  }
}

void next_turn(bool &player_turn) {
  if(player_turn){
    player_turn = false;
  } else {
    player_turn = true;
  }
}

void displayboard(int board[][7]) {
  char token;
  cout << "   1 2 3 4 5 6 7" << endl;
  for(int i=0; i < 6; i++) {
    cout << i+1 << " |";
    for(int j=0; j < 7; j++) {
      if(board[i][j] == 1) {
        token = 'X';
      } else if(board[i][j] == 2) {
        token = 'O';
      } else {
        token = ' ';
      }

      cout << token << "|";
    }
    cout << endl;
  }
}



int main() {
  bool player_turn, game_ended=false;
  int game_board[6][7]={0};
  char response;
  srandom(time(NULL));

  // Decides who starts first
  while (true) {
    cout << "Welcome to the Connect 4 Program! (Player tokens are 'O's while my tokens are 'X's)" << endl << "Would you like to start fist? (Y/N) ";
    cin >> response;
    if(response == 'Y') {
      player_turn = true;
      break;
    } else if(response == 'N') {
      player_turn = false;
      break;
    }
  }

  // Actual game
  int col, block, win, result, randomcol;
  bool legal_move;
  while (!game_ended) {
    cout << endl;
    displayboard(game_board);
    cout << endl;

    if(player_turn) {
       do {
        cout << "Enter which column to place your token: ";
        cin >> col;
      } while((col<1 || col >7) && game_board[0][col-1] == 0);
      drop_token(col, 2, game_board);
      next_turn(player_turn);
    } else {
      block = check_win_possible(2, game_board);
      win = check_win_possible(1, game_board);
      if (win != 0) {
        cout << "I drop my piece into column " << win << endl;
        drop_token(win, 1, game_board);
      } else if (block != 0) {
        cout << "I drop my piece into column " << block << endl;
        drop_token(block, 1, game_board);
      } else {
        randomcol = 1 + (random() % 7);
        cout << "I drop my piece into column " << randomcol << endl;
        drop_token(randomcol, 1, game_board);
      }
      next_turn(player_turn);
    }

    result = check_winner(game_board);
    if (result == 1) {
      cout << "I'm sorry, you've lost this round." << endl;
      displayboard(game_board);
      game_ended = true;
    } else if (result == 2) {
      cout << "Congratulations, you've won!" << endl;
      displayboard(game_board);
      game_ended = true;
    }
  }

  return 0;
}
