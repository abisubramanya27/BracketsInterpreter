#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<string>
using namespace std;
vector<string> vec;

# Need to add more errors

long int search(string nam){
    long int index=0,c=0;
    for(long int it=vec.size()-1;it>=0&&(vec[it]!="open"||c==0);it--){
            if(vec[it]==nam){index=it;c++;}
    }
    return index;
}

void varicheck(){
  string tmp;
  ifstream fin("lexer.txt");
  while(getline(fin,tmp,' ')){
    if(tmp=="OPENCB") vec.push_back("open");
    if(tmp=="CLOSECB"){
        for(long int it=vec.size()-1;vec[it]!="open";it--)
                vec.pop_back();
        vec.pop_back();
    }
    if(tmp=="alpha"||tmp=="num"){
        getline(fin,tmp,' ');
        while(getline(fin,tmp,' ')&&tmp!="EOLN\n"){
            if(tmp=="VARIABLE:"){
                getline(fin,tmp,' ');
                if(search(tmp)!=0) cout<<"redeclaration"<<endl;
                else vec.push_back(tmp);
            }
            if(tmp=="num"||tmp=="alpha") cout<<"error1"<<endl;
        }
        tmp="";
    }

    if(tmp=="VARIABLE:"){
        getline(fin,tmp,' ');
        if(search(tmp)==0) cout<<"undeclared variable"<<endl;
    }

  }
    fin.close();
}


int main(){
  vec.push_back("open");
  varicheck();
  }
