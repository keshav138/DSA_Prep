
#include<bits/stdc++.h>
using namespace std;

class Node{
    public: 
    int data;
    Node* next;

    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};


int main(){
    Node* head = new Node(7);
    head->next = new Node(5);
    head->next->next = new Node(4);

    Node* head2 = new Node(2);
    head2->next = new Node(4);
    head2->next->next = new Node(8);
    head2->next->next->next = new Node(2);



    int carry = 0;
    vector<int> temp;
    while(head!=nullptr && head2!=nullptr){
       int curr_sum = head->data + head2->data + carry;
       if(curr_sum >= 10){
        carry = (curr_sum / 10);
        temp.push_back(curr_sum%10);
       }
       else{
        temp.push_back(curr_sum);
        carry = 0;
       }

       head = head->next;
       head2 = head2->next;
    }


    while(head!=nullptr){
        int curr_sum = head->data + carry;
        if(curr_sum >= 10){
            carry = (curr_sum / 10);
            temp.push_back(curr_sum%10);
       }
       else{
            temp.push_back(curr_sum);
            carry = 0;
       }
       head = head->next;
    }

    while(head2!=nullptr){
        int curr_sum = head2->data + carry;
        if(curr_sum >= 10){
            carry = (curr_sum / 10);
            temp.push_back(curr_sum%10);
       }
       else{
            temp.push_back(curr_sum);
            carry = 0;
       }
       head2 = head2->next;
    }

    if(carry > 0){
        temp.push_back(carry);
    }



    for(auto i: temp){
        cout<<i<<endl;
    }
    // cout<<carry;
}