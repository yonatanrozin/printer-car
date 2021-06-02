# Printer Attachment

A pan-tilt marker attachment to my small car project that allows it to print lines of text. A look at the coding process can be found [here](https://wp.nyu.edu/yonatanrozin/printer-robot/) and a look at the fabrication process and diagrams can be found [here](http://wp.nyu.edu/yonatanrozin/toy-car-printer-attachment/).

## Introduction

Printer Attachment was my final project for my Material of Language and fabrication courses, in which I had to create a project that utilizes non-semantic elements of text and motors mounted to a material, respectively. The result was this project, which uses 2 combined servo motors and some laser-cut acrylic to create an arm to hold a sharpie or other marker that is attached to the front of a small Arduino car, allowing to function as a makeshift plotter that can print single lines of text. 

On the Material of Language side, a Jupyter Notebook is used to extract graphic font data from a .ttf font file. A simple font such as [Orbitron](https://fonts.google.com/specimen/Orbitron) is recommended. This font data is represented as a series of commands, each of which consist of a set of coordinates that are connected by lines, similar to "connect the dots", in order to form the shapes of letters or other characters. A command can either be "move" or "line", allowing for lines or spaces to be drawn as needed. The notebook receives a font file and a string of characters, returning the graphic data as an array of [x, y] coordinates in C++, the language which the Arduino reads.
