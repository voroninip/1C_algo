#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <map>

using namespace std;
using Time = uint32_t;
using cell = pair<int, int>;

int A, B, C, K;

static Time T = 0;


void go() {
  cout << 1;
  int verdict; // 0 or 1
  cin >> verdict;
  T += A;
}

void turn(int clockwise) { // 0 - counterclockwise, 1 - clockwise
  cout << 2 << clockwise;
  int verdict; // only 1
  cin >> verdict;
  T += B;
}

void turn_around() {
  turn(0);
  turn(0);
}

auto fire() {
  cout << 3;
  vector<string> Map(K*2  + 1);
  string s;
  for (int i = 0; i < K*2 + 1; ++i) {
    cin >> s;
  }
  T += C;
  vector<char> nearby = {Map[K-1][K], Map[K][K+1], Map[K+1][K], Map[K][K-1]};
  return nearby;
}

auto create_adj_list(const vector<char>& nearby, const cell& tmp) {
  vector<cell> adjacent;
  if (nearby[0] == '_') {
    adjacent.emplace_back(tmp.first, tmp.second + 1);
  }
  if (nearby[1] == '_') {
    adjacent.emplace_back(tmp.first + 1, tmp.second);
  }
  if (nearby[2] == '_') {
    adjacent.emplace_back(tmp.first, tmp.second - 1);
  }
  if (nearby[3] == '_') {
    adjacent.emplace_back(tmp.first - 1, tmp.second);
  }
  return adjacent;
}


void explore(cell& tmp, int direction, map<cell, bool>& visited) {
  vector<int> commands;

  auto nearby = fire();
  auto adj = create_adj_list(nearby, tmp);

  for (int i = 0; i < 4; ++i) {
    auto next = adj[i];
    if (!visited[next]) {
      if (abs(direction - i) == 2) {
        turn_around();
        commands.push_back(20);
        commands.push_back(20);
      } else
        if (direction > i or (direction == 0 and i == 3)) {
        turn(0);
        commands.push_back(20);
      } else {
        turn(1);
        commands.push_back(21);
      }
      go();
      commands.push_back(1);
      visited[next] = true;

      explore(next, i, visited);
    }
  }
  // returning to the beginning of temporary exploration
  turn_around();
  for (int j = commands.size() - 1; j >= 0; --j) {
    int command = commands[j];
    switch (command) {
      case 1: go();
      case 20: turn(1);
      case 21: turn(0);
      default: continue;
    }
  }
  turn_around();
}



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);


  uint32_t time = 0;

  int x, y, x_1, y_1;
  cin >> x >> y >> x_1 >> y_1 >> A >> B >> C >> K;

  int starting_direction;
  if (x_1 == x and y_1 == y + 1) {
    starting_direction = 0;
  } else
    if (x_1 == x and y_1 == y - 1) {
    starting_direction = 2;
  } else
    if (x_1 == x + 1 and y_1 == y) {
    starting_direction = 1;
  } else
    if (x_1 == x - 1 and y_1 == y) {
    starting_direction = 3;
  }

  map<cell, bool> visited;
  cell start = cell(x, y);
  explore(start, starting_direction, visited);
  cout << 4 << T;
}
