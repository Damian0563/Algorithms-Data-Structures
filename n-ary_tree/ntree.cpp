#include <iostream>
#include <queue>
#define N 3

template <typename T>
struct Node{
    T data;
    Node<T>* mem_map[N];
    Node(const T& data):data(data){
        for (int i=0;i<N;i++) mem_map[i]=nullptr;
    }
};

template <typename T>
class NaryTree{
    private:
        Node<T>* root;
        void clear_rec(Node<T>* node){
            if(!node) return;
            for(int i=0;i<N;i++) {
                clear_rec(node->mem_map[i]);
            }
            delete node;
        }
        void clear() noexcept{this->clear_rec(this->root);this->root=nullptr;}
        Node<T>* copy_rec(Node<T>* node) {
            if(!node) return nullptr;
            Node<T>* new_node=new Node<T>(node->data);
            for(int i=0;i<N;i++) new_node->mem_map[i]=copy_rec(node->mem_map[i]);
            return new_node;
        }
        void add(Node<T>* node, const T element){
            if(!node) return;
            std::queue<Node<T>*> q;
            q.push(node);
            while(!q.empty()){
                Node<T>* current=q.front();
                q.pop();
                int size=0;
                for(int i=0;i<N;i++) if(current->mem_map[i]) size++;
                if(size<N){
                    Node<T>* new_node=new Node<T>(element);
                    current->mem_map[size]=new_node;
                    return;
                }
                for(int i=0;i<N;i++){
                    if(current->mem_map[i]) q.push(current->mem_map[i]);
                }
            }
        }
        void preorder(Node<T>* node)const {
            if(!node) return;
            std::cout<<node->data<<" ";
            for(auto&itr : node->mem_map){
                preorder(itr);
            }
        }
        void inorder(Node<T>* node)const {
            if(!node) return;
            if(node->mem_map[0]) inorder(node->mem_map[0]);
            std::cout<<node->data<<" ";
            for(int i=1;i<N;i++) inorder(node->mem_map[i]);
        }
        void postorder(Node<T>* node)const {
            if(!node) return;
            for(auto&itr : node->mem_map){
                postorder(itr);
            }
            std::cout<<node->data<<" ";
        }
    public:
        NaryTree():root(nullptr){}
        ~NaryTree(){this->clear();}
        NaryTree(const NaryTree<T>& other){
            this->root=copy_rec(other.root);
        }
        NaryTree(NaryTree<T>&& other){
            this->root=other.root;
            other.root=nullptr;
        }
        NaryTree& operator=(const NaryTree<T>& other){
            if(this==&other) return *this;
            this->clear();
            this->root=copy_rec(other.root);
            return *this;
        }
        void preorder_traversal()const noexcept{this->preorder(this->root);}
        void inorder_traversal()const noexcept{this->inorder(this->root);}
        void postorder_traversal()const noexcept{this->postorder(this->root);}
        void insert(const T element){
            if(!this->root){
                this->root=new Node<T>(element);
            }else add(this->root,element);
        }   
        friend std::ostream& operator<<(std::ostream& os,const NaryTree<T>& tree){
            auto print_preorder=[&](auto&& self, Node<T>* node)->void{
                if(!node) return;
                os<<node->data<<" ";
                for(auto& child : node->mem_map) self(self, child);
            };
            print_preorder(print_preorder, tree.root);
            return os;
        }
};

int main(){
    NaryTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8); 
    //HELPER 1
    std::cout<<tree<<"\n"; //preorder traversal operator<<
    tree.preorder_traversal(); std::cout<<"\n";
    tree.inorder_traversal(); std::cout<<"\n";
    tree.postorder_traversal(); std::cout<<"\n";
    std::cout<<"\n";
    NaryTree<int> cpy(tree);
    NaryTree<int> dp=std::move(tree);
    std::cout<<cpy<<"\n";
    std::cout<<dp<<"\n";
    std::cout<<tree<<"\n";

    return 1;
}