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
  int begin;
  int end;
  cin >> begin >> end;
  int passwords = 0;
  for (int n = begin; n <= end; n++) {
    string s = to_string(n);
    bool noDecreases = true;
    bool doubleDigits = false;
    for (int i = 0; i < floor(log10(n)); i++) {
      if (s[i] > s[i+1]) {
	noDecreases = false;
      } else if (s[i] == s[i+1]) {
	doubleDigits = true;
      }
    }
    if (noDecreases && doubleDigits) {
      passwords += 1;
    }
  }
  cout << passwords << "\n";
  return 0;
}
