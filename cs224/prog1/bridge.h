// bridge.h
// class definitions for the bridge

#include <vector>
#include <utility>
#include <string>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <tuple>

#ifndef BRIDGE
#define BRIDGE

#define LINKTIME 1

enum state{DP, RP, NP};

// forward declaration
class Bridge;

// message class
struct Message{

    Message(int s, int d, int r) : sender(s), distance(d), root(r){
        return;
    }

    int sender;
    int distance;
    int root;

    void increment(){
        this->distance++;
    }

    std::string string(){
        return ("(" + std::to_string(sender) + "," + std::to_string(distance) + "," + std::to_string(root) + ")");
    }
};

// port class
class Node{
    public:
        // constructors
        Node(int);
            // no copying or empty constr
        Node() = delete;

        // functions
        int get_id() const;                             // return id
        void add_connection(Bridge*);                   // make a new connection
        void broadcast(Message, int);                   // broadcast to all but the sender

    private:
        // data
        int id;
        std::vector<Bridge*> connections;
};

// bridge class
class Bridge{
    public:
        // constructors
        Bridge(int, std::ostream*);
            // no copying or empty id
        Bridge() = delete;

        // access and modify
        int get_id(void) const;                         // your id
        int get_root(void) const;                       // who do you think is the root?
        void add_connection(Node*);                     // make a new connection
        void message(Message, int);                     // receive and buffer a message
        void broadcast(Message, int);                   // send/forward a message
        void broadcast_root();                          // send a message claiming root position
        void process_buffer();                          // process own message buffer
        void update_root(Message&, int);                // update current root
        
        // output and control
        void sort();                                    // sort nodes
        std::string print_connections();                // prints its connections

        static int currtime;

    private:
        // actual data
        static const std::string statuses[];
        std::vector<std::pair<Node*, state> > connections;
        std::vector<std::tuple<Message, int, int> > message_buffer;
        std::ostream* log;
        int root;
        int distance_to_root;
        int port_to_root;
        int sender_to_root;
        int id;
};

#endif
