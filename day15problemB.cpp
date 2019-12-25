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

// output: new state and result of move instruction
pair<pair<long long int[2000], pair<int, int>>, int> step(long long int opcodes[], int position, int relativeBase, int input) {
  int output;
  int old = 3-input+(4*(input >= 3));
  while (opcodes[position] != 99) {
    if (opcodes[position]%100 == 1) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 2) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 3) {
      if (opcodes[position]/100 == 2) {
	opcodes[opcodes[position+1]+relativeBase] = input;
      } else {
	opcodes[opcodes[position+1]] = input;
      }
      position += 2;
    } else if (opcodes[position]%100 == 4) {
      output = firstParameter(opcodes, position, relativeBase);
      position += 2;
      break;
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
  return pair<pair<long long int[2000], pair<int, int>>, int>(pair<long long int[2000], pair<int, int>>(opcodes, pair<int, int>(position, relativeBase)), output); // Does this work?
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

/*
int dfs(long long int opcodes[], int position, int relativeBase, int input, pair<int, int> location) {
  int output;
  int old = 3-input+(4*(input >= 3));
  while (opcodes[position] != 99) {
    if (opcodes[position]%100 == 1) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 2) {
      opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
      position += 4;
    } else if (opcodes[position]%100 == 3) {
      if (opcodes[position]/100 == 2) {
	opcodes[opcodes[position+1]+relativeBase] = input;
      } else {
	opcodes[opcodes[position+1]] = input;
      }
      position += 2;
    } else if (opcodes[position]%100 == 4) {
      output = firstParameter(opcodes, position, relativeBase);
      position += 2;
      break;
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
  // How do I get the program to stop when finding the oxygen?
  //cout << "TESTa\n"; // DEBUG
  if ((output == 0) or (output == 2)) {
    cout << "||WALL: " << location.first << " " << location.second << "\n"; // DEBUG
    return 0;
  } else {
    cout << "PATH: " << location.first << " " << location.second << "\n"; // DEBUG
  }
  int maxDistance = 0;
  //cout << "TESTb\n"; // DEBUG
  for (int direction = 1; direction <= 4; direction++) {
    if (direction != old) {
      maxDistance = max(maxDistance, dfs(opcodes, position, relativeBase, direction, move(location, direction)));
    }
  }
  return maxDistance+1;
}
*/

int main()
{
  long long int opcodes[2000];
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
  int fails = 0; // NEW
  /*
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
      if (opcodes[position]/100 == 2) {
	opcodes[opcodes[position+1]+relativeBase] = input;
      } else {
	opcodes[opcodes[position+1]] = input;
      }
      position += 2;
    } else if (opcodes[position]%100 == 4) {
      int output;
      output = firstParameter(opcodes, position, relativeBase);
      position += 2;
      if (output) {
	moves += 1;
	location = move(location, input);
	old = 3-input+(4*(input >= 3));
	if (output == 2) {
	  moves = 0; // NEW
	  old = 0; // NEW
	  //cout << "TEST\n"; // OLD
	  //break; // OLD
	} else {
	  fails += 1; // NEW
	  if (fails > 100) { // NEW
	    break; // NEW
	  }
	  }
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
  */
  deque<pair<long long int[2000], pair<pair<int, int>, pair<int, int>>>> states; // opcodes, position, relativeBase, direction, moves
  for (int direction = 1; direction <= 4; direction++) {
    states.push_back(pair<long long int[2000], pair<pair<int, int>, pair<int, int>>>(opcodes, pair<pair<int, int>, pair<int, int>>(pair<int, int>(position, relativeBase), pair<int, int>(direction, 0))));
  }
  while (not states.empty()) {
    bool done = false;
    pair<long long int[2000], pair<pair<int, int>, pair<int, int>>> current;
    current = states.front();
    states.pop_front();
    old = 3-(current.second.second.second)+(4*(current.second.second.second >= 3));
    for (int direction = 1; direction <= 4; direction++) {
      pair<pair<long long int[2000], pair<int, int>>, int> result = step(current.first, current.second.first.first, current.second.first.second, current.second.second.first);
      if (result.second == 2) {
	done = true;
      } else if (result.second == 1) {
	// TODO: can't directly push result. What to do?
	states.push_front(result.second);
      }
    }
    // Anything left?
    // TODO: DFS
  }
  // Do DFS or BFS?
  /*OLD
  int oxygenTime = 0;
  for (int direction = 1; direction <= 4; direction++) {
    oxygenTime = max(oxygenTime, dfs(opcodes, position, relativeBase, direction, pair<int, int>(location.first, location.second)));
  }
  cout << oxygenTime << "\n";
  */
  //cout << moves << "\n"; // NEW
  //cout << max(moves, 220) << "\n"; // NEW
  return 0;
}

// So how do I solve this? Presumably there's...
// What was I going to say?
// Anyway, here's the plan: When we reach the oxygen system, we reset moves to 0 and keep going down the tunnel.
// When we reach a dead end, we output the maximum distance from the oxygen system to either end of the tunnel.

// It doesn't work for some reason. Huh?

// Insight from r/adventofcode: Clone the intcode VMs so that DFS can be used.

// (Although I still kind of want to know why this solution fails but my solution for problem A works.)
// (But never mind that, I suppose.)

// Program returns segfault. Probably because 2000 integers * thousands of function calls = too much memory.
// For some reason, the program just charges right, bobbing up and down a bit, for six thousand units.
// There's even, like, a pattern to it.

// I really don't understand how to do the second part. Perhaps if I rewrite the DFS to find the oxygen tank, I'll know what's wrong.
// I have absolutely no idea.
// As in, "zero idea at all."
// Seriously! Ugh. You know what? ughhhhh
// Maybe I'll try and reverse-engineer it.
// Then again, that might be even harder.
// Yeah, that'd actually be insanely hard. Even if I managed to somehow figure out the maze...

// But no seriously why isn't the DFS working?

// memory[1033] = INPUT
// memory[1032] = (memory[1033] == 1)
// if (memory[1032]) JUMP LOC1
// memory[1032] = (memory[1033] == 2)
// if (memory[1032]) JUMP 58 // todo
// memory[1032] = (memory[1033] == 3)
// if (memory[1032]) JUMP 81 // todo
// memory[1032] = (memory[1033] == 4)
// if (memory[1032]) JUMP 104 // todo
// HALT
// LOC1
// memory[1039] = memory[1034]
// memory[1041] = memory[1036]
// memory[1040] = memory[1035]-1
// memory[1043] = (memory[1038] == 0)

// I'm seriously considering just giving up on this, to be honest.
// Either that or doing it in Python, though I'm not sure how much it'd help.
