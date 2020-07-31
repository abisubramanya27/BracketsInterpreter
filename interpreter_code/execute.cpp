/// PROJECT BRACKET((.))
///PROJECT DONE BY ABISHEK.S, class 12-A
///THIS CODE SEGMENT DOES THE ROLE OF INTERMEDIATE CODE GENERATION
///THAT CAN BE PROCESSED BY C++

#include"lexer.h"
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<string>
using namespace std;

///FILE OBJECT TO THE TEMPORARILY CREATED LEXER.TXT
fstream fin;

///CLASS DEFINITIONS.....
class var{
    public:
    string name;
    string dat;
    string val;
    var(string a,string b,string c){
        name=a;
        dat=b;
        val=c;

    }
};
vector<var> vec;

///FUNCTIONS DEFINITIONS
double pow10(int);
double tonum(string,int,int);
double tonumdeci(string,int,int);
string toalpha(string);
string tonumber(string);
long int search(string);
int prior(char);
bool find_no_op(string);
string arrexp();
string arrexp(stringstream&);
string main_fn(string);
void iter();
void iter(stringstream&,streampos);
int check(int);
int check(int cond,stringstream&,streampos);
string infix(string);
void in();
void in(stringstream&,streampos);
void out();
void out(stringstream&,streampos);
void variable(string,stringstream&,streampos);
void variable(string);

///FUNCTION DEFINITIONS
double pow10(int j) { ///FOR GETTING 10 RAISED TO AN INTEGER
	double v = 1;
	if (j>=0) {
		for(int i=0;i<j;i++) {
			v*=10;
		}
	}
	else {
		for(int i=0;i>j;i--)
			v/=10;
	}
	return v;
}

double tonum(string b, int s, int e) { ///FOR CONVERTING A NON-DECIMAL NUMBER IN STRING FORM TO DOUBLE TYPE
	double v = 0;int j = 0;
	for (int i=e;i>=s;i--,j++) {
		v+=(b[i]-48)*pow10(j);
	}
	return v;
}

double tonumdeci(string b, int s, int e) { ///FOR CONVERTING A DECIMAL NUMBER IN STRING FORM TO DOUBLE TYPE
	double v = 0;int j = 0, i = e, k;
	for(;b[i]!='.';i--);
	k=i;
	for(i=k-1;i>=s;i--,j++) {
		v+=(b[i]-48)*pow10(j);
	}
	j=-1;
	for(i=k+1;i<=e;i++,j--)
		v+=(b[i]-48)*pow10(j);
	return v;
}
string toalpha(string tmp){ ///FOR CONVERTING THE ASCII VALUE TO THE CHARACTER
    double n=tonum(tmp,0,tmp.length()-1);
    char s=(char)n;
    string a;
    a+=s;
    return a;
}
string tonumber(string tmp){ ///FOR CONVERTING A CHARACTER TO ITS ASCII EQUIVALENT IN STRING FORM
    char s=tmp[0];
    double n=(double)s;
    stringstream ss;
    ss << n;
    string a=ss.str();
    return a;
}
long int search(string nam){ ///FOR RETURNING THE INDEX OF A VARIABLE IN THE VARIABLE ARRAY
    long int index=0,c=0;
    for(long int it=vec.size()-1;it>=0&&(vec[it].name!=""||c==0);it--){
       if(vec[it].name==nam){index=it;c++;}
    }
    return index;
}
int prior(char v) { ///FOR RETURNING PRIORITY OF A GIVEN OPERATOR
	int i = 0;
	switch (v) {
	case '-':i = 5;
    break;
	case '+':i = 5;
	break;
	case '*':i = 6;
	break;
	case '/':i = 6;
	break;
	case '%':i = 6;
    break;
    case '!':i = 7;
    break;
    case '&':i = 2;
    break;
    case '^':i = 1;
    break;
    case '@':i = 4;  ///@ replacing <= for infix function alone
    break;
    case '<':i = 4;
    break;
    case '_':i = 4;  ///_ replacing >= for infix function alone
    break;
    case '>':i = 4;
    break;
    case '=':i = 3;  ///= replacing == for infix function alone
    break;
    case '#':i = 3;  ///# replacing != for infix function alone
	}
	return i;
}

bool find_no_op(string st){ ///CHECKS FOR ANY OPERATOR IN A GIVEN STRING
    bool op=0;
    op=(st.find('+')==string::npos)&&(st.find('-')==string::npos)&&(st.find('/')==string::npos)&&
       (st.find('*')==string::npos)&&(st.find('^')==string::npos)&&(st.find('=')==string::npos)&&
       (st.find('>')==string::npos)&&(st.find('<')==string::npos)&&(st.find('!')==string::npos)&&
       (st.find('&')==string::npos);
    return op;
}

string arrexp(){ ///TO EVALUATE A GIVEN EXPRESSION INVOLVING ARRAY INDEX
    string tmp,str1;
    int ob=1,cb=0;
    str1+='(';
    do{
        getline(fin,tmp,' ');
        if(tmp=="RELATION:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OPENB") {
           str1+='(';
           ob++;
       }
       else if(tmp=="INDEX:"){
           getline(fin,tmp,' ');
           str1+='#';
           if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
           else if(tmp=="OPENB") tmp=arrexp();
           str1+=tmp;
       }
       else if(tmp=="CLOSEB"){
           str1+=')';
           cb++;
       }
       else if(tmp=="VARIABLE:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OP:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="NUMB:"){
           getline(fin,tmp,' ');
           str1+=tmp;
           str1+=' ';
       }
       else if(tmp=="LIT:"){
           getline(fin,tmp,' ');
           if(tmp=="") str1+=tonumber(" ");
           else
           str1+=tonumber(tmp);
           str1+=' ';
       }
       else if(tmp=="NEGATION")
           str1+='!';
       else if(tmp=="AND")
           str1+='&';
       else if(tmp=="OR")
           str1+='^';
    }while(ob!=cb);
    return infix(str1);
}

