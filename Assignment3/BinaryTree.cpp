/*
Ankit Das
Submission for Assignment 3
Binary Tree written in C++
*/

#include<iostream>
#include<stack>
#include<queue>

class BinaryTree{
    private:
        struct Node {
                long double data;
                Node* left;
                Node* right;
            
                Node(){
                    this->data = 0;

                    this->left = nullptr;
                    this->right = nullptr;
                }

                Node(long double data){
                    this->data = data;

                    this->left = nullptr;
                    this->right = nullptr;
                }
        };
    
    Node *root;

    void clean(Node* temp){
        temp = nullptr;
        free((void*)temp);
    }

    public:
        BinaryTree(){
            this->root = nullptr;
        }

        ~BinaryTree(){
            clean(this->root);
        }  

        Node* getRoot(){
            if(this->root != nullptr){
                return this->root;
            }

            return nullptr;
        }

        void addNode(long double data, bool side){
            if(this->root == nullptr){
                this->root = new Node(data);
                return;
            }
            
            Node* current = this->root;

            if(current->left == nullptr && !side){
                current->left = new Node(data);
            }

            else if(current->right == nullptr && side){
                current->right = new Node(data);
            }

            else if(current->right != nullptr && side){
                while(current->right != nullptr){
                    current = current->right;
                }

                current->right = new Node(data);
            }
            
            else if(current->left != nullptr && !side){
                while(current->left != nullptr){
                    current = current->left;
                }

                current->left = new Node(data);
            }
        }

        void inorder(Node* root){
            if(root == nullptr){
                return;
            }

            inorder(root->left);
            std::cout<<root->data<<" ";
            inorder(root->right);
        }

        void preorder(Node* root){
            if(root == nullptr){
                return;
            }

            std::cout<<root->data<<" ";
            preorder(root->left);
            preorder(root->right);
        }

        void postorder(Node* root){
            if(root == nullptr){
                return;
            }

            postorder(root->left);
            postorder(root->right);
            std::cout<<root->data<<" ";
            
        }

        void inorder(){
            if(this->root == nullptr){
                return;
            }

            std::stack<Node *> Stack;
            Node* current = this->root;

            while(current != nullptr || !Stack.empty()){
                while(current != nullptr){
                    Stack.push(current);
                    current = current->left;
                }

                current = Stack.top();
                Stack.pop();

                std::cout<<current->data<<" ";

                current = current -> right;
            }
        }
        
        void preorder(){
            if(this->root == nullptr){
                return;
            }

            std::stack<Node*> Stack;
            Stack.push(this->root);

            while(!Stack.empty()){
                Node* current = Stack.top();

                std::cout<<current->data<<" ";
                Stack.pop();

                if(current->right){
                    Stack.push(current->right);
                }

                if(current->left){
                    Stack.push(current->left);
                }
            }
        }
        
        void postorder(){
            if(this->root == nullptr){
                return;
            }

            std::stack<Node*> Stack;
            Stack.push(this->root);

            std::stack<double> Output;

            while(!Stack.empty()){
                Node* current = Stack.top();
                Stack.pop();

                Output.push(current->data);

                if(current->left){
                    Stack.push(current->left);
                }

                if(current->right){
                    Stack.push(current->right);
                }
            }

            while (!Output.empty()){
                std::cout<<Output.top()<<" ";
                Output.pop();
            }
        }

        void Delete(Node* deepest){ 
            std::queue<Node*> Queue; 
            Queue.push(this->root); 
           
            Node* temp; 
            while(!Queue.empty()){ 
                temp = Queue.front(); 
                Queue.pop(); 

                if(temp == deepest) { 
                    temp = nullptr; 
                    clean(deepest); 
                    return; 
                } 

                if (temp->right) { 
                    if (temp->right == deepest){ 
                        temp->right = nullptr; 
                        clean(deepest); 
                        return; 
                    } 

                    else {
                        Queue.push(temp->right); 
                    }
                } 

                if (temp->left) { 
                    if (temp->left == deepest) { 
                        temp->left = nullptr; 
                        clean(deepest); 
                        return; 
                    } 

                    else {
                        Queue.push(temp->left); 
                    }
                } 
            } 
        } 
  
        void deleteNode(double data){ 
            std::queue<Node*> Queue; 
            Queue.push(root); 

            Node *temp; 
            Node *key = nullptr; 

            while (!Queue.empty()) 
            { 
                temp = Queue.front(); 
                Queue.pop(); 

                if (temp->data == data) 
                    key = temp; 

                if (temp->left) 
                    Queue.push(temp->left); 

                if (temp->right) 
                    Queue.push(temp->right); 
            } 

            double value = temp->data; 
            Delete(temp); 
            key->data = value; 
        } 
};

int main(){
    BinaryTree BT;
    unsigned int choice;
    int side;
    long double data;
    
    while(true){
        std::cout<<"-- MENU --\n";
        std::cout<<"1. ADD NODE\n";
        std::cout<<"2. RECURSIVE INORDER TRAVERSAL\n";
        std::cout<<"3. RECURSIVE PREORDER TRAVERSAL\n";
        std::cout<<"4. RECURSIVE POSTORDER TRAVERSAL\n";
        std::cout<<"5. ITERATIVE INORDER TRAVERSAL\n";
        std::cout<<"6. ITERATIVE PREORDER TRAVERSAL\n";
        std::cout<<"7. ITERATIVE POSTORDER TRAVERSAL\n";
        std::cout<<"8. DELETE NODE\n";
        std::cout<<"9. EXIT\n\n";
        std::cout<<"ENTER CHOICE: ";

        std::cin>>choice;

        switch(choice){
            case 1:
                std::cout<<"ENTER DATA: ";
                std::cin>>data;

                std::cout<<"ENTER SIDE: ";
                std::cin>>side;

                if(!(side < 0 || side > 1)){
                    BT.addNode(data,side);
                    std::cout<<"DATA ADDED!\n";   
                }

                else{
                    std::cout<<"INVALID SIDE! TRY AGAIN!";
                }
                break;
            
            case 2:
                BT.inorder(BT.getRoot());
                break;

            case 3:
                BT.preorder(BT.getRoot());
                break;

            case 4:
                BT.postorder(BT.getRoot());
                break;
            
            case 5:
                BT.inorder();
                break;

            case 6:
                BT.preorder();
                break;

            case 7:
                BT.postorder();
                break;
            
            case 8:
                std::cout<<"ENTER DATA: ";
                std::cin>>data;
                BT.deleteNode(data);
                break;

            case 9:
                return 0;
            
            default:
                std::cout<<"INVALID CHOICE! TRY AGAIN";
                break;
        }

        std::cout<<"\n\n";
    }

    return 0;
}
