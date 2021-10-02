// bridgesim.cpp
// function definitions for the network

#include "bridgesim.h"

// construction

// constructor
Network::Network(std::ostream& inlog = std::clog) 
                : log (inlog){

    // initialise nodes
    for(int i = 0; i < 26; i++){
        nodes.emplace_back(i);
    }

    return;
}

// access and modification

// add a new bridge to network
Bridge* Network::add_bridge(int id){
    bridges.emplace_back(id, &log);
    return &(bridges.back());
}

Node* Network::get_node(int id){
    return &(nodes.at(id));
}

void Network::add_connection(Bridge* b, int node_id){
    auto* n = this->get_node(node_id);
    b->add_connection(n);
    n->add_connection(b);

    return;
}

// output and control

// sort individual bridges
void Network::sort(){
    for(auto &b: bridges){
        b.sort();
    }

    // sort all bridges
    std::sort(bridges.begin(), bridges.end(), [](const Bridge& a, const Bridge& b){
                                                    return a.get_id() < b.get_id();
                                                });

    // nodes were generated sorted

    return;
}

// run actual STP algorithm
void Network::run_stp(){

    // set universal time
    Bridge::currtime = 0;
    for(auto &b : bridges){
        b.broadcast_root();
    }
    Bridge::currtime++;

    while(!check_same_root()){
        for(auto i = bridges.rbegin(); i < bridges.rend(); i++){
            i->process_buffer();
        }
        Bridge::currtime++;
    }
    // run once more for NP
    for(auto i = bridges.rbegin(); i < bridges.rend(); i++){
        i->process_buffer();
    }
    Bridge::currtime++;

    return;
}

bool Network::check_same_root(){
    bool same = true;

    int root = bridges.front().get_root();

    for(auto &b : bridges){
        if(b.get_root() != root){
            same = false;
            break;
        }
    }

    return same;
}

void Network::print_connections(std::ostream& out){

    for(auto &b: bridges){
        out << b.print_connections() << std::endl;
    }

    return;
}
