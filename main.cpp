#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include "test.hpp"
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;
using std::sort;


enum class State {kEmpty, kObstacle,kClosed,kPath,kStart,kFinish};
const int delta[4][2]={-1,0,0,-1,1,0,0,1};
vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

//compare two node vector<int>
bool Compare(const vector<int> t1, const vector<int> t2){
  int f1 = t1[2] + t1[3];
  int f2 = t2[2] + t2[3];
  if(f1 > f2)
    return true;
  else 
    return false;
}


int Heuristic(int x1, int y1,int x2,int y2){
  int d = abs(x2-x1)+abs(y2-y1);
  return d;
}
//sort cell function in descending order
void CellSort(vector<vector <int>> *v){
  sort(v->begin(),v->end(),Compare);
}
//check if the Cell is within the grid and state is empty
bool CheckValidCell(int x,int y, vector<vector<State>> &grid){
  bool on_grid_x=(x>=0&&x<grid.size());
  bool on_grid_y=(y>=0 && grid[0].size());
  if (on_grid_x&&on_grid_y){
    return grid[x][y]==State::kEmpty;
  }
  return false;

}

//add a node to the open list, the node can be expressed as x,y,gcost,hcost
void AddToOpen(int x,int y,int g,int h,vector<vector<int>> &openlist,vector<vector<State>> &grid){
  openlist.push_back(vector<int>{x,y,g,h});
  grid[x][y]=State::kClosed;
  //add to openlist & update grid value, the nodes will be marked as visited
}

//expand  the neighbor nodes and add them into the openlists
void ExpandNeighbors(const vector<int> &current,int goal[2],vector<vector<int>> &openlist,vector<vector<State>> &grid){
    //get current data 
    int x=current[0];
    int y=current[1];
    int g=current[2];
    //loop the neigbor grid,if valid, add them into the openlist
    for (int i=0;i<4;i++){
      int x1=x+delta[i][0];
      int y1=y+delta[i][1];
      if (CheckValidCell(x1,y1,grid)){
        int g1=g+1;
        int h=Heuristic(x1,y1,goal[0],goal[1]);
        AddToOpen(x1,y1,g1,h,openlist,grid);
      }
    }
}


// TODO: Write the Search function stub here.
vector<vector<State>> Search(vector<vector<State>> grid,int init[2],int goal[2]){
  vector<vector<int>> openlist={};
  int x=init[0];
  int y=init[1];
  int g=0;
  int h=Heuristic(x,y,goal[0],goal[1]);
  AddToOpen(x,y,g,h,openlist,grid);
  while(openlist.size()>0){
    CellSort(&openlist);
    vector<int> current=openlist.back();
    openlist.pop_back();//why pop_back is invoked here?
    x=current[0];
    y=current[1];
    grid[x][y]=State::kPath;
    if(x==goal[0]&&y==goal[1]){
      grid[init[0]][init[1]]=State::kStart;
      grid[goal[0]][goal[1]]=State::kFinish;
      return grid;
    }
    //or we will expand the search
    ExpandNeighbors(current,goal,openlist,grid);
  }


  cout << "No path Found!"<<"\n";
  vector<vector<State>> solution;
  return vector<vector<State>> {};

}


string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦   ";
    case State::kFinish: return "🏁   ";
    case State::kClosed:return "exp1";
    default: return "0   "; 
  }
}


void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}


int main() {
  // TODO: Declare 2D "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
   int init[2]={0, 0};
  int goal[2]={2, 3};
   //vector<vector<State>> solution;
  auto board = ReadBoardFile("1.board");
  // TODO: Call Search with "board", "init", and "goal". Store the results in the variable "solution".
  // TODO: Change the following line to pass "solution" to PrintBoard.
  auto solution = Search(board,init,goal);
  PrintBoard(solution);
  //test
  //TestHeuristic();
  //TestHeuristic();
  //TestAddToOpen();
  //TestCompare();
  //TestSearch();
  //TestCheckValidCell();
  //TestExpandNeighbors();
}


