#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
typedef long long ll; 
using namespace std;
template<class T>
class Tree{
    public:
    T lb,ub,low;
    int tc,flag=0;
    struct avl{
    //data-values:
    ll count=0;
    avl *left;
    ll height;
    avl *right;
    ll size;
    T val;
    };
    struct avl* root;
    Tree(){
        root=NULL;
    }

    //Functions:
    T max(T a, T b){
        return a>b?a:b;
    }
    T minimum(T a, T b){
        return a<b?a:b;
    }
    ll height(avl *node){
        if(node == NULL){
            return 0;
        }
        return node->height;
    }
    avl* newNode(T val){
        avl* node= new avl();
        node->left = NULL;
        node->height = 1;
        node->count=1;
        node->right = NULL;
        node->size=1;
        node->val = val;
        return node;
    } 
    avl* RR(avl* node){
        avl *left= node->left;
        avl *right =left->right;
        left->size=node->size;
        if(left->right==NULL){if(node->right==NULL) node->size=node->count;
        else node->size=node->right->size+node->count;}
        else node->size=node->right->size+left->right->size+node->count;
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
    void insert(T val){
            
        root=insert_val(root, val);
    }
   
    avl* min_val_node(avl* node){
        avl* curr = node;
        while(curr->left != NULL)
            curr=curr->left;
        return curr;
    }
    void deleteNode(T val){
            root = delete_node(root,val);
    }
    
    avl* locate(avl* root,T val){
        if(root==NULL){
            return NULL;
        }
        if(root->val==val){
            return root;
        }
        else if(root->val>val){
            return locate(root->left,val);
        }
        else if(root->val<val){
            return locate(root->right,val);
        }
    }
    avl* delete_node(avl* root, T val){
        if(root==NULL){
            return root;
        }
        if(flag==0){
            tc=1;
        }
        if(val<root->val){
            root->size=root->size-tc;
            root->left = delete_node(root->left, val);
        }
        else if(val>root->val){
            root->size=root->size-tc;
            root->right = delete_node(root->right,val);
        }
        else{
            if((root->left == NULL)||(root->right == NULL)){
                if(root->count>1){
                    root->size=root->size-tc;
                    root->count=root->count-1;
                    return root;
                }
                else{
                    avl* temp = root->left?root->left:root->right;
                    if(temp==NULL){
                        temp=root;
                        root=NULL;
                        free(temp);
                        return root;  
                    }
                    else
                    {
                        //temp->size=root->size;
                       *root=*temp;
                       free(temp); 
                       return root;

                    }
                    
                }
            }
            else{
                if(root->count>1){
                    root->size=root->size-tc;
                    root->count=root->count-1;
                    return root;
                }
                ll c;
                avl* temp=min_val_node(root->right);
                root->val = temp->val;
                
                root->size=root->size-tc;
                tc=temp->count;
                root->count=temp->count;
                temp->count=1;
                flag=1;
                root->right=delete_node(root->right,temp->val);

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
    bool Search(T val){
        avl* Temp = locate(root,val);
        if(Temp!=NULL){
            return true;
        }
        return false;
    }
    int Count(T val){
        avl* temp=locate(root,val);
        if(temp==NULL){
            return 0;
        }
        return temp->count;
    }
    T lower_bound_H(avl* root,T val){

       
        if(root->val<val){
            if(root->right==NULL){return NULL;}
           lb=lower_bound_H(root->right, val);
           return lb;
        }
        else if(root->val==val){
            lb=val;
            return lb;
        }
        else{
             if(root->left==NULL){
                 lb=root->val;
                 return lb;
            }
        }
        T a=lower_bound_H(root->left,val);
        //cout<<a<<endl;
        if(a!=NULL)
            lb=minimum(root->val,a);
        else lb=root->val;
        return lb;
    }
     avl* LR(avl* node){
        avl *right = node->right;
        avl* left=right->left;
        right->size=node->size;
        if(right->left==NULL) {if(node->left==NULL) node->size=node->count;
        else node->size=node->left->size+node->count;}
        else node->size=node->left->size+right->left->size+node->count;
        right->left = node;
        node->right = left; 
        node->height = max(height(node->left),height(node->right))+1;
        right->height = max(height(right->left),height(right->right))+1;
        return right;
    }
    T lowerbound(T val){
        lb=0;
        return lower_bound_H(root,val);
    }
    T upper_bound_H(avl* root, T val){

        if(root->val<=val){
            if(root->right==NULL){return NULL;}
            ub= upper_bound_H(root->right,val);
            return ub;
        }
        else{
             if(root->left==NULL){
                ub=root->val;
                return ub;
            }
        }
        T a=upper_bound_H(root->left,val);
        if(a!=NULL)
        ub=minimum(root->val,a);
        else
        ub=root->val;
        
        return ub;
    }
     avl* insert_val(avl* node, T val){
        if(node == NULL)
            return(newNode(val));
        if(val<node->val){
            node->size=node->size+1;
            node->left = insert_val(node->left,val);
        }
        else if(val>node->val){
            node->size=node->size+1;
            node->right = insert_val(node->right, val);
        }
        else{
            node->count= node->count+1;
            node->size=node->size+1;
            return node;
        }
        node->height=max(height(node->left),height(node->right))+1;
        int balance=Bal(node);

        if(balance>1 && val<node->left->val)
            return RR(node);
        if(balance<-1 && val>node->right->val)
            return LR(node);
        if(balance>1 && val>node->left->val){
            node->left=LR(node->left);
            return RR(node);
        }
        if(balance<-1 && val<node->right->val){
            node->right= RR(node->right);
            return LR(node);
        }
        return node;
    }
    T upperbound(T val){
        ub=0;
        return upper_bound_H(root,val);
    }
    T max_val_node(avl* node){
        avl* curr = node;
        while(curr->right != NULL)
            curr=curr->right;
        return curr->val;
    }
    T smaller(avl*root,T val){
    
        if(root==NULL){
            return low;
        }
        if(root->val>val){
            return smaller(root->left,val);
        }
        else if(root->val==val){
            low=root->val;
            return low;
        }
        low=max(root->val,smaller(root->right,val));
        return low;
    }
    
    int total, size_low, size_high;
    int Count_range(T lower,T upper){
        total=root->size;
        size_low=0,size_high=0;
        return Count_range_H(root,lower,upper);
    }
    int Count_lower(avl* root,T lower){
        if(root->val>lower){
            return Count_lower(root->left,lower);
        }
        if(root->val<lower){
            size_low+=left_size(root)+root->count;
            return Count_lower(root->right,lower);
        }
        else{
           return size_low+=left_size(root);
        }
    }
    int Count_upper(avl* root,T upper){
        if(root->val<upper){
            return Count_upper(root->right,upper);
        }
        if(root->val>upper){
            size_high+=right_size(root)+root->count;
            return Count_upper(root->left,upper);
        }
        else{
        return size_high+=right_size(root);
        }
    }
    int Count_range_H(avl* root,T lower, T upper){
        int min,max;
        if(!Search(lower)){
            T temp=lowerbound(lower);
            min=Count_lower(root,temp);
           
        }
        else{
            min=Count_lower(root,lower);
            
        }
        if(!Search(upper)){
            T temp=smaller(root,upper);
            max=Count_upper(root,temp);
            
        }
        else{
            max=Count_upper(root,upper);
            
        }
        return total-(min+max);
    }
    void closest_value_H(avl *ptr, T val, T &min_diff, T &min_diff_val) { 
    if (ptr == NULL) 
        return ; 
    if (ptr->val == val) 
    { 
        min_diff_val = val; 
        return; 
    } 
    if (min_diff > abs(ptr->val - val)) 
    { 
        min_diff = abs(ptr->val - val); 
        min_diff_val = ptr->val; 
    } 
    if (val < ptr->val) 
        closest_value_H(ptr->left, val, min_diff, min_diff_val); 
    else
        closest_value_H(ptr->right, val, min_diff, min_diff_val); 
} 

T closestvalue(T val) 
{ 
    T min_diff=INT_MAX, min_diff_val=INT_MAX; 
    closest_value_H(root, val, min_diff, min_diff_val); 
  
    return min_diff_val; 
} 
T KLN(int k){
    T ans = Kth_Largest(root, k);
    return ans;
}
int right_size(avl* root){
    if(root->right!=NULL) return root->right->size;
    return 0;
}
int left_size(avl*root){
    if(root->right!=NULL) return root->size-(right_size(root)+root->count);
    else return root->size-root->count;
}
T Kth_Largest(avl* root, T k){
    if(right_size(root)>=k){
        return Kth_Largest(root->right,k);
    }
    else{
        if(right_size(root)+root->count>=k) return root->val;
        else return Kth_Largest(root->left,k-(right_size(root)+root->count)); 
    }

}
void preordertrav(){
    preorder_H(root);
    cout<<endl;
}

void preorder_H(avl* root){
    if(root==NULL) return;
    cout<<root->val<<" "<<root->size<<endl;
    preorder_H(root->left);
    preorder_H(root->right);
    
}
};

int main(){
Tree<int> a;
    
    //cout<<"mini of 22 is = "<<a.mini(22)<<endl;
}