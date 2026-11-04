#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <string>
#include <vector>

using namespace std;

struct DepartmentNode {
    string name;
    DepartmentNode* parent;
    vector<DepartmentNode*> children;
};

class DepartmentTree {
public:
    DepartmentTree();
    ~DepartmentTree();

    bool empty() const;
    bool addDepartment(const string& name, const string& parentName);
    DepartmentNode* findDepartment(const string& name) const;
    DepartmentNode* root() const;
    int depthOf(const string& name) const;
    void displayHierarchy() const;
    void preorderTraversal() const;

private:
    DepartmentNode* root_;

    void deleteTree(DepartmentNode* node);
    void displayHierarchy(const DepartmentNode* node, int depth) const;
    void preorderTraversal(const DepartmentNode* node, bool& firstPrinted) const;
    static string trim(const string& text);
    static bool equalIgnoreCase(const string& lhs, const string& rhs);
};

#endif
