/*
    Game of Primes
    CS 601 Programming Assignment 2
    Sankalp Gambhir
    180260032
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>
#include <map>

typedef std::tuple<int, int, int, int> key;

std::map<key, bool> wins;

bool check_strategy(key f);

int main(){

    int num_inp;

    std::cin >> num_inp;

    // while input is being given, loop and check
    for(int inp = 0; inp < num_inp; inp++){
        // take input
        int n;
        std::vector<int> primes;
        std::vector<int> factors;

        std::cin >> n;

        for(int i = 0; i < n; i++){
            primes.emplace_back();
            std::cin >> primes.back();
        }

        for(int i = 0; i < n; i++){
            factors.emplace_back();
            std::cin >> factors.back();
        }

        int t[] = {0, 0, 0, 0};

        // construct factor list
        for(auto i : factors){
            if(i > 3){
                t[3]++;
            }
            else if(i >= 0){
                t[i]++;
            }
        }

        key f({t[0], t[1], t[2], t[3]});

        // call prime checker
        std::cout << (int) check_strategy(f) << std::endl;
    }

    return 0;
}

bool check_strategy(key f){
    // undetermined?
    if(wins.find(f) == wins.end()){
        // not found, compute
        // base case
        if(std::get<1>(f) == 0 && std::get<2>(f) == 0 && std::get<3>(f) == 0){
            // reduced to 0
            return false;
        }
        // enumerate and return
        bool result = false;

        // remove threes
        if(std::get<3>(f) > 0){
            result |= !check_strategy(key(std::get<0>(f), std::get<1>(f), std::get<2>(f)+1, std::get<3>(f)-1));
            result |= !check_strategy(key(std::get<0>(f), std::get<1>(f)+1, std::get<2>(f), std::get<3>(f)-1));
            result |= !check_strategy(key(std::get<0>(f)+1, std::get<1>(f), std::get<2>(f), std::get<3>(f)-1));
        }

        // remove twos
        if(std::get<2>(f) > 0){
            result |= !check_strategy(key(std::get<0>(f), std::get<1>(f)+1, std::get<2>(f)-1, std::get<3>(f)));
            result |= !check_strategy(key(std::get<0>(f)+1, std::get<1>(f), std::get<2>(f)-1, std::get<3>(f)));
        }

        // remove ones
        if(std::get<1>(f) > 0){
            result |= !check_strategy(key(std::get<0>(f)+1, std::get<1>(f)-1, std::get<2>(f), std::get<3>(f)));
        }

        // save result
        wins[f] = result;

        return result;
    }
    else{
        // return the value
        return wins[f];
    }
}
