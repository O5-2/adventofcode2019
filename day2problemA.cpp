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
  vector<int> opcodes;
  int data;
  char comma;
  while (cin >> data) {
    opcodes.push_back(data);
    cin >> comma;
  }
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
  cout << opcodes[0] << "\n";
  return 0;
}
