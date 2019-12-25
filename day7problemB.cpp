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

int main()
{
  vector<int> readonly;
  int data;
  char comma;
  while (cin >> data) {
    readonly.push_back(data);
    cin >> comma;
  }
  vector<int> order;
  for (int i = 5; i < 10; i++) {
    order.push_back(i);
  }
  long long int maxResult = 0;
  //int maxResult = 0;
  for (int i = 0; i < 120; i++) {
    //cout << "PERMUTATION " << i << "\n"; // DEBUG
    vector<long long int> opcodes[5];
    //vector<int> opcodes[5];
    for (int amplifier = 0; amplifier < 5; amplifier++) {
      for (int j = 0; j < readonly.size(); j++) {
	opcodes[amplifier].push_back(readonly[j]);
      }
    }
    long long int ioData[5];
    //deque<long long int> ioData[5];
    //deque<int> ioData[5];
    ioData[0] = 0;
    //ioData[0].push_back(0);
    int amplifier = 0;
    long long int result;
    //int result;
    bool halted = false;
    bool inputPhasesNotUsed = true;
    int positions[5];
    for (int p = 0; p < 5; p++) {
      positions[p] = 0;
    }
    while ((not halted) || (amplifier != 0)) {
      //cout << "AMPLIFIER " << amplifier << "\n"; // DEBUG
      //if (inputPhases) {
	//ioData[amplifier].push_front(order[amplifier]);
	//}
      int position = positions[amplifier];
      bool inputPhasesNotRead = inputPhasesNotUsed;
      while (true) { // Does this work?
      //while (not ((opcodes[amplifier][position]%10 == 3) && ioData[amplifier].empty())) {
	if (opcodes[amplifier][position]%10 == 1) {
	  long long int first;
	  //int first;
	  if (opcodes[amplifier][position]/100 % 10 == 1) {
	    first = opcodes[amplifier][position+1];
	  } else {
	    first = opcodes[amplifier][opcodes[amplifier][position+1]];
	  }
	  long long int second;
	  //int second;
	  if (opcodes[amplifier][position]/1000 == 1) {
	    second = opcodes[amplifier][position+2];
	  } else {
	    second = opcodes[amplifier][opcodes[amplifier][position+2]];
	  }
	  opcodes[amplifier][opcodes[amplifier][position+3]] = first+second;
	  position += 4;
	} else if (opcodes[amplifier][position]%10 == 2) {
	  long long int first;
	  //int first;
	  if (opcodes[amplifier][position]/100 % 10 == 1) {
	    first = opcodes[amplifier][position+1];
	  } else {
	    first = opcodes[amplifier][opcodes[amplifier][position+1]];
	  }
	  long long int second;
	  //int second;
	  if (opcodes[amplifier][position]/1000 == 1) {
	    second = opcodes[amplifier][position+2];
	  } else {
	    second = opcodes[amplifier][opcodes[amplifier][position+2]];
	  }
	  opcodes[amplifier][opcodes[amplifier][position+3]] = first*second;
	  position += 4;
	} else if (opcodes[amplifier][position]%10 == 3) {
	  if (inputPhasesNotRead) {
	    opcodes[amplifier][opcodes[amplifier][position+1]] = order[amplifier];
	    inputPhasesNotRead = false;
	  } else {
	    opcodes[amplifier][opcodes[amplifier][position+1]] = ioData[amplifier];
	  }
	  //opcodes[amplifier][opcodes[amplifier][position+1]] = ioData[amplifier].front();
	  //ioData[amplifier].pop_front();
	  position += 2;
	} else if (opcodes[amplifier][position]%10 == 4) {
	  if (opcodes[amplifier][position]/100 == 1) {
	    ioData[(amplifier+1)%5] = opcodes[amplifier][position+1];
	    //ioData[(amplifier+1)%5].push_back(opcodes[amplifier][position+1]);
	  } else {
	    ioData[(amplifier+1)%5] = opcodes[amplifier][opcodes[amplifier][position+1]];
	    ioData[(amplifier+1)%5] = opcodes[amplifier][opcodes[amplifier][position+1]];
	  }
	  position += 2;
	  break;
	} else if (opcodes[amplifier][position]%10 == 5) {
	  bool jump;
	  if (opcodes[amplifier][position]/100 % 10 == 1) {
	    jump = opcodes[amplifier][position+1];
	  } else {
	    jump = opcodes[amplifier][opcodes[amplifier][position+1]];
	  }
	  int jumpTo;
	  if (opcodes[amplifier][position]/1000 == 1) {
	    jumpTo = opcodes[amplifier][position+2];
	  } else {
	    jumpTo = opcodes[amplifier][opcodes[amplifier][position+2]];
	  }
	  if (jump) {
	    position = jumpTo;
	  } else {
	    position += 3;
	  }
	} else if (opcodes[amplifier][position]%10 == 6) {
	  bool jump;
	  if (opcodes[amplifier][position]/100 % 10 == 1) {
	    jump = opcodes[amplifier][position+1];
	  } else {
	    jump = opcodes[amplifier][opcodes[amplifier][position+1]];
	  }
	  int jumpTo;
	  if (opcodes[amplifier][position]/1000 == 1) {
	    jumpTo = opcodes[amplifier][position+2];
	  } else {
	    jumpTo = opcodes[amplifier][opcodes[amplifier][position+2]];
	  }
	  if (not jump) {
	    position = jumpTo;
	  } else {
	    position += 3;
	  }
	} else if (opcodes[amplifier][position]%10 == 7) {
	  long long int first;
	  //int first;
	  if (opcodes[amplifier][position]/100 % 10 == 1) {
	    first = opcodes[amplifier][position+1];
	  } else {
	    first = opcodes[amplifier][opcodes[amplifier][position+1]];
	  }
	  long long int second;
	  //int second;
	  if (opcodes[amplifier][position]/1000 == 1) {
	    second = opcodes[amplifier][position+2];
	  } else {
	    second = opcodes[amplifier][opcodes[amplifier][position+2]];
	  }
	  opcodes[amplifier][opcodes[amplifier][position+3]] = (first < second);
	  position += 4;
	} else if (opcodes[amplifier][position]%10 == 8) {
	  long long int first;
	  //int first;
	  if (opcodes[amplifier][position]/100 % 10 == 1) {
	    first = opcodes[amplifier][position+1];
	  } else {
	    first = opcodes[amplifier][opcodes[amplifier][position+1]];
	  }
	  long long int second;
	  //int second;
	  if (opcodes[amplifier][position]/1000 == 1) {
	    second = opcodes[amplifier][position+2];
	  } else {
	    second = opcodes[amplifier][opcodes[amplifier][position+2]];
	  }
	  opcodes[amplifier][opcodes[amplifier][position+3]] = (first == second);
	  position += 4;
	} else if (opcodes[amplifier][position] == 99) {
	  result = ioData[0];
	  //result = ioData[0].back();
	  halted = true;
	  break;
	} else {
	  cout << "UNDEFINED OPCODE\n";
	  cout << ioData[5];
	}
	/*
	for (int x = 0; x < opcodes[amplifier].size(); x++) { // DEBUG
	  if (x == position) { // DEBUG
	    cout << ">>";
	  } // DEBUG
	  cout << opcodes[amplifier][x] << " "; // DEBUG
	} // DEBUG
	cout << "\n"; // DEBUG
	*/
      }
      if (amplifier == 4) {
      	inputPhasesNotUsed = false;
      }
      //cout << ioData[amplifier] << " " << ioData[(amplifier+1)%5] << "\n"; // DEBUG
      positions[amplifier] = position;
      amplifier = (amplifier+1) % 5;
    }
    //cout << result << "\n"; // DEBUG
    maxResult = max(maxResult, result);
    next_permutation(order.begin(), order.end());
  }
  cout << maxResult << "\n";
  return 0;
}

// Well, I managed to get the program to produce the right answer on both test cases.
// Now to run it on the real thing.
// Either the program is too slow or it's in an infinite loop. Not sure which.
// As far as I can tell, the program encounters an integer overflow and enters an infinite loop.
// So... yeah...
// Not even long long int helps.

// Long story short: It is guaranteed that there is only one piece of output.
// Also, I badly misread a piece of debug advice.

// Here's what Test Case 1 does for each amplifier call:
// Put PHASE in MEMORY1.
// Subtract 4 from MEMORY1.
// GOTO LOC.
// Put INPUT in MEMORY2.
// Double MEMORY2.
// Add MEMORY1 to MEMORY2.
// Output MEMORY2.
// Subtract 1 from MEMORY3.
// If MEMORY3 is nonzero, GOTO LOC.

// So the output is effectively (PHASE-4)+(2*INPUT).

// Okay, as far as I can tell, here's the situation.
// We only need to input the phases once.
// We do, however, need to keep track of the pointers. The pointer locations carry over.

// Random note: Problem 8A is suspiciously easy for something involving "Space Tangle Format".

// I did it. And as a (blessing? curse?) to my future self, I am leaving all the comments in.
