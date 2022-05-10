#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <memory>

struct Coordinate {
  Coordinate(int x, int y) : x{x}, y{y} {}

  Coordinate(const std::size_t x, const std::size_t y) : x{static_cast<int>(x)}, y{static_cast<int>(y)} {}

  int x, y;
};

struct Cell {
  Cell(int x, int y) : x(x), y(y), visited(false), is_wall(true) {}

  int x;
  int y;
  bool visited;
  bool is_wall;
};

class Maze {
public:
  Maze(int height, int width) : height(height), width(width) {
	generate_maze_prim();
  }

  void generate_maze_prim() {
	for (int i = 0; i < height; i++) {
	  std::vector<std::shared_ptr<Cell>> row{};
	  for (int j = 0; j < width; j++) {
		row.push_back(std::make_shared<Cell>(Cell{j, i}));
	  }
	  map.push_back(row);
	}
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> rand_n_height(0, height - 1);
	std::uniform_int_distribution<int> rand_n_width(0, width - 1);
	int y = rand_n_height(dev);
	int x = rand_n_width(dev);

	std::vector<std::shared_ptr<Cell>> cell_stack{};

	cell_stack.push_back(map[y][x]);

	while (!cell_stack.empty()) {

	  std::uniform_int_distribution<int> rand_element(0, cell_stack.size() - 1);
	  int random_index = rand_element(dev);

	  auto cell = *(cell_stack.begin() + random_index);
	  cell_stack.erase(cell_stack.begin() + random_index);

	  cell->visited = true;

	  if (!divides_two_cooridors(cell)) {
		cell->is_wall = false;
	  }

	  auto neighbours = get_neighbours(cell);
	  for (auto const &neighbour : neighbours) {
		cell_stack.push_back(neighbour);
	  }
	  print_maze(cell);
	  std::cout << "\n";
	}

  }

  std::vector<std::shared_ptr<Cell>> get_neighbours(std::shared_ptr<Cell> cell) {
	std::vector<std::shared_ptr<Cell>> neighbours{};

	if (cell->y - 1 > 0) {
	  auto c = map[cell->y - 1][cell->x];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	if (cell->y - 1 > 0 && cell->x - 1 > 0) {
	  auto c = map[cell->y - 1][cell->x - 1];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	if (cell->y - 1 > 0 && cell->x + 1 < width) {
	  auto c = map[cell->y - 1][cell->x + 1];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	if (cell->x + 1 < width) {
	  auto c = map[cell->y][cell->x + 1];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	if (cell->x - 1 > 0) {
	  auto c = map[cell->y][cell->x - 1];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	if (cell->y + 1 < height) {
	  auto c = map[cell->y + 1][cell->x];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	if (cell->y + 1 < height && cell->x - 1 > 0) {
	  auto c = map[cell->y + 1][cell->x - 1];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	if (cell->y + 1 < height && cell->x + 1 < width) {
	  auto c = map[cell->y + 1][cell->x + 1];
	  if (!c->visited) {
		neighbours.push_back(c);
	  }
	}
	return neighbours;
  }

  bool divides_two_cooridors(std::shared_ptr<Cell> cell) {
	if (cell->x - 1 > 0 && cell->x + 1 < width) {
	  if (!map[cell->y][cell->x - 1]->is_wall && !map[cell->y][cell->x + 1]->is_wall) {
		return true;
	  }
	}

	if (cell->y - 1 > 0 && cell->y + 1 < height) {
	  if (!map[cell->y - 1][cell->x]->is_wall && !map[cell->y + 1][cell->x]->is_wall) {
		return true;
	  }
	}
	return false;
  }

  void print_maze() {
	for (auto const &row : map) {
	  for (auto const &cell : row) {
		if (cell->is_wall) {
		  std::cout << "x";
		} else {
		  std::cout << " ";
		}
	  }
	  std::cout << "\n";
	}
  }

  void print_maze(std::shared_ptr<Cell> current_cell) {
	for (auto const &row : map) {
	  for (auto const &cell : row) {
		if (cell == current_cell) {
		  std::cout << "O";
		} else if (cell->is_wall) {
		  std::cout << "X";
		} else {
		  std::cout << " ";
		}
	  }
	  std::cout << "\n";
	}
  }

private:
  std::vector<std::vector<std::shared_ptr<Cell>>> map{};
  int height;
  int width;
};

int main() {
  Maze m{30, 30};
  m.print_maze();
}

