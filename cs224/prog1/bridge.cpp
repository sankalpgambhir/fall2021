// bridge.cpp
// function definitions for the bridge

#include "bridge.h"

// Node functions

Node::Node(int inp_id) : id(inp_id){
    return;
}

int Node::get_id() const {
    return this->id;
}

void Node::add_connection(Bridge* b){
    this->connections.push_back(b);
}

void Node::broadcast(Message m, int sender){

    for(auto b : connections){
        if(b->get_id() != sender){
            b->message(m, this->id);
        }
    }

    return;
}

// Bridge functions

const std::string Bridge::statuses[] = {"DP", "RP", "NP"};
int Bridge::currtime = 0;

Bridge::Bridge(int inp_id, std::ostream* inplog) : id(inp_id), log(inplog){
    root = id; // identify self as root
    distance_to_root = 0;
    sender_to_root = id;

    return;
}

int Bridge::get_id() const {
    return this->id;
}

int Bridge::get_root() const {
    return this->root;
}

void Bridge::add_connection(Node* n){
    this->connections.push_back(std::pair<Node*, state>(n, state::DP));
}

void Bridge::message(Message m, int incoming_node){
    this->message_buffer.push_back(std::tuple<Message, int, int>(m, incoming_node, Bridge::currtime+LINKTIME));
}

void Bridge::broadcast(Message m, int incoming_node){

    bool sent = false;

    for(auto &c : connections){
        if(c.second == state::NP){
            continue;
        }
        else{
            // this is an active port, broadcast 
            if(c.first->get_id() != incoming_node){
                sent = true;
                c.first->broadcast(m, this->get_id());
            }
        }
    }

    if(sent){
        std::string s = std::to_string(Bridge::currtime) + " s B" + std::to_string(this->get_id()) + m.string();    
        *log << s << std::endl;
    }

}

void Bridge::broadcast_root(){
    assert(id == root);

    this->broadcast(Message(this->id, 0, this->root), -1);
}

void Bridge::process_buffer(){

    // read through received messages
    for(auto i = message_buffer.rbegin(); i < message_buffer.rend(); i++){
        auto &p = *i;

        if(std::get<2>(p) > currtime){
            // message is "in transit"
            continue;
        }

        auto m = std::get<0>(p);
        auto port = std::get<1>(p);

        // log msg
        std::string s = std::to_string(Bridge::currtime) + " r B" + std::to_string(this->get_id()) + m.string();

        *log << s << std::endl;

        // is the message worth broadcasting?
        if (m.root <= get_root()){
            bool cutline = false;

            // better root discovered?
            if(m.root < get_root()){
                this->update_root(m, port);
            }
            else{
                // shorter path discovered?
                if((m.distance+1) < distance_to_root){
                    this->update_root(m, port);
                }
                // better sender discovered?
                else if(distance_to_root == (m.distance+1) && m.sender < sender_to_root){
                    this->update_root(m, port);
                }
                else{
                    // nothing changed
                    // = root, => distance, => sender
                    // this is either root port or loop
                    // if loop, cut
                    for(auto &c : connections){
                        if(c.second != state::RP && c.first->get_id() == port && get_id() > m.sender){
                            c.second = state::NP;
                            break;
                        }
                    }
                }
            }

            // is this a cut line?
            for(auto &c : connections){
                if(c.first->get_id() == port && c.second == state::NP){
                    cutline = true;
                    break;
                }
            }

            if(!cutline){
                // broadcast
                m.increment();
                m.sender = get_id();
                this->broadcast(m, port);
            }
        }
    }

    // remove processed messages
    while(!message_buffer.empty()){
        if(std::get<2>(message_buffer.front()) > currtime){
            break;
        }
        else{
            message_buffer.erase(message_buffer.begin());
        }
    }


    // if nothing better than self was found
    if(get_id() == get_root()){
        broadcast_root();
    }
}

void Bridge::update_root(Message &m, int port){
    // update root with the bridge indicated in m received from node 'port'
    this->root = m.root;
    this->port_to_root = port;
    this->sender_to_root = m.sender;
    this->distance_to_root = m.distance + 1;

    for(auto &c : connections){
        if(c.second == state::RP){
            c.second = state::DP;
        }
        if(c.first->get_id() == port){
            c.second = state::RP;
        }
    }
}

void Bridge::sort(){
    std::sort(connections.begin(), connections.end(), [](const std::pair<Node*, state>& a, const std::pair<Node*, state>& b){
                                                            return a.first->get_id() < b.first->get_id();
                                                        });
}

std::string Bridge::print_connections(){
    std::string s = "B" + std::to_string(id) + ":";

    for(auto &c : connections){
        s += " " + std::string(1, (char)(c.first->get_id() + 'A')) + "-" + Bridge::statuses[c.second];
    }

    return s;
}