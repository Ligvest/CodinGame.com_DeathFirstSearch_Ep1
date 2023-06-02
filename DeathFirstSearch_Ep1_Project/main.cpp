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

LinkedPair getLinkToBreak(std::vector<LinkedPair>& links, const std::vector<int>& gateways) {
    int linksCurrentPos = 0;
    for (auto [LeftNode, RightNode] : links) {
        for (int Gateway : gateways) {
            std::cerr << LeftNode << '-' << RightNode << ";\n";
            if ((LeftNode == Gateway) || (RightNode == Gateway)) {
                links.erase(links.begin() + linksCurrentPos);
                return LinkedPair{ LeftNode, RightNode };
            }
        }
        ++linksCurrentPos;
    }

    return LinkedPair{ 0, 0 };
}

int main()
{

    std::vector<LinkedPair> links;
    std::vector<int> gateways;
    int n; // the total number of nodes in the level, including the gateways
    int l; // the number of links
    int e; // the number of exit gateways
    cin >> n >> l >> e; cin.ignore();
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


        auto [LeftNode, RightNode] = getLinkToBreak(links, gateways);


        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // Example: LeftNode and RightNode are the indices of the nodes you wish to sever the link between
        std::cout << LeftNode << ' ' << RightNode << std::endl;
    }
}