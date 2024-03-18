# RocketC - RefactoringCompiler

This branch was created in order to organize the RocketC compiler project in a better way, as well as improve some
details regarding its implementation. 
It is organized as follows:
- Lexer: This folder contains all files related to the lexical analyzer.
- Parser: This folder contains all files related to the syntactic analyzer. 
- Util: General purpose utility files, as well as some typedefs and constants.
## Makefile
The new makefile included with this project allows to generate only specific
components (i.e. only the lexer, or only the parser), or to fully generate the project.
For building the complete project, just run "make all" under the project root.

## Testing
For testing the lexer, after running make, just go to the "Output" folder and
run ./RocketC <SrcFile.c> --lex
