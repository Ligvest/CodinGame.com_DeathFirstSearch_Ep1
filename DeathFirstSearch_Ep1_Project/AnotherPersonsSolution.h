#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

struct Node {
    bool isGateway;
    std::set<int> links;
};

class Nodes : public std::vector<Node> {
public:
    Nodes(int size) : std::vector<Node>(size) {}

    void link(int nodeA, int nodeB) {
        (*this)[nodeA].links.insert(nodeB);
        (*this)[nodeB].links.insert(nodeA);
    }

    void unlink(int nodeA, int nodeB) {
        (*this)[nodeA].links.erase(nodeB);
        (*this)[nodeB].links.erase(nodeA);
    }
};

int main()
{
    int numberOfNodes, numberOfLinks, numberOfGateways;

    std::cin >> numberOfNodes >> numberOfLinks >> numberOfGateways;
    Nodes nodes{ numberOfNodes };

    for (int linkA, linkB, i = 0; i < numberOfLinks; ++i) {
        std::cin >> linkA >> linkB;
        nodes.link(linkA, linkB);
    }

    for (int gatewayNode, i = 0; i < numberOfGateways; ++i) {
        std::cin >> gatewayNode;
        nodes[gatewayNode].isGateway = true;
    }

    for (;;) {
        struct QueueItem {
            int depth;
            int nodeIdx;
        };

        int currentVirusPosition;
        int shortestPath2Gateway = -1;
        std::queue<QueueItem> nodes2search;

        std::cin >> currentVirusPosition;
        nodes2search.emplace(QueueItem{
            .depth = 0,
            .nodeIdx = currentVirusPosition
            });

        while (!nodes2search.empty()) {
            auto current = nodes2search.front();
            nodes2search.pop();

            /*
            * Here we remember last checked node with depth 1 and never change it.
            * So actually we could not search for 2-depth nodes and break right after the last depth-1 nodes.
            * But obviously still check if any of 1-depth nodes is a gateway
            */
            if (1 == current.depth)
                shortestPath2Gateway = current.nodeIdx;

            /*
            * When we find a first gateway it will be the closest one to the agent.
            * So break the link between the Agent and the node linked with it.
            * It will be the link closest to the Agent but it doesn't depend on the location of gateways
            */
            if (nodes[current.nodeIdx].isGateway) {
                nodes.unlink(currentVirusPosition, shortestPath2Gateway);
                nodes2search = {};
                break;
            }

            /*
            * Searching Agent childs until we find a gateway that is the closest to the Agent
            * The search is BFS (Breadth First Search)
            * And in the nodes2search vector nodes of the next level always will be after
            * nodes of previous level ( sorted )
            */
            for (auto childNode : nodes[current.nodeIdx].links)
                nodes2search.emplace(QueueItem{
                    .depth = 1 + current.depth,
                    .nodeIdx = childNode
                    });
        }

        if (-1 != shortestPath2Gateway)
            std::cout << currentVirusPosition << ' ' << shortestPath2Gateway << '\n';
    }
}
