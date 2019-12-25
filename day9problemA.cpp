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
  while (opcodes[position] != 99) {
    if (opcodes[position]%100 == 1) {
      /*
      long long int first;
      if (opcodes[position]/100 % 10 == 1) {
	first = opcodes[position+1];
      } else {
	first = opcodes[opcodes[position+1]];
      }
      long long int second;
      if (opcodes[position]/1000 == 1) {
	second = opcodes[position+2];
      } else {
	second = opcodes[opcodes[position+2]];
      }
      */
      opcodes[thirdParameter(opcodes, position, relativeBase)] = add(opcodes, position, relativeBase);
      //opcodes[opcodes[position+3]] = first+second;
      position += 4;
    } else if (opcodes[position]%100 == 2) {
      /*
      long long int first;
      if (opcodes[position]/100 % 10 == 1) {
	first = opcodes[position+1];
      } else {
	first = opcodes[opcodes[position+1]];
      }
      long long int second;
      if (opcodes[position]/1000 == 1) {
	second = opcodes[position+2];
      } else {
	second = opcodes[opcodes[position+2]];
      }
      */
      opcodes[thirdParameter(opcodes, position, relativeBase)] = multiply(opcodes, position, relativeBase);
      //opcodes[opcodes[position+3]] = first*second;
      position += 4;
    } else if (opcodes[position]%100 == 3) {
      if (opcodes[position]/100 == 2) {
	opcodes[opcodes[position+1]+relativeBase] = 1;
      } else {
	opcodes[opcodes[position+1]] = 1;
      }
      position += 2;
    } else if (opcodes[position]%100 == 4) {
      if (opcodes[position]/100 == 2) {
	cout << opcodes[opcodes[position+1]+relativeBase] << " ";
      } else if (opcodes[position]/100 == 1) {
	cout << opcodes[position+1] << " ";
      } else {
	cout << opcodes[opcodes[position+1]] << " ";
      }
      position += 2;
    } else if (opcodes[position]%100 == 5) {
      /*
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
      */
      position = jumpIfTrue(opcodes, position, relativeBase);
    } else if (opcodes[position]%100 == 6) {
      /*
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
      */
      position = jumpIfFalse(opcodes, position, relativeBase);
    } else if (opcodes[position]%100 == 7) {
      /*
      long long int first;
      if (opcodes[position]/100 % 10 == 1) {
	first = opcodes[position+1];
      } else {
	first = opcodes[opcodes[position+1]];
      }
      long long int second;
      if (opcodes[position]/1000 == 1) {
	second = opcodes[position+2];
      } else {
	second = opcodes[opcodes[position+2]];
      }
      */
      opcodes[thirdParameter(opcodes, position, relativeBase)] = lessThan(opcodes, position, relativeBase);
      //opcodes[opcodes[position+3]] = (first < second);
      position += 4;
    } else if (opcodes[position]%100 == 8) {
      /*
      long long int first;
      if (opcodes[position]/100 % 10 == 1) {
	first = opcodes[position+1];
      } else {
	first = opcodes[opcodes[position+1]];
      }
      long long int second;
      if (opcodes[position]/1000 == 1) {
	second = opcodes[position+2];
      } else {
	second = opcodes[opcodes[position+2]];
      }
      */
      opcodes[thirdParameter(opcodes, position, relativeBase)] = equalTo(opcodes, position, relativeBase);
      //opcodes[opcodes[position+3]] = (first == second);
      position += 4;
    } else if (opcodes[position]%100 == 9) {
      relativeBase = adjustRelativeBase(opcodes, position, relativeBase);
      position += 2;
    } else {
      cout << "UNDEFINED OPCODE\n";
      break;
    }
    /*
    cout << "\n";
    for (int i = 0; i < 1001; i++) {
      if (i == position) {
	cout << ">>";
      } else if (i == 203) {
	cout << "->";
      }
      cout << opcodes[i] << " ";
    }
    cout << "\n";
    cout << "--" << relativeBase << "++\n";
    */
  }
  cout << "\n";
  return 0;
}
