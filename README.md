# CAD-Tool
This repository holds CAD-Tool app, its source code and documentation.

## Objective

The package have the following functionalities -
 1. To reconsturct a 3D object from its given 3 orthographic views(Top view, Front view and Right Side view).
 2. To draw orthographic projections of a given 3D object.

## Installing

	The app folder contains an AppImage(named CAD_Tool) which can run on Linux systems. 
	Make the app executable by running the following command in the app folder:
	
	```
	chmod a+x CAD_Tool
	```
	To execute run the executable or run command:
	
	```
	./CAD_Tool
	```

### Build from sources ####
        
	In the project directory run the following commands:
	```
	qmake CAD_Tool.pro
	make
	```
	And to execute go to bin directory and run the executable or run command:
	```
	./CAD_Tool
	```
	
## Dependencies for build
	The project make use of the QT libraries for c++.
	Use the following command to install qt:
	```
	sudo apt-get install qt
	```

## Input/Output Format ##

### 3D to 2D

#### Input

###### Provide 3D object description in *.txt* file in the below format:- ######
	
	N    -> number of vertices

	x0 y0 z0                -> coordinates of vertex V(0)
	......
	....
	..
	.
	x(N-1) y(N-1) z(N-1)    -> coordinates of vertex V(N-1)


	E    -> number of edges

	a b         -> this means that there is an edge between ath vertex and bth vertex, a and b are 0 indexed
	....
	...
	..


#### Output

* Application generates output in a window which appears after clicking button in gui.

### 2D to 3D

### Input

###### Provide 2D object in *.txt* format as follows:- ######
	N   			 -> number of vertices

	t0.x t0.y   -> top view projection of vertex V(0)      |
	f0.x f0.y   -> front view projection of vertex V(0)    | ----> first vertex
	s0.x s0.y   -> side view projection of vertex V(0)     |

	t1.x .....
	...
	..
	.
	
	t(N-1).x t(N-1).y   -> top view projection of vertex V(N-1)      |
	f(N-1).x f(N-1).y   -> front view projection of vertex V(N-1)    | ----> last vertex
	s(N-1).x s(N-1).y   -> side view projection of vertex V(N-1)     |

	Te   			  -> number of edges in top view

	x0,y0,x0',y0'  		  -> edge between coordinates (x0,y0) and (x0',y0') in top view
	.....
	....

	Fe   			  -> number of edges in front view

	x0,y0,x0',y0'  		  -> edge between coordinates (x0,y0) and (x0',y0') in front view
	....
	..

	Se   			  -> number of edges in right side view

	x0,y0,x0',y0'  		  -> edge between coordinates (x0,y0) and (x0',y0') in side view
	....
	..

### Output

* Application generates output in  *.obj* file (filename is given as input, file generated in the same directory of the app).

#### Format of *.obj* file ####
		v x y z    # a vertex => charcter 'v' followed by (x, y, z) coordinates of the point
		v ...
		...

		f 1 3 4 5 1    # a face => character 'f' followed by indices(1-indexed) of vertices lying on that face
		f ...
		...
		
		Explanatioon => f 1 3 4 5 1, face contains loop with edges (1,3),(3,4),(4,5),(5,1), the order of the edges decides the direction of the normal of the face and the direction of the normal decides hollowness of the face.

### Obj File viewers

* For Windows -> Print 3D (default software for obj in windows 10)
* For Linux   -> G3DViewer (to install - sudo apt-get install g3dviewer)
* Online      -> **[Online 3D Viewer](https://3dviewer.net/)**

## Authors ##

* **[Manish Tanwar](https://github.com/manishtanwar/)**
* **[Abhinash Kumar](https://github.com/sabhi2257)**


