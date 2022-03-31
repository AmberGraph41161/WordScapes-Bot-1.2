#include <iostream>
#include <cctype>
#include <fstream>
#include <vector>
#include <conio.h>

/*
NOTE TO SELF:
There is a special character used in "engmix.txt" and it looks like this:
"ƒ"

basically it is an "ƒ" with a hook, and not the character "f"
wiki on it:
https://en.wikipedia.org/wiki/%C6%91

to solve this problem, what I did was just create another version of "engmix.txt"
this other version just has all of the "ƒ" replaced with a "+F"

the code to replace all "ƒ" with "+F" is "resources\
*/

/*
Another note to self. Make sure to convert "engmix_EDITED.txt" to "Unix(LF)" from "Windows(CR LF)"
reason being? idk. seekg() and tellg() both just seem to break when using "Windows(CR LF)", but "Unix(LF)" works

*/
int main()
{
	//vars
	std::string engmixlocation = "resources\\engmix_EDITED.txt";
	//open read
	std::fstream read;
	read.open(engmixlocation, std::ios::in);
	if(read.fail())
	{
		std::cerr << "read.fail()" << std::endl;
		std::cerr << "failed to open\"" << engmixlocation << "\"\terminating program...";
		exit(-1);
	}

	//97 = a
	//122 = z
	char letter = 97;
	char a_z = 97;
	std::string temp = "";
	while(!read.eof())
	{
		if(letter > 122)
        {
            //if passed ascii value for z, leave
            break;
        }
		while(a_z <= 122)
		{
			//init/reset vars after iteration
			std::string stringletter = "";
        	stringletter.push_back(letter);
        	stringletter.push_back(a_z);

			//open letter output file thing
			std::string outputlocation = "output\\" + stringletter + ".txt";
			std::fstream write;
			write.open(outputlocation , std::ios::out);
			//file fail somehow?
			if(write.fail())
			{
				std::cerr << "failed to open a write file..." << std::endl;
				std::cerr << "terminating program..." << std::endl;
				exit(EXIT_FAILURE);
			}

			//write to worddump to write to file
			std::string specialchar = "+F";
			std::string specialcharreplace = "ƒ";
			std::string specialcharreplacedefault = "f";
			std::vector<std::string> worddump;
			int lastpos = read.tellg();
			std::getline(read, temp);
			while(true)
			{
			    //specialchar handling
			    int specialcharpos;
			    bool specialcharflag = false;
			    std::string specialchartemp;
				if(temp.find(specialchar) != std::string::npos)
				{
					std::cerr << "SPECIAL CHAR DELIM FOUND" << std::endl;
					specialcharflag = true;
					specialchartemp = temp;
					//specialchartemp is the output we want
					while(specialchartemp.find(specialchar) != std::string::npos)
                    {
                        specialchartemp.insert(specialchartemp.find(specialchar), specialcharreplace);
                        specialchartemp.erase(specialchartemp.find(specialchar), 2);
                        std::cout << specialchartemp << "_________________________________________________________" << std::endl;
                    }
                    //temp will be the reading we want (replace "+F" with 'f')
                    while(temp.find(specialchar) != std::string::npos)
                    {
                        temp.insert(temp.find(specialchar), specialcharreplacedefault);
                        temp.erase(temp.find(specialchar), 2);
                    }
				}

				//read n write stuff
				if(temp.length() <= 1 && temp[0] == letter)
				{
				    std::cout << "TEMP <= 1 = " << temp << " = LETTER = " << letter << std::endl;
					specialcharflag ? worddump.push_back(specialchartemp) : worddump.push_back(temp);
					lastpos = read.tellg();
				} else if(temp.substr(0, 2) == stringletter)
				{
				    std::cout << "TEMP.SUBSTR(0, 2) = " << temp.substr(0, 2) << " = STRINGLETTER = " << stringletter << " || temp = " << temp << std::endl;
				    specialcharflag ? worddump.push_back(specialchartemp) : worddump.push_back(temp);
				    lastpos = read.tellg();
				} else
				{
				    std::cout << "*TERMINATING BECUASE TEMP = " << temp << " != stringletter = " << stringletter << " || TEMP.SUBSTR(0, 2) =  " << temp.substr(0, 2) << std::endl;
					read.seekg(lastpos);
                    break;
                }
                lastpos = read.tellg();
				std::getline(read, temp);
			}
			//write worddump to write file
			for(int x = 0; x < worddump.size(); x++)
			{
				//std::cout << worddump[x] << std::endl;
				write << worddump[x];
				write << "\n";
			}
			//end, close write to reset what file to write to
			std::cout << "^^^letter " + stringletter + " finished^^^" << std::endl;
			write.close();
			a_z++;
		}
		//97 = a
		//122 = z
		a_z = 97;
		letter++;
	}
	std::cout << "\ndone\n" << std::endl;
}
