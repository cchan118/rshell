#ifndef CMDCHECK_H
#define CMDCHECK_H

#include "Connector.h"
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <unistd.h>
using namespace std;
class CmdCheck {
    public:
        CmdCheck() {};
        Base* check(istringstream &ss, Base* head = 0) 
        {
            string token;
            vector<string> v;
            string con = ""; 

	        vector<string> test;
            stringstream newtoken;
	        string temp;
            while (ss >> token) //gets input from string stream and doesnt echo quotation marks
            {
                
                //Check quotation and # before anything
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
                
                
		        else if (token == "test") //implement 
		        {
			
		        }
		        else if (token.at(0) == '[') // TEST CHECK - TODO: run stat() based on flag
		        {
			        bool done = false;
			        while (done == false)
			        {
			        
				        unsigned i = 0;
				    
				        if (token.at(i) == '[')
				        {
					        ++i;
				        }
				        for (; i < token.size(); i++)
				        {
					        if (token.at(i) != ']')
					        {
						        newtoken << token.at(i);
					        }
					        else
					        {
						        done = true;
					        }
				        }
				
				        newtoken << ' ';
			            ss >> token;
		            }
		    
			        token = newtoken.str();
			        cout << "YO: " << token << endl;

			        string flag;
			        string path;
			        int sep = 0;
			    
			        for (unsigned i = 1; i < token.size()-1; i++)
			        {	
				        if (token.at(i) == ' ')
				        {
					        sep = i;
				        }
			        }
			    
			        for (unsigned i = 1; i < sep; i++)
			        {	
				        flag += token.at(i);
			        }
			    
			        for (unsigned i = sep; i < token.size()-1; i++)
			        {	
				        path += token.at(i);
			        }
		        }
		        else if (token.at(0) == '(') // PARETHESIS CHECK TODO: APPLY LOGIC FOR PRECEDENCE
		        {
		        
			        bool done = false;
			        while (done == false)
			        {
				        unsigned i = 0;
				        if (token.at(i) == '(')
				        {
					        ++i;
				        }
				        for (; i < token.size(); i++)
				        {
					        if (token.at(i) != ')')
					        {
						        newtoken << token.at(i);
					        }
					        else
					        {
						        done = true;
					        }
				        }
                
                        	token = newtoken.str();
				
				//Check for connectors in parenthesis
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

                        	newtoken.str( std::string() );
                        	newtoken.clear();
		                //newtoken << ' ';
		                ss >> token;

		            }
			        //token = newtoken.str();
			        //cout << "W/O parenthesis: " << token << endl;
			 
			        //TODO Run string as two separate commands then determine if true/false
		        }   
                
                	//If no parenthesis, then just check for connector
		        else
		        {
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
