#include <iostream>
#include <tuple>
#include <map>



struct factorset{
    int zero;
    int one;
    int two;
    int three;

    factorset(int z, int o, int t, int tp) : zero(z), one(o), two(t), three(tp){
        return;
    }

    int operator[](int pos){
        switch (pos)
        {
        case 0:
            return this->zero;
        case 1:
            return this->one;
        case 2:
            return this->two;
        case 3:
            return this->three;
        default:
            //assert(false);
            break;
        }
    }
};


typedef std::tuple<int, int, int, int> key;

std::map<key, bool> wins;

int main(){

    wins[{1, 1, 1, 1}] = false;
    wins[{1, 1, 1, 2}] = true;

    key a({1, 2, 3, 4});

    std::cout << wins[{1, 1, 1, 1}] << wins[{1, 1, 1, 2}] << std::get(a)<3>;
    return 0;
}