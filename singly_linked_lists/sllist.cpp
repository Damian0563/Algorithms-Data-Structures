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
        Singly(const Singly<T>&& other){

        }
        Singly& operator=(const Singly<T>&& other){

        }
        Singly& operator=(const Singly<T>& list){
            
        }
        void push_front(const T data){
            Node* new_node=new Node();
            new_node->data=data;
            new_node->next=this->head;
            this->head=new_node;
        }
        T front(){
            if(this->head!=nullptr){
                return this->head->data;
            }
            throw std::out_of_range("Can not access front element on an empty list!");
        }
        void pop_front(){
            if(this->head==nullptr) return;
            if(this->head->next!=nullptr){
                this->head=this->head->next;
            }else this->head=nullptr;
        }
        void remove(const T element){
            if(this->head==nullptr) return;
            while(this->head && this->head->data==element){
                Node* temp=this->head;
                this->head=this->head->next;
                delete temp;
            }
            Node* curr=this->head;
            Node* prev=nullptr;
            while(curr!=nullptr){
                if(curr->data==element){
                    Node* temp=curr;
                    prev->next=curr->next;
                    curr=curr->next;
                    delete temp;
                }else{
                    prev=curr;
                    curr=curr->next;
                }
            }
        }
        void insert_after(Node* position,const T element){

        }
        void clear(){
            if(this->head==nullptr) return;
            Node* temp=this->head;
            while(this->head!=nullptr){
                temp=this->head;
                this->head=this->head->next;
                delete temp;
            }
            this->head=nullptr;
        }
        friend std::ostream& operator<<(std::ostream& os,const Singly<T>& list){
            Node* curr=list.head;
            os<<"[";
            bool first=true;
            while(curr!=nullptr){
                if(!first) os<<", ";
                os<<curr->data;
                first=false;
                curr=curr->next;
            }
            os<<"]";
            return os;
        }
};

int main(){
    try{
        Singly<int> sllist;
        sllist.push_front(12);
        Singly<int> cpy(sllist);
        sllist.push_front(12);
        sllist.push_front(22);
        sllist.push_front(12);
        sllist.push_front(45);
        sllist.push_front(12);
        sllist.push_front(12);
        std::cout<<sllist<<"\n";
        std::cout<<cpy<<"\n";
        std::cout<<sllist.front()<<"\n";
        std::cout<<"Removing 12"<<"\n";
        std::cout<<sllist<<"\n";
        sllist.remove(12);
        std::cout<<sllist<<"\n";
        std::cout<<"Popping front once:"<<"\n";
        sllist.pop_front();
        std::cout<<sllist<<"\n";
        sllist.clear();
        std::cout<<sllist<<"\n";
    }
    catch(const std::exception& e){
        std::cerr<<"Exception occured: "<<e.what()<<"\n";
    }
    return 1;
}