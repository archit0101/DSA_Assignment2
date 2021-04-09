#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
typedef long long ll; 
using namespace std;
template<class T, class U>
class Map{
    public:
    ll count=0;
    struct avl{
    //data-values:
    U val;
    avl *right;
    ll height;
    avl *left;
    T key;
    };
    struct avl*root;
    Map(){
        root=NULL;
    }
    avl* newNode(T key, U val){
        avl* node= new avl();
        node->val = val;
        node->left = NULL;
        node->height = 1;
        node->key = key;
        node->right = NULL;
        return node;
    } 
    //Functions:
    T max(T a, T b){
        return a>b?a:b;
    }
    ll height(avl *node){
        if(node == NULL){
            return 0;
        }
        return node->height;
    }
    
    avl* RR(avl* node){
        avl *left= node->left;
        avl *right =left->right;
        left->right=node;
        node->left = right;
        node->height = max(height(node->left),height(node->right))+1;
        left->height = max(height(left->left),height(left->right))+1;
        return left;  
    }
    
    int Bal(avl* node){
        if(node==NULL){
            return 0;
        }
        return height(node->left)-height(node->right);
    }
    void insert(T key, U value){
        avl*temp=locate(root, key);
        if(temp!=NULL){
            temp->val=value;
        }
        else{
            count++;
            root=insert_val(root,key,value);
        }
    }
    avl* insert_val(avl* node, T key,U val){
        if(node == NULL)
            return(newNode(key,val));
        if(val<node->val){
            node->left = insert_val(node->left,key,val);
        }
        else if(val>node->val){
            node->right = insert_val(node->right, key, val);
        }
        else{
            node->val= val;
            return node;
        }
        node->height=max(height(node->left),height(node->right))+1;
        int balance=Bal(node);

        if(balance>1 && key<node->left->val)
            return RR(node);
        if(balance<-1 && key>node->right->val)
            return LR(node);
        if(balance>1 && key>node->left->val){
            node->left=LR(node->left);
            return RR(node);
        }
        if(balance<-1 && key<node->right->val){
            node->right= RR(node->right);
            return LR(node);
        }
        return node;
    }
    avl* min_val_node(avl* node){
        avl* curr = node;
        while(curr->left != NULL)
            curr=curr->left;
        return curr;
    }
    void erase(T key){
        avl*temp=locate(root, key);
        if(temp!=NULL){
            count--;
            root=delete_node(root,key);
        }
    }
    
    
    avl* locate(avl* root,T key){
        if(root==NULL){
            return NULL;
        }
        if(root->key==key){
            return root;
        }
        else if(root->key>key){
            return locate(root->left,key);
        }
        else if(root->key<key){
            return locate(root->right,key);
        }
        
    }
    avl* LR(avl* node){
        avl *right = node->right;
        avl* left = right->left;
        right->left = node;
        node->right = left; 
        node->height = max(height(node->left),height(node->right))+1;
        right->height = max(height(right->left),height(right->right))+1;
        return right;
    }
    bool find(T val){
        //cout<<"find"<<endl;
        avl* Temp = locate(root,val);
        if(Temp!=NULL){
           // cout<<"mil gaya element"<<endl;
            return true;
        }
        //cout<<"nhi mila"<<endl;
        return false;
    }
    int size(){
        return count;
    }
    void clear_node(avl* root){
        if(root==NULL) return;
        clear_node(root->left);
        clear_node(root->right);
        delete(root);
    }
    avl* delete_node(avl* root, T key){
        if(root==NULL){
            return root;
        }
        if(key<root->key){
            root->left = delete_node(root->left, key);
        }
        else if(key>root->key){
            root->right = delete_node(root->right,key);
        }
        else{
            if((root->left == NULL)||(root->right == NULL)){
                    avl* temp = root->left?root->left:root->right;
                    if(temp==NULL){
                        temp=root;
                        root=NULL;
                        free(temp);
                        return root;  
                    }
                    else
                    {
                       *root=*temp; 
                       free(temp);
                    }
                    
            }
            else{
                ll c;
                avl* temp=min_val_node(root->right);
                root->key = temp->key;
                root->val = temp->val;
                root->right=delete_node(root->right,temp->key);
            }
        }
        root->height=max(height(root->left),height(root->right))+1;
        int balance= Bal(root);
        if (balance > 1 && Bal(root->left) >= 0)  
            return RR(root);  
        if (balance > 1 && Bal(root->left) < 0){  
            root->left = LR(root->left);  
            return RR(root);  
    }  
    if (balance < -1 && Bal(root->right) <= 0)  
        return LR(root);    
    if (balance < -1 && Bal(root->right) > 0){  
        root->right = RR(root->right);  
        return LR(root);  
    }  
  
    return root;  

    }
    void clear(){
        clear_node(root);
        root=NULL;
        count=0;
    }
    U& operator[](T key){
        if(find(key)){
            avl*temp=locate(root,key);
            //cout<<"returning value when key is present"<<endl; 
            return temp->val;
        }
        insert(key,0);
        avl*temp=locate(root,key);
        //cout<<"returning value when key was inserted"<<endl;
        return temp->val;
    }
};

int main(){
    Map<int,int>m;
    m.insert(1,1);
    m.insert(2,3);
    m.insert(3,4);
    m.insert(4,4);
    m.erase(5);
    m.erase(3);
    int count=m.size();
    cout<<count<<endl;
    cout<<m.find(2)<<endl;
    cout<<m.find(3)<<endl;
    m[2]=m[2]+1;
    cout<<m[2]<<endl;
    m.clear();
    cout<<m.size()<<endl;
    cout<<m.find(1)<<endl;
    m[2]=m[2]+1;
    cout<<m[2]<<endl;
    return 0;
}