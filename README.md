# EmbASP++
A C++ porting of the framework for integration of Logic Programming EmbASP

- The library uses some C++17 features and the **Boost.Filesystem** and **Boost.Process** libraries; 
- The library also uses the C++11 thread library;
---
Use the following flags to compile without "undefined reference" problems:

`-std=c++17 -lboost_system -lboost_filesystem -pthread`
