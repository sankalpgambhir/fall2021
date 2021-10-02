// bridgesim.h
// class definitions for the network

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <deque>

#include "bridge.h"

#ifndef BRIDGESIM
#define BRIDGESIM

// network class
class Network{
    public:
        // constructors
        Network(std::ostream&);                     // will write to streams of choice, clog/cout by default
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
        bool check_same_root(void);                 // check if all bridges settled on same root
        void print_connections(std::ostream&);      // print connection status to given stream


    private:
        // data
        std::ostream& log;
        std::deque<Bridge> bridges;
        std::deque<Node> nodes;

};

#endif
