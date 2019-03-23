#!/usr/bin/env python3
#
# Test the repword program by comparing the output generated from a
# test vector with the expected output.
#

import sys

""" This is the test script for the program """

def main():
   if len(sys.argv) != 3:
      print("Wrong number of command line parameters")
      print("%s <input_file> <expected_file>" % sys.argv[0])
      raise ValueError("Test not run")
   else:
      try:
         inputFileContents = ""
         expectedFileContents = ""
         try:
            with open(sys.argv[1], "r") as inputFile:
               inputFileContents = inputFile.read()
         except:
            print("Input file %s not found" % sys.argv[1])
            raise ValueError("Test not run")

         try:
            with open(sys.argv[2], "r") as expectedFile:
               expectedFileContents = expectedFile.read()
         except:
            print("Expected file %s not found" % sys.argv[2])
            raise ValueError("Test not run")
         
         if expectedFileContents == inputFileContents:
            print("Test passed")
         else:
            print("Test failed")

      except ValueError as error:
         print(error)
         
if __name__ == "__main__":
   main()

