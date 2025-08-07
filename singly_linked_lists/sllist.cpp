#include <forward_list>
#include <iostream>
#include <algorithm>
#include <iterator>

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
        Node* begin(){return this->head;}
        Node* at(int index){
            Node* temp=this->head;
            int curr=0;
            while(temp){
                if(curr==index){
                    return temp;
                }
                curr++;
                temp=temp->next;
            }
            throw std::out_of_range();
            return nullptr;
        }
        Node* end(){
            Node* temp=this->head;
            while(temp->next){
                temp=temp->next;
            }
            return temp;
        }
        Singly(Singly<T>&& other)noexcept :head(nullptr){
            this->head=other.head;
            other.head=nullptr;
        }
        Singly& operator=(Singly<T>&& other) noexcept{
            if(this==&other) return *this;
            this->clear();
            this->head=other.head;
            other.head=nullptr;
            return *this;
        }
        Singly& operator=(const Singly<T>& list){
            if(this==&list) return *this;
            this->clear();
            Node* temp=list.head;
            Node** curr=&this->head;
            while(temp!=nullptr){
                *curr=new Node{temp->data, nullptr};
                curr=&((*curr)->next);
                temp=temp->next;
            }
            return *this;
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
            Node* temp=this->head;
            this->head=this->head->next;
            delete temp;
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
            Node* next=position->next ? position->next : nullptr;
            Node* new_node=new Node{element,next};
            position->next=new_node;
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


template <typename T>
std::ostream& operator<<(std::ostream& os,const std::forward_list<T> list){
    bool flag=false;
    os<<"[";
    for(auto& itr: list){
        if(flag) os<<",";
        flag=true;
        os<<itr;
    }
    os<<"]";
    return os;
}

template <typename T>
std::forward_list<T> merge(std::forward_list<T>& list1,std::forward_list<T>& list2){
    std::forward_list<T> result;
    list1.reverse();
    list2.reverse();
    while(std::distance(list1.begin(),list1.end())>0 || std::distance(list2.begin(),list2.end())>0){
        result.push_front(list1.front());
        result.push_front(list2.front());
        list1.pop_front();
        list2.pop_front();
    }
    if(std::distance(list2.begin(),list2.end())>0 && std::distance(list1.begin(),list1.end())==0){
        while(std::distance(list2.begin(),list2.end())>0){
            result.push_front(list2.front());
            list2.pop_front();
        }
    }else if(std::distance(list2.begin(),list2.end())==0 && std::distance(list1.begin(),list1.end())>0){
        while(std::distance(list1.begin(),list1.end())>0){
            result.push_front(list1.front());
            list1.pop_front();
        }
    }
    return result;
}

template <typename T>
void merge_inplace(std::forward_list<T>& list1,std::forward_list<T>& list2){
    if(list2.empty()) return;
    if(list1.empty()){
        list1=std::move(list2);
        return;
    }
    auto it1_before=list1.before_begin();
    auto it2_before=list2.before_begin();
    while(std::next(it1_before)!=list1.end() && std::next(it2_before)!=list2.end()){
        list1.splice_after(it1_before, list2, it2_before);
        it1_before++;
    }
    if(!list2.empty()) list1.splice_after(it1_before, std::move(list2));
}

bool check_palindrome(const std::string& word){
    std::string reversed_word=word;
    std::reverse(reversed_word.begin(), reversed_word.end());
    // std::cout<<word<<" "<<reversed_word<<"\n";
    return word==reversed_word;
}


void leave_palindromes(std::forward_list<std::string>& list){
    auto itr=list.before_begin();
    while(std::next(itr)!=list.end()){
        auto current_element_itr=std::next(itr);
        if(!check_palindrome(*current_element_itr)) itr=list.erase_after(itr);
        else itr++;
    }
    for(auto& itr: list){
        if(!check_palindrome(itr)) leave_palindromes(list); 
    }
}

int main(){
    try{
        Singly<int> sllist;
        Singly<int> test;
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
        test=std::move(sllist);
        std::cout<<test<<"\n"<<"\n";
        Singly<int> llist;
        llist.push_front(10);
        llist.push_front(16);
        llist.push_front(28);
        llist.push_front(5);
        std::cout<<llist<<"\n";
        llist.insert_after(llist.begin(),7);
        std::cout<<llist<<"\n";
    }
    catch(const std::exception& e){
        std::cerr<<"Exception occured: "<<e.what()<<"\n";
    }
    //exercises with std::forward_list
    std::forward_list<std::string> list1;
    std::forward_list<std::string> list2;
    list1.push_front("Anna");
    list1.push_front("Bart");
    list1.push_front("Jim");
    list1.push_front("Cook");
    list2.push_front("Shawn");
    list2.push_front("Jambo");
    list2.push_front("Shawn");
    list2.push_front("Jill");
    std::cout<<list1<<"\n";
    std::cout<<list2<<"\n";
    std::forward_list<std::string> list4;
    list4.push_front("Anna");
    list4.push_front("Bart");
    list4.push_front("Jim");
    list4.push_front("Cook");
    std::forward_list<std::string> list5;
    list5.push_front("Shawn");
    list5.push_front("Jambo");
    list5.push_front("Shawn");
    list5.push_front("Jill");
    std::forward_list<std::string> list3=merge(list1,list2);
    merge_inplace(list4,list5);
    std::cout<<list3<<"\n";
    std::cout<<list4<<"\n";
    std::forward_list<std::string> palindromes={"bob","samantha","Bob","mum","jasmine","a"};
    std::cout<<palindromes<<"\n";
    leave_palindromes(palindromes);
    std::cout<<palindromes<<"\n";

    return 1;
}