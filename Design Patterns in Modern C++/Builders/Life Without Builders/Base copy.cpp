#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

int main()
{
  // <p>hello</p>
  auto text = "hello";
  string output;
  output += "<p>";                  //We haven't layered strings like this in the past
  output += text;                   //We knew you could use operations but haven't used it much in string related codes
  output += "</p>";
  printf("<p>%s</p>", text);        //We haven't used printf before


  string words[] = { "hello", "world" };    //
  ostringstream oss;
  oss << "<ul>";
  for (auto w : words)              //We've made an array of strings before, but haven't used a loop parameter like this
    oss << "  <li>" << w << "</li>";     //I understand the mechanisms behind these so far, but I just 
  oss << "</ul>";                       //haven't implemented them in this particular way before
  printf(oss.str().c_str());            //so I'm still trying to adapt to this way of coding

}