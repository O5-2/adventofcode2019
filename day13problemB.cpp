#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>

#include <cmath>
#include <iomanip>
#include <array>

using namespace std;

long long int firstParameter(long long int opcodes[], int position, int relativeBase) {
  if (opcodes[position]/100 % 10 == 2) {
    return opcodes[opcodes[position+1]+relativeBase];
  } else if (opcodes[position]/100 % 10 == 1) {
    return opcodes[position+1];
  } else {
    return opcodes[opcodes[position+1]];
  }
}

long long int secondParameter(long long int opcodes[], int position, int relativeBase) {
  if (opcodes[position]/1000 % 10 == 2) {
    return opcodes[opcodes[position+2]+relativeBase];
  } else if (opcodes[position]/1000 % 10 == 1) {
    return opcodes[position+2];
  } else {
    return opcodes[opcodes[position+2]];
  }
}

int thirdParameter(long long int opcodes[], int position, int relativeBase) {
  if (opcodes[position]/10000 == 2) {
    return opcodes[position+3]+relativeBase;
  } else {
    return opcodes[position+3];
  }
}

long long int add(long long int opcodes[], int position, int relativeBase) {
  long long int first = firstParameter(opcodes, position, relativeBase);
  long long int second = secondParameter(opcodes, position, relativeBase);
  return first+second;
}

long long int multiply(long long int opcodes[], int position, int relativeBase) {
  long long int first = firstParameter(opcodes, position, relativeBase);
  long long int second = secondParameter(opcodes, position, relativeBase);
  return first*second;
}

int jumpIfTrue(long long int opcodes[], int position, int relativeBase) {
  long long int jump = firstParameter(opcodes, position, relativeBase);
  long long int jumpTo = secondParameter(opcodes, position, relativeBase);
  if (jump) {
    return jumpTo;
  } else {
    return position+3;
  }
}

int jumpIfFalse(long long int opcodes[], int position, int relativeBase) {
  long long int jump = firstParameter(opcodes, position, relativeBase);
  long long int jumpTo = secondParameter(opcodes, position, relativeBase);
  if (not jump) {
    return jumpTo;
  } else {
    return position+3;
  }
}

int lessThan(long long int opcodes[], int position, int relativeBase) {
  long long int first = firstParameter(opcodes, position, relativeBase);
  long long int second = secondParameter(opcodes, position, relativeBase);
  return (first < second);
}

int equalTo(long long int opcodes[], int position, int relativeBase) {
  long long int first = firstParameter(opcodes, position, relativeBase);
  long long int second = secondParameter(opcodes, position, relativeBase);
  return (first == second);
}

int adjustRelativeBase(long long int opcodes[], int position, int relativeBase) {
  long long int first = firstParameter(opcodes, position, relativeBase);
  return relativeBase+first;
}

string display(map<pair<int, int>, int> tiles) {
  string screen;
  for (int y = 0; y <= 20; y++) {
    for (int x = -5; x <= 50; x++) {
      if ((tiles.find(pair<int, int>(x, y)) != tiles.end()) && (tiles[pair<int, int>(x, y)] != 0)) {
	if (tiles[pair<int, int>(x, y)] == 1) {
	  screen += "O";
	} else if (tiles[pair<int, int>(x, y)] == 2) {
	  screen += "X";
	} else if (tiles[pair<int, int>(x, y)] == 3) {
	  screen += "_";
	} else if (tiles[pair<int, int>(x, y)] == 4) {
	  screen += "*";
	}
      } else {
	screen = screen + " ";
      }
    }
    screen = screen + "\n";
  }
  return screen;
}

int main()
{
  long long int opcodes[10000];
  long long int data;
  char comma;
  int i = 0;
  while (cin >> data) {
    opcodes[i] = data;
    i += 1;
    cin >> comma;
  }
  opcodes[0] = 2;
  int position = 0;
  int relativeBase = 0;
  map<pair<int, int>, int> tiles; // 0 = empty. 1 = wall. 2 = block. 3 = paddle. 4 = ball.
  pair<int, int> tile = pair<int, int>(-2, -2);
  int score = 0;
  int ballX;
  int paddleX;
  while (opcodes[position] != 99) {
    if (opcodes[position]%100 == 1) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 2) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 3) {
      cout << display(tiles);
      cout << score << "\n";
      int joystick = 0;
      if (paddleX < ballX) {
	joystick = 1;
      } else if (ballX < paddleX) {
	joystick = -1;
      }
      if (opcodes[position]/100 == 2) {
        opcodes[opcodes[position+1]+relativeBase] = joystick;
      } else {
        opcodes[opcodes[position+1]] = joystick;
      }
      position += 2;
    } else if (opcodes[position]%100 == 4) {
      int output;
      if (opcodes[position]/100 == 2) {
	output = opcodes[opcodes[position+1]+relativeBase];
      } else if (opcodes[position]/100 == 1) {
	output = opcodes[position+1];
      } else {
	output = opcodes[opcodes[position+1]];
      }
      position += 2;
      if (tile.first == -2) {
	tile = pair<int, int>(output, -2);
      } else if (tile.second == -2) {
	tile = pair<int, int>(tile.first, output);
      } else {
	if (tile == pair<int, int>(-1, 0)) {
	  score = output;
	} else {
	  tiles.erase(tile);
	  tiles.emplace(tile, output);
	  if (output == 4) {
	    ballX = tile.first;
	  } else if (output == 3) {
	    paddleX = tile.first;
	  }
	}
	tile = pair<int, int>(-2, -2);
      }
    } else if (opcodes[position]%100 == 5) {
      position = jumpIfTrue(opcodes, position, relativeBase);
    } else if (opcodes[position]%100 == 6) {
      position = jumpIfFalse(opcodes, position, relativeBase);
    } else if (opcodes[position]%100 == 7) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = lessThan(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 8) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = equalTo(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 9) {
      relativeBase = adjustRelativeBase(opcodes, position, relativeBase);
      position += 2;
    } else {
      cout << "UNDEFINED OPCODE\n";
      break;
    }
  }
  cout << display(tiles);
  cout << score << "\n";
  return 0;
}

// I'm beginning to notice a trend: I have one or two stupid bugs in my code, and each of them takes me something like half an hour to find.
