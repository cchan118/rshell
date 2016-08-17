#ifndef CMD_H
#define CMD_H

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
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
            while (args[numArgs] != 0) //deletes each argument one by one
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
            if (args[0] == 0)
	    { 
		return 1;
	    }

            if (strcmp(args[0], "exit") == 0) //exits if argument is "exit"
            {
                exit(0);
            }

            pid_t pid = fork(); // fork allows to look at processes one by one
            int status;
            if (pid == 0) 
            {
                int x = execvp(args[0], args); //execvp actually runs the argument
                exit(x);
            }
            int waitpid = wait(&status); //wait is used to wait for process to finish

            return waitpid;
        };

};

#endif
