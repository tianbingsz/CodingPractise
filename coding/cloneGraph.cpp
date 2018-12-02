/*
Given the head of a graph, return a deep copy (clone) of the graph. Each node in the graph contains a label (int) and a list (List[UndirectedGraphNode]) of its neighbors. There is an edge between the given node and each of the nodes in its neighbors.


OJ's undirected graph serialization (so you can understand error output):
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.


As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.


Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
Note: The information about the tree serialization is only meant so that you can understand error output if you get a wrong answer. You don't need to understand the serialization to solve the problem.
Solution: BFS + MAP
there might exist circle, which implies some node already copied during BFS expansion,
so we use map to store to avoid duplicated copies.
BFS (root):
    rootCopy = new Graph(root->label)
    map[root->val] = rootCopy
    queue.push(root)
    while(queue not empty):
        get cur = queue.front, queue.pop
        for next in cur->neighbors:
            if not copy for next:
                nextCopy = new Graph(next->label)
                map[next->label] = nextCopy
                queue.push(next) // first visit
            // add nextCopy into curCopy's neighbors
            map[cur->label]->neighbors.push_back(map[next->label])
    return rootCopy
*/
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == nullptr) return nullptr;
        return BFSClone(node);
    }
private:
    unordered_map<int, UndirectedGraphNode*> nodeMap;
    UndirectedGraphNode *BFSClone(UndirectedGraphNode *root) {
        if (root == nullptr) return nullptr;
        auto rootCopy = new UndirectedGraphNode(root->label);
        nodeMap[root->label] = rootCopy;
        queue<UndirectedGraphNode *> q;
        q.push(root);
        while(! q.empty()) { // BFS all nodes
            auto node = q.front();  q.pop();
            for (const auto &next: node->neighbors) {
                if (next == nullptr) continue;
                if (nodeMap.count(next->label) == 0) { // first copy
                    nodeMap[next->label] = new UndirectedGraphNode(next->label);
                    q.push(next); // next candiate
                }
                // either already copied for copy for the first copy
                nodeMap[node->label]->neighbors.push_back(nodeMap[next->label]);
            }
        }
        return rootCopy;
    }
};
