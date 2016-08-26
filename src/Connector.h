#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Cmd.h"

class Connector : public Base {
    private:
        Base* left;
        Base* right;
        string type;
    public:
        Connector() {};
        ~Connector() 
        {
            delete left;
            delete right;
        };

        Connector(string t) : type(t) {};

        Connector(Base* l, Base* r, string t) : left(l), right(r), type(t) {};

        void addLeft(Base* l) 
	{
            left = l;
        };

        void addRight(Base* r) 
	{
            right = r;
        };

        int run() 
        {
            int status = left->run();

            if (status == 0 && type == "yes") //left side succeeds and type is &&
            {
                status = right->run();        
            }

            else if (status != 0 && type == "no") //left side fails and type is || 
            {
                status = right->run();
            }

            else if (type == "skip") //run anyway since type is ;
            {
                status = right->run();                
            }

            return status;
        };

};
#endif
