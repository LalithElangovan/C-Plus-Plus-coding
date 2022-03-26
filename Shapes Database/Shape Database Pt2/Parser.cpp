

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void create_Shape(string name, string type, int loc_x, int loc_y, int size_x, int size_y);
void command_create(string k, stringstream &linestream);
void command_move(string m,stringstream &linestream);
void command_group(string n, stringstream &linestream);
void command_delete(string n,stringstream &linestream);
void command_draw(string n);
bool ShapeNameisFound(string name);
bool GroupNameValid(string name);
bool GlobalCheck(string name);

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        command_create(command, lineStream);
        command_move(command, lineStream);
        command_group(command, lineStream);
        command_delete(command, lineStream);
        command_draw(command);

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        // Once the command has been processed, prompt for the
        // next command
        command="";
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    return 0;
}



void create_Shape(string name, string type, int loc_x, int loc_y, int size_x, int size_y)
{
    Shape* main= new Shape(name,type,loc_x,loc_y,size_x,size_y);
    ShapeNode* g = new ShapeNode;
    g->setShape(main);

    gList->getHead()->getShapeList()->insert(g);
}



void command_create(string k, stringstream &linestream)
{
    if (k == "shape")
    {
        string name, type;
        int loc_x, loc_y, size_x, size_y;

        linestream >> name;
        if(!GlobalCheck(name)){
            cout<<"error: invalid name"<<endl;
            return;
        }
        
        if(ShapeNameisFound(name)||GroupNameValid(name)){
            cout << "error: name " << name << " exists" << endl;
            return;
        }

        
        linestream >> type >> loc_x >> loc_y >> size_x >> size_y;   

        create_Shape(name, type, loc_x, loc_y, size_x, size_y);
        cout<<name<<':'<<type<<' '<<loc_x<<' '<<loc_y<<' '<<size_x<<' '<<size_y<<endl;
    }
}

void command_move(string m,stringstream &linestream){
    if (m=="move"){
        bool more = false;
        string name;
        string groupname;
        linestream >> name;
        linestream >> groupname;
        if(!GlobalCheck(name) || !GlobalCheck(groupname)){
            cout<<"error: invalid name"<<endl;
            return;
        }
        
        if(ShapeNameisFound(name)){
            more=true;
        }
        else{
            cout<<"error: shape "<<name<<' '<<"not found"<<endl;
            return;
        }
        
        more = false;
       
        if(GroupNameValid(groupname)){
            more=true;
        }
        else{
            cout<<"error: group "<<groupname<<' '<<"not found"<<endl;
            return;
        }
        
        if(more){

            
            GroupNode* current = gList->getHead();
            ShapeNode* trav = NULL;
            GroupNode* current2 = gList->getHead();
            while(current!=nullptr){
                if(current->getShapeList()->find(name)!=NULL){
                    trav=current->getShapeList()->remove(name);
                    break;
                }
                current=current->getNext();
            }
            while(current2!=nullptr){
                if(current2->getName()==groupname){
                    current2->getShapeList()->insert(trav);
                }
                current2=current2->getNext();
            }
            cout<<"moved"<<' '<<name<<' '<<"to"<<' '<<groupname<<endl;
        }
    }
}

void command_group(string n, stringstream &linestream){
    if (n == "group")
    {
        string groupname;
 
        
        linestream >> groupname;
        if(!GlobalCheck(groupname)){
            cout<<"error: invalid name"<<endl;
            return;
        }
        
        if(ShapeNameisFound(groupname)||GroupNameValid(groupname)){
            cout << "error: name " << groupname << " exists" << endl;
            return;
        }
        GroupNode* main = new GroupNode(groupname);
        gList->insert(main);
        cout<<groupname<<':'<<' '<<"group"<<endl;
    }
}

void command_delete(string n, stringstream &linestream){
    if(n=="delete"){
        string name;
        linestream >> name;
        
        
        if(!GlobalCheck(name)){
            cout<<"error: invalid name"<<endl;
            return;
        }
        if(!ShapeNameisFound(name) && !GroupNameValid(name)){
            cout<<"error: shape "<<name<<' '<<"not found"<<endl;
            return;
        }
        
        if(GroupNameValid(name)){
            
            GroupNode* current =gList->getHead();
            while(current!=nullptr)
            {
                if(current->getName()==name)
                {
                    
                    ShapeNode* temp = current->getShapeList()->getHead();
                    GroupNode* current2 = gList->getHead();
                    
                    ShapeNode* ptr = current2->getShapeList()->getHead(); 
                    if(ptr==nullptr){
                        current2->getShapeList()->setHead(current->getShapeList()->getHead());
                                    current->getShapeList()->setHead(NULL);
                                    
                                  
                                    GroupNode* removedNode = gList->remove(name);
                                    delete removedNode;
                                    cout<<name<<':'<<' '<<"deleted"<<endl;
                                    return;
                    }
                    while (ptr!=nullptr){
                                if(ptr->getNext()==NULL){
                                    ShapeNode* ptr2=ptr;
                                    ptr2->setNext(temp);
                                    current->getShapeList()->setHead(NULL);
                                    
                                  
                                    GroupNode* removedNode = gList->remove(name);
                                    delete removedNode;
                                    cout<<name<<':'<<' '<<"deleted"<<endl;
                                    
                                    
                                    return;
                                }
                        ptr=ptr->getNext();
                    }
                }
                current=current->getNext();
            }
        }
        else if (ShapeNameisFound(name)){
            GroupNode* current = gList->getHead();
            while(current!=NULL){
                if(current->getShapeList()->find(name)!=nullptr){
                    delete current->getShapeList()->remove(current->getShapeList()->find(name)->getShape()->getName());
                    cout<<name<<':'<<' '<<"deleted"<<endl;
                }
                current=current->getNext();
            }
            
        }
    }
}

void command_draw(string n){
    if(n=="draw"){
        cout<<"drawing:"<<endl;
        gList->print();
    }
}




bool ShapeNameisFound(string name){
    bool checker = false;
    GroupNode* current = gList->getHead();
    while (current!=nullptr){
        if(current->getShapeList()->find(name)!=nullptr){
            checker=true;
            return checker;
        }    
        current=current->getNext();
    }
    return checker;
}

bool GroupNameValid(string name){
    bool verdict = false;
    GroupNode* current = gList->getHead();
    while(current!=nullptr){
        if(current->getName()==name){
            verdict = true;
            return verdict;
        }
        current=current->getNext();
    }
    return verdict;
}

bool GlobalCheck(string name){
    bool valid = true;
    for (int i = 0; i < 6; i++)
    {
        if (name == keyWordsList[i])
        {
            valid = false;
        }
    }
    for (int j = 0; j < 3; j++)
    {
        if (name == shapeTypesList[j])
        {
            valid = false;
        }
    }
    return valid;
}





