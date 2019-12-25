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

bool inTractorBeam(long long int original[], int x, int y) {
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
      position += 2;
      return output;
      /*
      if (output) { // DEBUG
	cout << "#"; // DEBUG
      } else { // DEBUG
	cout << "."; // DEBUG
      } // DEBUG
      */
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
  /*
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
      position += 2;
      return output;
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
  // Does this whole thing work?
  */
  return false; // Is this needed?
}

bool satisfiesConditions(long long int opcodes[], int x, int y) {
  int points = 0;
  for (int xMod = 0; xMod <= 99; xMod++) {
    for (int yMod = 0; yMod <= 99; yMod++) {
      points += inTractorBeam(opcodes, x+xMod, y+yMod);
    }
  }
  // Does this whole thing work?
  return (points == 10000);
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
  int baseX = 1120; // Should be 1104
  int baseY = 1245; // Should be 154
  for (int yMod = 0; yMod <= 5; yMod++) { // Should be 100
    for (int xMod = 0; xMod <= 5; xMod++) { // Should be 100
      cout << satisfiesConditions(opcodes, baseX+xMod, baseY+yMod);
      //cout << inTractorBeam(opcodes, baseX+xMod, baseY+yMod);
    }
    cout << "\n";
  }
  // TODO: big giant plan to figure out the closest x, y
  return 0;
}

// As far as I can tell, here's how it works:
// Six rows, each of them shifted one to the right of the one above.
// Then, the width of the rows increases by one, and the next group of six doesn't shift to the right.
// Width, in theory, is exactly row#/6, round down.

// We want the 100th-from-last spot in the first row that is 100+n wide, where n = the amount that the rows will shift by, 100 rows later.
// How much do rows shift after 100 rows?
// (5/6 of (100-(100 % 6))) plus (100 % 6), according to my calculations, which is 84.
// So we want the 100th-from-last spot in the first row that is 184 wide.
// The y coordinate is obviously 184*6 = 1104, and the x coordinate must be the amount that the rows have shifted by after 1104 rows.
// And that is just (5/6 of (1104-(1104 % 6))) plus (1104 % 6), as far as I can tell, which is 920.
// Which doesn't work, as far as I can tell.

// So 154*10000 + 1104 = 1541104.

// Okay, that didn't work. The answer was too low. Well then, no more mister nice guy.

// After much trial and error, I did it. Yay.
