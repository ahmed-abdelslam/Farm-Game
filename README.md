------------------------------------The Farm
Project------------------------------------

* * * * *

FIRST OF ALL; COPY SDL Library FOLDER AND PASTE IT TO C: TO RUN THE
PROJECT WITHOUT ERRORS PROBABLY YOU'LL NEED TO COPY ALL DLL FILES AND
PASTE IT TO C:\Windows\System32
\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

THIS IS A SUMMARY OF HOW THE CODES WORK, IF YOU WANT A DETAILED INFORMATION,
============================================================================

EVERY SINGLE LINE HAS A COMMENT THAT EXPLAIN IT\#

######################################## 

The project partitioned into 9 classes
======================================

######################################## 

1- trainingGame Class:

implements the following functions :

a- init function, which is responsible for intialize the sdl library,
create the window of the game with fixed width and height, create the
render of the window control the running or exiting from the game,
initialize the following objects: stage(setting to the first stage),
course(with argument: path of background image), Head(the head of the
wagon), Farmer(farmer with no crop), FarmerWithCrop, obstacle,
lose(notification of loss), win(notification of win)

b- handleEvents function, which is responsible for handling key pressing
w to move to the north, s move to the south, d move to the east, a move
to the west, r to restart the game (after a collision), c to continue to
the next stage(when reach the maximum points of the current stage)

c- randomXposition & randomYposition function, to generate random values
of x and y positions of the farmer considering the width and height of
the window and the places of the obstacles

d- update function, which is responsible for showing the carts based on
the length and calling the simulator function from object carts to let
the carts simulate the movment of the head of wagon, calling update
function from object course to run the timer of the game, set the farmer
to the default position, moving the wagon in the four directions,
calling statusOfHead function to store detailed information about the
head(this will be used later to help carts to simulate the head), call
collisionWithFarmer function to generate a new farmer when the head hit
the current farmer, check if there is a collision between the head one
of the obsatcles or any cart and stop the game , call restart function
to restart the game if there is a request, call moveToNextStage if there
is a request to continue to the next stage,\
 call stopTheGame function when time is over, call reachTheScore
function when the user reach the maximum points of the current stage

e- collisionWithFarmer function, responsible for choosing randomly
between normal farmer and farmer with crop with increasing the carts of
the wagon by one or two based on what's the type of the farmer was
hitted, increase the displayed points on the screen and the length also,
call calculateThePositionOfTheNewCart function to do some calculations
to let the new cart simulate the head with the appropriate location

f- stopTheGame function to stop the whole game and allow the user to
press key r to restart

g- reachTheScore function to stop the whole game and allow the user to
press key c to move to the next stage

h- statusOfHead function to receive all the information about the head
for ex. current x and y position then store these information into a 2d
array, this array will help the carts to simulate the movemtents of the
head

i- calculateThePositionOfTheNewCart function, to calculate the
appropriate location of the new cart by equation "row + (-35 \* (TailNO
+ 1))" which means subtracting from the current row in the 2d array by
35 multiply the number of the cart and add one , the idea is to get the
old information of the head and let the new cart begin from there,
number 35 is the most approprite number to let the cart behind the
existing carts and adding one because the number of the first cart will
be 0

j- restart function responsible for hide the carts, let the user press
keys of directions again, hide the loss image, call reset function from
course object to reset the information in the inforamtion bar, prevent
the user from pressing key r

k- moveToNextStage responsible for hide the carts, let the user press
keys of directions again, hide the win image, call reset function from
course object to reset the information in the inforamtion bar, prevent
the user from pressing key c, call setStage function from stage object
to setup the next stage

l- render function responsible for rendering every element shown on the
screen

m- clean function to delete objects, desrtory the window, the renderer
and quit from sdl library

2- trainingCourse Class: responsible for creating a texture to the
background and to the text of the information bar , run a timer
function, update the information on the screen, rendering the texture of
the background and text

3- Cart Class : responsible for creating a texture to the cart, let the
carts simulate the movements of the head by changing the values of x
position and y position and so on, the values used in changing it from
storageOfMovement array which contains every single movement of the
head, rendering the texture of the carts

4- Notification Class: responsible for creating a texture to lose image
or win image and rendering the texture

5- Obstacle Class : responsible for creating a texture to the obstacles,
checking if there is a collision between the head of the wagon and one
of the obstacles or not, rendering the texture of the obstacles

6- Passenger Class : responsible for creating a texture to the farmer,
checking if there is a collision between the head of the wagon and the
farmer or not, change the location of the farmer after the collision
with the previous farmer, rendering the farmer

7- Stages Class : responsible for changing the information in the bar at
the beginning of the stage and increasing the number of obstacles based
on the current stage there are 3 stages

8- TextureManager Class : responsible for loading the images that will
be shown on the screen and the text using sdl methods

9- Wagon Class : responsible for creating a texture to the head of the
wagon, checking if there is a collision between the head of the wagon
and one of the carts or not, moving the head in the four directions,
sending all information about the positions of the head all over the
time, rendering the texture of the head
