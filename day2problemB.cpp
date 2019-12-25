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
  for (int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      vector<int> opcodes;
      for (int i = 0; i < readonly.size(); i++) {
	opcodes.push_back(readonly[i]);
      }
      opcodes[1] = noun;
      opcodes[2] = verb;
      int position = 0;
      while (opcodes[position] != 99) {
	if (opcodes[position] == 1) {
	  opcodes[opcodes[position+3]] = opcodes[opcodes[position+1]]+opcodes[opcodes[position+2]];
	} else if (opcodes[position] == 2) {
	  opcodes[opcodes[position+3]] = opcodes[opcodes[position+1]]*opcodes[opcodes[position+2]];
	} else {
	  cout << "UNDEFINED OPCODE\n";
	  break;
	}
	position += 4;
      }
      if (opcodes[0] == 19690720) {
	cout << "Noun: " << noun << "\n";
	cout << "Verb: " << verb << "\n";
	cout << "Answer: " << (noun*100)+verb << "\n";
      }
    }
  }
  return 0;
}
