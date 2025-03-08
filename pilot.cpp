 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include "headers/lexer.hpp"  
 using namespace std; 

int main(int argc, char ** argv){
  if(argc<2)
  {
    cout<<"please supply the source file"; 
    exit(1);
  }
  cout<<"reading the file: "<<argv[1]<<endl;
  ifstream sourcefileStream(argv[1]); 

  std::stringstream buffer;

  char temp; 
  while(sourcefileStream.get(temp)){
   if (temp != '\0') {  // Skip null characters
        buffer << temp;
    }
  } 

  std::string sourcecode = buffer.str(); 
  // cout<<"blah blah"<< endl <<sourcecode; 

  Lexer lexer(sourcecode);
  std::vector<Token *> tokens = lexer.tokenize(); 
  int counter = 0; 
  for (Token * temp : tokens)
{
  counter++; 
  std::cout << counter << ") " << temp->VALUE << " " << typeTostring(temp->TYPE) << std::endl;

}
  std::cout<<"this is the end of program"<<endl; 

  for (Token* token : tokens) {
    delete token;
  }
  return 0; 

}


  
  
