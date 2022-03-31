#include <iostream>
#include <fstream>

int main()
{
   std::fstream read;
   std::fstream write;
   read.open("engmix.txt", std::fstream::in);
   write.open("engmix_EDITED.txt", std::fstream::out);
   if(read.fail() || write.fail())
   {
       std::cerr << "something went wrong lol" << std::endl;
   }

   std::string specialchar = "ƒ";
   while(!read.eof())
   {
       std::string temp = "";;
       std::getline(read, temp);
       std::cout << temp << std::endl;
       while(temp.find(specialchar) != std::string::npos)
       {
           std::cout << temp.find(specialchar) << std::endl;
            temp.insert(temp.find(specialchar), "+F");
            temp.erase(temp.find(specialchar), 1);
       }
       write << temp;
       write << "\n";
   }
}