#pragma once
#ifndef TEST_H
#define TEST_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include "main.cpp"
//#include "test.cpp"
using std::cout;
//using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;
using std::sort;
enum class State {kEmpty, kObstacle,kClosed,kPath,kStart,kFinish};
void PrintVector(vector<int> v);
void PrintVectorOfVectors(vector<vector<int>> v);
void PrintVectorOfVectors(vector<vector<State>> v);
void TestHeuristic();
void TestAddToOpen() ;
void TestCompare();
void TestSearch() ;
void TestCheckValidCell();
void TestExpandNeighbors();














#endif