#include <valarray>

#include "ShapeList.h"
#include "ShapeNode.h"

    ShapeList::ShapeList(){
        head=nullptr;
    }                        // sets head to nullptr
    ShapeList::~ShapeList(){
        ShapeNode* ptr=head;
        ShapeNode* current=NULL;
        while(ptr != NULL){
            current=ptr;
            ptr=ptr->getNext();
            delete current;
        }
    }                       // deletes all list nodes starting
                                        // with head plus associated Shapes
    
    ShapeNode* ShapeList::getHead() const{
        return head;
    }         // returns the head pointer
    void ShapeList::setHead(ShapeNode* ptr){
        head=ptr;
    }       // sets the head pointer to ptr
    
    ShapeNode* ShapeList::find(string name) const{
        ShapeNode* tptr = head;
        while (tptr != NULL){
            if(tptr->getShape()->getName()==name)
                return tptr;
            tptr=tptr->getNext();
        }
        return nullptr;
    } // finds a shape node with the specified shape name
                                        // returns a pointer to the node if found, otherwise
                                        // returns nullptr if the node is not found
    void ShapeList::insert(ShapeNode* s){
        ShapeNode* tptr=head;
        if(head==NULL){
            head=s;
        }
        else{
            while(tptr->getNext()!=NULL){
                tptr=tptr->getNext();
            }
            tptr->setNext(s);
            s->setNext(NULL);
        }
        return;
    }          
    // inserts the node pointed to by s at the end
                                        // of the list; s should never be nullptr
    ShapeNode* ShapeList::remove(string name){
        ShapeNode* current=head;
        ShapeNode* temp=NULL;
        //If Name is first node 
        if(head==NULL)
            return NULL;
        if(current->getShape()->getName()==name)
        {
            temp=current;
            current=temp->getNext();
            head=current;
            temp->setNext(NULL);
            return temp;
        }
        while(current != NULL){
            if(current->getNext()!=NULL){
                if(current->getNext()->getShape()->getName()==name){
                    temp=current->getNext();
                    current->setNext(temp->getNext());
                    temp->setNext(NULL);
                    return temp;
                }
            }
            else if ((current->getNext()== NULL)&&(current->getShape()->getName()==name)){
                 temp=current;
                 temp->setNext(NULL);
                 return temp;
            }
            current=current->getNext();
        }
        return temp;
    }     // removes the node with the shape called name
                                        // returns a pointer to the removed node or
                                        // nullptr is a node with name does not exist
    
    
    
    void ShapeList::print() const{
        ShapeNode* current = head;
        if(head==NULL)
            return;
        while(current!=NULL){
            current->print();
            current=current->getNext();
        }
    }               // prints the list
