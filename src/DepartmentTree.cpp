// Purpose: department insertion, search, preorder. Author: Codex (AI assistance).
#include "../include/DepartmentTree.h"
#include "../include/FileUtils.h"
DepartmentNode::DepartmentNode(const std::string& name, DepartmentNode* parent)
    : name(name), parent(parent) {}
// Parents must be accepted before their children.
DepartmentTree::DepartmentTree(const std::string& directory) {
    Input::load(directory, "departments.txt", [&](const std::vector<std::string>& f) -> std::string {
        if (!Input::validFields(f, 2)) return "expected two nonempty fields";
        return add(f[0], f[1]);
    });
}
DepartmentNode* DepartmentTree::findNode(DepartmentNode* node, const std::string& key) const {
    if (!node) return nullptr;
    if (Input::key(node->name) == key) return node;
    for (const auto& child : node->children)
        if (DepartmentNode* match = findNode(child.get(), key)) return match;
    return nullptr;
}
bool DepartmentTree::empty() const { return !root; }
// Validate before changing the tree; the file and menu share these rules.
std::string DepartmentTree::add(const std::string& input, const std::string& parentName) {
    const std::string name = Input::trim(input);
    if (name.empty()) return "department name cannot be blank";
    if (findNode(root.get(), Input::key(name))) return "duplicate department: " + name;
    if (!root) {
        if (Input::key(parentName) != "NONE") return "first department must use parent NONE";
        root.reset(new DepartmentNode(name, nullptr));
        return "";
    }
    DepartmentNode* parent = findNode(root.get(), Input::key(parentName));
    if (!parent) return "unknown parent: " + Input::trim(parentName);
    parent->children.emplace_back(new DepartmentNode(name, parent));
    return "";
}
// Derive depth from parent links; root depth is zero.
void DepartmentTree::search(const std::string& name) const {
    if (Input::trim(name).empty()) { std::cout << "Department name cannot be blank.\n"; return; }
    const DepartmentNode* node = findNode(root.get(), Input::key(name));
    if (!node) { std::cout << "Department not found: " << Input::trim(name) << '\n'; return; }
    std::size_t depth = 0;
    for (auto ancestor = node->parent; ancestor; ancestor = ancestor->parent) ++depth;
    std::cout << "Department: " << node->name << "\nParent: "
              << (node->parent ? node->parent->name : "None")
              << "\nDirect children: " << node->children.size() << "\nDepth: " << depth << '\n';
}
// Visit the parent before each child; indentation is optional.
void DepartmentTree::preorder(const DepartmentNode* node, std::size_t depth, bool indent) const {
    if (!node) return;
    std::cout << std::string(indent ? depth * 4 : 0, ' ') << node->name << '\n';
    for (const auto& child : node->children) preorder(child.get(), depth + 1, indent);
}
void DepartmentTree::displayHierarchy() const {
    if (!root) std::cout << "No departments available.\n";
    else preorder(root.get(), 0, true);
}
void DepartmentTree::displayPreorder() const {
    if (!root) std::cout << "No departments available.\n";
    else preorder(root.get(), 0, false);
}
