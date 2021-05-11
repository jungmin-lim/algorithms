#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include <vector>

int main(int argc, char* argv[]) {
    std::string filename = "";
    int number_of_streetlight = 0;
    int initial_location = 0;
    
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

    inputfile >> number_of_streetlight;
    inputfile >> initial_location;

    std::vector<int> D(number_of_streetlight+1, 0);
    std::vector<int> WS(number_of_streetlight+1, 0);

    std::vector<std::vector<std::vector<int>>> EE(number_of_streetlight+1, std::vector<std::vector<int>>(number_of_streetlight+1, std::vector<int>(2, 0)));
    std::vector<std::vector<std::vector<int>>> PP(number_of_streetlight+1, std::vector<std::vector<int>>(number_of_streetlight+1, std::vector<int>(2, 0)));

    for(int i = 1; i <= number_of_streetlight; ++i) {
        inputfile >> D[i];
        inputfile >> WS[i];
        WS[i] = WS[i] + WS[i-1];
    }

    int R = number_of_streetlight - 1;
    for(int L = 1; L <= initial_location; ++L) {
        for(; R >= initial_location; --R) {
            int ll = std::numeric_limits<int>::max(), rl = std::numeric_limits<int>::max();
            int lr = std::numeric_limits<int>::max(), rr = std::numeric_limits<int>::max();
            
            if(L > 1) {
                ll = EE[L-1][R][0] + ((D[L] - D[L-1]) * (WS[number_of_streetlight] - WS[R] + WS[L-1]));
                rl = EE[L-1][R][0] + ((D[R] - D[L-1]) * (WS[number_of_streetlight] - WS[R] + WS[L-1]));
            }

            if(R < number_of_streetlight) {
                lr = EE[L][R+1][1] + ((D[R+1] - D[L]) * (WS[number_of_streetlight] - WS[R] + WS[L-1]));
                rr = EE[L][R+1][1] + ((D[R+1] - D[R]) * (WS[number_of_streetlight] - WS[R] + WS[L-1]));
            }

            if(ll < lr) {
                EE[L][R][0] = ll;
                PP[L][R][0] = 0;
            }
            else {
                EE[L][R][0] = lr;
                PP[L][R][0] = 1;
            }

            if(rl < rr) {
                EE[L][R][1] = rl;
                PP[L][R][1] = 0;
            }
            else {
                EE[L][R][1] = rr;
                PP[L][R][1] = 1;
            }
        }
        R = number_of_streetlight;
    }

    if(EE[initial_location][initial_location][0] <= EE[initial_location][initial_location][0]) {
        outputfile << EE[initial_location][initial_location][0] << std::endl;
        int L = initial_location, R = initial_location, prev = 0;
        int loc = initial_location;
        while((L != 1) || (R != number_of_streetlight)) {
            outputfile << loc << std::endl;
            if(!PP[L][R][prev]) {
                if(loc == L) {
                    prev = 0;
                }
                else {
                    prev = 1;
                }
                L = L - 1;
                loc = L;
            }
            else {
                if(loc == L) {
                    prev = 0;
                }
                else {
                    prev = 1;
                }
                R = R + 1;
                loc = R;
            }
        }
        outputfile << loc;
    }
    else {
        outputfile << EE[initial_location][initial_location][1] << std::endl;
        int L = initial_location, R = initial_location, prev = 1;
        int loc = initial_location;
        while((L != 1) || (R != number_of_streetlight)) {
            outputfile << loc << std::endl;
            if(!PP[L][R][prev]) {
                if(loc == L) {
                    prev = 0;
                }
                else {
                    prev = 1;
                }
                L = L - 1;
                loc = L;
            }
            else {
                if(loc == L) {
                    prev = 0;
                }
                else {
                    prev = 1;
                }
                R = R + 1;
                loc = R;
            }
        }
        outputfile << loc;
    }

    inputfile.close();
    outputfile.close();
    return 0;
}