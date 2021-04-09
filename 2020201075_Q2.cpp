#include<stdio.h>
#include<iostream>
#include<sstream>
#include<bits/stdc++.h>
#define size 5209
typedef long long ll;
using namespace std;
template<class T, class U>
class Unordered_map{
    public:
    struct node{
        T key;
        U val;
        node* next;
    };
    node* a[size];
    node* newNode(T key, U val){
        node* temp = new node();
        temp->key=key;
        temp->val=val;
        temp->next=NULL;
        return temp;
    }
    ll Hash(string s){
        ll x=107, mul = 1, index = 0;
        for (ll i = 0; i < s.length(); i++){
            if (i == 0) index = index + (mul * s[i]);
            else{mul = (mul * x) % size;
                index = index + (mul * s[i]);}
        }
        index=index%size;
        return index;
    }
    bool find(T key){
        ostringstream ss;
        ss<<key;
        string s=ss.str();
        ll index=Hash(s);
        if(a[index]==NULL){
            return false;
        }
        else{
            node*temp=a[index];
            do{
                if(temp->key==key){
                    return true;
                }
                temp=temp->next;
            }while(temp!=NULL);
        }
        return false;
    }
    void erase(T key){
        if(find(key)){
        ostringstream ss;
        ss<<key;
        string s=ss.str();
        ll index=Hash(s);
        node*temp=a[index];
        node*prev=a[index];
        if(temp==NULL){
            return;
        }
        if(temp->key==key){
            a[index]=NULL;
            return;
        }
        temp=temp->next;
        do{
            if(temp->key==key){
                prev->next=temp->next;
                free(temp);
                return;
            }
            prev=temp;
            temp=temp->next;
        }while(temp!=NULL);
        }
    }
    void insert(T key, U val){
        if(!find(key)){
        ostringstream ss;
        ss<<key;
        string s=ss.str();
        ll index=Hash(s);
        if(a[index]==NULL){
            node*temp=newNode(key,val);
            a[index]=temp;
        }
        else{
            node*temp=a[index];
            while(temp->next!=NULL){
                temp=temp->next;
            }
            node*x=newNode(key,val);
            temp->next=x;
        }
        }
    }
    U &operator[](T key){
        if(find(key)){
            ostringstream ss;
            ss<<key;
            string s=ss.str();
            ll index=Hash(s);
            node*temp=a[index];
            while(temp!=NULL){
                if(temp->key==key) return temp->val;
                temp=temp->next;
            }
        }
    }
};

int main(){
    Unordered_map<string,float> m;
    m.insert("abc",2.26);
    m.insert("ubg",6.52);
    m.insert("xcd",20.97);
    m.insert("lkj",5.22);
    /*m.erase("xcd");
    m.erase("abc");
    m.erase("ubg");
    m.erase("lkj");*/
    cout<<m.find("xcd")<<endl;
    cout<<m.find("abc")<<endl;
    cout<<m.find("ubg")<<endl;
    cout<<m["abc"]<<endl;
    Unordered_map<float,float> n;
    n.insert(2.26,9.5);
    n.insert(56.25,56.32);
    cout<<n[2.26]<<endl;
}