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

#include <cstdlib>
#include <ctime>

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

///*
pair<int, int> move(pair<int, int> location, int direction) {
  if (direction == 1) {
    return pair<int, int>(location.first, location.second+1);
  } else if (direction == 2) {
    return pair<int, int>(location.first, location.second-1);
  } else if (direction == 3) {
    return pair<int, int>(location.first-1, location.second);
  } else {
    return pair<int, int>(location.first+1, location.second);
  }
}
//*/

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
  pair<int, int> location = pair<int, int>(0, 0);
  int moves = 0;
  int x = 1;
  int input;
  int old = 3-input+(4*(input >= 3));
  while (opcodes[position] != 99) {
    if (opcodes[position]%100 == 1) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 2) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 3) {
      do {
	srand (x);
	input = (rand() % 4)+1;
	x += 1;
      } while (input == old);
      //cout << input << "\n"; // DEBUG
      if (opcodes[position]/100 == 2) {
	opcodes[opcodes[position+1]+relativeBase] = input;
      } else {
	opcodes[opcodes[position+1]] = input;
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
      if (output) {
	moves += 1;
	location = move(location, input); // How do I deal with this? Well, do I really need it anymore?
	old = 3-input+(4*(input >= 3));
	if (output == 2) {
	  break;
	}
      }
      cout << "OUTPUT: " << output << ". " << location.first << " " << location.second << ". " << input << "\n"; // DEBUG
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
  cout << moves << "\n";
  return 0;
}
