cat
===

The most basic "Software Tool": Read one or more files, or the standard input,
and combine their contents to the standard output.

Java problems
-------------

Java does not detect errors in `System.out.write`, so broken pipes like

    yes | java cat | head

will loop instead of exiting.

C++ problems
------------

C++ does not distinguish meaningfully between end-of-file and a read error, so

    ./cat < /etc

will produce an empty output instead of an error.
