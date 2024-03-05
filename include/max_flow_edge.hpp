#ifndef COMPETITIVE_PROGRAMMING_MAX_FLOW_EDGE_H
#define COMPETITIVE_PROGRAMMING_MAX_FLOW_EDGE_H

class MaxFlowEdge {
public:
    int flow, capacity;
    unsigned int u, v;

    inline MaxFlowEdge(unsigned int a, unsigned int b, int c) {
        u = a;
        v = b;
        capacity = c;
        flow = 0;
    }
    [[nodiscard]] bool isResidual() const { return capacity == 0; }
};

#endif //COMPETITIVE_PROGRAMMING_MAX_FLOW_EDGE_H
