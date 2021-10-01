// bridge.h
// class definitions for the bridge

#include <vector>
#include <utility>

#ifndef BRIDGE
#define BRIDGE

enum state{DP, RP, NP};

// forward declaration
class Bridge;

// message class
struct Message{
    int sender;
    int distance;
    int root;

    void increment(){
        this->distance++;
    }
};

// port class
class Node{
    public:
        // constructors
        Node(int);
            // no copying or empty constr
        Node() = delete;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;

        // functions
        void add_connection(Bridge*);                     // make a new connection
        void broadcast(int, Message);                   // broadcast to all but the sender

    private:
        // data
        int id;
        std::vector<Bridge*> connections;
};

// bridge class
class Bridge{
    public:
        // constructors
        Bridge(int);
            // no copying or empty id
        Bridge() = delete;
        Bridge(const Bridge&) = delete;
        Bridge& operator=(const Bridge&) = delete;

        // access and modify
            /*
                TODO
                what to access?
                index, port connections, status of each port?
            */
        int get_id(void);                               // your id
        int get_root(void);                             // who do you think is the root?
        void add_connection(Node*);                     // make a new connection
        void message(Message);                          // receive and buffer a message
        void broadcast(Message);                        // send/forward a message
        void broadcast_root();                          // send a message claiming root position
        
        // output and control
        void sort();                                    // sort nodes
        std::string print_connections();                // prints its connections

    private:
        // actual data
        std::vector<std::pair<Node*, state> > connections;
        int root;
        int distance_to_root;
        int id;
};

#endif
