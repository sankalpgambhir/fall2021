// bridgesim.h
// class definitions for the network

#include <vector>
#include <iostream>
#include <sstream>

#include "bridge.h"

#ifndef BRIDGESIM
#define BRIDGESIM

// network class
class Network{
    public:
        // constructors
        Network(std::ostream&);                     // will write to stream of choice, clog by default
            // no copying
        Network(const Network&) = delete;
        Network& operator=(const Network&) = delete;

        Bridge* add_bridge(int);
        Bridge* get_root(void);

    private:
        // data
        std::vector<Bridge> nodes;

};

#endif
