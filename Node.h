#pragma once
//Node.h
//Matt Grant
//Simple node implementation
//9 May 2016

class Node {
public:
    Node(int id);
    int id() const;
private:
    const int _id;
};

Node::Node(int id) : _id(id) {

}

int Node::id() const {
    return _id;
}