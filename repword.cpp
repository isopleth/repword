// MIT License
//
// Copyright (c) 2019 Jason Leake
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


// repword <input file> [<input file>...]
//
// This program copies the text files specified as command line
// parameters to stdout, removing repeated words in the process.  I
// tend to duplicate words in LaTex and text files, and this is a
// simple program for fixing that.
//
// e.g.
//
// Input file:
// ant bear camel camel deer emu
//
// Output:
// ant bear camel  deer emu
//
// Whitespace is carefully preserved even when words are deleted -
// hence the two spaces in front of deer in the output example above.

#include <algorithm>
#include <cctype>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

auto main(int argc, char** argv) -> int {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <files>" << endl;
    return EINVAL;
  }

  // For each file provided in the command line
  for (auto&& index = 1; index < argc; index++){
    auto file = ifstream{argv[index]};
    if (file.is_open()) {
      auto line = string{};
      auto firstWord = false;
      auto previousWord = string{};
      while (getline(file, line)) {
	if (!line.empty()) {
	  if (all_of(line.begin(), line.end(),
		     [](char ch)->bool{return (isspace(ch));})){
	    // Echo lines containing just whitespace
	    cout << line;
	  }
	  else {
	    // Else search for duplicate words
	    auto inputStringStream = istringstream(line);
	    auto word = string{};
	    
	    while (inputStringStream >> word) {
	      // echo whitespace before the word
	      auto positionOfWord = line.find(word);
	      cout << line.substr(0, positionOfWord);
	      
	      line = line.substr(positionOfWord + word.length());
	      if (firstWord) {
		// Always echo the first word in the file
		firstWord = false;
		cout << word;
		previousWord = firstWord;
	      }
	      else if (previousWord != word) {
		// Echo the word if it doesn't match the previous one
		cout << word;
	      }
	      // Remember the current word so that it can be compared
	      // with the next one
	      previousWord = word;
	    }
	  }
	}
	// All lines terminated by a newline, even empty ones
	cout << endl;
      }
      file.close();
    }
    else {
      cerr << "Unable to open " << argv[index] << endl;
    }
  }
  return 0;
}