string arrexp(stringstream& fin){ ///OVERLOADED FOR A NESTED STATEMENT BLOCK
    string tmp,str1;
    int ob=1,cb=0;
    str1+='(';
    do{
        getline(fin,tmp,' ');
        if(tmp=="RELATION:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OPENB") {
           str1+='(';
           ob++;
       }
       else if(tmp=="INDEX:"){
           getline(fin,tmp,' ');
           str1+='#';
           if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
           else if(tmp=="OPENB") tmp=arrexp();
           str1+=tmp;
       }
       else if(tmp=="CLOSEB"){
           str1+=')';
           cb++;
       }
       else if(tmp=="VARIABLE:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OP:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="NUMB:"){
           getline(fin,tmp,' ');
           str1+=tmp;
           str1+=' ';
       }
       else if(tmp=="LIT:"){
           getline(fin,tmp,' ');
           if(tmp=="") str1+=tonumber(" ");
           else
           str1+=tonumber(tmp);
           str1+=' ';
       }
       else if(tmp=="NEGATION")
           str1+='!';
       else if(tmp=="AND")
           str1+='&';
       else if(tmp=="OR")
           str1+='^';
    }while(ob!=cb);
    return infix(str1);
}

string main_fn(string a){ ///MAIN FUNCTION FOR NESTED STATEMENT BLOCK
    stringstream inp;
    inp<<a;
    string str;
    var openb("","","");
    vec.push_back(openb);
    long int cb=0,ob=1;
    long int condi=0,gap=0;
    while(ob!=cb&&getline(inp,str,' ')){
        if(str=="OPENCB\n"){
            gap++;
            ob++;
            vec.push_back(openb);
        }
        else if(str=="CLOSECB\n"){
          gap++;
          cb++;
          if(ob!=cb){
          for(long int it=vec.size()-1;vec[it].name!="";it--){
                vec.pop_back();
          }
          vec.pop_back();

          }
        }
        else if(str=="EOLN\n")gap++;
        else if(str=="en") {cout<<'\n';gap++;}
        else if(str=="RESERVED:"){
          str="";
          getline(inp,str,' ');
          if(str=="out") {
            streampos posi=inp.tellg();
            out(inp,posi);
          }
          else if(str=="in") {
            gap++;
            streampos posi=inp.tellg();
            in(inp,posi);
          }
          else if(str=="alpha"||str=="num") {
            gap++;
            streampos posi=inp.tellg();
            variable(str,inp,posi);
          }
          else if(str=="iter") {
            gap++;
            streampos posi=inp.tellg();
            iter(inp,posi);
          }
          else if(str=="check"||str=="or"||str=="orelse"){
            streampos posi=inp.tellg();
            if(str=="check") gap++;
            if(gap!=0){condi=0;gap=0;}
            if(str=="orelse"){
                int ob=1,cb=0;
                getline(inp,str,' ');
                string st="";
                while(ob!=cb&&getline(inp,str,' ')){
                    if(str=="OPENCB\n") ob++;
                    else if(str=="CLOSECB\n") cb++;
                    st+=str;
                    st+=' ';
                }
                if(condi==0&&gap==0)
                main_fn(st);
            }
            else if(str=="or"){
                condi+=check(condi,inp,posi);
            }
            else {
                condi+=check(condi,inp,posi);
            }
          }
        }
        else if(str=="VARIABLE:"){
            long int ind=0;
            gap++;
            string v;
            getline(inp,str,' ');
            long int n=search(str),a;
            getline(inp,str,' ');
            if(str=="INDEX:"){
                getline(inp,str,' ');
                if(str=="VARIABLE:") {
                    getline(inp,str,' ');
                    long int n1=search(str);
                    ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
                }
                else if(str=="OPENB") {str=arrexp(inp);ind=tonum(str,0,str.length()-1);}
                else
                ind=tonum(str,0,str.length()-1);
                getline(inp,str,' ');
            }
            if(str=="ASSIGN"){
            while(getline(inp,str,' ')&&str!="EOLN\n"){
               if(str=="VARIABLE:"){
                 getline(inp,str,' ');
                 v+=str;
               }
               else if(str=="RELATION:"){
                 getline(inp,str,' ');
                 v+=str;
               }
               else if(str=="OP:"){
                 getline(inp,str,' ');
                 v+=str;
               }
               else if(str=="INDEX:"){
                 getline(inp,str,' ');
                 v+='#';
                 if(str=="VARIABLE:")
                    getline(inp,str,' ');
                 else if(str=="OPENB") str=arrexp(inp);
                 v+=str;
               }
               else if(str=="NEGATION")
                  str+='!';
               else if(str=="AND")
                  str+='&';
               else if(str=="OR")
                  str+='^';
               else if(str=="CLOSEB") v+=')';
               else if(str=="OPENB") v+='(';
               else{
                if(vec[n].dat=="alpha"){
                   if(str=="LIT:"){
                      getline(inp,str,' ');
                      if(str=="") v+=tonumber(" ");
                      else
                      v+=tonumber(str);
                      v+=' ';
                   }
                   else if(str=="NUMB:"){
                     getline(inp,str,' ');
                     v+=(str);
                     v+=' ';
                   }
                }
                else if(vec[n].dat=="num"){
                   if(str=="NUMB:"){
                      getline(inp,str,' ');
                      v+=str;
                      v+=' ';
                   }
                   else if(str=="LIT:"){
                      getline(inp,str,' ');
                      if(str=="") v+=tonumber(" ");
                      else
                      v+=tonumber(str);
                      v+=' ';
                   }
                }
            }
        }
      }
      if(vec[n+ind].dat=="alpha")
        vec[n+ind].val=toalpha(infix(v));
      else {
            vec[n+ind].val=infix(v);
            if(vec[n+ind].val=="") vec[n].val="0";
        }
      }
    }
    return str;
}

