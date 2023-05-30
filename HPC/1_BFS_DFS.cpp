#include<iostream>
#include<omp.h>
#include<queue>
#include<stack>

using namespace std;

class TreeNode{
    public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x){
        val = x;
        left = NULL;
        right = NULL;
    }
};

void pBFS(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int qs = q.size();
        #pragma omp parallel for
        for(int i = 0; i < qs; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                cout << node->val << " ";
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
    }
}

void pDFS(TreeNode* root){
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        int ss = s.size();
        #pragma omp parallel for
        for(int i = 0; i < ss; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                cout << node->val << " ";
                s.pop();
                if(node->left) s.push(node->left);
                if(node->right) s.push(node->right);
            }
        }
    }
}

int main(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3); 
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    cout << "Parallel BFS: ";
    pBFS(root);
    cout<<endl;
    cout << "Parallel DFS: ";
    pDFS(root);
}

// g++ -fopenmp 2_parallel_bubble.cpp -o a.o && ./a.o