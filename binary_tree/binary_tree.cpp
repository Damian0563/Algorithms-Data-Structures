#include <iostream>
#include <vector>
template <typename T>
struct Node{
    T data;
    Node<T>* left;
    Node<T>* right;
    Node(const T data,Node<T>* left=nullptr,Node<T>* right=nullptr):data(data),left(left),right(right){}
};

template <typename T>
class BinaryTree{
    private:
        Node<T>* root;
        void levelOrderRec(Node<T>* root, int level, std::vector<std::vector<int>>& res) {
            if(root==nullptr) return;
            if(res.size()<=level) res.push_back({});        
            res[level].push_back(root->data);
            levelOrderRec(root->left, level + 1, res);
            levelOrderRec(root->right, level + 1, res);
        }
    public:
        BinaryTree():root(nullptr){}
        BinaryTree(const BinaryTree<T>& b){

        }
        BinaryTree(const BinaryTree<T>&& b){}
        BinaryTree& operator=(BinaryTree<T>& b){}
        ~BinaryTree(){}
        void insert(const T element){
            Node<T>* new_node=new Node<T>(element,nullptr,nullptr);
            if(!this->root) this->root=new_node;
            else{
                Node<T>* left=this->root->left;
                Node<T>* right=this->root->right;
                while(true){
                    if(left && left->data<element){
                        left=left->left;
                    }else if(right && right->data<element){
                        right=right->right;
                    }else{
                        if(!left && right) left=new_node;
                        else if(left && !right) right=new_node;
                        else left=new_node;
                        return;
                    }
                }
            }
        }
        Node<T>* search(const T value){}
        friend std::ostream& operator<<(std::ostream& os,const BinaryTree<T>& b){
            std::vector<std::vector<int>> res; 
            //levelOrderRec(b.root, 0, res);
            for(int i=0;i<res.size();i++){
                for(int j=0;j<res[i].size();j++){
                    os<<res[i][j]<<"  ";
                }
                os<<"\n";
            }
            return os;
        }
};

int main(){
    BinaryTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    std::cout<<tree<<"\n";
    return 1;
}