void iter(){ ///PROCESSES AN ITERATIVE STATEMENT BLOCK
    string tmp,str1,str2;
    getline(fin,tmp,' ');
    str1+='(';
    long int ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')){
       if(tmp=="RELATION:") {
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OPENB") {
           str1+='(';
           ob++;
       }
       else if(tmp=="INDEX:") {
            getline(fin,tmp,' ');
            str1+='#';
            if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
            else if(tmp=="OPENB") tmp=arrexp();
            str1+=tmp;
       }
       else if(tmp=="CLOSEB") {
           str1+=')';
           cb++;
       }
       else if(tmp=="VARIABLE:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OP:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="NUMB:"){
           getline(fin,tmp,' ');
           str1+=tmp;
           str1+=' ';
       }
       else if(tmp=="LIT:"){
           getline(fin,tmp,' ');
           if(tmp=="") str1+=tonumber(" ");
           else
           str1+=tonumber(tmp);
           str1+=' ';
       }
       else if(tmp=="NEGATION")
           str1+='!';
       else if(tmp=="AND")
           str1+='&';
       else if(tmp=="OR")
           str1+='^';
    }
    getline(fin,tmp,' ');
    ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')){
        str2+=tmp;
        if(tmp=="OPENCB\n") ob++;
        else if(tmp=="CLOSECB\n") cb++;
        str2+=' ';
    }
    stringstream ss;
    ss<<infix(str1);
    int res;
    ss>>res;
    while(res!=0){
        main_fn(str2);
        stringstream ss;
        ss<<infix(str1);
        res=0;
        ss>>res;
    }
}

void iter(stringstream& fin,streampos posi){ ///OVERLOADED FOR NESTED STATEMENT BLOCK
    fin.seekg(posi,ios::beg);
    string tmp,str1,str2;
    getline(fin,tmp,' ');
    str1+='(';
    long int ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')){
        if(tmp=="RELATION:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OPENB") {
           str1+='(';
           ob++;
       }
       else if(tmp=="CLOSEB"){
           str1+=')';
           cb++;
       }
       else if(tmp=="INDEX:"){
           getline(fin,tmp,' ');
           str1+='#';
           if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
           else if(tmp=="OPENB") tmp=arrexp(fin);
           str1+=tmp;
       }
       else if(tmp=="VARIABLE:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OP:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="NUMB:"){
           getline(fin,tmp,' ');
           str1+=tmp;
           str1+=' ';
       }
       else if(tmp=="LIT:"){
           getline(fin,tmp,' ');
           if(tmp=="") str1+=tonumber(" ");
           else
           str1+=tonumber(tmp);
           str1+=' ';
       }
       else if(tmp=="NEGATION")
           str1+='!';
       else if(tmp=="AND")
           str1+='&';
       else if(tmp=="OR")
           str1+='^';
    }
    getline(fin,tmp,' ');
    ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')){
        str2+=tmp;
        if(tmp=="OPENCB\n") ob++;
        else if(tmp=="CLOSECB\n") cb++;
        str2+=' ';
    }
    stringstream ss;
    ss<<infix(str1);
    int res;
    ss>>res;
    while(res!=0){
        main_fn(str2);
        stringstream ss;
        ss<<infix(str1);
        res=0;;
        ss>>res;
    }
}

int check(int cond){ ///PROCESSES A CONDITIONAL STATEMENT BLOCK
    string tmp,str1,str2;
    getline(fin,tmp,' ');
    str1+='(';
    long int ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')) {
        if(tmp=="RELATION:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OPENB") {
           str1+='(';
           ob++;
       }
       else if(tmp=="INDEX:"){
           getline(fin,tmp,' ');
           str1+='#';
           if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
           else if(tmp=="OPENB") tmp=arrexp();
           str1+=tmp;
       }
       else if(tmp=="CLOSEB"){
           str1+=')';
           cb++;
       }
       else if(tmp=="VARIABLE:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OP:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="NUMB:"){
           getline(fin,tmp,' ');
           str1+=tmp;
           str1+=' ';
       }
       else if(tmp=="LIT:"){
           getline(fin,tmp,' ');
           if(tmp=="") str1+=tonumber(" ");
           else
           str1+=tonumber(tmp);
           str1+=' ';
       }
       else if(tmp=="NEGATION")
           str1+='!';
       else if(tmp=="AND")
           str1+='&';
       else if(tmp=="OR")
           str1+='^';
    }
    getline(fin,tmp,' ');
    ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')){
        str2+=tmp;
        if(tmp=="OPENCB\n") ob++;
        else if(tmp=="CLOSECB\n") cb++;
        str2+=' ';
    }
    stringstream ss;
    ss<<infix(str1);
    int res;
    ss>>res;
    if(res!=0&&cond==0){
        main_fn(str2);
    }
    return res;
}

int check(int cond,stringstream&fin,streampos posi){ ///OVERLOADED FOR NESTED STATEMENT BLOCK
    fin.seekg(posi,ios::beg);
    string tmp,str1,str2;
    getline(fin,tmp,' ');
    str1+='(';
    long int ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')) {
        if(tmp=="RELATION:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OPENB") {
           str1+='(';
           ob++;
       }
       else if(tmp=="CLOSEB"){
           str1+=')';
           cb++;
       }
       else if(tmp=="INDEX:"){
            getline(fin,tmp,' ');
            str1+='#';
            if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
            else if(tmp=="OPENB") tmp=arrexp(fin);
            str1+=tmp;
       }
       else if(tmp=="VARIABLE:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="OP:"){
           getline(fin,tmp,' ');
           str1+=tmp;
       }
       else if(tmp=="NUMB:"){
           getline(fin,tmp,' ');
           str1+=tmp;
           str1+=' ';
       }
       else if(tmp=="LIT:"){
           getline(fin,tmp,' ');
           if(tmp=="") str1+=tonumber(" ");
           else
           str1+=tonumber(tmp);
           str1+=' ';
       }
       else if(tmp=="NEGATION")
           str1+='!';
       else if(tmp=="AND")
           str1+='&';
       else if(tmp=="OR")
           str1+='^';
    }
    getline(fin,tmp,' ');
    ob=1,cb=0;
    while(ob!=cb&&getline(fin,tmp,' ')){
        str2+=tmp;
        if(tmp=="OPENCB\n") ob++;
        else if(tmp=="CLOSECB\n") cb++;
        str2+=' ';
    }
    stringstream ss;
    ss<<infix(str1);
    int res;
    ss>>res;
    if(res!=0&&cond==0){
        main_fn(str2);
    }
    return res;
}

