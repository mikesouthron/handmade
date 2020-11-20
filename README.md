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

## JSON

JSON parsing is currently done as a one off parse for individual structs, copying the example code to get started.
This is laborious, but frankly JSON is a crap transfer format and I would only ever use it for web type communication as JavaScript can natively handle it.
In this scenario I would aim to keep my JSON small and simple, preferring server side rendering for as much as possible, and JSON only as and when it was needed for limited async work.

I may write a generic handler that uses a HashMap to simply shove the entire JSON object into memory, but this doesn't allow for static typing or validation of the data.

JSON output is not done yet, but this is actually an easier task to do on a struct by struct basis (if your data is simple and flat) you just write a function that builds up a string.

An alternative to JSON is a custom string or binary format, where data is just sent up as a delemited data that both ends know how to handle, the disadvantage of this is: Custom Javascript for parsing a handwritten format may be slower than JSON.parse() and it isn't as easy for a human to read (the real reason JSON is popular).

If I needed complex JSON parsing, I expect I would have to leave the 'handmade' philosophy behind and use the jansson library, it is a library with a decent API and no extra dependecies, it is fairly easy to just include the source in an application and compile it.