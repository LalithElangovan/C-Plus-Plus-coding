#include "GroupList.h"

    GroupList::GroupList(){
        head=nullptr;
    }                                 // sets head to nullptr
    GroupList::~GroupList(){
        GroupNode* ptr=head;
        GroupNode* current=NULL;
        while(ptr != NULL){
            current=ptr;
            ptr=ptr->getNext();
            delete current;
        }
    }                     // deletes all list nodes, including all the ShapeList
                                      // attached to each GroupNode
    
    GroupNode* GroupList::getHead() const{
        
        return head;
    }       // returns the head pointer
    void GroupList::setHead(GroupNode* ptr){
        head=ptr;
    }     // sets the head pointer to ptr
    void GroupList::insert(GroupNode* s){
        GroupNode* tptr=head;
        if(head==NULL)
        {
            head=s;
            return;
        }
            while(tptr!=NULL){
                if(tptr->getNext()==NULL){
                    tptr->setNext(s);
                    return;
                }
                tptr=tptr->getNext();
            }
    }        // inserts the node pointed to by s at the end of the list

    
    
  GroupNode* GroupList::remove(string name){
    if(head == nullptr)
        return nullptr;
    
    GroupNode* temp = nullptr;
    GroupNode* current = head;

    
    while(current != nullptr){
        if(current->getName() == name)
            break;
        else{
            temp = current;
            current = current->getNext();
        }
    }
    
    // Remove first node
    if(temp == nullptr){
        head = current->getNext();
        return current;
    }
    
    // Other cases where node is found
    else if(current != nullptr){
        temp->setNext(current->getNext());
        return current;
    }
    
    // If shape not found
    return nullptr;
}



  
    void GroupList::print() const{
        GroupNode* current = head;
        if(head==NULL)
            return;
        while(current!=NULL){
            cout<<current->getName()<<':'<<endl;
            current->print();
            current=current->getNext();
        }
    }               // prints the list, one GroupNode at a time




