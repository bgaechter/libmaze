#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <memory>

struct Coordinate {
	Coordinate( int x, int y) : x{x}, y{y} {}
	Coordinate(const std::size_t x, const std::size_t y) : x{static_cast<int>(x)}, y{static_cast<int>(y)} {}
	int x, y;
};

struct Cell {
	Cell(int x, int y) : x(x), y(y), visited(false), is_wall(true){}

	int x;
	int y;
	bool visited;
	bool is_wall;
};

class Maze {
	public:
		Maze(int height, int width) : height(height), width(width)
	{
		generate_maze_prim();
	}

		void generate_maze_prim() {
			for(int i = 0; i < height; i++) {
				std::vector<Cell> row {};
				for(int j = 0; j < width; j++) {
					row.push_back(Cell{j,i});
				}
				map.push_back(row);
			}
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<int> rand_n_height(0,height-1);
			std::uniform_int_distribution<int> rand_n_width(0,width-1);
			int y = rand_n_height(dev);
			int x = rand_n_width(dev);

			std::vector<std::shared_ptr<Cell>> cell_stack{};

			cell_stack.push_back(std::make_shared<Cell>(map[y][x]));

			while(!cell_stack.empty())
			{
				std::shared_ptr<Cell> cell = cell_stack.back();
				std::cout << "Selected " << cell->x << "/" << cell->y << std::endl;
				cell_stack.pop_back();

				cell->visited = true;

				if(!divides_two_cooridors(cell))
				{
					cell->is_wall = false;
				}

				auto neighbours = get_neighbours(cell);
				for(auto const &neighbour : neighbours){
					cell_stack.push_back(neighbour);
				}

				// for(auto c: cell_stack){
				// std::cout << "Cell: " << c->x << "/" << c->y;
				// if(c->is_wall)
				// {
				// std::cout << " is wall";
				// }
				// if(c->visited)
				// {
				// std::cout << " is visited \n" << std::endl;
				// }
				//
				// }
			}
			// auto cell = cell_stack.front();
			// std::cout << "Selected " << cell->x << "/" << cell->y << std::endl;
		}

		std::vector<std::shared_ptr<Cell>> get_neighbours(std::shared_ptr<Cell> cell) {
			std::vector<std::shared_ptr<Cell>> neighbours{};

			if ( cell->y-1 > 0 )
			{
				auto c = std::make_shared<Cell>(map[cell->y-1][cell->x]);
				if(!c->visited){
					neighbours.push_back(c);
				}
			}
			if (cell->y -1 > 0 && cell->x-1 >0)
			{
				auto c = std::make_shared<Cell>(map[cell->y-1][cell->x-1]);
				if(!c->visited){
					neighbours.push_back(c);
				}
			}
			if (cell->y -1 > 0 && cell->x+1 <width)
			{
				auto c = std::make_shared<Cell>(map[cell->y-1][cell->x+1]);
				if(!c->visited){
					neighbours.push_back(c);
				}
			}
			if (cell->x+1 <width)
			{
				auto c = std::make_shared<Cell>(map[cell->y][cell->x+1]);
				if(!c->visited){
					neighbours.push_back(c);
				}
			}
			if (cell->x-1 >0)
			{
				auto c = std::make_shared<Cell>(map[cell->y][cell->x-1]);
				if(!c->visited){
					neighbours.push_back(c);
				}
			}
			if ( cell->y+1 < height )
			{
				auto c = std::make_shared<Cell>(map[cell->y+1][cell->x]);
				if(!c->visited){
					neighbours.push_back(c);
				}
			}
			if (cell->y+1 < height && cell->x-1 >0)
			{
				auto c = std::make_shared<Cell>(map[cell->y+1][cell->x-1]);
				if(!c->visited){
					neighbours.push_back(c);
				}
			}
			if (cell->y+1 < height && cell->x+1 <width)
			{
				auto c = std::make_shared<Cell>(map[cell->y+1][cell->x+1]);
				if(!c->visited){
					neighbours.push_back(c);
				}
				neighbours.push_back(c);
			}
			return neighbours;
		}

		bool divides_two_cooridors(std::shared_ptr<Cell> cell)
		{
			if (cell->x-1>0 && cell->x+1 <width)
			{
				if (!map[cell->y][cell->x-1].is_wall && !map[cell->y][cell->x+1].is_wall)
				{
					return true;
				}
			}

			if (cell->y-1>0 && cell->y+1 <height)
			{
				if (!map[cell->y-1][cell->x].is_wall && !map[cell->y+1][cell->x].is_wall)
				{
					return true;
				}
			}
			return false;
		}

		void print_maze() {
			for(auto const &row: map){
				for(auto const &cell : row){
					if (cell.is_wall){
						std::cout << "x";
					}
				}
				std::cout << "\n";
			}
		}
	private:
		std::vector<std::vector<Cell>> map{{}};
		int height;
		int width;
};

int main() {
	std::cout << "Hello" << std::endl;
	Maze m{10,10};
	m.print_maze();
}