string infix(string a){ ///EVALUATES AN INFIX EXPRESSION
    vector<char> c;
    string b;
	long int l = a.length();
	if(a[l-1]!='+'&&a[l-1]!='-'&&a[l-1]!='*'&&a[l-1]!='/'&&a[l-1]!='^'&&a[l-1]!='&'&&a[l-1]!='!'&&a[l-1]!='='&&a[l-1]!='>'&&a[l-1]!='<'){
	a.push_back(')');
	c.push_back('(');
	for (long int i = 0;i < (l + 1);i++) {
    	if (a[i] == ' ' ||( a[i] == '.'&&!(isdigit(a[i+1]))));
		else if ((a[i] >= '0'&&a[i] <= '9')||a[i]=='.') {
            if(a[i]=='.') b.push_back('0');
			b.push_back(a[i]);
			while ((a[i + 1] >= '0'&&a[i + 1] <= '9') || (a[i + 1] == '.'&&a[i + 2] >= '0'&&a[i + 2] <= '9')) {
				b+=a[++i];
			}
			b+=' ';
		}
		else if (isalpha(a[i])) {
            string abc,def;
            int cnt=0,ind=0;
            while(isalpha(a[i])||isdigit(a[i])||a[i]=='_'){
                abc+=a[i];
                i++;
            }
            i--;
            if(a[i+1]=='#') cnt++;

            if(cnt!=0){
                i+=2;
                int start=i;
                while(isdigit(a[i])||isalpha(a[i])||a[i]=='_'){
                   def+=a[i];
                   i++;
                }
                i--;
                if(isalpha(a[start])) {
                    long int n1=search(def);
                    ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
                    }
                else
                ind=tonum(def,0,def.length()-1);
            }
            long int n=search(abc);
            if(vec[n+ind].dat=="alpha")
            b+=tonumber(vec[n+ind].val);
            else b+=vec[n+ind].val;
            b+=' ';
		}
		else if (a[i] == ')') {
			char v = 0;
			while (v != '(') {
                v=c[c.size()-1];
				c.pop_back();
				if (v != '(') {
					b+= v;
					b+=' ';
				}
			}
		}
		else if (a[i] == '('){
			c.push_back(a[i]);
			}
		else {
		    int cnt=0;
		    char cd=a[i];
            if((a[i]=='>'||a[i]=='<'||a[i]=='='||a[i]=='!')&&a[i+1]=='='){cnt++;i++;}
            if(cnt!=0){
                if(a[i-1]=='>') cd='_';
                else if(a[i-1]=='<') cd='@';
                else if(a[i-1]=='!') cd='#';
            }
			if (prior(cd) <= prior(c.back())) {
				while (prior(cd) <= prior(c.back())) {
					char v = 0;
					v=c[c.size()-1];
					c.pop_back();
					b+=v;
					b+=' ';
				}
				c.push_back(cd);
			}
			else
				c.push_back(cd);
		}
	}
	}
	else b=a;
	vector<double> d;
	for(int i = 0;b[i] != 0;i++) {
		if (b[i] == ' ');
		else if ((b[i] >= '0'&&b[i] <= '9')) {
			int j = i, k = 0;
			for (;b[i] != ' ';i++)
				if (b[i] == '.')
					k++;
			double v;
			if (k>0)
				v = tonumdeci(b,j, i - 1);
			else
				v = tonum(b, j, i - 1);
			d.push_back(v);
		}
		else if(isalpha(b[i])) {d.push_back((double)b[i]);}
		else {
			double v1, v2;
			v2=d[d.size()-1];
			d.pop_back();
			if(d.size()==0) {v1=0;}
			else{
			v1=d[d.size()-1];
			d.pop_back();
			}
			switch (b[i]) {
			case'+':d.push_back(v1 + v2);
				break;
			case'-':d.push_back(v1 - v2);
				break;
			case'*':d.push_back(v1*v2);
				break;
			case'/':d.push_back(v1 / v2);
				break;
			case'%':d.push_back(int(v1) % int(v2));
				break;
            case '#':{
                bool res=v1!=v2;
                d.push_back((double)res);
            }
            break;
            case'!':{
                bool res=!v2;
                //d.push_back(v1);
                d.push_back((double)res);
            }
            break;
            case '_':{
                bool res=v1>=v2;
                d.push_back((double)res);
            }
            break;
            case '>':{
                bool res=v1>v2;
                d.push_back((double)res);
            }
            break;
            case '@':{
                bool res=v1<=v2;
                d.push_back((double)res);
            }
            break;
            case '<':{
                bool res=v1<v2;
                d.push_back((double)res);
            }
            break;
            case '=':{
                bool res=v1==v2;
                d.push_back((double)res);
            }
            break;
            case '&':{
                bool res=v1&&v2;
                d.push_back((double)res);
            }
            break;
            case '^':{
                bool res=v1||v2;
                d.push_back((double)res);
            }
            break;
            }
        }
    }
	double result=0;
	if(d.size()!=0){
	result=d[d.size()-1];
	d.pop_back();
	}
	stringstream ss;
    ss << result;
    string a=ss.str();
    return a;
}

void in(){ ///PROCESSES AN INPUT STATEMENT
    string tmp="";
    int chh=0,ind=0,str=0;
    while(tmp!="EOLN\n"){
        if(chh==0) getline(fin,tmp,' ');
        if(tmp=="VARIABLE:"){
            getline(fin,tmp,' ');
            long int n=search(tmp);
            getline(fin,tmp,' ');
            chh++;
            if(tmp=="INDEX:") {
                chh=0;
                getline(fin,tmp,' ');
                if(tmp=="VARIABLE:")
                    getline(fin,tmp,' ');
                else if(tmp=="OPENB") tmp=arrexp();
                else if(tmp==""||tmp=="CLOSEB"){
                   str++;
                }
                if(str==0){
                if(isdigit(tmp[0]))
                ind=tonum(tmp,0,tmp.length()-1);
                else{
                    long int n1=search(tmp);
                    ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
                }
                }
            }
            string value;
            cin>>value;
            if(str==0){
            if(vec[n+ind].dat=="alpha") {
                if(isalpha(value[0]))
                   vec[n+ind].val=value;
                else vec[n+ind].val=toalpha(value);
            }
            else if(vec[n+ind].dat=="num"){
                if(isalpha(value[0]))
                    vec[n+ind].val=tonumber(value);
                else {
                  if(value[0]=='.'){ vec[n+ind].val+='0';
                  vec[n+ind].val+=value;
                  }
                  else vec[n+ind].val=value;
                }
            }
            }
            else{
                for(long int i=0;i<value.length();i++){
                    vec[n].val=value[i];
                    n++;
                }
            }
        }
        else chh=0;
        ind=0;
        str=0;
    }
}

