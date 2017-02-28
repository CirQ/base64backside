# base64backside
This repository implements the back side algorithms using to encode/decode under base64 scheme.

In order to keep the efficiency, the backside algorithm is written in C language and process the character string in bit-wise operation. It is assumed that all the input strings consist of 8-bits characters and the decoded strings are valid Base64 encoded string (the length is the multiple of 4, consist of [A-Za-Z0-9+/] and the postfix has no more than two '='s).

The main use is to compile the source code as a dynamic link library to provide service to the front side.
