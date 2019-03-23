# repword

This program copies the text files specified as command line
parameters to stdout, removing repeated words in the process.  I
sometimes duplicate words in text and LaTeX documents, and this is a
simple program for fixing that.

`repword <input file> [<input file>...]`

e.g.

Input file:

`ant␣bear␣camel␣camel␣deer␣emu`

(where `␣` is a space)

Output:

`ant␣bear␣camel␣␣deer␣emu`

Whitespace is carefully preserved even when words are deleted - hence
the two spaces in front of deer in the output example above. This
isn't important for the LaTeX documents I wrote this for, but for
plain text documents you might need to fix the spacing.

## Building

Requires a g++ that supports C++17.  Run `make` to build the repword image.

Program can be tested using `make test`, which runs a Python 3 script
to compare the output from a test vector with the expected output.