void in(stringstream& sin,streampos posi){ ///OVERLOADED FOR NESTED STATEMENT BLOCK
    sin.seekg(posi,ios::beg);
    string tmp;
    int chh=0,ind=0,str=0;
    while(tmp!="EOLN\n"){
        if(chh==0)getline(sin,tmp,' ');
        if(tmp=="VARIABLE:"){
            getline(sin,tmp,' ');
            long int n=search(tmp);
            chh++;
            getline(sin,tmp,' ');
            if(tmp=="INDEX:") {
                chh=0;
                getline(sin,tmp,' ');
                if(tmp=="VARIABLE:")
                    getline(sin,tmp,' ');
                else if(tmp=="OPENB") tmp=arrexp(sin);
                else if(tmp==""||tmp=="CLOSEB") str++;
                if(str==0){
                if(isdigit(tmp[0]))
                ind=tonum(tmp,0,tmp.length()-1);
                else{
                    long int n1=search(tmp);
                    ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
                }
                }
            }
            string value;
            cin>>value;
            if(str==0){
            if(vec[n+ind].dat=="alpha") {
                if(isalpha(value[0]))
                   vec[n+ind].val=value;
                else vec[n+ind].val=toalpha(value);
            }
            else if(vec[n+ind].dat=="num"){
                if(isalpha(value[0]))
                    vec[n+ind].val=tonumber(value);
                else {
                  if(value[0]=='.'){ vec[n+ind].val+='0';
                  vec[n+ind].val+=value;
                  }
                  else vec[n+ind].val=value;
                }
            }
            }
            else{
                for(long int i=0;i<value.length();i++){
                    vec[n].val=value[i];
                    n++;
                }
            }
        }
        else chh=0;
        ind=0;
        str=0;
    }
}

void out(){ ///PROCESSES AN OUTPUT STATEMENT
   int op=0,co=0,sp=0,clit=0,str=0;
   string tmp,st;
   long int ind=0,a=-1;
   getline(fin,tmp,' ');
   while(tmp!="EOLN\n"){
       if(clit==0)
        getline(fin,tmp,' ');
        clit=0;
       if(tmp=="STRING:"){
        tmp="";
        while((tmp!="CLOSEB")&&(tmp!="OPENB")&&tmp!="STRING:"&&tmp!="en"&&tmp!="NUMB:"&&tmp!="LIT:"&&
               tmp!="OP:"&&tmp!="VARIABLE:"&&getline(fin,tmp,' ')){
        if(tmp=="") {if(getline(fin,tmp,' ')&&(tmp!="CLOSEB")&&(tmp!="OPENB")&&tmp!="en"&&tmp!="STRING:"&&
                        tmp!="NUMB:"&&tmp!="LIT:"&&tmp!="VARIABLE:"&&tmp!="OP:") {cout<<" ";}}
        if((tmp!="CLOSEB")&&(tmp!="OPENB")&&tmp!="STRING:"&&tmp!="NUMB:"&&tmp!="LIT:"&&tmp!="en"&&
           tmp!="OP:"&&tmp!="VARIABLE:") {if(sp>0) cout<<" ";
        cout<<tmp;}
        sp++;
        if(tmp=="STRING:") clit++;
       }
       sp=0;
       }
       if(tmp=="OPENB"){
         st+='('; op++;
       }
       else if(tmp=="en") cout<<'\n';
       else if(tmp=="CLOSEB"){
          co++;
          if(op>=co){
            st+=')';
          }
          if(op==co){
            op=0;co=0;
          }
          else if(op==0&&co>0){
            if(st.length()!=0){
            int check=find_no_op(st);
            if(check!=1||a==-1){
            st=infix(st);
            cout<<st;
            st="";
            }
            else{
                st=infix(st);
                if(vec[a+ind].dat=="alpha") cout<<toalpha(st);
                else cout<<st;
                st="";
            }
            a=-1;
          }
          }
       }
       else if(tmp==""){
          if(st.length()!=0){
            int check=find_no_op(st);
            if(check!=1||a==-1){
            st=infix(st);
            cout<<st;
            st="";
            }
            else{
                st=infix(st);
                if(vec[a+ind].dat=="alpha") cout<<toalpha(st);
                else cout<<st;
                st="";
            }
            a=-1;
          }
       }
       else if(tmp=="RELATION:"){
           getline(fin,tmp,' ');
           st+=tmp;
       }
       else if(tmp=="VARIABLE:"){
           getline(fin,tmp,' ');
           a=search(tmp);
           ind=0;
           string tmp2;
           getline(fin,tmp2,' ');
           clit++;
           if(tmp2=="INDEX:"){
                getline(fin,tmp2,' ');
                if(tmp2=="VARIABLE:")
                    getline(fin,tmp2,' ');
                else if(tmp2=="OPENB") {tmp2=arrexp();}
                else if(tmp2==""||tmp2=="CLOSEB"){
                    while(vec[a].val!=""){
                        cout<<vec[a].val;
                        a++;
                    }
                    str++;
                    a=-1;
                    getline(fin,tmp2,' ');
                }
                if(str==0){
                  if(isdigit(tmp2[0]))
                     ind=tonum(tmp2,0,tmp2.length()-1);
                  else{
                     long int n1=search(tmp2);
                     ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
                  }
                  getline(fin,tmp2,' ');
                  tmp+='#';
                  stringstream ss;
                  ss<<ind;
                  tmp+=ss.str();
                }
           }
           if(str==0){
             st+=tmp;
             st+=' ';
           }
           tmp=tmp2;
           str=0;

       }
       else if(tmp=="OP:"){
           getline(fin,tmp,' ');
           st+=tmp;
       }
       else if(tmp=="NEGATION")
           st+='!';
       else if(tmp=="AND")
           st+='&';
       else if(tmp=="OR")
           st+='^';
       else if(tmp=="NUMB:"){
           getline(fin,tmp,' ');
           st+=tmp;
           st+=' ';
       }
       else if(tmp=="LIT:"){
           getline(fin,tmp,' ');
           string tmp2;
           getline(fin,tmp2,' ');
           clit++;
           if(tmp2==""||tmp2=="CLOSEB"){
              if(tmp!="")
                cout<<tmp;
              else
                cout<<' ';
           }
           else{
           if(tmp=="") st+=tonumber(" ");
           else
           st+=tonumber(tmp);
           st+=' ';
           }
           tmp=tmp2;
       }
    }
   tmp="";
}

