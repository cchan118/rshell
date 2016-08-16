#include "Cmd.h"

int main() {
    CmdComposer c;
    char username[40];
    char hostname[40];
    for (int i = 0; i < 40; ++i) 
    {
        username[i] = 0;
        hostname[i] = 0;
    }

    getlogin_r(username, 40);
    gethostname(hostname, 40);

    while (true) 
    {
        cout << username << "@" << hostname << "$ ";
        string str;
        getline(cin, str);
        istringstream ss(str);
        Base* bc = c.compose(ss);
        bc->run();
        delete bc;
    }
}
