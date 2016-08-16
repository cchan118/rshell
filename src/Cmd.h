#ifndef CMD_H
#define CMD_H

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <sys/wait.h>

using namespace std;

class Base {
  public:
    Base() {};
    virtual ~Base() {};
    virtual void addLeft(Base* l) = 0;
    virtual void addRight(Base* r) = 0;
    virtual int run() = 0;
};

class Cmd : public Base {
    private: 
        char** args;
    public:
        Cmd() {};
        ~Cmd() 
        {
            int numArgs = 0;
            while (args[numArgs] != 0) 
            {
                delete[] args[numArgs];
                ++numArgs;
            }
            delete[] args;
            
        };
        
        Cmd(char ** arg) : args(arg) {};
        void addLeft(Base* l) {};
        void addRight(Base* r) {};

        int run() 
        {
            if (args[0] == 0) return 1;
            if (strcmp(args[0], "exit") == 0) 
            {
                exit(0);
            }
            int procID;
            int status;
            procID = fork();
            
            if (procID == 0) 
            {
                int i = execvp(args[0], args);
                exit(i);
            }
            int waitID = wait(&status);
            return waitID;
        };

};
#include "Connector.h"
class CmdComposer {
    public:
        CmdComposer() {};
        Base* compose(istringstream &ss, Base* head = 0) 
        {
            string tstr;
            vector<string> v;
            int conType = -1; //default no connector
            
            while (ss >> tstr) 
            {
                if (tstr.at(0) == '"') 
                {
                    bool done = false;
                    tstr = tstr.substr(1, tstr.size() - 1);
                    while (!done) {
                        string tstr2;
                        if (ss >> tstr2) {
                            int i;
                            for (i = 0; i < tstr2.size(); ++i) 
                            {
                                if(tstr2.at(i) == '"') {
                                    done = true;
                                    break;
                                }
                            }
                            if (done) 
                            {
                                for ( ; i < tstr2.size() - 1; ++i) 
                                {
                                    tstr2.at(i) = tstr2.at(i + 1);
                                }
                                tstr2 = tstr2.substr(0, tstr2.size() - 1);
                            }
                            if (tstr.at(tstr.size() - 1) != '\n') {
                                 tstr += " ";    
                            }
                            tstr += tstr2;
                        }
                        else 
                        {
                            string tempstr;
                            cout << "> ";
                            tstr += '\n';
                            getline(cin, tempstr);
                            ss.str(tempstr);
                            ss.clear();
                        }
                    }
                } //end quotation marks
                else 
                {
                    bool isComment = false;
                    for (int i = 0; i < tstr.size(); ++i) 
                    {
                        if (tstr.at(i) == '#') 
                        {
                            tstr = tstr.substr(0, i);
                            isComment = true;
                        }
                    }
                    if (isComment == true)
                    {
                        break;
                    }
                }
                
                if (tstr.at(tstr.size() - 1) == ';') 
                {
                    conType = next; //semicolon
                    v.push_back(tstr.substr(0, tstr.size() - 1));
                    break;
                }
                else if (strcmp(tstr.c_str(), "||") == 0) 
                {
                    conType = success; 
                    break;
                }
                else if (strcmp(tstr.c_str(), "&&") == 0) 
                {
                    conType = failure;
                    break;
                }
                
                
                v.push_back(tstr);
                
            }
            
            char** args = new char*[v.size() + 1];
            //dynamically allocate mem
            
            for (int i = 0; i < v.size(); ++i) 
            {
                args[i] = new char[v.at(i).size() + 1];
                strcpy(args[i], v.at(i).c_str());
            }
            
            args[v.size()] = 0;
            
            Base* tempCmd = new Cmd(args);
            
            if (head == 0) 
            {
                head = tempCmd;
            }
            
            else 
            {
                head->addRight((tempCmd));
            }
            
            if (conType == -1) 
            {
                return head;
            }
            
            else 
            {
                Base* newCon = new Connector((ConType)conType);
                newCon->addLeft(head);
                head = newCon;
                return compose(ss, head);
            }
        };
};

#endif
