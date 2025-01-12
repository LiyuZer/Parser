#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <sstream> // For stringstream

#pragma once
/*
GPT was instrumental in getting this dot helper function done, an existential crisis disguised as a transformer. 
Some key points: the ParseNode has a children's unordered map, which contains the children of the current node 
and mappings to ParseNodes as one rule or token might have multiple occurrences, we store them in a vector)
*/
using namespace std;

class ParseNode {
private:
    string type;
    string value;
    bool is_dynamic;
    // Using a map where the key is the child node type, and the value is a vector of child nodes
    unordered_map<string, vector<shared_ptr<ParseNode> > > children;

public:
    ParseNode(string type, string value, bool is_dynamic = false) : type(type), value(value), is_dynamic(is_dynamic) {}

    void addChildren(string next_node_type, shared_ptr<ParseNode> next_node) {

        if (children.find(next_node_type) != children.end()) {
            children[next_node_type].push_back(next_node);
        }
        else {// If the key does not exist, then we create a new vector and add the node to the vector
        
            children[next_node_type] = {next_node};
        }
    }

    bool addChildrenVec(string child, vector<shared_ptr<ParseNode> >& vec) {

        if(children.find(child) != children.end()){
            vec = children[child];
            return true;
        }

        return false;
    }
    vector<shared_ptr<ParseNode> > findChildren(string child) {
        vector<shared_ptr<ParseNode> > vec;     

        if(children.find(child) != children.end()){
            vec = children[child];
            return vec;
        }

        return vec;
    }
    vector<shared_ptr<ParseNode> > find_only_child() {
        // If there is only one child
        vector<shared_ptr<ParseNode> > vec;     

        for(auto child : children){
            return child.second;// This is such a bad method for doing this but here we are
        }
    }
    shared_ptr<ParseNode> copy() const {
        // Create a new ParseNode with the same type, value, and is_dynamic flag
        auto new_node = make_shared<ParseNode>(type, value, is_dynamic);

        // Add the same children (shallow copy)
        for (const auto& [child_type, child_nodes] : children) {
            new_node->children[child_type] = child_nodes;
        }

        return new_node;
    }
    string getType() const {
        return type;
    }

    string getValue() const {
        return value;
    }

    // **Function to Print the Parse Tree**
    void printParseTree(int depth = 0) const {
        // Print indentation based on depth
        for (int i = 0; i < depth; ++i) cout << "  ";
        // Print current node type and value
        cout << "(" << type;
        if (!value.empty()) cout << ": " << value;
        cout << ")" << endl;

        // Recursively print all children
        for (const auto& [child_type, child_nodes] : children) {
            for (const auto& child : child_nodes) {
                child->printParseTree(depth + 1);
            }
        }
    }

    // **Function to Convert the Parse Tree to DOT Format and Save to a File**
    // Usage:
    // root->toDot("parse_tree.dot");
    void toDot(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Error: Unable to open file " << filename << " for writing." << endl;
            return;
        }

        outFile << "digraph ParseTree {" << endl;
        outFile << "    node [shape=box];" << endl;

        int node_id = 0; // Unique identifier for each node
        toDotHelper(outFile, node_id, -1, ""); // -1 indicates no parent for the root
 
        outFile << "}" << endl;
        outFile.close();

        cout << "Parse tree DOT file generated: " << filename << endl;
    }

    // **Function to Collapse Dynamic Nodes**
    void collapseDynamicNodes() {
        collapseDynamicNodesHelper(*this);
    }

private:
    // Helper function for toDot
    // parent_id: The unique ID of the parent node. -1 if current node is root.
    // edge_label: Label for the edge connecting to the parent.
    // Returns the unique ID of the current node.
    int toDotHelper(ostream& out, int& current_id, int parent_id, const string& edge_label) const {
        int my_id = current_id++;
        // Create a label for the current node
        string label = type;
        if (!value.empty()) {
            label += ": " + value;
        }
        // Escape quotes in labels
        size_t pos = 0;
        while ((pos = label.find('"', pos)) != string::npos) {
            label.replace(pos, 1, "\\\"");
            pos += 2;
        }

        out << "    node" << my_id << " [label=\"" << label << "\"];" << endl;

        // If there's a parent, create an edge from parent to current node
        if (parent_id != -1) {
            out << "    node" << parent_id << " -> node" << my_id;
            if (!edge_label.empty()) {
                out << " [label=\"" << edge_label << "\"]";
            }
            out << ";" << endl;
        }

        // Iterate over all children and give each child its own node and edge
        for (const auto& [child_type, child_nodes] : children) {
            for (size_t i = 0; i < child_nodes.size(); ++i) {
                const auto& child = child_nodes[i];
                // Create an indexed edge label for clarity (e.g., "child1", "child2", ...)
                string indexed_label = child_type + "[" + to_string(i + 1) + "]";
                child->toDotHelper(out, current_id, my_id, indexed_label);
            }
        }

        return my_id;
    }
    // **Helper function to recursively collapse dynamic nodes**
    void collapseDynamicNodesHelper(ParseNode& parent) {
        // Iterate over each entry in the children map
        for (auto it = parent.children.begin(); it != parent.children.end(); ) {
            auto& child_vector = it->second;

            // Iterate over the vector of child nodes
            for (auto child_it = child_vector.begin(); child_it != child_vector.end(); ) {
                auto child = *child_it;

                if (child->is_dynamic) {
                    // If the child is dynamic, we need to collapse it
                    // First, recursively collapse its children
                    child->collapseDynamicNodesHelper(*child);

                    // Iterate over the dynamic child's children and promote them
                    for (const auto& [grandchild_type, grandchild_nodes] : child->children) {
                        for (const auto& grandchild : grandchild_nodes) {
                            // Add grandchild to the current parent under the appropriate type
                            parent.addChildren(grandchild_type, grandchild);
                        }
                    }

                    // Remove the dynamic child from the current parent's children
                    child_it = child_vector.erase(child_it);
                }
                else {
                    // If the child is not dynamic, recurse on it
                    child->collapseDynamicNodesHelper(*child);
                    ++child_it;
                }
            }

            // If the current type has no more children, erase the key from the map
            if (it->second.empty()) {
                it = parent.children.erase(it);
            }
            else {
                ++it;
            }
        }
    }
};
