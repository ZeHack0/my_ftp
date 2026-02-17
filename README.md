# MyFTP

the ```MyFTP``` project is a program developed in C++ language.</br>
It's the first project of the module ```NWR (Network Programming)```

## Table of contents

- [Description](#description)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#Usage)
- [Authors](#authors)

## 📝 Description

The project ```MyFTP``` is a server that adheres to the principes of the ```FTP protocol``` and the ```RFC959``` standard.</br>
The project's objective is to implement a server capable of handling multiple clients simultaneously, ensuring anonymous authentification,</br>
and enabling file transfers via ```TCP``` sockets in both active and passive modes.</br>
The server uses polling to efficiently manage multiple connections and forking to isolate ```data transfers```, thus guaranteeing good performance and robust network architecture.

## Prerequisites

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)
- [LibC++](https://www.w3schools.com/cpp/cpp_getstarted.asp)

## Installation

### 🛠️ Installation Steps

1. Clone the repository :

   ```bash
   git clone https://github.com/ZeHack0/my_ftp.git

1. Navigate to the project directory :

   ```bash
   cd (name of directory project)

1. Compile the project :

   ```bash
   make
This command uses the Makefile to compile the project. Ensure that the Makefile is correctly configured for your environment.


## 📋 Usage

### How tu use

- example :

   ```bash
   ./myftp port path

## Authors
- Ronan BOTREL | [Github](https://github.com/ZeHack0)
