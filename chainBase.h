#include "card.h"
#include "cardFactory.h"

// ChainBase is an abstract chain interface used to reference chains of any type from the Player class
class ChainBase { 
protected:
    bool base = true; // true if object is of type ChainBase. False if object is of type Chain<T>
public:
    ChainBase(){};  // Default constructor
    ChainBase( bool b ) : base(b) {};  // Constructor with bool variable
    bool isEmpty() { return base; };  // Returns true if object is of type ChainBase, false if object is of Chain<T>.
    virtual void print(ostream& o) { o << "Empty chain"; };  // Prints ChainBase - Used when we print empty chains
    virtual int sell() { return 0; };
    virtual ChainBase& operator+=(Card* c) { return *this; }; // Return *this because Chain<T> has not been initialized
    // Insertion operator to print Chain on an std::ostream. 
    friend ostream& operator<<(ostream& o, ChainBase& cb) {
        cb.print(o);
        return o;
    };
};