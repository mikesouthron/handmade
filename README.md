# Handmade Repo

This is my handmade repo where I am writing tools, utilities and applications from scratch.

Why? For fun and to learn about stuff!

My aim is to write a number of small libraries and build up to writing some full sized applications.

Example applications to end with:
- Web Applications
- Desktop Applications
    - Basic text editor
- etc.

Exmaples of libraries:
- HashMap
- CSV Parser/Writer
- JSON Parser/Writer
- etc.

There are 2 things I won't be doing:
- Writing my own Operating System
    - While this would be a super fun project, and I would learn loads I just don't have the free time to devote to it
- Writing my own programming language
    - Again while fun, I will be writing everying in C, it's a low level fast language that is ubiquitous, every language can talk to it, most OS based libraries can be interacted with very easily using it.
    - Some cool languages that I would consider other than C would be Zig and Odin, check them out!

There are 2 things I would like to get to but for now won't be doing.

- Writing a database
    - A big project, will be fun when I get to it
    - I will be using SQLite or Postgres depending on my needs
- Programming Editor/IDE
    - A very fun and challenging project, but quite long term.
    - I will be using a combination of VS/VSCode/Emacs for writing my C code.

# Libraries

## HashMap

Basic header only hashmap implementation. 

Using FNV-1a for it's hashing function.

## CSV

CSVReader header library.

Has a nice feature where the header goes into a HashMap char* -> int.