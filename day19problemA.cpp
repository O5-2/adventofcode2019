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

int main()
{
  long long int original[10000];
  long long int data;
  char comma;
  int i = 0;
  while (cin >> data) {
    original[i] = data;
    i += 1;
    cin >> comma;
  }
  int points = 0;
  for (int y = 0; y <= 49; y++) {
    for (int x = 0; x <= 49; x++) {
      long long int opcodes[10000];
      for (int i = 0; i < 10000; i++) {
	opcodes[i] = original[i];
      }
      int position = 0;
      int relativeBase = 0;
      bool askedForX = false;
      while (opcodes[position] != 99) {
	if (opcodes[position]%100 == 1) {
	  opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
	  position += 4;
	} else if (opcodes[position]%100 == 2) {
	  opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
	  position += 4;
	} else if (opcodes[position]%100 == 3) {
	  int input;
	  if (not askedForX) {
	    input = x;
	    askedForX = true;
	  } else {
	    input = y;
	  }
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
	  points += output;
	  position += 2;
	  if (output) { // DEBUG
	    cout << "#"; // DEBUG
	  } else { // DEBUG
	    cout << "."; // DEBUG
	  } // DEBUG
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
    }
    cout << "\n"; // DEBUG
  }
  cout << points << "\n";
  return 0;
}
