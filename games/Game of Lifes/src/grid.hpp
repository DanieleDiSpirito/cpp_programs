#pragma once
#include <vector>

class Grid {
    public:
        Grid(int width, int height, int cellSize):
            rows(height/cellSize),
            columns(width/cellSize),
            cellSize(cellSize),
            cells(rows, std::vector<int>(columns, 0)) {};
        void Draw();
        bool isWithinBounds(int row, int column);
        void setValue(int row, int column, int value);
        int getValue(int row, int column);
        int getRows()       { return rows;      }
        int getColumns()    { return columns;   }
        void FillRandom();
        void Clear();
        void ToggleCell(int row, int column);
    private:
        int rows;
        int columns;
        int cellSize;
        std::vector<std::vector<int>> cells;
};