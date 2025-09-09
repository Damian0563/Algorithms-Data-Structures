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
        int size() noexcept{
            if(!this->head) return 0;
            Node<T>* temp=this->head;
            int size=0;
            while(temp){
                size++;
                temp=temp->next;
            }
            return size;
        }
        void remove(int index){
            index--;
            if(index>this->size()) return;
            if(index+1==this->size()-1){ 
                this->pop();
                return;
            }
            int counter=0;
            Node<T>* curr=this->head;
            while(counter!=index){
                counter++;
                curr=curr->next;
            }
            Node<T>* temp=curr->next;
            curr->next=temp->next;
            temp->next->prev=curr;
            delete temp;
        }   
        void insert(int index,const T element){
            index--;
            if(index>this->size()) return;
            if(index+1==this->size()){
                push(element);
                return;
            }
            Node<T>* new_node=new Node<T>{element,nullptr,nullptr};
            Node<T>* curr=this->head;
            int counter=0;
            while(counter!=index){
                counter++;
                curr=curr->next;
            }
            new_node->next=curr->next;
            new_node->prev=curr;
            curr->next=new_node;

        }
        T at(const int index){
            if(index>=this->size() || index<0) throw std::out_of_range("invalid index for 'at' funnction.");
            int counter=0;
            Node<T>* curr=this->head;
            while(counter!=index){
                counter++;
                curr=curr->next;
            }   
            return curr->data;
        }
        void pop(){
            if(!this->head) return;
            if(!this->head->next){
                delete this->head;
                this->head=nullptr;
                return;
            }
            Node<T>* temp=this->head;
            while(temp->next->next){
                temp=temp->next;
            }
            delete temp->next;
            temp->next=nullptr;
        }
        Dllist& operator=(const Dllist<T>&& list){
            if(this==&list) return *this;
            this->clear();
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
    movOp.pop();
    std::cout<<movOp<<"  "<<movOp.size()<<"\n";
    movOp.push(77);
    movOp.push(120);
    movOp.push(6);
    std::cout<<movOp<<"\n";
    movOp.remove(3);
    std::cout<<movOp<<"\n";
    movOp.insert(3,44);
    std::cout<<movOp<<"\n";
    std::cout<<"At index 2: "<<movOp.at(2)<<std::endl;

    return 1;
}