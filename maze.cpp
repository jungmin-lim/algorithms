#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

int in_range(int y, int x, int size) {
    if((0 < y) && (y <= size) && (0 < x) && (x <= size)) {
        return 1;
    }
    return 0;
}

void print_path(std::ofstream& outputfile, std::vector<std::vector<int>> touch, int y, int x) {
    int dy[4] = { 0, 1, 0, -1 };
    int dx[4] = { 1, 0, -1, 0 };

    if(touch[y][x] < 0) {
        outputfile << y << " " << x << std::endl;
        return;
    }

    print_path(outputfile, touch, y-dy[touch[y][x]], x-dx[touch[y][x]]);
    outputfile << y << " " << x << std::endl;

    return;
}

void solve(std::ofstream& outputfile, std::vector<std::string> maze, int size) {
    std::vector<std::vector<int>> length(size+1, std::vector<int>(size+1, std::numeric_limits<int>::max()));
    length[1][1] = 0;
    std::vector<std::vector<int>> touch(size+1, std::vector<int>(size+1, 0));
    touch[1][1] = -1;

    int dy[4] = { 0, 1, 0, -1 };
    int dx[4] = { 1, 0, -1, 0 };

    std::priority_queue<std::pair<int, std::pair<int, int>>> queue;
    queue.emplace(0, std::pair<int, int>(1, 1));

    while(!queue.empty()) {
        int cur_length = -queue.top().first;
        std::pair<int, int> cur_loc = queue.top().second;
        queue.pop();

        for(int i = 0; i < 4; ++i) {
            int y_cor = cur_loc.first + dy[i];
            int x_cor = cur_loc.second + dx[i];

            if(in_range(y_cor, x_cor, size)) {
                if((maze[y_cor-1][x_cor-1] == '0') && (length[y_cor][x_cor] > cur_length + 1)) {
                    length[y_cor][x_cor] = cur_length + 1;
                    touch[y_cor][x_cor] = i;
                    queue.emplace(-length[y_cor][x_cor], std::pair<int, int>(y_cor, x_cor));
                }

                if((maze[y_cor-1][x_cor-1] == '1') && (length[y_cor][x_cor] > cur_length)) {
                    length[y_cor][x_cor] = cur_length;
                    touch[y_cor][x_cor] = i;
                    queue.emplace(-length[y_cor][x_cor], std::pair<int, int>(y_cor, x_cor));
                }
            }
        }
    }

    outputfile << length[size][size] << std::endl;
    print_path(outputfile, touch, size, size);
}

int main(int argc, char *argv[]) {
    std::string filename = "";
    int size = 0;
    
    std::cout << "input file name? ";
    std::cin >> filename;

    std::ifstream inputfile(filename);
    std::ofstream outputfile("output.txt");

    if(!inputfile.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
        return EXIT_FAILURE;
    }
    if(!outputfile.is_open()) {
        std::cerr << "Could not open file output.txt" << std::endl;
        return EXIT_FAILURE;
    }

    inputfile >> size;
    std::vector<std::string> maze(size+1, "");
    for(int i = 0; i < size; ++i) {
        inputfile >> maze[i];
    }

    solve(outputfile, maze, size);
    return 0; 
}