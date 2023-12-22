#pragma once
class Grid
{
public:
	static Grid& instance() {
		static Grid inst;
		return inst;
	}

	Grid(const Grid&) = delete;
	Grid& operator=(const Grid&) = delete;
	Grid(Grid&&) = delete;
	Grid& operator=(Grid&&) = delete;

	int** getGrid() { return grid; }
	void setGrid(int** nGrid) { grid = nGrid; }
	void setSquare(int x, int y, int n) { grid[x][y] = n; }

private:
	Grid() {};
	int** grid;
};

