/*
  Ankit Das
  C++ implementation of DoublyLinkedList
  Assignment 2
*/

#include<iostream>

class DoublyLinkedList{
    private:
        struct node{
            int data;
            node *next;
            node *previous;
        };

        node *head;
        unsigned int size;

        void clean(node *ptr){
            ptr = nullptr;
            free((void*)ptr);
        }

    public:
        DoublyLinkedList(){
            this->head = nullptr;
            size = 0;
        }

        ~DoublyLinkedList(){
            clean(this->head);
        }

        void insertFront(int data){
            if(this->head == nullptr){
                this->head = new node();
                this->head->data = data;
                this->head->previous = nullptr;
                this->head->next = nullptr;
                this->size++;
                return;
            }

            node *temp = new node();
            temp->data = data;
            temp->next = this->head;
            temp->previous = nullptr;

            this->head->previous = temp;
            this->head = temp;

            this->size++;
            clean(temp);          
        }

        void insertRear(int data){
            if(this->head == nullptr){
                this->head = new node();
                this->head->data = data;
                this->head->next = nullptr;
                this->head->previous = nullptr;
                this->size++;
                return;
            }

            node *temp = this->head;
            while(temp->next != nullptr){
                temp = temp->next;
            }

            temp->next = new node();
            temp->next->data = data;
            temp->next->next = nullptr;
            temp->next->previous = temp;
            
            this->size++;
            clean(temp);
        }

        void insertAt(int data, int position){         
            if(position < this->size && position > 0){
                node *current = this->head;
                while(--position && current){
                    current = current->next;
                }
                node *temp = new node();
                temp->data = data;
                temp->next = current->next;
                temp->previous = current;
                current->next = temp;
                
                this->size++;

                clean(temp);
                clean(current);
            }

            else if(position == 0){
                insertFront(data);
            }

            else if(position == this->size){
                insertRear(data);
            }

            else{
                std::cout<<"SizeError! Cannot Add\n";
            }
        }

        int getFront(){
            return this->head->data;
        }

        int getRear(){
            node *temp = this->head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            int save = temp->data;
            clean(temp);
            return save;
        }

        int getAt(int position){
            if(this->head == nullptr){
                return 0;
            }
            
            if(position < this->size && position > 0){
                node *current = this->head;
                while(position--){
                    current = current->next;
                }

                int save = current->data;
                clean(current);

                return save;
            }

            else if(position == 0){
                return getFront();
            }

            else if(position == this->size){
                return getRear();
            }

            else{
                std::cout<<"Invalid Position! Try again";
                return 0;
            }
            return 0; // execution never reaches here
        }

        void deleteFront(){
            if(this->head == nullptr){
                return;
            } 

            if(this->head->next == nullptr){
                clean(this->head);
                this->head = nullptr;
                return;
            }

            this->head = this->head->next;
            this->head->previous = nullptr;
            this->size--;
        }

        void deleteRear(){
            if(this->head == nullptr){
                return;
            }

            if(this->head->next == nullptr){
                clean(this->head);
                this->head = nullptr;
                return;
            }
            
            node *current = this->head;

            while(current->next->next != nullptr){
                current = current->next;
            }
            
            clean(current->next);
            current->next = nullptr;
            this->size--;
            clean(current);
        }

        void deleteBy(int value){
            if(this->head == nullptr){
                return;
            }
            
            node *current = this->head;
            if(current && current->data == value && this->head->next != nullptr){
                    this->head = this->head->next;
                    this->head->previous = nullptr;

                    this->size--;
                    clean(current);
                    return;
            }

            else if(current && current->data == value && current->next == nullptr){
                clean(current);
                this->head = nullptr;
                return;
            }

            else{
                node *prev = current;
                while(current->next != nullptr && current->data != value){   
                    current = current->next;
                }  

                if(current->next == nullptr && current->data == value){
                    current->previous->next = nullptr;
                    clean(current);
                    return;
                }
            
                if(current->data == value){
                    std::cout<<"ELEMENT "<<current->data<<" DELETED!";
                    prev->next = prev->next->next;
                    prev->next->previous = prev;
                    this->size--;
                }

                else{
                    std::cout<<"ELEMENT "<<value<<" NOT FOUND!";
                }
            clean(current);
            }
        }

        void deleteAt(int position){
            if(position < this->size && position > 0){
                node *current = this->head;
                while(--position){
                    current = current->next;
                }
                std::cout<<"DELETING ELEMENT AT "<<getAt(position)<<"\n";
                node *save = current->next->next;
                clean(current->next);
                current->next = save;
                current->next->previous = current;
                
                this->size--;
                clean(save);
                clean(current);
                return;
            }

            else if(position == 0){
                deleteFront();
            }

            else if(position == this->size){
                deleteRear();
            }

            else{
                std::cout<<"Invalid Position! Try again";
            }
        }

