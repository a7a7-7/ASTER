# ASTER
DDos tool for server security.

Currently, ASTER supports these DDoS methods.

SYN flooding, 

ASTER is compiled with **makefile, g++**

supported g++ version is **6.3.0-1** ~ 
It may be worked in a lower version but for stability, I recommend using over 6.3.0

ASTER will not support Windows afterward because raw TCP socket of Winsock2 has **limitations** to prevent IP spoofing and DDoS.
