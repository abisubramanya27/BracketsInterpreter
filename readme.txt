SYNTAX SHEET FOR BRACKETS V3.0.1 :
********************************
************************************************* NO EDIT!! *************************************************************
•ALWAYS A STRING IS GIVEN WITHN DOUBLE QUOTES, A SINGLE CHARACTER OR LITERAL WITHIN SINGLE QUOTES!!
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FOR DISPLAYING DATA:
      out(....);
     • The data displayed :
               if an number or expression involving operations with variables and numbers or simply a variable, just put them inside out() without any quotes.
               if a single character, put the character within ' ' (single quotes).
               if a sentence or word, put them within " " (double quotes).
               if a string variable, put them as varID# .
               if a new line, put en.
     • There can be a combination or sequence of the above separated by commas (,) .
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FOR INPUTTING DATA:
      in(....);
      • The data inputted :
               if a variable, just put the varID.
               if a string, put varID# .
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FOR COMMENTS:
       cmt(ANYTHING YOU WISH);
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DATATYPES:     
       • num      //FOR INTEGER AND DECIMAL NUMBERS
       • alpha    //FOR ALPHABETS, SINGLE CHARACTERS
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ARRAYS/STRINGS:
       It should be given as varID#size during declaration and initialisation, and varID#index during usage of that element index.
       Strings follow the same rules as a character array except there has to be a null character at the end of the string, which requires an extra size.If we dont provode that extra size it cannot be treated as a string.
       Strings need not be given implicitly a null character at the end. It is automatically done by the compiler but that extra size has to be provided.
       The array index or size , if a character(whose ASCII value will be taken) or an expression or another array's element, has to be given as varID#(expr) . 
       The array or string is numbered starting from 0 (zero) .
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DECLARATION:
      It is given as:
             datatype varID_1,varID_2,......;
      • For array declaration and string declaration provide size too like: varID#(size) or varID#size as required .
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INITIALISATION AND DECLARATION:
      It is given as:
             (FOR INITIALISATION):   datatype varID_1=(expr),.......;     //(...) needed only for expressions, not for single characters or single integer, decimal
             (FOR DECLARATION):     varID_1=(expr),.......;     //(...) needed only for expressions, not for single characters or single integer, decimal
      •For arrays, varID#(size)(value_1,value_2,.....) //As per number of values given, that many number of elements from the beginning is filled with the corrresponding values. The number of values given should be less than or equal to size of array
      •For strings, varID#(size)("string") //The number of characters must be one less than size of string
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
• CONTROL STRUCTURES:-
   LOOP:
         iter(condition){....}     //{,} are necessary for even single statement loops
 
   CONDITION STATEMENTS REPLACING IF,ELSE OF, AMD ELSE IN C++:
        • One way:
           check(condition){...}
        • Two way:
           check(condition){...}
           orelse{...}
        • N-way:
           check(condition){...}
           or(condition){...}
           orelse{...}
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
• LOGICAL OPERATORS:-
    1.OR  ^
    2.AND &
    3.NOT !
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
• RELATIONAL OPERATORS:-
    1.EQUAL TO                 ==
    2.GREATER                  >
    3.LESSER                   <
    4.GREATER THAN OR EQUAL TO >=
    5.LESSER THAN OR EQUAL TO  <=
    6.NOT EQUAL TO             !=
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
• ALL OTHER RELATIONAL,LOGICAL AND ARITHMETIC OPERATORS SAME AS C++
• NO POST OR PRE- INCREMENT OR DECREMENT IS AVAILABLE
• MULTIPLE AND NESTED LOOPS AND CHECK'S ARE ALLOWED!!
• ANY OTHER METHOD OR SYNTAX ADOPTED MAY LEAD TO PROGRAM CRASHING!!