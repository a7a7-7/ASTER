# ASTER

### Server Dos testing tool that is written in C++.

---

* ### Feature
    * **SYN flooding**
    * **LAND attack**

* ### Build
    ASTER is compiled with **makefile, g++**.
    
    ```
        make
    ```
    and output should be looked like this
    ```
        src/func/syn_flood.cpp
        ...
        src/main.cpp
    ```

    to clean build files:
    ```
        make clean
    ```

    supported g++ version is **6.3.0-1** or higher version.
    It may be worked in a lower version but for stability, **Higly** recommend using over 6.3.0.
    
* ### Run
    Print manual or usage :
    ```
        aster
        aster -h
    ```
    
    Use Dos :
    ```c++
        // To use SYN flood..
        aster 192.168.1.1 // or
        aster -s 192.168.1.1
        // Also port can be specified like this (Default is 80)
        aster 192.168.1.1 -p 25565
    ```
    
---
### Legal notice
> This software is provided for **educational use or for security test only**. a7a7-7(author) will not be held **responsible** for any **illegal activity** by user. By using this software, user **agree to these terms**.

###### ASTER will not support **Windows** afterward because raw TCP socket of Winsock2 has **limitations** to prevent IP spoofing and DoS attack.
