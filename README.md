# Compiler Design and Construction — Lab Works

**Name:** Suvekshya Jha
**Lab No.:** 2
**Roll No.:** 80117729
**Course:** BSc. CSIT, 6th Semester
**Subject:** Compiler Design and Construction

## Objective

- To implement DFAs for pattern recognition over a binary alphabet and generate prefixes, suffixes, and substrings of a string.
- To build lexical analysis tools that identify comments, validate identifiers/keywords, classify operators, and tokenize source code (manually and via Flex).
- To preprocess a Context-Free Grammar by eliminating left recursion and applying left factoring.
- To compute FIRST and FOLLOW sets and construct an LL(1) parsing table for top-down predictive parsing.
- To implement a non-recursive top-down (LL(1)) parser and a shift-reduce parser for bottom-up parsing.
- To construct SLR(1), canonical LR(1), and LALR(1) parsing tables, and to build a parser using Flex and Bison.
- To implement a symbol table supporting insert, search, update, and delete operations for identifiers.
- To design a scoped symbol table using nested hash maps to handle variable declaration and lookup across block scopes.
- To perform type checking and implicit type coercion on expressions, assignments, and array references.
- To implement semantic validation rules for control structures (`if`, `while`, `for`) using the Visitor design pattern.
- To generate intermediate code in Three-Address Code (Quadruple) form for expressions, control flow, and function calls.
- To translate intermediate code into target (8086) assembly code.
- To implement code optimization techniques, including constant folding, constant propagation, dead code elimination, and peephole optimization.

## Lab Works Included

### Part 1 — Lexical & Syntax Analysis

| No. | Title | File |
|-----|-------|------|
| 1 | DFA Implementation (starts with 01 / ends with 01 / contains 001) | `dfa_implementation.cpp` |
| 2 | Prefixes, Suffixes, and Substrings Generator | `prefix_suffix_substring.cpp` |
| 3 | Comment Identifier | `comment_identifier.cpp` |
| 4 | C Identifier and Keyword Validator | `identifier_validator.cpp` |
| 5 | Lexical Analyzer for Operators | `operator_lexer.cpp` |
| 6 | Lexical Analysis via Flex (.l) | `lexer.l` |
| 7 | Grammar Transformations (Left Recursion & Left Factoring) | `grammar_transform.cpp` |
| 8 | FIRST and FOLLOW Computation | `first_follow.cpp` |
| 9 | LL(1) Parsing Table Construction | `ll1_table.cpp` |
| 10 | Top-Down Non-Recursive Descent Parser | `ll1_parser.cpp` |
| 11 | Shift Reduce Parser | `shift_reduce_parser.cpp` |
| 12 | SLR(1) Parsing Table Construction | `slr_table.cpp` |
| 13 | LR(1) Parsing Table Construction | `lr1_table.cpp` |
| 14 | LALR(1) Parsing Table Construction | `lalr1_table.cpp` |
| 15 | LALR(1) Parsing via Flex/Bison | `parser.y` |

### Part 2 — Semantic Analysis, Intermediate Code & Optimization

| No. | Title | File |
|-----|-------|------|
| 16 | Symbol Table Implementation | `symbol_table.cpp` |
| 17 | Symbol Table Construction and Scope Management | `scoped_symbol_table.cpp` |
| 18 | Type Checking for Expressions | `type_checking.cpp` |
| 19 | Semantic Rules for Control Structures | `control_structure_semantics.cpp` |
| 20 | Intermediate Code Generation for Expressions | `tac_expressions.cpp` |
| 21 | TAC Generation for Control Flow Statements | `tac_control_flow.cpp` |
| 22 | Intermediate Code for Functions and Parameters | `tac_functions.cpp` |
| 23 | Code Generation (TAC to 8086 Assembly) | `code_generation.cpp` |
| 24 | Constant Folding and Constant Propagation | `constant_folding.cpp` |
| 25 | Dead Code Elimination and Control Flow Graph | `dead_code_elimination.cpp` |
| 26 | Peephole Optimization | `peephole_optimization.cpp` |

## Tools & Requirements

- Language: C/C++ (C++11 or later)
- Compiler: g++ / any standard C++ compiler
- Flex and Bison (for Lab 6 and Lab 15)
- OS: Windows / Linux / macOS

## How to Compile and Run

**C/C++ programs:**
```bash
g++ <filename>.cpp -o output
./output
```

**Flex (Lab 6):**
```bash
flex lexer.l
gcc lex.yy.c -o lexer -lfl
./lexer
```

**Flex + Bison (Lab 15):**
```bash
bison -d parser.y
flex lexer.l
gcc parser.tab.c lex.yy.c -o parser -lfl
./parser
```

## Folder Structure

```
├── Part 1/
│   ├── dfa_implementation.cpp
│   ├── prefix_suffix_substring.cpp
│   ├── comment_identifier.cpp
│   ├── identifier_validator.cpp
│   ├── operator_lexer.cpp
│   ├── lexer.l
│   ├── grammar_transform.cpp
│   ├── first_follow.cpp
│   ├── ll1_table.cpp
│   ├── ll1_parser.cpp
│   ├── shift_reduce_parser.cpp
│   ├── slr_table.cpp
│   ├── lr1_table.cpp
│   ├── lalr1_table.cpp
│   └── parser.y
├── Part 2/
│   ├── symbol_table.cpp
│   ├── scoped_symbol_table.cpp
│   ├── type_checking.cpp
│   ├── control_structure_semantics.cpp
│   ├── tac_expressions.cpp
│   ├── tac_control_flow.cpp
│   ├── tac_functions.cpp
│   ├── code_generation.cpp
│   ├── constant_folding.cpp
│   ├── dead_code_elimination.cpp
│   └── peephole_optimization.cpp
└── README.md
```

## Notes

Each program prints the Lab No., Name, and Roll No. after its main output, as required by the lab report format.
