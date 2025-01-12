#include "parser/parser.h"
#include "lexer/lexer.h"
#include "grammar/grammar_def.h"
#include "utilities/utilities.h"

// You can run the parser by running the following command:
// ./parser++ <filename> -i <filename parse tree dot file> 
// -i is optional and is used to print the parse tree
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please provide a filename" << endl;
        return 1;
    }

    // We will convert the incoming argument to a filename
    string input_file(argv[1]);   
    string input_text;
    readFile(input_file, input_text);

    Lexer myLexer;
    Parser myParser;
    shared_ptr<ParseNode> ptr;
    bool result = myParser.parse(myLexer,input_text, rules, ptr);
    if (result) {
        cout << "Parse successful!" << endl;
        if (argc == 4 && string(argv[2]) == "-i") {
            string output_file(argv[3]);
            ptr->toDot(output_file);
        }

    } else {
        cout << "Parse failed!" << endl;
    }

    
    return 0;
}
