#include<iostream>

class LinkedList{
    private:
        struct node{
            public:
                int data;
                node *next;
        };

        node* head;
        unsigned int size = 0;

    public:
        LinkedList(){
            this->head = nullptr;
        }

        void insertFront(int data){            
            node* temp = new node();
            temp->data = data;
            temp->next = this->head;
            this->head = temp;
            this->size++;
            temp = nullptr;
            free((void*)temp);
        }

        void insertRear(int data){
            if(this->head == nullptr){
                this->head = new node();
                this->head->data = data;
                this->head->next = nullptr;
            }
            else{
                node *save = this->head;
                while(save->next != nullptr){
                    save = save->next;
                }
                node *temp = new node();
                temp->data = data;
                temp->next = nullptr;
                save->next = temp;
                temp = nullptr;
                save = nullptr;
                free((void*)temp);
                free((void*)save);
            }
            this->size++;
        }

        void insertAt(int position, int data){
            
            if(position < this->size && position > 0){
                node *current = this->head;
                while(--position && current){
                    current = current->next;
                }
                node *temp = new node();
                temp->data = data;
                temp->next = current->next;
                current->next = temp;
                
                this->size++;

                temp = nullptr;
                current = nullptr;

                free((void*)temp);
                free((void*)current);
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
            if(this->head == nullptr){
                return 0;
            }
            
            return this->head->data;
        }

        int getRear(){
            if(this->head == nullptr){
                return 0;
            }
            
            node *current = this->head;
            while(current->next){
                current = current->next;
            }

            int save = current->data;
            current = nullptr;
            free((void*)current);
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

                current = nullptr;
                free((void*)current);

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

        int getSize(){
            if(this->head == nullptr){
                return 0;
            }
            
            return this->size;
        }

        void deleteFront(){
            if(this->head == nullptr){
                return;
            }
            
            node *save = this->head->next;
            std::cout<<"ELEMENT WITH VALUE "<<this->head->data<<" DELETED!\n";
            free((void*)this->head);
            this->head = save;
            this->size--;
            save = nullptr;
            free((void*)save);
        }

        void deleteRear(){
            if(this->head == nullptr){
                return;
            }
            
            node *current = this->head;

            while(current->next->next){
                current = current->next;
            }
            std::cout<<"ELEMENT WITH VALUE "<<current->next->data<<" DELETED!\n";
            free((void*)current->next);
            current->next = nullptr;
            this->size--;
        }

        void deleteAt(int position){
            if(position < this->size && position > 0){
                node *current = this->head;
                while(--position){
                    current = current->next;
                }
                std::cout<<"DELETING ELEMENT AT "<<getAt(position)<<"\n";
                node *save = current->next->next;
                free((void*)current->next);
                current->next = save;
                
                save = nullptr;
                free((void*)save);
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

        void deleteByValue(int value){
            if(this->head == nullptr){
                return;
            }
            
            node *current = this->head;
            node *previous = nullptr;

            if(current && current->data == value){
                    this->head = this->head->next;
                    free((void*)current);
                    return;
            }

            else{
                while(current && current->data != value){
                    previous = current;
                    current = current->next;
                }  

                if(current == nullptr){
                    return;
                }
            
            previous->next = previous->next->next;
            free((void*)current);
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
            
                while(current && current->data != valueToRemove){
                    current = current->next;
                }

                if(current == nullptr){
                    return;
                }
                
                if(current->data == valueToRemove){
                    current->data = valueToAdd;
                }

                else{
                    std::cout<<"VALUE "<<valueToRemove<<" NOT FOUND!";
                }
            }
        }

        void reverse(){
            if(this->head == nullptr){
                return;
            }

            node *previous = nullptr;
            node *current = this->head;
            node *next = nullptr;

            while(current){
                next = current->next;
                current->next = previous;

                previous = current;
                current = next;
            }
            
            this->head = previous;

            current = nullptr;
            previous = nullptr;
            next = nullptr;
            free((void*)current);
            free((void*)previous);
            free((void*)next);
        }

        void concatenate(){
            node *head_second = new node();
            
            unsigned int n = 0;
            std::cout<<"ENTER SIZE: ";
            std::cin>>n;

            std::cout<<"ENTER SECOND LIST: ";
            std::cin>>head_second->data;
            head_second->next = nullptr;
            n--;

            node *current = head_second;
            
            while(n--){
                node *temp = new node();
                std::cin>>temp->data;
                temp->next = nullptr;
                current->next = temp;
                current = current->next;
            } 

            current = this->head;
            while(current->next){
                current = current->next;
            }  

            current->next = head_second;
            current = nullptr;
            head_second = nullptr;

            free((void*)current);   
            free((void*)head_second);     
        }
        

        void display(){            
            if(this->head == nullptr){
                std::cout<<"LIST EMPTY!";
                return;
            }

            node *current = this->head;

            while(current){
                std::cout<<current->data<<"->";
                current = current->next;
            }
            current = nullptr;
            free((void*)current);
            std::cout<<"NULL ";
        }
};


// Uneccessary driver bullshit
int main(){
    LinkedList l;
    unsigned int choice = 0;
    unsigned int position = 0;
    int data = 0;

    while(true){
    std::cout<<"-- MENU --\n";
    std::cout<<"1. INSERT AT FRONT\n";
    std::cout<<"2. INSERT AT REAR\n";
    std::cout<<"3. INSERT AT POSITION\n";
    std::cout<<"4. SHOW FRONT\n";
    std::cout<<"5. SHOW REAR\n";
    std::cout<<"6. SHOW AT POSITION\n";
    std::cout<<"7. SHOW SIZE\n";
    std::cout<<"8. DELETE AT FRONT\n";
    std::cout<<"9. DELETE AT REAR\n";
    std::cout<<"10. DELETE AT POSITION\n";
    std::cout<<"11. DELETE BY VALUE\n";
    std::cout<<"12. REVERSE THE LIST\n";
    std::cout<<"13. REPLACE VALUE\n";
    std::cout<<"14. CONCATENATE\n";
    std::cout<<"15. DISPLAY LIST\n";
    std::cout<<"16. EXIT\n";
    std::cout<<"ENTER CHOICE: ";
    std::cin>>choice;

    switch (choice)
    {
    case 1:
        std::cout<<"ENTER DATA: ";
        std::cin>>data;
        l.insertFront(data);
        break;
    
    case 2:
        std::cout<<"ENTER DATA: ";
        std::cin>>data;
        l.insertRear(data);
        break;
    
    case 3:
        std::cout<<"ENTER DATA: ";
        std::cin>>data;
        std::cout<<"ENTER POSITION: ";
        std::cin>>position;
        l.insertAt(position,data);
        break;

    case 4:
        std::cout<<"FRONT: "<<l.getFront()<<"\n";
        break;
    
    case 5:
        std::cout<<"REAR: "<<l.getRear()<<"\n";
        break;
    
    case 6:
        std::cout<<"ENTER POSITION: ";
        std::cin>>position;
        std::cout<<"ELEMENT AT "<<position<<" IS "<<l.getAt(position)<<"\n";
        break;
    
    case 7:
        std::cout<<"SIZE: "<<l.getSize()<<"\n";
        break;
    
    case 8:
        l.deleteFront();
        break;
    
    case 9:
        l.deleteRear();
        break;
    
    case 10:
        std::cout<<"ENTER POSITION: ";
        std::cin>>position;
        l.deleteAt(position);
        break;

    case 11:
        std::cout<<"ENTER VALUE: ";
        std::cin>>data;
        l.deleteByValue(data);
        break;

    case 12:
        l.reverse();
        std::cout<<"LIST REVERSED\n";
        break;
    
    case 13:
        std::cout<<"ENTER VALUE TO REMOVE: ";
        std::cin>>position;
        std::cout<<"ENTER VALUE TO ADD: ";
        std::cin>>data;
        l.replace(position,data);
        break;

    case 14:
        l.concatenate();
        break;

    case 15:
        std::cout<<"--\n";
        l.display();
        std::cout<<"\n";
        break;
    
    case 16:
        return 0;
    
    default:
        break;
    }

    std::cout<<"\n\n";
    }

    return 0;
}