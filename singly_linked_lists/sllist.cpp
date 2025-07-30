#include <forward_list>
#include <iostream>

template <typename T> 
class Singly{
    private:
        struct Node{
            T data;
            Node* next;
        };
        Node* head; 
    public:
        Singly():head(nullptr){};
        ~Singly(){
            Node* temp = this->head;
            while(temp){
                Node* curr = temp;
                temp = temp->next;
                delete curr;
            }
            this->head = nullptr;
        }
        Singly(const Singly<T>& list):head(nullptr) {
            if(list.head==nullptr) return;
            Node* src=list.head;
            Node** dst=&this->head;
            while(src){
                *dst=new Node{src->data, nullptr};
                dst=&((*dst)->next);
                src=src->next;
            }
        }
        void push_front(const T data){
            Node* new_node = new Node();
            new_node->data = data;
            new_node->next = this->head;
            this->head = new_node;
        }
        friend std::ostream& operator<<(std::ostream& os,const Singly<T>& list){
            Node* curr = list.head;
            os << "[";
            bool first = true;
            while (curr != nullptr) {
                if (!first) os << ", ";
                os << curr->data;
                first = false;
                curr = curr->next;
            }
            os << "]";
            return os;
        }
};

int main(){
    Singly<int> sllist;
    sllist.push_front(10);
    Singly<int> cpy(sllist);
    std::cout<<sllist<<"\n";
    std::cout<<cpy<<"\n";
    return 1;
}