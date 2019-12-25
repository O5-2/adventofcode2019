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

long long int gcd(long long int a, long long int b) {
  if ((a == 0) || (b == 0)) {
    return a+b;
  } else if (a >= b) {
    return gcd(b, a % b);
  }
  return gcd(a, b % a);
}

long long int lcm(long long int a, long long int b) {
  return (a*b)/gcd(a, b);
}

bool unequal(array<int, 8> a, array<int, 8> b) {
  bool equal = true;
  for (int i = 0; i < 8; i++) {
    equal = equal && (a[i] == b[i]);
  }
  return not equal;
}

int main()
{
  array<array<int, 8>, 3> input;
  input[0] = {5, -11, 0, -13, 0, 0, 0, 0};
  input[1] = {4, -11, 7, 2, 0, 0, 0, 0};
  input[2] = {4, -3, 0, 10, 0, 0, 0, 0};
  long long int periods[3];
  pair<int, int> pairs[6] = {pair<int, int>(0, 1), pair<int, int>(0, 2), pair<int, int>(0, 3), pair<int, int>(1, 2), pair<int, int>(1, 3), pair<int, int>(2, 3)};
  for (int axis = 0; axis < 3; axis++) {
    int steps = 0;
    array<int, 8> state;
    for (int i = 0; i < 8; i++) {
      state[i] = input[axis][i];
    }
    do {
      array<int, 8> newState;
      for (int i = 0; i < 4; i++) {
	newState[i+4] = state[i+4];
      }
      for (int i = 0; i < 6; i++) {
	if (state[pairs[i].first] > state[pairs[i].second]) {
	  newState[(pairs[i].first)+4] -= 1;
	  newState[(pairs[i].second)+4] += 1;
	} else if (state[pairs[i].first] < state[pairs[i].second]) {
	  newState[(pairs[i].first)+4] += 1;
	  newState[(pairs[i].second)+4] -= 1;
	}
      }
      for (int i = 0; i < 4; i++) {
	newState[i] = state[i]+newState[i+4];
      }  
      for (int i = 0; i < 8; i++) {
	state[i] = newState[i];
      }
      steps += 1;
    } while (unequal(input[axis], state));
    periods[axis] = steps;
  }
  cout << lcm(lcm(periods[0], periods[1]), periods[2]) << "\n";
  return 0;
}

// Done. Finally. Ugh.
