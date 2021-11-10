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
#include <algorithm>

typedef std::vector<int> key;

std::map<key, bool> wins;

bool check_strategy(key &f);

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

        std::sort(factors.begin(), factors.end());

        // call prime checker
        std::cout << (int) check_strategy(factors) << std::endl;
    }

    return 0;
}

bool check_strategy(key &f){
    // undetermined?
    // for(int i = 0; i < f.size(); i++){
    //     std::cout << f[i];
    // }
    // std::cout << std::endl;
    if(wins.find(f) == wins.end()){
        // not found, compute
        // base case
        if(f.back() == 0){
            return false;
        }
        // recurse

        bool result = false;

        for(int i = 0; i < f.size(); i++){
            if(f[i] > 0){
                key g = f;
                g[i]--;
                std::sort(g.begin(), g.end());
                result |= !check_strategy(g);

                if(result) break;
            }

        }

        wins[f] = result; 

        return result;
    }
    else{
        // return the value
        return wins[f];
    }
}
