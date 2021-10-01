// bridge.cpp
// function definitions for the bridge

#include "bridge.h"

Node::Node(int inp_id) : id(inp_id){
    return;
}

void Node::broadcast(int sender, Message m){

    for(auto b : connections){
        if(b->get_id() != sender){
            b->message(m);
        }
    }

    return;
}