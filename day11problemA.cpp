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

pair<int, int> movement(pair<int, int> location, int direction) {
  if (direction == 3) {
    return pair<int, int>(location.first-1, location.second);
  } else if (direction == 2) {
    return pair<int, int>(location.first, location.second-1);
  } else if (direction == 1) {
    return pair<int, int>(location.first+1, location.second);
  } else {
    return pair<int, int>(location.first, location.second+1);
  }
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
  int position = 0;
  int relativeBase = 0;
  map<pair<int, int>, int> painted; // black = 0, false. white = 1, true.
  pair<int, int> location = pair<int, int>(0, 0); // AKA, the origin.
  int direction = 0; // 0 = up, 1 = right, 2 = down, 3 = left
  int paint = -1;
  while (opcodes[position] != 99) {
    bool color = ((painted.find(location) != painted.end()) && (painted[location]));
    if (opcodes[position]%100 == 1) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 2) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 3) {
      if (opcodes[position]/100 == 2) {
	opcodes[opcodes[position+1]+relativeBase] = color;
      } else {
	opcodes[opcodes[position+1]] = color;
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
      if (paint == -1) {
	paint = output;
      } else {
	painted.erase(location);
	painted.emplace(location, paint);
	if (output) {
	  direction = (direction+1) % 4;
	} else {
	  direction = (direction+3) % 4;
	}
	location = movement(location, direction);
	paint = -1;
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
  cout << painted.size() << "\n";
  return 0;
}

// It returns 9601, but that's incorrect.
// For some reason, after the first ten steps or so, it just keeps heading up.
// As if there was something wrong with movement() or direction.
// The default % operator is awful. Why am I not surprised?

// It returns 56, but that's also incorrect.
// How to debug?
// It's a little strange how it gets stuck in this 2,9->2,10->3,10->3,9->etc. loop.
// I'm a little confused that it doesn't outright go into an infinite loop.

// Well, at the very least, output is working correctly. Always 0 or 1.
// And as far as I can tell, there's nothing wrong with the directions.
// Current suspects: color, interpretation of output, and an error with the intcode computation (which I doubt, because it'd probably break harder)
// Looks like the interpretation of output is a major suspect: There are no black squares in the final result.
// As usual, it's not my fault: It's C++, forcing you to call erase() if you want to actually update the map.
// Seriously. emplace() and insert() are practically identical, couldn't you make one of them automatically call erase()?
