#include <iostream>

template <typename T>
struct Node{
    T data;
    Node<T>* prev;
    Node<T>* next;
    Node(const T data,Node<T>* next=nullptr,Node<T>* prev=nullptr):data(data),next(next),prev(prev){}
};

template <typename T>   
class Dllist{
    private:
        Node<T>* head;
    public:
        inline bool isEmpty() noexcept {return this->head==nullptr;}
        Dllist():head(nullptr){}
        ~Dllist(){this->clear();}
        void clear() noexcept{
            Node<T>* temp=this->head;
            Node<T>* curr=nullptr;
            while(temp){
                curr=temp;
                temp=temp->next;
                delete curr;
            }
        }
        void push(const T element){
            if(!this->head) this->head=new Node<T>{element,nullptr,nullptr};
            else{
                Node<T>* temp=this->head;
                Node<T>* curr=nullptr;
                while(temp->next){
                    curr=temp;
                    temp=temp->next;
                }
                temp=new Node<T>{element,nullptr,nullptr};
                curr==nullptr? temp->prev=this->head:temp->prev=curr;
            }
        }
        friend std::ostream& operator<<(std::ostream& os,const Dllist<T>& dllist){

            return os;
        }
};


int main(){
    Dllist<int> dlist;
    dlist.push(10);
    dlist.push(17);
    dlist.push(24);

    return 1;
}