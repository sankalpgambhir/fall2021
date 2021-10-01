/*
    CS224M
    Assignment 01
    Bridge Simulation
    (Spanning Tree Protocol)
    Sankalp Gambhir - 180260032
*/


// libraries
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

// classes
#include "bridgesim.h"

int main(){
    // init
    std::ostringstream log_buf; // buffer the traces
    Network network(log_buf);

    // read input data
    int output_trace; // print trace?
    std::cin >> output_trace;

    int num_bridges;
    std::cin >> num_bridges;

    Bridge* b = nullptr;

    for(int i = 0; i < num_bridges; ){
        std::string s, t;
        std::getline(std::cin, s);
        std::istringstream iss(s);

        while (iss >> t){

            if(t.back() == ':'){
                // got a new bridge
                b = network.add_bridge( (int) (*(t.end()-2) - '0') );
                i++; continue;
            }

            // new connection for current bridge
            network.add_connection(b, (int) (*(t.end()-1) - 'A'));

            assert(b != nullptr);

        }

    }

    network.sort();

    // call the network simulation
    network.run_stp();

    // return the output
        // print bridge connections directly to stdout
        network.print_connections(std::cout);
        // print trace if asked
        if(output_trace){
            std::cout << log_buf.str();
        }

    return 0;
}
