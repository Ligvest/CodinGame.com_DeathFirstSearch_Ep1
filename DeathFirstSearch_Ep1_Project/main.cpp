#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
using LinkedPair = std::pair<int, int>;
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


std::vector<int> GetDistancesBetweenNodesAndAgent(std::vector<LinkedPair>& links, int AgentPos, int NumberOfNodes) {
    std::vector<int> NodeNumberToDistanceToAgent(NumberOfNodes);

    std::cerr << "All distances:\n";
    for (int i = 0; i < links.size(); ++i) {
        for (auto it = links.begin(); it != links.end(); ++it) {
            auto [LeftNode, RightNode] = *it;

            if (LeftNode == AgentPos) {
                NodeNumberToDistanceToAgent[RightNode] = 1;
            }
            else if (RightNode == AgentPos) {
                NodeNumberToDistanceToAgent[LeftNode] = 1;
            }

            if (NodeNumberToDistanceToAgent[LeftNode] > 0) {
                if (NodeNumberToDistanceToAgent[RightNode] == 0) {
                    NodeNumberToDistanceToAgent[RightNode] = NodeNumberToDistanceToAgent[LeftNode] + 1;
                }
            }
            else if (NodeNumberToDistanceToAgent[RightNode] > 0) {
                if (NodeNumberToDistanceToAgent[LeftNode] == 0) {
                    NodeNumberToDistanceToAgent[LeftNode] = NodeNumberToDistanceToAgent[RightNode] + 1;
                }
            }
        }
    }

    NodeNumberToDistanceToAgent[AgentPos] = 0;
    return NodeNumberToDistanceToAgent;
}

LinkedPair getLinkToBreak(std::vector<LinkedPair>& links, int AgentPos, int NumberOfNodes, std::vector<int>& gateways) {
    std::vector<int> NodeNumberToDistanceToAgent = GetDistancesBetweenNodesAndAgent(links, AgentPos, NumberOfNodes);
    int ClosestToAgentNodeLinkedWithGateway = 501; // The maximum index of the node is 500 so 501 we consider as infinity
    int DistanceFromNodeToAgent = 501;

    LinkedPair LinkToBreak = *links.begin();
    auto IterLinkToRemove = links.begin();
    for (int GatewayPos : gateways) {
        for (auto it = links.begin(); it != links.end(); ++it) {
            auto [LeftNode, RightNode] = *it;

            if (LeftNode == GatewayPos) {
                if (NodeNumberToDistanceToAgent[RightNode] < DistanceFromNodeToAgent) {
                    ClosestToAgentNodeLinkedWithGateway = RightNode;
                    DistanceFromNodeToAgent = NodeNumberToDistanceToAgent[RightNode];
                    auto& [LeftNodeToBreak, RightNodeToBreak] = LinkToBreak;
                    LeftNodeToBreak = LeftNode;
                    RightNodeToBreak = RightNode;
                    IterLinkToRemove = it;
                }
            }

            if (RightNode == GatewayPos) {
                if (NodeNumberToDistanceToAgent[LeftNode] < DistanceFromNodeToAgent) {
                    ClosestToAgentNodeLinkedWithGateway = LeftNode;
                    DistanceFromNodeToAgent = NodeNumberToDistanceToAgent[LeftNode];
                    auto& [LeftNodeToBreak, RightNodeToBreak] = LinkToBreak;
                    LeftNodeToBreak = LeftNode;
                    RightNodeToBreak = RightNode;
                    IterLinkToRemove = it;
                }
            }
        }
    }

    links.erase(IterLinkToRemove);
    return LinkToBreak;
}

int main()
{
    int n; // the total number of nodes in the level, including the gateways
    int l; // the number of links
    int e; // the number of exit gateways
    cin >> n >> l >> e; cin.ignore();

    std::vector<LinkedPair> links;
    links.reserve(l);

    std::vector<int> gateways;
    gateways.reserve(e);

    for (int i = 0; i < l; i++) {
        int n1; // N1 and N2 defines a link between these nodes
        int n2;
        cin >> n1 >> n2; cin.ignore();
        links.emplace_back(n1, n2);
        //std::cerr << n1 << '-' << n2 << ";\n";
    }
    for (int i = 0; i < e; i++) {
        int ei; // the index of a gateway node
        cin >> ei; cin.ignore();
        gateways.emplace_back(ei);
    }

    // game loop
    while (1) {
        int BobnetAgentPos; // The index of the node on which the Bobnet agent is positioned this turn
        cin >> BobnetAgentPos; cin.ignore();

        auto [LeftNode, RightNode] = getLinkToBreak(links, BobnetAgentPos, n, gateways);

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // Example: LeftNode and RightNode are the indices of the nodes you wish to sever the link between
        std::cout << LeftNode << ' ' << RightNode << std::endl;
    }
}



