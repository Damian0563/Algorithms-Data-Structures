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
        Dllist(const Dllist<T>& list){
            this->head=nullptr;
            Node<T>* temp=list.head;
            Node<T>** curr=&this->head;
            Node<T>* holder=nullptr;
            while(temp){
                *curr=new Node<T>{temp->data,nullptr,nullptr};
                (*curr)->prev=holder;
                holder=*curr;
                curr=&((*curr)->next);
                temp=temp->next;
            }
        }
        Dllist(Dllist<T>&& list){
            this->head=list.head;
            list.head=nullptr;
        }
        void remove(){

        }
        void insert(){

        }
        Dllist& operator=(const Dllist<T>&& list){
            if(*this==&list) return *this;
            this->head=list.head;
            list.head=nullptr;
            return *this;
        }
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
                Node<T>* new_node=new Node<T>{element, nullptr, temp};
                temp->next=new_node;
            }
        }
        friend std::ostream& operator<<(std::ostream& os,const Dllist<T>& dllist){
            Node<T>* temp=dllist.head;
            os<<"[";
            while(temp){
                os<<temp->data;
                if(temp->next) os<<",";
                temp=temp->next;
            }
            os<<"]";
            return os;
        }
};


int main(){
    Dllist<int> dlist;
    dlist.push(10);
    dlist.push(17);
    dlist.push(24);
    std::cout<<dlist<<"\n";
    Dllist<int> cpy(dlist);
    std::cout<<cpy<<"\n";

    Dllist<int> mov(std::move(dlist));
    std::cout<<mov<<"  "<<dlist<<"\n";
    Dllist<int> movOp=std::move(mov);
    std::cout<<movOp<<"  "<<mov<<"\n";

    return 1;
}