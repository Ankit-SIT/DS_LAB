/*
Ankit Das
Submission for Part 2 of Assignment3
Written in C++
*/

#include<iostream>
#include<stack>

class BinarySearchTree{
    private:
        struct Node{
            double data;

            Node* left;
            Node* right;

            Node(double data){
                this->data = data;
                this->left = nullptr;
                this->right = nullptr;
            }

            Node(){
                this->data = 0.0;
                this->left = nullptr;
                this->right = nullptr;
            }
        };

        Node *root;

        void clean(Node *ptr){
            ptr = nullptr;
            free((void*)ptr);
        }
    
    public:
        BinarySearchTree(){
            this->root = nullptr;
        }

        ~BinarySearchTree(){
            clean(this->root);
        }

        Node* getRoot(){
            return this->root;
        }

        void setRoot(Node* root){
            this->root = root;
        }

        void addNode(double data){
            if(this->root == nullptr){
                this->root = new Node(data);

                return;
            }

            Node *current = this->root;
            while(current != nullptr){
                if(current->data > data){
                    if(current->left != nullptr){
                        current = current->left;
                    }

                    else{
                        current->left = new Node(data);
                        clean(current);
                        return;
                    }
                }

                else if(current->data < data){
                    if(current->right != nullptr){
                        current = current->right;
                    }

                    else{
                        current->right = new Node(data);
                        clean(current);
                        return;
                    }
                }
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

        Node* min(Node* root){
            if (root == nullptr) {
                return nullptr;
            }

            Node* temp = root;

            while(temp->left != nullptr){
                temp = temp->left;
            }

            return temp;

        }


        Node* Delete(Node* root, double data){
            if (root == nullptr) {
               return nullptr;
            }

            if (data < root->data) {  // data is in the left sub tree.
                root->left = Delete(root->left, data);
            } 
            
            else if (data > root->data) { // data is in the right sub tree.
                root->right = Delete(root->right, data);
            } 
            
            else {
               if (root->left == nullptr && root->right == nullptr) {
                  delete(root); 
                  root = nullptr;
               }

               else if (root->left == nullptr) {
                  Node *temp = root; 
                  root = root->right;
                  delete temp;
               }

               else if (root->right == NULL) {
                  Node *temp = root; 
                  root = root->left;
                  delete temp;
               }

               else {
                  Node *temp = min(root->right); 
                  root->data = temp->data; 
                  root->right = Delete(root->right, temp->data); 
               }
            }

    return root; 
    }
};  

int main(){
    BinarySearchTree BST;    
    unsigned int choice;
    int side;
    double data;
    
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

                BST.addNode(data);
                break;
            
            case 2:
                BST.inorder(BST.getRoot());
                break;

            case 3:
                BST.preorder(BST.getRoot());
                break;

            case 4:
                BST.postorder(BST.getRoot());
                break;
            
            case 5:
                BST.inorder();
                break;

            case 6:
                BST.preorder();
                break;

            case 7:
                BST.postorder();
                break;
            
            case 8:
                std::cout<<"ENTER DATA: ";
                std::cin>>data;
                BST.Delete(BST.getRoot(), data);
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
