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
        static void levelOrderRec(Node<T>* root,int level,std::vector<std::vector<int>>& res) {
            if(root==nullptr) return;
            if(res.size()<=level) res.push_back({});        
            res[level].push_back(root->data);
            levelOrderRec(root->left,level+1,res);
            levelOrderRec(root->right, level+1,res);
        }
        void printTree(Node<T>* node,int depth=0) const noexcept{
            if(!node) return;
            printTree(node->right,depth+1);
            for(int i=0;i<depth;i++) std::cout<< "    ";
            std::cout<<node->data<<"\n";
            printTree(node->left,depth+1);
        }
        Node<T>* deep_copy(const Node<T>* original_node) {
            if(!original_node) return nullptr;
            Node<T>* new_node= new Node<T>(original_node->data);
            new_node->left=deep_copy(original_node->left);
            new_node->right=deep_copy(original_node->right);
            return new_node;
        }
    public:
        BinaryTree():root(nullptr){}
        BinaryTree(const BinaryTree<T>& b):root(this->deep_copy(b.root)){}
        BinaryTree(BinaryTree<T>&& b){
            this->root=b.root
            b.root=nullptr;
        }
        BinaryTree& operator=(BinaryTree<T>& b){
            if(this==&b) return *this;
            this->clear();
            this->root=b.root;
            b.root=nullptr;
            return *this;
        }
        void clear(Node<T>*& node) noexcept{
            if(!node) return;
            clear(node->left);
            clear(node->right);
            delete node;
            node=nullptr;
        }
        ~BinaryTree(){this->clear(this->get_root());}
        void insert(const T element){
            Node<T>* new_node=new Node<T>(element,nullptr,nullptr);
            if(!this->root) this->root=new_node;
            else{
                Node<T>* current=this->root;
                while(true){
                    if(element<current->data){
                        if(!current->left){
                            current->left=new_node;
                            break;
                        }
                        current=current->left;
                    }else{
                        if(!current->right){
                            current->right=new_node;
                            break;
                        }
                        current=current->right;
                    }
                }
            }
        }
        Node<T>* search(Node<T>* node,const T value){
            if(!node) return nullptr;
            else if(node->data==value) return node;
            Node<T>* result=search(node->left, value);
            if(result) return result;
            return search(node->right, value);
        }
        inline Node<T>* get_root()const noexcept{return this->root;}
        void prettyPrint() const{printTree(this->root);}
        void preorder_traversal(const Node<T>* node)const noexcept{
            if(!node) return;
            std::cout<<node->data<<" ";
            preorder_traversal(node->left);
            preorder_traversal(node->right);
        }
        void inorder_traversal(const Node<T>* node) const noexcept{
            if(!node) return;
            inorder_traversal(node->left);
            std::cout<<node->data<<" ";
            inorder_traversal(node->right);
        }
        void postorder_traversal(const Node<T>* node)const noexcept{
            if(!node) return;
            postorder_traversal(node->left);
            postorder_traversal(node->right);
            std::cout<<node->data<<" ";
        }
        friend std::ostream& operator<<(std::ostream& os,const BinaryTree<T>& b){
            b.prettyPrint();
            return os;
        }
};

int main(){
    BinaryTree<int>* tree=new BinaryTree<int>();
    tree->insert(1);
    tree->insert(2);
    tree->insert(4);
    tree->insert(3);
    tree->insert(5);
    tree->insert(0);
    std::cout<<*tree<<"\n";
    tree->preorder_traversal(tree->get_root());
    std::cout<<"\n";
    tree->inorder_traversal(tree->get_root());
    std::cout<<"\n";
    tree->postorder_traversal(tree->get_root());
    std::cout<<"\n";
    Node<int>* four=nullptr;
    four=tree->search(tree->get_root(), 4);
    std::cout<<four->data<<"\n";
    four=tree->search(tree->get_root(),27);
    if(!four) std::cout<<"Correctly not found a non existing element"<<"\n";

    return 1;
}