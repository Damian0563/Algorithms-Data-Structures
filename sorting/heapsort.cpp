#include <iostream>
#include <vector>

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(const int data,Node* l=nullptr,Node* r=nullptr):data(data),left(l),right(r){}
};

class Tree{
    private:
        Node* root;
        void clear_rec(Node* node){
            if(!node) return;
            clear_rec(node->left);
            clear_rec(node->right);
            delete node;
        }
    public:
        Tree():root(nullptr){}
        ~Tree(){this->clear_rec(this->root);}
        void insert(const int data){
            if(!this->root) this->root=new Node{data}; return;
        }
        Tree* heapify(std::vector<int> vec){
            for(auto& itr:vec){
                this->insert(itr);
            }
        }
};


void print(const std::vector<int>& vec){
    std::cout<<"[";
    bool first=true;
    for(auto& itr: vec){
        if(!first) std::cout<<",";
        std::cout<<itr;
        first=false;
    }
    std::cout<<"]"<<std::endl;
}



std::vector<int> heapsort(std::vector<int>& vec){
    Tree* root=new Tree();
    root=root->heapify(vec);



    return vec;
}   


int main(){
    std::vector<int> v1={10,23,5,7,2,17,0,8};
    print(v1);
    v1=heapsort(v1);
    print(v1);

    return 0;
}