void out(stringstream& sin,streampos posi){ ///OVERLOADED FOR NESTED STATEMENT BLOCK
   sin.seekg(posi,ios::beg);
   int op=0,co=0,sp=0,clit=0,str=0;
   string tmp,st;
   long int ind=0,a=-1;
   getline(sin,tmp,' ');
   while(tmp!="EOLN\n"){
       if(clit==0)
        getline(sin,tmp,' ');
        clit=0;
       if(tmp=="STRING:"){
        tmp="";
        while((tmp!="CLOSEB")&&(tmp!="OPENB")&&tmp!="STRING:"&&tmp!="en"&&tmp!="NUMB:"&&
              tmp!="LIT:"&&tmp!="OP:"&&tmp!="VARIABLE:"&&getline(sin,tmp,' ')){
        if(tmp=="") {if(getline(sin,tmp,' ')&&(tmp!="CLOSEB")&&(tmp!="OPENB")&&tmp!="en"&&tmp!="STRING:"&&
                        tmp!="NUMB:"&&tmp!="LIT:"&&tmp!="VARIABLE:"&&tmp!="OP:") {cout<<" ";}}
        if((tmp!="CLOSEB")&&(tmp!="OPENB")&&tmp!="STRING:"&&tmp!="NUMB:"&&tmp!="LIT:"&&
           tmp!="en"&&tmp!="OP:"&&tmp!="VARIABLE:") {if(sp>0) cout<<" ";
        cout<<tmp;}
        sp++;
        if(tmp=="STRING:") clit++;
        }
       }
       if(tmp=="OPENB"){
         st+='('; op++;
       }
       else if(tmp=="en") cout<<'\n';
       else if(tmp=="CLOSEB"){
          co++;
          if(op>=co){
            st+=')';
          }
          if(op==co){
            op=0;co=0;
          }
          else if(op==0&&co>0){
            if(st.length()!=0){
            int check=find_no_op(st);
            if(check!=1||a==-1){
            st=infix(st);
            cout<<st;
            st="";
            }
            else{
                st=infix(st);
                if(vec[a+ind].dat=="alpha") cout<<toalpha(st);
                else cout<<st;
                st="";
            }
            a=-1;
          }
          }
       }
       else if(tmp==""){
          if(st.length()!=0){
            int check=find_no_op(st);
            if(check!=1||a==-1){
            st=infix(st);
            cout<<st;
            st="";
            }
            else{
                st=infix(st);
                if(vec[a+ind].dat=="alpha") cout<<toalpha(st);
                else cout<<st;
                st="";
            }
            a=-1;
          }
       }
      else if(tmp=="RELATION:"){
           getline(sin,tmp,' ');
           st+=tmp;
       }
       else if(tmp=="VARIABLE:"){
           getline(sin,tmp,' ');
           a=search(tmp);
           string tmp2;
           ind=0;
           getline(sin,tmp2,' ');
           clit++;
           if(tmp2=="INDEX:"){
                getline(sin,tmp2,' ');
                if(tmp2=="VARIABLE:")
                    getline(sin,tmp2,' ');
                else if(tmp2=="OPENB") tmp2=arrexp(sin);
                else if(tmp2==""||tmp2=="CLOSEB"){
                    while(vec[a].val!=""){
                        cout<<vec[a].val;
                        a++;
                    }
                    str++;
                    a=-1;
                    getline(sin,tmp2,' ');
                }
                if(str==0){
                if(isdigit(tmp2[0]))
                ind=tonum(tmp2,0,tmp2.length()-1);
                else{
                    long int n1=search(tmp2);
                    ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
                }
                getline(sin,tmp2,' ');
                tmp+='#';
                stringstream ss;
                ss<<ind;
                tmp+=ss.str();
                }
           }
           if(str==0){
             st+=tmp;
             st+=' ';
           }
           tmp=tmp2;
           str=0;
       }
       else if(tmp=="OP:"){
           getline(sin,tmp,' ');
           st+=tmp;
       }
       else if(tmp=="NEGATION")
           st+='!';
       else if(tmp=="AND")
           st+='&';
       else if(tmp=="OR")
           st+='^';
       else if(tmp=="NUMB:"){
           getline(sin,tmp,' ');
           st+=tmp;
       }
       else if(tmp=="LIT:"){
           getline(sin,tmp,' ');
           string tmp2;
           getline(sin,tmp2,' ');
           clit++;
           if(tmp2==""||tmp2=="CLOSEB"){
              if(tmp!="")
                cout<<tmp;
              else
                cout<<' ';
           }
           else{
           if(tmp=="") st+=tonumber(" ");
           else
           st+=tonumber(tmp);
           }
           tmp=tmp2;
       }
     }
   tmp="";
}

