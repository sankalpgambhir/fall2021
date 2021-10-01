// bridge.h
// class definitions for the bridge

#include <vector>

#ifndef BRIDGE
#define BRIDGE

// port class
class Port{
    public:
        // constructors
        Port(Bridge*);
            // no copying or empty constr
        Port() = delete;
        Port(const Port&) = delete;
        Port& operator=(const Port&) = delete;

    private:
        // data
        Bridge* owner;
        Port* opposite;
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

        // access
            /*
                TODO
                what to access?
                index, port connections, status of each port?
            */

        // modify

    private:
        // actual data
        std::vector<Port> ports;
};

#endif
