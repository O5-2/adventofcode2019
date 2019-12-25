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
  pair<int, int> minZerosProduct = pair<int, int>(151, 0);
  string image;
  getline(cin, image);
  char c;
  for (int layer = 0; layer < image.length()/150; layer++) {
    int digits[3];
    for (int i = 0; i < 3; i++) {
      digits[i] = 0;
    }
    char c;
    for (int i = 0; i < 150; i++) {
      c = image[(150*layer)+i];
      digits[c-'0'] += 1;
    }
    if (digits[0] <= minZerosProduct.first) {
      minZerosProduct = pair<int, int>(digits[0], digits[1]*digits[2]);
    }
  }
  cout << minZerosProduct.second << "\n";
  return 0;
}
