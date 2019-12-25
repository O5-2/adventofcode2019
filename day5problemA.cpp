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
  queue<int> input;
  input.push(1);
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
	cout << opcodes[position+1] << " ";
      } else {
	cout << opcodes[opcodes[position+1]] << " ";
      }
      position += 2;
    } else {
      cout << "UNDEFINED OPCODE\n";
      break;
    }
  }
  cout << "\n";
  return 0;
}
