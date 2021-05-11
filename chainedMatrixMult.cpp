#include <iostream>
#include <fstream>
#include <string>
#include <limits>

int min_mult(int inputnumber, int *d, int **p);
void print_order(std::ofstream& outputfile, int **p, int i, int j);
void print_array(int inputnumber, int ** M, int **p);

int main(int argc, char *argv[]) {
    std::string filename = "";
    int inputnumber = 0, result = 0;
    int *d, **p;

    std::cout << "input file name? ";
    std::cin >> filename;

    std::ifstream inputfile (filename);
    std::ofstream outputfile ("output.txt");

    if(!inputfile.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
        return EXIT_FAILURE;
    }
    if(!outputfile.is_open()) {
        std::cerr << "Could not open file output.txt" << std::endl;
        return EXIT_FAILURE;
    }

    inputfile >> inputnumber;
    d = new int[inputnumber];
    p = new int*[inputnumber];
    for(int i = 0; i < inputnumber; ++i) {
        p[i] = new int[inputnumber];
    }

    for(int i = 0; i < inputnumber; ++i) {
        inputfile >> d[i];
    }

    result = min_mult(inputnumber, d, p);
    print_order(outputfile, p, 1, inputnumber-1);

    for(int i = 0; i < inputnumber; ++i) {
        delete [] p[i];
    }
    delete [] p;
    delete [] d;

    inputfile.close();
    outputfile.close();

    return 0;
}

int min_mult(int inputnumber, int *d, int **p) {
    int result = 0;
    int **M = new int*[inputnumber];
    
    for(int i = 0; i < inputnumber; ++i) {
        M[i] = new int[inputnumber];
    }

    for(int i = 1; i < inputnumber; ++i) {
        M[i][i] = 0;
    }

    for(int i = 1; i < inputnumber-1; ++i) {
        for(int j = 1; j < inputnumber - i; ++j) {
            M[j][j+i] = std::numeric_limits<int>::max();
            for(int k = j; k < j+i; ++k) {
                int temp = M[j][k] + M[k+1][j+i] + (d[j-1]*d[k]*d[j+i]);
                
                if(temp < M[j][j+i]) {
                    M[j][j+i] = temp;
                    p[j][j+i] = k;
                }
            }
        }
    }

    result = M[1][inputnumber-1];

    for(int i = 0; i < inputnumber; ++i) {
        delete [] M[i];
    }
    delete [] M;

    return result;
}

void print_order(std::ofstream& outputfile, int **p, int i, int j) {
    int k;
    if(i == j) {
        outputfile << i << ' ';
        return;
    }

    k = p[i][j];
    outputfile << "( ";
    print_order(outputfile, p, i, k);
    print_order(outputfile, p, k+1, j);
    outputfile << ") ";

    return;
}

void print_array(int inputnumber, int ** M, int **p) {
    for(int i = 1; i < inputnumber; ++i) {
        for(int j = 1; j < inputnumber; ++j) {
            std::cout << M[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << "__________________" << std::endl;
    for(int i = 1; i < inputnumber; ++i) {
        for(int j = 1; j < inputnumber; ++j) {
            std::cout << p[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << "__________________" << std::endl;
}