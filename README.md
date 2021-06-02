# Printer Attachment

A pan-tilt marker attachment to my small car project that allows it to print lines of text. A look at the coding process can be found on [my blog](https://wp.nyu.edu/yonatanrozin/printer-robot/) and a look at the fabrication process and diagrams can be found [here](http://wp.nyu.edu/yonatanrozin/toy-car-printer-attachment/).

## Introduction

Printer Attachment was my final project for my Material of Language and fabrication courses, in which I had to create a project that utilizes non-semantic elements of text and motors mounted to a material, respectively. The result was this project, which uses 2 combined servo motors and some laser-cut acrylic to create an arm to hold a sharpie or other marker that is attached to the front of a small Arduino car, allowing to function as a makeshift plotter that can print single lines of text. 

On the Material of Language side, a Jupyter Notebook is used to extract graphic font data from a .ttf font file. A simple font such as [Orbitron](https://fonts.google.com/specimen/Orbitron) is recommended. This font data is represented as a series of commands, each of which consist of a set of coordinates that are connected by lines, similar to "connect the dots", in order to form the shapes of letters or other characters. A command can either be "move" or "line", allowing for lines or spaces to be drawn as needed. The notebook receives a font file and a string of characters, returning the graphic data as an array of [x, y] coordinates in C++, the language which the Arduino reads. "Move" coordinates, which are not connected by a line, are preceeded by the coordinates [-1. -1], which tell the Arduino to raise the pen off the surface of the page before moving to the next coordinates. For all other commands, the pen is lowered onto the surface of the page by default. 

To create horizontal lines, vertical lines and spaces (the absence of a line), the pen must move along the x-, y- and z-axes, each axis being accomplished by a different motor. The horizontal motion is accomplished by an axel of 2 DC motors, which move the entirety of the car along the length of the page. As the car moves horizontally, a servo motor moves the pen along the y-axis to create vertical strokes. When a space is required, a second servo motor lifts the entire pen attachment off the page to prevent further lines from being drawn. 

Though the inspiration behind this project was a plotter machine, such as the [Axidraw](https://shop.evilmadscientist.com/productsmenu/846), these motions are modeled more closely after the motions of handwriting, in which the various axes a pen must move along are accomplished by different muscles. Horizontal motion is accomplished by the largest muscle: the arm, vertical motion is accomplished mainly by the fingers and the smallest motion of the pen on and off the page is mainly accomplished by the wrist. The end result is somewhat a combination of the two: a plotter-like machine whose breakdown of motions resembles an arm writing by hand.

## Credits

A huge thanks to Ben Light for his [Fabrication course](https://itp.nyu.edu/fab/) and to Allison Parrish for her [Material of Language](https://mol.decontextualize.com/schedule/) course!
