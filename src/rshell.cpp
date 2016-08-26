#include "Cmd.h"
#include "CmdCheck.h"

int main() {
    CmdCheck c;

    char username[80];
    char hostname[80];

    for (int i = 0; i < 80; ++i) 
    {
        username[i] = 0;
        hostname[i] = 0;
    }

    getlogin_r(username, 80);
    gethostname(hostname, 80);

    string str;
    while (str != "exit") 
    {
        cout << username << "@" << hostname << "$ "; //extra credit

        //get input and call run on each statement
        getline(cin, str);
        istringstream ss(str);
        Base* b = c.check(ss);
        b->run();
        delete b;
    }
}
