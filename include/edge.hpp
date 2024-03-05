#ifndef COMPETITIVE_PROGRAMMING_EDGE_HPP
#define COMPETITIVE_PROGRAMMING_EDGE_HPP

class Edge{
public:
    unsigned int u, v;
    long w;

    Edge(unsigned int a, unsigned int b, long c){
        u = a;
        v = b;
        w = c;
    }
};

#endif //COMPETITIVE_PROGRAMMING_EDGE_HPP
