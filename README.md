cat
===

The most basic "Software Tool": Read one or more files, or the standard input,
and combine their contents to the standard output.

C++ problems
------------

C++ does not distinguish meaningfully between end-of-file and a read error, so

    ./cat-c++ < /etc

will produce an empty output instead of an is-a-directory error.
