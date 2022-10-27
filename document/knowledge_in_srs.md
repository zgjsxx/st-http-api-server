# knowledge in SRS
- [knowledge in SRS](#knowledge-in-srs)
  - [About headers include](#about-headers-include)

## About headers include
in srs project we use <> to include all of our headers, it is ok.

Refer from here, https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html

These options specify directories to search for header files, for libraries and for parts of the compiler:

-I dir
-iquote dir
-isystem dir
-idirafter dir

Directories specified with -iquote apply only to the quote form of the directive, #include "file". 
Directories specified with -I, -isystem, or -idirafter apply to lookup for both the #include "file" and #include <file> directives.



## About log module
Srs log module does not contain function name and line information, maybe it can be enhanced