#include <iostream>

template <typename T>
struct Node{
    T data;
    Node<T>* next;
    Node(const T data,Node<T>* next=nullptr):data(data),next(next){}
};

template <typename T>
class Stack{
    private:
        Node<T>* head;
        unsigned int len;
    public:
        Stack():head(nullptr),len(0){}
        Stack(const Stack<T>& other){}
        Stack(const Stack<T>&& other){}
        ~Stack(){this->clear();}
        void clear(){
            Node<T>* temp=this->head;
            Node<T>* curr=nullptr;
            while(temp){
                curr=temp;
                delete curr;
                temp=temp->next;
            }
            this->head=nullptr;
            this->len=0;
        }
        inline T peek()const {return this->head?this->head->data:throw std::out_of_range("No element to peek!");}
        inline bool isEmpty()const noexcept{return this->len==0;}
        void push(const T data){
            Node<T>* new_node=new Node<T>{data};
            if(this->head) new_node->next=this->head;
            this->head=new_node;
            this->len++;
        }
        void pop(){
            if(!this->head) throw std::out_of_range("No element to peek!");
            Node<T>* temp=this->head;
            if(this->head->next) this->head=this->head->next;
            delete temp; 
            this->len--;
        }
        inline unsigned int size()const {return this->len;}
        friend std::ostream& operator<<(std::ostream& os,const Stack<T>& stack){
            os<<"[";
            Node<T>* temp=stack.head;
            bool first=true;
            while(temp){
                if(!first) os<<",";
                os<<temp->data;
                first=false;
                temp=temp->next;
            }
            os<<"]";
            return os;
        }
        Stack& operator=(Stack<T>&& other){}
        Stack& operator=(const Stack<T>& other){}
};

int main(){
    Stack<std::string> my_stack;
    std::cout<<my_stack<<"\n";
    my_stack.push("some variable");
    my_stack.push("yogurt");
    my_stack.push("crossaint");
    std::cout<<my_stack<<"\n";
    std::cout<<"Peek: "<<my_stack.peek()<<" , size: "<<my_stack.size()<<" isEmpty: "<<my_stack.isEmpty()<<"\n";
    my_stack.pop();
    std::cout<<my_stack<<"\n";
    std::cout<<"Peek: "<<my_stack.peek()<<" , size: "<<my_stack.size()<<" isEmpty: "<<my_stack.isEmpty()<<"\n";
    my_stack.clear();
    std::cout<<my_stack<<"\n";
    std::cout<<"Size: "<<my_stack.size()<<" isEmpty: "<<my_stack.isEmpty()<<"\n";

    return 1;
}