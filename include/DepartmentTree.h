// Purpose: ordered general department tree. Author: Codex (AI assistance).
#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H
#include <memory>
#include <string>
#include <vector>
struct DepartmentNode {
    std::string name;
    DepartmentNode* parent;
    std::vector<std::unique_ptr<DepartmentNode>> children;
    // Each node owns its children and borrows its parent pointer.
    DepartmentNode(const std::string& name, DepartmentNode* parent);
};
class DepartmentTree {
    std::unique_ptr<DepartmentNode> root;
    // Search/traverse recursively in sibling insertion order.
    DepartmentNode* findNode(DepartmentNode* node, const std::string& key) const;
    void preorder(const DepartmentNode* node, std::size_t depth, bool indent) const;
public:
    explicit DepartmentTree(const std::string& directory);
    bool empty() const;
    // Empty result means success; otherwise return a rejection reason.
    std::string add(const std::string& name, const std::string& parent);
    void search(const std::string& name) const;
    void displayHierarchy() const;
    void displayPreorder() const;
};
#endif
