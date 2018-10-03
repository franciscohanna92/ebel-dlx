> _I did not write this code. I found it on [http://www.iro.umontreal.ca/~bergeret/EBEL-DLX/](http://www.iro.umontreal.ca/~bergeret/EBEL-DLX/). Since it was GNU 2.0 licensed I thought it will be a good idea to put it out here so it's reviewed and used by the community._

# Authors
This software was originally developed by [Etienne Bergeron](bergeret@iro.umontreal.ca) and [Eric Lesage](lesagee@iro.umontreal.ca).

# Overview
This repository contains release 1.0.3 of the EBEL DLX system. EBEL DLX includes a DLX compiler and simulator. This release has been built successfully on an i686 PC with Linux 2.2 (ELF) and glibc 2.1. 

The EBEL DLX system conforms to the DLX architecture standard. Installation instructions are given in the next section. 

The user manual for the EBEL system is in the [wiki page](https://github.com/franciscohanna92/ebel-dlx/wiki) of this repository

If you have any questions concerning EBEL system please address them to bergeret@iro.umontreal.ca or lesagee@iro.umontreal.ca.
 
The latest official release of the system can be obtained [here](http://www.iro.umontreal.ca/~bergeret/EBEL-DLX/).

# How to use

Download or clone and `cd` into the root folder. Run `make`.  After a succesful _make_ a executable file named `dlx` would be generated. Run `./dlx` to execute the system.

# Todo
- Finish and verify floating point instructions assembly and simulation.
  (Not completed and not tested.)
- Some instructions are not implemented in the VM. ( mov** cvt** ).
- Parse the command line with a lex/yacc grammar to accept complex
  expressions.


# Known limitations and deficiencies
- The last line of the input file needs a `<cr>` to be accepted. Without the `<cr>`, you will obtain a "parse error".