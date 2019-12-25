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
  int a[70] = {65,44,66,44,66,44,65,44,67,44,65,44,65,44,67,44,66,44,67,10,82,44,56,44,76,44,49,50,44,82,44,56,10,82,44,49,50,44,76,44,56,44,82,44,49,48,10,82,44,56,44,76,44,56,44,76,44,56,44,82,44,56,44,82,44,49,48,10,110,10};
  queue<int> instructions;
  for (int i = 0; i < 70; i++) {
    instructions.push(a[i]);
  }
  while (opcodes[position] != 99) {
    if (opcodes[position]%100 == 1) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 2) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 3) {
      int input;
      input = instructions.front();
      instructions.pop();
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
      if (output < 256) {
	cout << (char)output;
      } else {
	cout << output << "\n";
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
  return 0;
}

// So how are we going to do this?
// Picture for reference:
/*
..........###########........................
..........#.........#........................
..........#.........#.......#########........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#########.#############...#........
..................#.........#...#...#........
............###########.....#.#########......
............#.....#...#.....#.#.#...#.#......
............#.....#...#.....#.#.#...#.#......
............#.....#...#.....#.#.#...#.#......
............#.....#.^########.#.#...#########
............#.....#...#.......#.#.....#.....#
..........#########...#.#########.....#.....#
..........#.#.........#.#.....#.......#.....#
#############.........#########.......#.....#
#.........#.............#.............#.....#
#.......#########.......#.............#.....#
#.......#.#.....#.......#...................#
#.......#.#.....#.......#...................#
#.......#.#.....#.......#...................#
#.......#.#############.#.......#############
#.......#.......#.....#.#.......#............
#.......#.......#.....#.#.......#............
#.......#.......#.....#.#.......#............
#########.......#########.......#............
......................#.........#............
......................#.........#............
......................#.........#............
......................###########............
 */
// Possible path: R,8,L,12,R,8,R,12,L,8,R,10,R,12,L,8,R,10,R,8,L,12,R,8,R,8,L,8,L,8,R,8,R,10,R,8,L,12,R,8,R,8,L,12,R,8,R,8,L,8,L,8,R,8,R,10,R,12,
// L,8,R,10,R,8,L,8,L,8,R,8,R,10 (edited)
// Total ASCII characters in the commands: 85. We need to perform a speedup of a factor of 4, at least.
// ... wait one second. 10 commands in A, and 10 calls to A = 100 characters of effect. If this is possible, it is only barely so.
// ... no, seriously! Even 9 commands in A and 9 calls to A = 81 characters of effect.
// Is my path typoed? Either I'm really bad at doing this, or it's impossible. Way too little similarity as is.
// I think I see the problem. One genuine typo, and a whole lot of off-by-one errors.

// A is probably R,8,L,12,R,8
// B might be R,12,L,8,R,10
// C might be R,8,L,8,L,8,R,8,R,10
// and the whole thing would be A,B,B,A,C,A,A,C,B,C
// 36 characters total.

// Still not enough?!?
// Oh, wait. It says "20 characters *each*".
// So all I need to do now is put those movecodes into the queue.

// So A,B,B,A,C,A,A,C,B,C,\nR,8,L,12,R,8\nR,12,L,8,R,10\nR,8,L,8,L,8,R,8,R,10\nn\n
// Which works out to be
// 65 44 66 44 66 44 65 44 67 44 65 44 65 44 67 44 66 44 67 10
// 82 44 56 44 76 44 49 50 44 82 44 56 10
// 82 44 49 50 44 76 44 56 44 82 44 49 48 10
// 82 44 56 44 76 44 56 44 76 44 56 44 82 44 56 44 82 44 49 48 10
// 110 10
