# My Chill Parser

A lightweight, extensible, and handcrafted parser designed for flexibility and fun. Built as part of a larger project, I wanted to show this first!
Currently in the debugging case, so if you notice any bugs, please let me know! 

## Features

- **Extensible Grammar**: Add new rules and tokens dynamically.
- **Modular Design**: Easy to tweak and extend.
- **Efficient**: Uses a stack-based approach for smooth parsing.
- **Dynamic Rule Handling**: Define and apply rules on the fly.
- **AST Generation**: Outputs a clean Abstract Syntax Tree (AST).

## How It Works

1. **Lexer**: Tokenizes your input.
2. **Parser**: Matches tokens against defined rules using a stack.
3. **Dynamic Rules**: Handles subexpressions and new grammar rules.
4. **Output**: Produces a Parse tree that you can take and make into an AST tree.

If you want to make any changes, check out the grammar folder and lexer folder; there, you can define custom grammars and tokens!
## Quick Start

### Clone and Build

```bash
git clone https://github.com/LiyuZer/Parser.git
cd Parser
make
```

### Run

```bash
./parser++ file_name -i <file for parse graph>
```

### Customize Rules

Edit the `rules` map in the source code to add or modify grammar rules.
Check out the 

## Why This Parser?

- Built entirely from scratch.
- Highly adaptable for custom DSLs or scripting languages, and in the future, hopefully all languages(even context-sensitive ones)
- The format is easy to work with for beginners 

## Contact

- **Email**: liyulg0@gmail.com

Let’s make parsing simple and fun!

This is an image of a parser tree(from one of the files in this repo) 
![Parse Tree!](assets/image.png)

