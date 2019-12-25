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
  string image;
  getline(cin, image);
  char black = 35;
  char white = 32;
  for (int pixel = 0; pixel < 150; pixel++) {
    for (int layer = 0; layer < image.length()/150; layer++) {
      if (image[(150*layer)+pixel] == '1') {
	cout << black;
	break;
      } else if (image[(150*layer)+pixel] == '0') {
	cout << white;
	break;
      }
    }
    if (pixel % 25 == 24) {
      cout << "\n";
    }
  }
  return 0;
}
