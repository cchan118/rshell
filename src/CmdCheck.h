#ifndef CMDCHECK_H
#define CMDCHECK_H

#include "Connector.h"
#include <string.h>
#include <sstream>
#include <vector>
#include <unistd.h>

class CmdCheck {
    public:
        CmdCheck() {};
        Base* check(istringstream &ss, Base* head = 0) 
        {
            string token;
            vector<string> v;
            string con = ""; 
            
            while (ss >> token) //gets input from string stream and doesnt echo quotation marks
            {
                if (token.at(0) == '"') 
                {
                    token = token.substr(1, token.size() - 2);
                } 

		//Anything that appears after a # character should be considered a comment. 
                else 
                {
                    bool comment = false;
                    for (unsigned i = 0; i < token.size(); ++i) 
                    {
                        if (token.at(i) == '#') 
                        {
                            token = token.substr(0, i);
                            comment = true;
                        }
                    }
                    if (comment == true)
                    {
                        break;
                    }
                }
                
		// identifies token as either ; && or || and places into vector
                if (token.at(token.size() - 1) == ';') 
                {
                    con = "skip"; 
                    v.push_back(token.substr(0, token.size() - 1));
                    break;
                }
                else if (strcmp(token.c_str(), "||") == 0) 
                {
                    con = "yes"; 
                    break;
                }
                else if (strcmp(token.c_str(), "&&") == 0) 
                {
                    con = "no";
                    break;
                }
                
                
                v.push_back(token);
                
            }
            
	    //moves from vector to argument list
            char** args = new char*[v.size() + 1];
            for (unsigned i = 0; i < v.size(); ++i) 
            {
                args[i] = new char[v.at(i).size() + 1];
                strcpy(args[i], v.at(i).c_str());
            }
            
            args[v.size()] = 0;
            
            Base* tempCmd = new Cmd(args);
            if (head == 0) //when finished checking statement
            {
                head = tempCmd;
            }
            
            else //checking right side
            {
                head->addRight((tempCmd));
            }
            
            if (con == "") //no assigned type (; && ||)
            {
                return head;
            }
            
            else //continues to the next connector
            {
                Base* newCon = new Connector((string)con);
                newCon->addLeft(head);
                head = newCon;
                return check(ss, head);
            }
        };
};
#endif
