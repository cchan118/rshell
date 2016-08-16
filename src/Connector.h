#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Cmd.h"

enum ConType {success, failure, next};

class Connector : public Base {
    private:
        Base* left;
        Base* right;
        ConType type;
    public:
        Connector() { };
        Connector(ConType t) : type(t) {};
        Connector(Base* l, Base* r, ConType t) : left(l), right(r), 
            type(t) { };
        void addLeft(Base* l) {
            left = l;
        };
        void addRight(Base* r) {
            right = r;
        };
        int run() 
        {
            int status = left->run();
            if (status == 0 && type == success)
            {
                status = right->run();        
            }
            else if (status != 0 && type == failure)
            {
                status = right->run();
            }
            else if (type == next)
            {
                status = right->run();                
            }
            return status;
        };
        ~Connector() 
        {
            delete left;
            delete right;
        };
};
#endif