        void replace(int valueToRemove, int valueToAdd){
            if(this->head == nullptr){
                return;
            }

            if(this->head->data == valueToRemove){
                this->head->data = valueToAdd; 
            }

            else{
                node *current = this->head;    
                while(current->next != nullptr && current->data != valueToRemove){
                    current = current->next;
                }

                if(current->data == valueToRemove){
                    current->data = valueToAdd;
                }

                else{
                    std::cout<<"VALUE "<<valueToRemove<<" NOT FOUND!";
                }
                clean(current);
            }
        }

        void reverse(){
            if(this->head == nullptr){
                return;
            }
            
            node *temp = nullptr; 
            node *current = this->head; 

            while (current != nullptr){ 
               temp = current->previous; 
               current->previous = current->next; 
               current->next = temp;             
               current = current->previous; 
            } 

            if(temp != nullptr){
               this->head = temp->previous; 
            }
        }

        void concatenate(){
            node *head_second = new node();
            
            unsigned int n = 0;
            std::cout<<"ENTER SIZE: ";
            std::cin>>n;

            std::cout<<"ENTER SECOND LIST: ";
            std::cin>>head_second->data;
            head_second->next = nullptr;
            head_second->previous = nullptr;
            n--;

            node *current = head_second;
            
            while(n--){
                node *temp = new node();
                std::cin>>temp->data;
                temp->next = nullptr;
                temp->previous = current;
                current->next = temp;

                current = current->next;
            } 

            current->next = this->head;
            this->head->previous = current;
            this->head = head_second;

            clean(current);
            clean(head_second);     
        }

        void display(){       
            if(this->head == nullptr){
                std::cout<<"EMPTY!";    
                return;
            }

            node *current = this->head;

            while(current->next != nullptr){
                std::cout<<current->data<<" <-> ";
                current = current->next;
            }

            std::cout<<current->data<<" <-> ";
            clean(current);
            std::cout<<"NULL ";
        }

        void reverseTraversal(){
            if(this->head == nullptr){
                std::cout<<"EMPTY!";
                return;
            }

            node *current = this->head;
            while(current->next != nullptr){
                current = current->next;
            }

            while(current->previous != nullptr){
                std::cout<<current->data<<" <-> ";
                current = current->previous;
            }
            std::cout<<current->data<<" <-> HEAD";
        }
};

int main(){
    DoublyLinkedList D;
    unsigned int choice = 0;
    unsigned int position = 0;
    int data = 0;

    while(true){
        std::cout<<"-- MENU --\n";
        std::cout<<"1. INSERT AT FRONT\n";
        std::cout<<"2. INSERT AT REAR\n";
        std::cout<<"3. INSERT AT POSITION\n";
        std::cout<<"4. GET FRONT\n";
        std::cout<<"5. GET REAR\n";
        std::cout<<"6. GET AT\n";
        std::cout<<"7. DELETE FRONT\n";
        std::cout<<"8. DELETE REAR\n";
        std::cout<<"9. DELETE AT POSITION\n";
        std::cout<<"10. DELETE BY ELEMENT\n";
        std::cout<<"11. REPLACE\n";
        std::cout<<"12. REVERSE\n";
        std::cout<<"13. CONCATENATE\n";
        std::cout<<"14. DISPLAY\n";
        std::cout<<"15. EXIT\n";
        std::cout<<"ENTER CHOICE: ";
        std::cin>>choice;

        switch (choice)
        {
        case 1:
            std::cout<<"ENTER DATA: ";
            std::cin>>data;
            D.insertFront(data);
            break;

        case 2:
            std::cout<<"ENTER DATA: ";
            std::cin>>data;
            D.insertRear(data);
            break;

        case 3:
            std::cout<<"ENTER DATA: ";
            std::cin>>data;
            std::cout<<"ENTER POSITION: ";
            std::cin>>position;
            D.insertAt(data,position);
            break;

        case 4:
            std::cout<<"FRONT: "<<D.getFront();
            break;

        case 5:
            std::cout<<"REAR: "<<D.getRear();
            break;

        case 6:
            std::cout<<"ENTER POSITION: ";
            std::cin>>position;
            std::cout<<"["<<position<<"]: " <<D.getAt(position);
            break;

        case 7:
            D.deleteFront();
            break;

        case 8:
            D.deleteRear();
            break;

        case 9:
            std::cout<<"ENTER POSITION: ";
            std::cin>>position;
            D.deleteAt(position);
            break;

        case 10:
            std::cout<<"ENTER ELEMENT: ";
            std::cin>>data;
            D.deleteBy(data);
            break;

        case 11:
            std::cout<<"ENTER DATA TO REPLACE: ";
            std::cin>>data;
            std::cout<<"ENTER DATA TO REPLACE WITH: ";
            std::cin>>position;
            D.replace(data,position);
            break;

        case 12:
            D.reverse();
            break;

        case 13:
            D.concatenate();
            break;

        case 14:
            D.display();
            //D.reverseTraversal();
            break;

        case 15:
            return 0;

        default:
            std::cout<<"INVALID CHOICE! TRY AGAIN!";
            break;
        }

        std::cout<<"\n\n";
    }

    return 0;
}
