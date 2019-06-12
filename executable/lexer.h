#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<windows.h>
//#include "lexer.h"
#include<string>

using namespace std;


string tokens;
vector<string> keyword;


int iskeyword(string a) {
    /*KEYWORDS :
      iter  //while type
      out
      in
      check
      or
      orelse
      num
      alpha
      //type
      string
      //inc
      cmt
    */
    if(find(keyword.begin(),keyword.end(),a)!=keyword.end())
        return 1;
    else return 0;
}
bool isvari(string t){
    long int c=0;
    for(long int i=0;i<t.length();i++){
        if(isalpha(t[i])||isdigit(t[i])||t[i]=='_') c++;
    }
    if(t!=""&&isalpha(t[0])&&c==t.length()) return 1;
    else return 0;
}

string lexer(string filepath) {
    fstream fin(filepath,ios::in);
    fstream fout("errors.txt",ios::out|ios::ate);
    keyword.push_back("iter");
    keyword.push_back("out");
    keyword.push_back("in");
    keyword.push_back("check");
    keyword.push_back("or");
    keyword.push_back("orelse");
    keyword.push_back("num");
    keyword.push_back("alpha");
    keyword.push_back("type");
    keyword.push_back("string");
    keyword.push_back("inc");
    keyword.push_back("cmt");

    char tmp;//temp;
	string t;
	fin.get(tmp);
	long int cnt=0;

	while(!fin.eof()){
        if(tmp=='%'||tmp=='&'||tmp=='^'||tmp=='!'||tmp=='.'||(isdigit(tmp)==1&&!isvari(t))||tmp=='>'||tmp=='<'||tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/'||tmp=='='||tmp==' '||tmp=='('||tmp==')'||tmp=='{'
           ||tmp=='}'||tmp==';'||tmp==','||tmp==':'||tmp=='\''||tmp=='\"'||tmp=='\n'||tmp=='#'||tmp=='~') {
            if(tmp==' ');
            if(t==keyword[11]){
                char te='\0';
                int ob=0,cb=0;
                if(tmp=='(') ob++;
                do{
                   fin.get(te);
                   if(te=='(') ob++;
                   else if(te==')') cb++;
                }while(ob!=cb);
                t="";
                tmp='\0';
            }
            if (iskeyword(t)==1&&cnt==0){
                tokens.append("RESERVED: ");
                tokens.append(t);
                tokens.append(" ");
                t="";
            }
            if(tmp=='~'){    //ntr:NOTHING TO RETURN
                cnt++;
            }
            if(tmp=='\"'){
                 string te;
                 char c=0;//(") check
                 while(c!='\"'){
                    fin.get(c);
                    if(c!='\"')
                    te+=c;
                 }
                 te+=' ';
                 tokens.append("STRING: ");
                 tokens.append(te);
                 t="";
            }
            else if(tmp=='\''){
                fin.get(tmp);
                tokens.append("LIT: ");
                tokens+=tmp;
                tokens+=" ";
                fin.get(tmp);
                tmp='\0';
            }
            else if(tmp=='.'||isdigit(tmp)==1){
                tokens.append("NUMB: ");
                while(isdigit(tmp)==1||tmp=='.'){
                      //  cout<<tmp<<endl;
                    tokens+=tmp;
                    fin.get(tmp);
                }
                fin.unget();
                tmp='\0';
                tokens+=" ";
            }
            else if(t=="en"){
                tokens.append("en ");
                t="";
            }
            else if(t!=""){
                //cout<<t<<endl;
                if(cnt==0){
                tokens.append("VARIABLE: ");
                tokens.append(t);
                tokens.append(" ");
                t="";
                }
                else if(cnt==1) {
                    tokens.append("RETURNTYPE: ");
                    tokens.append(t);
                    tokens+=' ';
                    t="";
                    cnt++;
                }
                else if(cnt==2){
                    tokens.append("FNNAME: ");
                    tokens.append(t);
                    tokens+=' ';
                    t="";
                    cnt=0;
                }
            }
            if(tmp==',') tokens.append(" ");
            if(tmp=='(') {
                tokens.append("OPENB ");
                t="";
            }
            if(tmp==')') {
                tokens.append("CLOSEB ");
                t="";
            }
            if(tmp=='{') {
                tokens.append("OPENCB\n ");
                t="";
            }
            if (tmp=='}') {
                tokens.append("CLOSECB\n ");
                t="";
            }
            if(tmp==';') tokens.append("EOLN\n ");
            if(tmp=='%') tokens.append("OP: % ");
            if(tmp=='!'){
                char ch=tmp;
                fin.get(tmp);
                if(tmp=='=') {
                    tokens.append("RELATION: ");
                    string a="";
                    a+=ch;
                    a.append("= ");
                    tokens.append(a);
                }
            else{
                fin.unget();
                tokens.append("NEGATION ");
            }
            }
            if(tmp=='='){
                char ch=tmp;
                fin.get(tmp);
                if(ch==tmp) {
                    tokens.append("RELATION: ");
                    tokens.append("== ");
                }
                else{
                    fin.unget();
                    tokens.append("ASSIGN ");
                }
            }
            if(tmp=='#'){
                tokens.append("INDEX: ");
                string a="";
                while(fin.get(tmp)&&isdigit(tmp)) a+=tmp;
                tokens.append(a);
                if(a!="")
                tokens+=' ';
                tmp='\0';
                fin.unget();
            }
            if(tmp=='&') tokens.append("AND ");
            if(tmp=='^') tokens.append("OR ");
            if(tmp=='>'||tmp=='<'){
                char ch=tmp;
                fin.get(tmp);
                if(tmp=='=') {
                    tokens.append("RELATION: ");
                    string a="";
                    a+=ch;
                    a.append("= ");
                    tokens.append(a);
                }
                else{
                    //t<<fin.tellg()<<endl;
                    //fin.seekg(-1L);
                    /*char b;
                    fin.read((char*)&b,sizeof(b));
                    cout<<b<<endl;
                    cout<<fin.tellg()<<endl;*/
                    fin.unget();
                    tokens.append("RELATION: ");
                    string a;
                    a+=ch;
                    a+=" ";
                    tokens.append(a);
                }
            }
            if(tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/'){
                tokens.append("OP: ");
                string a="";
                a+=tmp;
                tokens.append(a);
                tokens.append(" ");
            }
        }
        else{
            if(tmp!='\n'&&tmp!=' '){
               t+=tmp;
            }
        }
        //temp=tmp;
        fin.get(tmp);
	}
	fin.close();
    fout.close();
	return tokens;
}
string puttotxt(string filepath){

string a=lexer(filepath);
return a;

}



#endif // LEXER_H_INCLUDED
