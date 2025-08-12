#include <iostream>
#include <queue>
template <typename T>
struct Node{
    T data;
    Node* next;
    Node(const T& data,Node<T>* next=nullptr):data(data),next(next){}
};

template <typename T>
class Queue{
    private:
        Node<T>* head;
        Node<T>* tail;
        unsigned int current_size;
    public:
        Queue():head(nullptr), tail(nullptr), current_size(0) {};
        ~Queue(){this->clear();}
        unsigned int size()const {return this->current_size;}
        T front() const{return this->head?this->head->data:throw std::out_of_range("no front element in empty queue.");}
        T back() const{return this->tail?this->tail->data:throw std::out_of_range("no back element in empty queue.");}
        T pop(){
            if(!this->isEmpty()){
                Node<T>* first=this->head;
                T value=first->data;
                if(this->head->next) this->head=this->head->next;
                else{
                    this->head=nullptr;
                    this->tail=nullptr;
                }
                delete first;
                this->current_size--;
                return value;
            }
            throw std::out_of_range("pop from empty list");
        }
        void push_back(const T& data){
            Node<T>* new_node=new Node<T>{data,nullptr};
            if(!this->head){
                this->head=new_node;
                this->tail=new_node;
            }else{
                this->tail->next=new_node;
                this->tail=new_node;
            }
            this->current_size++;
        }
        bool isEmpty() const noexcept{return this->size()==0;}   
        friend std::ostream& operator<<(std::ostream& os,const Queue<T>& queue){
            os<<"[";
            unsigned int size=queue.size();
            Node<T>* curr=queue.head;
            while(size>0){
                os<<curr->data;
                if(size!=1) os<<",";
                curr=curr->next;
                size--;
            }
            os<<"]";
            return os;
        }
        Queue<T> reverse(){
            Node<T>* prev=nullptr;
            Node<T>* current=this->head;
            Node<T>* next=nullptr;
            this->tail=this->head;
            while(current!=nullptr) {
                next=current->next;
                current->next=prev;
                prev=current;
                current=next;
            }
            this->head=prev;
            return *this;
        } 
        Queue(const Queue<T>& queue){
            this->head=nullptr;
            this->tail=nullptr;
            this->current_size=queue.size();
            Node<T>* curr=queue.head;
            while(curr){
                Node<T>* newNode = new Node<T>{curr->data, nullptr};
                if(!this->head){
                    this->head = newNode;
                    this->tail = newNode;
                }else{
                    this->tail->next=newNode;
                    this->tail=newNode;
                }
                curr=curr->next;
            }
        }
        Queue(Queue<T>&& queue){
            this->current_size=queue.size();
            this->head=queue.head;
            this->tail=queue.tail;
            queue.head=nullptr;
            queue.tail=nullptr;
            queue.current_size=0;
        }
        void clear(){
            Node<T>* curr=this->head;
            Node<T>* temp=nullptr;
            while(curr){
                temp=curr;
                curr=curr->next;
                delete temp;
            }
            this->current_size=0;
            this->head=nullptr;
            this->tail=nullptr;
        }
        Queue& operator=(Queue<T>&& queue){
            if(*this==&queue) return this;
            this->clear();
            this->current_size=queue.size();
            this->head=queue.head;
            this->tail=queue.tail;
            queue.head=nullptr;
            queue.tail=nullptr;
            queue.current_size=0;
            return this;
        }
};

template <typename T>
struct NodeP{
    T data;
    unsigned int priority;
    NodeP* next;
    NodeP(const T data,const unsigned int priority,const NodeP<T>* next=nullptr):data(data),priority(priority),next(next){}
};
template <typename T>
class PriorityQueue{
    private:
        NodeP<T>* head;
        NodeP<T>* tail;
        int size;
    public:
        PriorityQueue():head(nullptr),tail(nullptr),size(0){};
        PriorityQueue(const PriorityQueue<T>& q){
            NodeP<T>* temp=q.head;
            this->head=nullptr;
            this->tail=nullptr;
            this->size=q.size();
            while(temp){
                NodeP<T>* new_node=new NodeP<T>{temp->data,temp->priority,nullptr};
                if(!this->head){
                    this->head=new_node;
                    this->tail=new_node;
                }else{
                    this->tail->next=new_node;
                    this->tail=new_node;
                }
                temp=temp->next;
            }
        }
        PriorityQueue(const PriorityQueue<T>&& q){

        }
        PriorityQueue& operator=(PriorityQueue<T>&& q){

        }
        friend std::ostream& operator<<(std::ostream& os,const PriorityQueue<T>& q){
            os<<"[";
            unsigned int size=q.len();
            NodeP<T>* curr=q.head;
            while(size>0){
                os<<curr->data;
                if(size!=1) os<<",";
                curr=curr->next;
                size--;
            }
            os<<"]";
            return os;
        }
        ~PriorityQueue(){this->clear();}
        void clear(){
            NodeP<T>* curr=this->head;
            NodeP<T>* temp=nullptr;
            while(curr){
                temp=curr;
                curr=curr->next;
                delete temp;
            }
            this->size=0;
            this->head=nullptr;
            this->tail=nullptr;
        }
        inline unsigned int len(){return this->size;}
        void push_back(T data,int priority){
            NodeP<T> new_node=new NodeP<T>{data,priority,nullptr};
            if (!this->head || priority>this->head->priority) {
                new_node->next=this->head;
                this->head=new_node;
                if(!this->tail) this->tail=new_node;
            }else{
                NodeP<T>* curr=this->head;
                while(curr->next && curr->next->priority>priority){
                    curr=curr->next;
                }
                new_node->next=curr->next;
                curr->next=new_node;
                if(!new_node->next) this->tail=new_node;
            }
        }
};



int main(){
    Queue<int> q;
    std::cout<<q<<"\n";
    q.push_back(10);
    q.push_back(99);
    q.push_back(49);
    q.push_back(21);
    std::cout<<q<<"\n";
    int popped=q.pop();
    std::cout<<"Popped: "<<popped<<"\t"<<"from "<<q<<"\n";
    std::cout<<q.reverse()<<"\n";
    Queue<int> cpy(q);
    std::cout<<cpy<<"\n";
    Queue<int> mo=std::move(q);
    std::cout<<mo<<" "<<q<<"\n";

    return 1;
}