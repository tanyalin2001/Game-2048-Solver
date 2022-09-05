#include "ArgumentManager.h"
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct struct1 {
  string path;
  vector<vector<int>> m;
};
class Graph {
private:
  int sum = 0;

public:
  int row;
  int col;
  int value;
  vector<vector<int>> b;
  queue<vector<vector<int>>> qmatrix;
  queue<string> qpath;

  int count() {
    int sum = 0;
    for (int i = 0; i < b.size(); i++) {
      for (int j = 0; j < b.size(); j++) {
        sum += b[i][j];
      }
    }
    return sum;
  }
  bool isSolved(vector<vector<int>> board) {
    stack<int> count;
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board.size(); j++) {
        if (board[i][j] != 0 && board[i][j] != 2048)
          count.push(1);
      }
    }
    if (count.size() != 1)
      return false;
    else
      return true;
  }

  void buildboard(string infile) {
    // ifstream input("input36.txt");
    ifstream input(infile);
    input >> row;
    col = row;
    for (int i = 0; i < row; i++) {
      vector<int> temp;
      for (int j = 0; j < col; j++) {
        input >> value;
        temp.push_back(value);
      }
      b.push_back(temp);
    }
  }
  vector<vector<int>> movement(vector<vector<int>> board, int command) {
    switch (command) {
    case 1:
      for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
          for (int k = j + 1; k < board.size(); k++) {
            if (board[j][i] == 0) {
              if (board[k][i] == 2048)
                break;
              else if (board[k][i] != 0 && board[k][i] != 2048) {
                board[j][i] = board[k][i];
                board[k][i] = 0;
                break;
              }
            }
          }
        }
      }
      return board;
      break;

    case 3:
      for (int i = 0; i < board.size(); i++) {
        for (int j = board.size() - 1; j >= 0; j--) {
          for (int k = j - 1; k >= 0; k--) {
            if (board[j][i] == 0) {
              if (board[k][i] == 2048)
                break;
              else if (board[k][i] != 0 && board[k][i] != 2048) {
                board[j][i] = board[k][i];
                board[k][i] = 0;
                break;
              }
            }
          }
        }
      }
      return board;
      break;

    case 4:
      for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
          for (int k = j + 1; k < board.size(); k++) {
            if (board[i][j] == 0) {
              if (board[i][k] == 2048)
                break;
              else if (board[i][k] != 0 && board[i][k] != 2048) {
                board[i][j] = board[i][k];
                board[i][k] = 0;
                break;
              }
            }
          }
        }
      }
      return board;
      break;

    case 2:
      for (int i = 0; i < board.size(); i++) {
        for (int j = board.size() - 1; j >= 0; j--) {
          for (int k = j - 1; k >= 0; k--) {
            if (board[i][j] == 0) {
              if (board[i][k] == 2048)
                break;
              else if (board[i][k] != 0 && board[i][k] != 2048) {
                board[i][j] = board[i][k];
                board[i][k] = 0;
                break;
              }
            }
          }
        }
      }
      return board;
      break;
    }
  }
  vector<vector<int>> update(vector<vector<int>> board, int command) {
    switch (command) {
    case 1:
      for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size() - 1; j++) {
          if (board[j][i] != 0 && board[j][i] != 2048 &&
              board[j][i] == board[j + 1][i]) {
            board[j][i] += board[j + 1][i];
            board[j + 1][i] = 0;
          }
        }
      }
      board = movement(board, 1);
      return board;
      break;

    case 3:
      for (int i = 0; i < board.size(); i++) {
        for (int j = board.size() - 1; j > 0; j--) {
          if (board[j][i] != 0 && board[j][i] != 2048 &&
              board[j][i] == board[j - 1][i]) {
            board[j][i] += board[j - 1][i];
            board[j - 1][i] = 0;
          }
        }
      }
      board = movement(board, 3);
      return board;
      break;
    case 4:
      for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size() - 1; j++) {
          if (board[i][j] != 0 && board[i][j] != 2048 &&
              board[i][j] == board[i][j + 1]) {
            board[i][j] += board[i][j + 1];
            board[i][j + 1] = 0;
          }
        }
      }
      board = movement(board, 4);
      return board;
      break;

    case 2:
      for (int i = 0; i < board.size(); i++) {
        for (int j = board.size() - 1; j > 0; j--) {
          if (board[i][j] != 0 && board[i][j] != 2048 &&
              board[i][j] == board[i][j - 1]) {
            board[i][j] += board[i][j - 1];
            board[i][j - 1] = 0;
          }
        }
      }
      board = movement(board, 2);
      return board;
      break;
    }
  }
  vector<vector<int>> up(vector<vector<int>> board) {
    board = movement(board, 1);
    board = update(board, 1);
    return board;
  }
  vector<vector<int>> right(vector<vector<int>> board) {
    board = movement(board, 2);
    board = update(board, 2);
    return board;
  }
  vector<vector<int>> down(vector<vector<int>> board) {
    board = movement(board, 3);
    board = update(board, 3);
    return board;
  }
  vector<vector<int>> left(vector<vector<int>> board) {
    board = movement(board, 4);
    board = update(board, 4);
    return board;
  }

  void path(queue<vector<vector<int>>> &qmatrix, queue<string> &qpath,
            struct1 tmp, char command) {
    vector<vector<int>> tmpB = tmp.m;
    string p = tmp.path;
    if (p.size() > 12)
      return;
    if (command == '1')
      tmpB = up(tmp.m);
    if (command == '2')
      tmpB = right(tmp.m);
    if (command == '3')
      tmpB = down(tmp.m);
    if (command == '4')
      tmpB = left(tmp.m);
    if (tmpB != tmp.m) {
      p += command;
      qmatrix.push(tmpB);
      qpath.push(p);
    }
  }

  void printMatrix(vector<vector<int>> board) {
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board.size(); j++) {
        cout << board[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  void solve(string outfile, struct1 tmp) {
    ofstream output(outfile);

    while (!qmatrix.empty()) {
      tmp.m = qmatrix.front();
      qmatrix.pop();
      tmp.path = qpath.front();
      qpath.pop();
      if (tmp.path.size() > 12) {
        output << "Impossible";
        cout << "Impossible";
        break;
      }
      if (count() % 2 != 0)
        output << "Impossible";
      if (isSolved(tmp.m)) {
        cout << "solved" << endl;
        if (tmp.path.size() == 0) {
          output << '0';
          cout << '0';
        } else {
          output << tmp.path;
          cout << tmp.path;
        }
        break;
      }
      path(qmatrix, qpath, tmp, '1');
      path(qmatrix, qpath, tmp, '2');
      path(qmatrix, qpath, tmp, '3');
      path(qmatrix, qpath, tmp, '4');
    }
  }
};

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string infile = am.get("input");
  string outfile = am.get("output");

  Graph graph;
  graph.buildboard(infile);
  graph.qmatrix.push(graph.b);
  struct1 tmp;
  tmp.path = "";
  graph.qpath.push(tmp.path);
  graph.solve(outfile, tmp);

  return 0;
}
