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
  int moons[4][2][3];
  int input[12] = {5, 4, 4, -11, -11, -3, 0, 7, 0, -13, 2, 10};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      moons[i][0][j] = input[(i*3)+j];
      moons[i][1][j] = 0;
    }
  }
  pair<int, int> pairs[6] = {pair<int, int>(0, 1), pair<int, int>(0, 2), pair<int, int>(0, 3), pair<int, int>(1, 2), pair<int, int>(1, 3), pair<int, int>(2, 3)};
  for (int step = 0; step < 1000; step++) {
    int newMoons[4][2][3];
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
	newMoons[i][1][j] = moons[i][1][j];
      }
    }
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
	if (moons[pairs[i].first][0][j] > moons[pairs[i].second][0][j]) {
	  newMoons[pairs[i].first][1][j] -= 1;
	  newMoons[pairs[i].second][1][j] += 1;
	} else if (moons[pairs[i].first][0][j] < moons[pairs[i].second][0][j]) {
	  newMoons[pairs[i].first][1][j] += 1;
	  newMoons[pairs[i].second][1][j] -= 1;
	}
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
	newMoons[i][0][j] = moons[i][0][j]+newMoons[i][1][j];
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 2; j++) {
	for (int k = 0; k < 3; k++) {
	  moons[i][j][k] = newMoons[i][j][k];
	}
      }
    }
  }
  int sum = 0;
  for (int i = 0; i < 4; i++) {
    int potential = 0;
    for (int j = 0; j < 3; j++) {
      potential += abs(moons[i][0][j]);
    }
    int kinetic = 0;
    for (int j = 0; j < 3; j++) {
      kinetic += abs(moons[i][1][j]);
    }
    sum += potential*kinetic;
  }
  cout << sum << "\n";
  return 0;
}
