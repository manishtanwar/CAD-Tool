# CAD-Tool# AutoCAD
Projections of 3D objects and reconstruction of 3D object from given projections


## Installing

	The app folder contains an AppImage which can run on Linux systems. 
	Make the app executable by running 

	chmod a+x CAD.AppImage 

	in the app folder.

### Build from sources ####
```
qmake CAD.pro
make
```


##Input/Output Format##

###3D to 2D

####Input

######Provide 3D object description in *.txt* file in the below format:-######
	
	N    -> no of vertices

	x1 y1 z1    -> coordinates of v1
	......
	....
	..
	.
	xn yn zn    -> coordinates of vn


	E    -> no of edges

	a b         -> this means that there is an edge between ath vertex and bth vertex
	....
	...
	..

	S    -> no of surfaces

	e1 e2 e3 ... en     -> surface consists of edge e1,....,en
	....
	...
	..


####Output

* Application generates output in a window which appears after clicking button in gui.

###2D to 3D

###Input

######Provide 2D object in *.txt* format as follows:-######
	N   			 -> no of vertices

	t1.x t2.y t3.z   -> top view projection of v1      |
	f1.x f1.y f1.z   -> front view projection of v1		| ----> first vertex
	s1.x s1.y s1.z   -> side view projection of v1	   |

	t2.x .....
	...
	..
	.

	Te   			  -> no of edges in top view

	a b  			  -> edge between ath vertex and bth vertex in top view
	.....
	....

	Fe   			  -> no of edges in front view

	a b  			  -> edge between ath vertex and bth vertex in front view
	....
	..

	Se   			  -> no of edges in side view

	a b  			  -> edge between ath vertex and bth vertex in side view
	....
	..

###Output

* Application generates output in  *.obj* file (filename of your choice).

#### Format of *.obj* file ####
		v 1 2 3    # a vertex 'v' followed by (x, y, z) coordinates of the point
		v ...
		...

		f 1 3 4    # a face 'f' followed by indices of vertices lying on that plane(sequence of vertex decides the hollowness of the object)
		f ...
		...

###obj viewer

* For Linux   -> 
* For Windows -> Print 3D
* Online      -> **[Online 3D Viewer](https://3dviewer.net/)**

##Authors##

* **[Manish Tanwar](https://github.com/manishtanwar/)**
* **[Abhinash Kumar](https://github.com/sabhi2257)**


