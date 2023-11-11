#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

enum tokenum {
    ID = 0, NUM, ATR, MAIS, MENOS, VEZES, DIV, LPAR, RPAR, PEV, IF, ELSE, WHILE, DO, RETURN, BREAK, CONTINUE, SWITCH, CASE, DEFAULT, INT, CHAR, FLOAT
};

struct token {
    tokenum token;
    string type;
    string text;
};

token v[1024];
int n = 0;

bool verifyChar(string in){

    if(in == "="){
        v[n++] = {ATR, "<ATR>", in};
        return true;
    }

    else if(in == "("){
        v[n++] = {LPAR, "<LPAR>", in};
        return true;
    }

    else if(in == ")"){
        v[n++] = {RPAR, "<RPAR>", in};
        return true;
    }

    else if(in == "+"){
        v[n++] = {MAIS, "<MAIS>", in};
        return true;
    }

    else if(in == "-"){
        v[n++] = {MENOS, "<MENOS>", in};
        return true;
    }

    else if(in == "*"){
        v[n++] = {VEZES, "<VEZES>", in};
        return true;
    }

    else if(in == "/"){
        v[n++] = {DIV, "<DIV>", in};
        return true;
    }

    else if(in == ";"){
        v[n++] = {PEV, "<PEV>", in};
        return true;
    }

    return false;
}

bool verify_specialToken(string in){
    if(in == "if"){
        v[n++] = {IF, "<IF>", in};
        return true;
    }
    else if(in == "else"){
        v[n++] = {ELSE, "<ELSE>", in};
        return true;
    }

    else if(in == "while"){
        v[n++] = {WHILE, "<WHILE>", in};
        return true;
    }

    else if(in == "do"){
        v[n++] = {DO, "<DO>", in};
        return true;
    }

    else if(in == "return"){
        v[n++] = {RETURN, "<RETURN>", in};
        return true;
    }

    else if(in == "break"){
        v[n++] = {BREAK, "<BREAK>", in};
        return true;
    }

    else if(in == "continue"){
        v[n++] = {CONTINUE, "<CONTINUE>", in};
        return true;
    }

    else if(in == "return"){
        v[n++] = {RETURN, "<RETURN>", in};
        return true;
    }

    else if(in == "switch"){
        v[n++] = {SWITCH, "<SWITCH>", in};
        return true;
    }

    else if(in == "case"){
        v[n++] = {CASE, "<CASE>", in};
        return true;
    }

    else if(in == "default"){
        v[n++] = {DEFAULT, "<DEFAULT>", in};
        return true;
    }

    else if(in == "int"){
        v[n++] = {INT, "<INT>", in};
        return true;
    }

    else if(in == "char"){
        v[n++] = {CHAR, "<CHAR>", in};
        return true;
    }

    else if(in == "float"){
        v[n++] = {FLOAT, "<FLOAT>", in};
        return true;
    }

    return false;

}

int main() {

    #pragma region variables
    string input, fileName;
    regex numberRegex ("-{0,1}[0-9]+"); // this regex accepts negative numbers
    regex idRegex ("_{0,1}[a-z]{1}[_a-zA-Z]*");
    fstream inputFile;
    ofstream outputFile("output.txt");

    cout << "Input the file name: ";
    cin >> fileName;

    inputFile.open(fileName, ios::in);

    //Verify if the file exists, if not: quit the program
    if(!inputFile)
    {
        cout<<"Error! File Does not Exist";
        getchar();
        return 1;
    }

    cout << endl << endl;
    #pragma endregion variables

    #pragma region logic
    while(inputFile >> input) {

        cout << input << endl;

        if(input.length() == 1){
            if(!verifyChar(input))
                if(regex_match(input, numberRegex))
                    v[n++] = {NUM, "<NUM>", input};
        }

        else if(input.length() >= 2){

            if(!verify_specialToken(input)){

                if(regex_match(input, idRegex))
                    v[n++] = {ID, "<ID>", input};

                else if(regex_match(input, numberRegex))
                    v[n++] = {NUM, "<NUM>", input};
            }
        }

        else {
            cout << "Lexical error!" << endl;
            return 1;
        }
    }

    #pragma endregion logic

    #pragma region output
    for(int i = 0; i < n; i++){
        if(v[i].token == NUM or v[i].token == ID)
            outputFile << v[i].token << ", " << v[i].type << " " << v[i].text << endl;
        else{
            outputFile << v[i].token << " " << v[i].type <<endl;
        }
    }

    for(int i = 0; i < n; i++){
            cout << v[i].token << ", " << v[i].type << " " << v[i].text << endl;
    }

    #pragma endregion output

    inputFile.close();
    outputFile.close();

    return 0;
}