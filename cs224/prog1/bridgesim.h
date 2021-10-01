// bridgesim.h
// class definitions for the network

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

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

        // access and modify
        Bridge* add_bridge(int);                    // add new bridge to network
        Node* get_node(int);                        // return node pointer for access
        void add_connection(Bridge*, int);          // add a connection between node and bridge

        // output and control
        void sort(void);                            // sort bridges and nodes
        void run_stp(void);                         // run the spanning tree simulation
        void print_connections(std::ostream&);      // print connection status to given stream


    private:
        // data
        std::ostream& log;
        std::vector<Bridge> bridges;
        std::vector<Node> nodes;

};

#endif
