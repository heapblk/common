########################### common ###########################

compiler for the esoteric programming language with the same
name, a programming language in which everything is a comment!

_______________
| Features    |
---------------
- can parse comments from lots of programming languages!
- flags!!!
- compiles to .com files in record speed :)
- best compiler for common (as of 2025-10-14)

____________
| Usage    |
------------
simply create a file (really, any file!), we'll use a simple
`common_test.txt` file here, on linux do:
	$ touch common_test.txt
then fill it up with whatever you want to comment!
by default common uses the C/C++ comments, so we'll write:
	// this is a C/C++ line comment
	/* 
	   this is
	   a C/C++ block
	   comment
	*/
of course we used vim to edit the file ;)
now the good part, actually using the common compiler!
for C/C++ comments, simply do 
	$ common common_test.txt
and out pops a `common_test.com` file!
"b-but what if I want to use python-style comment" you ask?
worry not, common has lots of flags that enable it to parse
all kinds of comment styles :D 
for example, for python-style comments we'd do this:
	$ common --style=python common_python_test.txt
and out pops a `common_python_test.com` file yay!
