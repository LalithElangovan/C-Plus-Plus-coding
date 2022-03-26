
#include "ShapeNode.h"
    ShapeNode::ShapeNode(){
        myShape=nullptr;
        next=nullptr;
    }                   // sets myShape and next to nullptr
    ShapeNode::~ShapeNode(){
        delete myShape;
        myShape=nullptr;
    }                  // deletes the shape pointed to by myShape
    Shape* ShapeNode::getShape() const{
        return myShape;
    }       // returns myShape
    void ShapeNode::setShape(Shape* ptr){
        myShape=ptr;
    }     // sets myShape to ptr
    ShapeNode* ShapeNode::getNext() const{
        return next;
    }    // returns next
    void ShapeNode::setNext(ShapeNode* ptr){
        next=ptr;
    }  // sets next to ptr
    void ShapeNode::print() const{
        myShape->draw();
    }            // prints the ShapeNode
