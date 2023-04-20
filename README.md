# Project_CS162_APCS22: VisualGo clone in C++

A visualization tool for common data structures, written in C++ using the SFML library.

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Supported Data Structures](#supported-data-structures)
- [License](#license)

## Introduction

Data Structure Visualization is a program that allows users to visualize the behavior of common data structures such as linked lists, stacks, queues. This program is written in C++ and uses the SFML library for graphics rendering.

## Features

- Users can select from seven different data structures to visualize: array, linked list, doubly linked list, queue, stack, binary search tree, and AVL tree.
- Users can customize the data structure by selecting the size of the data structure and the values to be included.
- Users can insert, delete, search, and update values in the data structure.
- The program includes animations of the algorithms responsible for inserting, deleting, searching, and updating values in the data structure.
- Users can control the speed of the animations and play or pause the animations.

## Installation

### Prerequisites

- C++ compiler (such as g++ or clang++)
- SFML library (installation instructions available on the [SFML website](https://www.sfml-dev.org/download.php)

### Building

1. Download or clone the repository to your local machine.
2. Install SFML library by following the instructions in SFML's official website.
3. Navigate to the project directory and open a terminal.
4. Compile the code using the following command:
```console
cd src/
g++ -fdiagnostics-color=always -g *.cpp -o DataVisual.exe -Ipath_to_SFML/include -Ipath_to_project/header -DSFML_STATIC -Lpath_to_SFML/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows
```

### Running

1. Navigate to the directory of the project.
2. Run the executable file through terminal:
```console
./src/DataVisual.exe
```
or move the DataVisual.exe file in the "src/" folder to its parent folder and double-click it.

## Credits

This program was created by Le Duc Phu (dphu2609) as a project for CS162 - Introduction to Computer Science II at VNU - University of Science.

## Supported Data Structures

This program currently supports the following data structures:

- Static Array
- Dynamic Array
- Singly Linked List
- Doubly Linked List
- Circular Linked List
- Stack
- Queue

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