void variable(string str){ ///PROCESSES A VARIABLE INITIALISATION STATEMENT
    string tmp,varn,v;
    long int n,a,ind;
    while(tmp!="EOLN\n"&&getline(fin,tmp,' ')){
        if(tmp=="VARIABLE:"){
            tmp="";
            getline(fin,tmp,' ');
            varn=tmp;
            var t(varn,str,"");
            vec.push_back(t);
            n=search(varn);
            v="";
        }
        else if(tmp=="INDEX:"){
            getline(fin,tmp,' ');
            if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
            else if(tmp=="OPENB") tmp=arrexp();
            if(isdigit(tmp[0]))
            ind=tonum(tmp,0,tmp.length()-1);
            else {
                long int n1=search(tmp);
                ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
            }
            var t(varn,str,"");
            for (long int i=1;i<ind;i++) vec.push_back(t);
        }
        else if(tmp=="OPENB"){
            long int cnt=0,strr=0;
            int ob=1,cb=0;
            while(ob!=cb){
              while(getline(fin,tmp,' ')&&tmp!=""&&ob!=cb){
               if(tmp=="VARIABLE:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="STRING:"){
                 strr++;
                 long int sp=0;
                 string st="";
                 tmp="";
                 while((tmp!="CLOSEB")&&getline(fin,tmp,' ')){
                 if(tmp=="") {if(getline(fin,tmp,' ')&&(tmp!="CLOSEB")) {st+=' ';}}
                 if((tmp!="CLOSEB")) {if(sp>0) st+=' ';
                 st+=tmp;}
                 sp++;
                 }
                 cb++;
                 for(long int i=0;i<st.length();i++){
                    vec[n+cnt].val=st[i];
                    cnt++;
                 }
               }
               else if(tmp=="INDEX:"){
                 getline(fin,tmp,' ');
                 v+='#';
                 if(tmp=="VARIABLE:")
                    getline(fin,tmp,' ');
                 else if(tmp=="OPENB") tmp=arrexp();
                 v+=tmp;
               }
               else if(tmp=="RELATION:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="OP:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="NEGATION")
                   v+='!';
               else if(tmp=="AND")
                   v+='&';
               else if(tmp=="OR")
                   v+='^';
               else if(tmp=="CLOSEB") {v+=')';cb++;}
               else if(tmp=="OPENB") {v+='(';ob++;}
               else{
                if(str=="alpha"){
                   if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") {v+=tonumber(" ");}
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                   else if(tmp=="NUMB:"){
                     getline(fin,tmp,' ');
                     v+=tmp;
                     v+=' ';
                   }
                }
                else if(str=="num"){
                   if(tmp=="NUMB:"){
                      getline(fin,tmp,' ');
                      v+=tmp;
                      v+=' ';
                   }
                   else if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") v+=tonumber(" ");
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                }
            }
            }
        if(strr==0){
        if(ob==cb) v.pop_back();
        if(str=="alpha")
        vec[n+cnt].val=toalpha(infix(v));
        else {
            vec[n+cnt].val=infix(v);
            if(vec[n+cnt].val=="") vec[n+cnt].val="0";
        }
        v="";
        cnt++;
        }
        }
        }
        else if(tmp=="ASSIGN"){
            while(getline(fin,tmp,' ')&&tmp!=""&&tmp!="EOLN\n"){
               if(tmp=="VARIABLE:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="INDEX:"){
                 getline(fin,tmp,' ');
                 v+='#';
                 if(tmp=="VARIABLE:")
                    getline(fin,tmp,' ');
                 else if(tmp=="OPENB") tmp=arrexp();
                 v+=tmp;

               }
               else if(tmp=="RELATION:"){
                 getline(fin,tmp,' ');
                 v+=tmp;

               }
               else if(tmp=="OP:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="NEGATION")
                   v+='!';
               else if(tmp=="AND")
                   v+='&';
               else if(tmp=="OR")
                   v+='^';
               else if(tmp=="CLOSEB") v+=')';
               else if(tmp=="OPENB") v+='(';
               else{

                if(str=="alpha"){
                   if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") {v+=tonumber(" ");}
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                   else if(tmp=="NUMB:"){
                     getline(fin,tmp,' ');
                     v+=tmp;
                     v+=' ';
                   }
                }
                else if(str=="num"){
                   if(tmp=="NUMB:"){
                      getline(fin,tmp,' ');
                      v+=tmp;
                      v+=' ';
                   }
                   else if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") v+=tonumber(" ");
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                }
            }
        }

        if(str=="alpha"){
        vec[n].val=toalpha(infix(v));
        }
        else {
            vec[n].val=infix(v);
            if(vec[n].val=="") vec[n].val="0";
        }
        v="";
        }

    }
    }

void variable(string str,stringstream& fin,streampos posi){
    ///OVERLOADED FOR NESTED STATEMENT BLOCK
    fin.seekg(posi,ios::beg);
    string tmp,varn,v;
    long int n,a,ind;
    while(tmp!="EOLN\n"&&getline(fin,tmp,' ')){
        if(tmp=="VARIABLE:"){
            tmp="";
            getline(fin,tmp,' ');
            varn=tmp;
            var t(varn,str,"");
            vec.push_back(t);
            n=search(varn);
            v="";
        }
        else if(tmp=="INDEX:"){
            getline(fin,tmp,' ');
            if(tmp=="VARIABLE:")
                getline(fin,tmp,' ');
            else if(tmp=="OPENB") tmp=arrexp(fin);
            if(isdigit(tmp[0]))
            ind=tonum(tmp,0,tmp.length()-1);
            else {
                long int n1=search(tmp);
                ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
            }
            var t(varn,str,"");
            for (long int i=1;i<ind;i++) vec.push_back(t);
        }
        else if(tmp=="OPENB"){
            long int cnt=0,strr=0;
            int ob=1,cb=0;
            while(ob!=cb){
              while(getline(fin,tmp,' ')&&tmp!=""&&ob!=cb){
               if(tmp=="VARIABLE:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="STRING:"){
                 strr++;
                 long int sp=0;
                 string st="";
                 tmp="";
                 while((tmp!="CLOSEB")&&getline(fin,tmp,' ')){
                 if(tmp=="") {if(getline(fin,tmp,' ')&&(tmp!="CLOSEB")) {st+=' ';}}
                 if((tmp!="CLOSEB")) {if(sp>0) st+=' ';
                 st+=tmp;}
                 sp++;
                 }
                 cb++;
                 for(long int i=0;i<st.length();i++){
                    vec[n+cnt].val=st[i];
                    cnt++;
                 }
               }
               else if(tmp=="RELATION:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="OP:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="NEGATION")
                   v+='!';
               else if(tmp=="AND")
                   v+='&';
               else if(tmp=="OR")
                   v+='^';
               else if(tmp=="CLOSEB") {v+=')';cb++;}
               else if(tmp=="OPENB") {v+='(';ob++;}
               else{
                if(str=="alpha"){
                   if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") v+=tonumber(" ");
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                   else if(tmp=="NUMB:"){
                     getline(fin,tmp,' ');
                     v+=tmp;
                     v+=' ';
                   }
                }
                else if(str=="num"){
                   if(tmp=="NUMB:"){
                      getline(fin,tmp,' ');
                      v+=tmp;
                      v+=' ';
                   }
                   else if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") v+=tonumber(" ");
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                }
            }
          }
        if(strr==0){
        if(ob==cb) v.pop_back();
        if(str=="alpha")
        vec[n+cnt].val=toalpha(infix(v));
        else {
            vec[n+cnt].val=infix(v);
            if(vec[n+cnt].val=="") vec[n].val="0";
        }
        v="";
        cnt++;
        }
        }
        }
        else if(tmp=="ASSIGN"){
            while(getline(fin,tmp,' ')&&tmp!=""&&tmp!="EOLN\n"){

              if(tmp=="VARIABLE:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="INDEX:"){
                 getline(fin,tmp,' ');
                 v+='#';
                 if(tmp=="VARIABLE:")
                    getline(fin,tmp,' ');
                 else if(tmp=="OPENB") tmp=arrexp(fin);
                 v+=tmp;
               }
               else if(tmp=="RELATION:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="OP:"){
                 getline(fin,tmp,' ');
                 v+=tmp;
               }
               else if(tmp=="NEGATION")
                   v+='!';
               else if(tmp=="AND")
                   v+='&';
               else if(tmp=="OR")
                   v+='^';
               else if(tmp=="CLOSEB") v+=')';
               else if(tmp=="OPENB") v+='(';
               else{
               if(str=="alpha"){
                   if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") v+=tonumber(" ");
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                   else if(tmp=="NUMB:"){
                     getline(fin,tmp,' ');
                     v+=tmp;
                     v+=' ';
                   }
                }
                else if(str=="num"){
                   if(tmp=="NUMB:"){
                      getline(fin,tmp,' ');
                      v+=tmp;
                      v+=' ';
                   }
                   else if(tmp=="LIT:"){
                      getline(fin,tmp,' ');
                      if(tmp=="") v+=tonumber(" ");
                      else
                      v+=tonumber(tmp);
                      v+=' ';
                   }
                }
            }
        }
        if(str=="alpha")
        vec[n].val=toalpha(infix(v));
        else {
            vec[n].val=infix(v);
            if(vec[n].val=="") vec[n].val="0";
        }
        }
    }
}

int main(int argc,char** argv){   ///DECIDED WHAT FUNCTION TO CALL AND WHEN
    ///ARGUMENTS TO MAIN ARE USED AS THIS FUNCTION IS BEING CALLED BY THE IDE
    fin.open("lexer.txt",ios::out);
    fin<<puttotxt(argv[1]);
    fin.close();
    fin.open("lexer.txt",ios::in);
    var openb("","","");
    vec.push_back(openb);
    string str;
    int gap=0,condi=0;
    while(getline(fin,str,' ')){
        if(str=="OPENCB\n"){
            gap++;
            vec.push_back(openb);
        }
        else if(str=="CLOSECB\n"){
          gap++;
            for(long int it=vec.size()-1;vec[it].name!="";it--){
                vec.pop_back();
            }
            vec.pop_back();
          }
        else if(str=="EOLN\n")gap++;
        else if(str=="en") {gap++;cout<<'\n';}
        else if(str=="RESERVED:"){
          str="";
          getline(fin,str,' ');
          if(str=="out") {gap++;out();}
          else if(str=="in") {gap++;in();}
          else if(str=="alpha"||str=="num") {gap++;variable(str);}
          else if(str=="iter") {gap++;iter();}
          else if(str=="check"||str=="or"||str=="orelse"){
            if(str=="check") gap++;
            if(gap!=0){condi=0;gap=0;}
            if(str=="orelse"){
                int ob=1,cb=0;
                getline(fin,str,' ');
                string st="";
                while(ob!=cb&&getline(fin,str,' ')){
                    if(str=="OPENCB\n") ob++;
                    else if(str=="CLOSECB\n") cb++;
                    st+=str;
                    st+=' ';
                }
                if(condi==0&&gap==0)
                main_fn(st);
            }
            else if(str=="or"){
                condi+=check(condi);
            }
            else{
                condi+=check(condi);
            }
          }
        }
        else if(str=="VARIABLE:"){
            gap++;
            string v;
            long int ind=0;
            getline(fin,str,' ');
            long int n=search(str),a;
            getline(fin,str,' ');
            if(str=="INDEX:"){
                getline(fin,str,' ');
                if(str=="VARIABLE:") {
                    getline(fin,str,' ');
                    long int n1=search(str);
                    ind=tonum(vec[n1].val,0,vec[n1].val.length()-1);
                }
                else if(str=="OPENB") {str=arrexp();ind=tonum(str,0,str.length()-1);}
                else
                ind=tonum(str,0,str.length()-1);
                getline(fin,str,' ');
                }
            if(str=="ASSIGN"){
            while(getline(fin,str,' ')&&str!="EOLN\n"){
               if(str=="VARIABLE:"){
                 getline(fin,str,' ');
                 v+=str;
               }
               else if(str=="RELATION:"){
                 getline(fin,str,' ');
                 v+=str;
               }
               else if(str=="INDEX:"){
                 getline(fin,str,' ');
                 v+='#';
                 if(str=="VARIABLE:")
                    getline(fin,str,' ');
                 else if(str=="OPENB") str=arrexp();
                 v+=str;
               }
               else if(str=="OP:"){
                 getline(fin,str,' ');
                 v+=str;
               }
               else if(str=="NEGATION")
                   str+='!';
               else if(str=="AND")
                   str+='&';
               else if(str=="OR")
                   str+='^';
               else if(str=="CLOSEB") v+=')';
               else if(str=="OPENB") v+='(';
               else{
                if(vec[n].dat=="alpha"){
                   if(str=="LIT:"){
                      getline(fin,str,' ');
                      if(str=="") v+=tonumber(" ");
                      else
                      v+=tonumber(str);
                      v+=' ';
                   }
                   else if(str=="NUMB:"){
                     getline(fin,str,' ');
                     v+=(str);
                     v+=' ';
                   }
                }
                else if(vec[n].dat=="num"){
                   if(str=="NUMB:"){
                      getline(fin,str,' ');
                      v+=str;
                      v+=' ';
                   }
                   else if(str=="LIT:"){
                      getline(fin,str,' ');
                      if(str=="") v+=tonumber(" ");
                      else
                      v+=tonumber(str);
                      v+=' ';
                   }
                }
            }
        }
      }
      if(vec[n+ind].dat=="alpha")
        vec[n+ind].val=toalpha(infix(v));
      else {
            vec[n+ind].val=infix(v);
            if(vec[n+ind].val=="") vec[n].val="0";
        }
      }
    }
    fin.close();
    DeleteFile("lexer.txt");
    cout<<"\n\n";
    system("pause");
}
