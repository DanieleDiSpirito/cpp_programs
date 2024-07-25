#include "simulation.hpp"

int mod(int n, int d) {
    return (n % d >= 0) ? n % d : (n % d) + d;
}

void Simulation::Draw() {
    grid.Draw();
}

void Simulation::setCellValue(int row, int column, int value) {
    grid.setValue(row, column, value);
}

int Simulation::countLiveNeighbors(int row, int column) {
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neightbotOffsets = {
        {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}
    };
    for(const auto& offset: neightbotOffsets) {
        int neighborRow = mod((row + offset.first), grid.getRows());
        int neighborColumn = mod((column + offset.second), grid.getColumns());
        if(grid.getValue(neighborRow, neighborColumn) > 0) {
            liveNeighbors++;
        }
    }
    return liveNeighbors;
}

void Simulation::Update() {
    for(int row = 0; row < grid.getRows(); row++) {
        for(int column = 0; column < grid.getColumns(); column++) {
            int liveNeighbors = countLiveNeighbors(row, column);
            int cellValue = grid.getValue(row, column);
            if(cellValue > 0) {
                if(liveNeighbors > 3 || liveNeighbors < 2) tempGrid.setValue(row, column, 0);
                else tempGrid.setValue(row, column, 1);
            } else {
                if(liveNeighbors == 3) tempGrid.setValue(row, column, 1);
                else tempGrid.setValue(row, column, 0);
            }
        }
    }
    grid = tempGrid;
}

void Simulation::ClearGrid() {
    if(!isRunning()) grid.Clear();
}

void Simulation::CreateRandomState() {
    if(!isRunning()) grid.FillRandom();
}

void Simulation::ToggleCell(int row, int column) {
    if(!isRunning()) grid.ToggleCell(row, column);
}