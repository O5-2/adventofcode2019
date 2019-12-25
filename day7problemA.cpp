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
  for (int i = 0; i < 5; i++) {
    order.push_back(i);
  }
  int maxResult = 0;
  for (int i = 0; i < 120; i++) {
    vector<int> opcodes;
    for (int j = 0; j < readonly.size(); j++) {
      opcodes.push_back(readonly[j]);
    }
    int result = 0;
    for (int amplifier = 0; amplifier < 5; amplifier++) {
      queue<int> input;
      input.push(order[amplifier]);
      input.push(result);
      int position = 0;
      while (opcodes[position] != 99) {
	if (opcodes[position]%10 == 1) {
	  int first;
	  if (opcodes[position]/100 % 10 == 1) {
	    first = opcodes[position+1];
	  } else {
	    first = opcodes[opcodes[position+1]];
	  }
	  int second;
	  if (opcodes[position]/1000 == 1) {
	    second = opcodes[position+2];
	  } else {
	    second = opcodes[opcodes[position+2]];
	  }
	  opcodes[opcodes[position+3]] = first+second;
	  position += 4;
	} else if (opcodes[position]%10 == 2) {
	  int first;
	  if (opcodes[position]/100 % 10 == 1) {
	    first = opcodes[position+1];
	  } else {
	    first = opcodes[opcodes[position+1]];
	  }
	  int second;
	  if (opcodes[position]/1000 == 1) {
	    second = opcodes[position+2];
	  } else {
	    second = opcodes[opcodes[position+2]];
	  }
	  opcodes[opcodes[position+3]] = first*second;
	  position += 4;
	} else if (opcodes[position]%10 == 3) {
	  opcodes[opcodes[position+1]] = input.front();
	  input.pop();
	  position += 2;
	} else if (opcodes[position]%10 == 4) {
	  if (opcodes[position]/100 == 1) {
	    result = opcodes[position+1];
	  } else {
	    result = opcodes[opcodes[position+1]];
	  }
	  position += 2;
	} else if (opcodes[position]%10 == 5) {
	  bool jump;
	  if (opcodes[position]/100 % 10 == 1) {
	    jump = opcodes[position+1];
	  } else {
	    jump = opcodes[opcodes[position+1]];
	  }
	  int jumpTo;
	  if (opcodes[position]/1000 == 1) {
	    jumpTo = opcodes[position+2];
	  } else {
	    jumpTo = opcodes[opcodes[position+2]];
	  }
	  if (jump) {
	    position = jumpTo;
	  } else {
	    position += 3;
	  }
	} else if (opcodes[position]%10 == 6) {
	  bool jump;
	  if (opcodes[position]/100 % 10 == 1) {
	    jump = opcodes[position+1];
	  } else {
	    jump = opcodes[opcodes[position+1]];
	  }
	  int jumpTo;
	  if (opcodes[position]/1000 == 1) {
	    jumpTo = opcodes[position+2];
	  } else {
	    jumpTo = opcodes[opcodes[position+2]];
	  }
	  if (not jump) {
	    position = jumpTo;
	  } else {
	    position += 3;
	  }
	} else if (opcodes[position]%10 == 7) {
	  int first;
	  if (opcodes[position]/100 % 10 == 1) {
	    first = opcodes[position+1];
	  } else {
	    first = opcodes[opcodes[position+1]];
	  }
	  int second;
	  if (opcodes[position]/1000 == 1) {
	    second = opcodes[position+2];
	  } else {
	    second = opcodes[opcodes[position+2]];
	  }
	  opcodes[opcodes[position+3]] = (first < second);
	  position += 4;
	} else if (opcodes[position]%10 == 8) {
	  int first;
	  if (opcodes[position]/100 % 10 == 1) {
	    first = opcodes[position+1];
	  } else {
	    first = opcodes[opcodes[position+1]];
	  }
	  int second;
	  if (opcodes[position]/1000 == 1) {
	    second = opcodes[position+2];
	  } else {
	    second = opcodes[opcodes[position+2]];
	  }
	  opcodes[opcodes[position+3]] = (first == second);
	  position += 4;
	} else {
	  cout << "UNDEFINED OPCODE\n";
	  break;
	}
      }
    }
    maxResult = max(maxResult, result);
    next_permutation(order.begin(), order.end());
  }
  cout << maxResult << "\n";
  return 0;
}
