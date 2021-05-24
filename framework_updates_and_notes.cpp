/*

                                      MINI ENGINE SIDE PROJECT   (by David Prefontaine)
-----------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------

          "BOARD" OF PROJECT IDEAS
-------------------------------------------------
Early on (to play around with the framework):
 -Running game (after motion and camera)
 -Ball bouncing game (after motion and hitboxes + physics)
 -Dungeon exploring game (after motion, hitboxes, camera)

Later on (once getting the framework to a good point and "mastering" it)
 -Platforming game (w/ physics stuff like gravity)
 -Tower Defense (w/ more emphasis on AI)

Dream projects (assuming this ever does go far)
 -Expanded exploring game
 -Faeround
 -Envoys



Side notes:

Later:
 -Keep tutorials 28,30,31,34,36,37,38 for future reference
 -May have a Lua interpreter whenever editable areas are more defined
 -May implement templates for interface rendering
 -May implement svg

For now:
 -Might add template to mechanics code AND add a backend game object queue to loading rooms (have to think more about this)
 -Add adding scaling and offset to visual media (somehow)

 -Will have to play with the current framework more to see how to implement generic




8/28/18
------------
Done (since then):
 -Added timers
 -Added base rooms
 -Added media elements (all based on SDL tutorials)
 -Added change in ticks to room update behavior

To Do:
 -Expand on room behaviors and parameters
      -What if time is not needed?
      -What if room follows "different" maths?
      -What to do if a certain asset or media is not needed at the moment?

Idea for room & viewports:
 -All of them have inherited interface (so then they can all be updated as long as they are in a stack of the interface)
      -Interface includes:
          -Viewport position and size
          -Is active or not
          -Background
          -Other UI stuff (which can be passed as parameters)
          -Buttons and background click event

8/29/18
------------
 -Added comments to room's update behavior

8/30/18
------------
 -Added comments to room's render behavior
 -Added more ideas to managing viewports
 -Added game interface class

10/15/18
------------
 -Set to -std=C++14
 -Added binary and linear searches
 -Added random and other math stuff

10/17/18
------------
 -Code maintenance
 -Set j increments for click event of game interface to whenever coordinate does not evaluate instead, so onward, the button condition does not evaluate the wrong index of the stack
 -Added media bins for game interface
 -Added an integer reference ID to media objects for stack management sake

10/18/18
------------
 -Added listening setting component to game interface, so the game interface can be visible or active, but it can or cannot listen to events
 -Removed active parameter from game interface initiation
 -Added methods to media elements

11/15/18
------------
 -Added orientation, color tint, transparency, and additional constructors to image class
 -Created an empty font library folder
 -Created a primitive shape class

11/19/18
------------
 -Made it through SDL tutorials 27 and 29
 -Created a class for hitboxes

11/20/18
------------
 -Tutorials 30,32,33
 -Created a camera class
 -Created an integer reader class

11/21/18
------------
 -Tutorial 35
 -Created a window class

To do:
 -Figure what to do with both room and window

11/23/18 - 11/29/18
--------------
 -Room made into multiple rooms instead vs one main room
 -Moved some stacks of interface to rooms instead
 -Added more conditions to rooms (i.e. if it uses time or not)
 -Changed the ID variable of objects to element ID to make stack index and indicating integers easier to distinguish
 -Cleared some initiation steps
 -Moved room checker to before the event loop
 -Main timer spike cleared when playing after stop
 -Comparison or sorting step added to media and math elements w/ element ID
 -Bit of cleaning up and rearranging of global variables and enumerations

11/30/18
--------------
 -Added activate/unactivate feature to room (to keep adding/removing media separate from activation)
 -Fixed an issue with initiation procedures (arrays don't have negative indexes you dumbass xp)
 -Added a load room function to pre-game loop steps
 -Moved room enumeration
 -Added instruction comments file

Things to add left:
 -Interface actions and behavior loading
 -Slot for adding game rules

12/1/18
--------------
 -Added comparison method to images and text
 -Sorting media for interfaces

12/2/18
--------------
 -Added active variable to image
 -Added media manager behaviors

To do:
 -Add sorting to media managers
 -Add pixel position to images/text/shapes

Things to add left:
 -Means of adding game rules

12/3/18
--------------
 -Changed closing procedures
 -Modified initiation methods for text, images, and shapes
 -Removed un-needed scopes to behaviors
 -Fixed hung app issue while closing
 -Added wipe behavior to sound
 -Added fullscreen switch and moved constants to window header and code

12/5/18
--------------
 -Changed rooms initialization to pointer becoming array
 -Fixed closing issue
 -Added coordinate variables and behaviors to visual media
 -Tweaked rendering steps and interface scopes
 -Added active variable to camera (to get first active camera in interface)

12/6/18
--------------
 -Removed coordinates and so forth from visual media
 -Created a coordinate class to help w/ rendering
 -Created struct to help w/ rendering a media over and over again
 -Tweaked game interface behaviors to deal w/ bundles

12/7/18
--------------
 -Tweaked delete behaviors to delete based on given element ID
 -Add and remove behaviors for points
 -Added shape behaviors to interface

12/8/18
--------------
 -Added element ID to shape
 -Tweaked media initiation to have blank initiations possible
 -Added missing behaviors for shape
 -Added button class and button bundle
 -Tweaked interface behaviors to comply with button bundle
 -Added behaviors for button bundles

12/9/18
--------------
 -Touch event for room now return an array of int
 -Added comparison for sorting behaviors of interface

Things to do:
 -Create swap method for arraylists
 -Add swap method to sorting behaviors
 -Fixed some comparison methods

12/11/18
--------------
 -Added magnitude function
 -Added print to room event touch (to make interfaces easier to keep track of)
 -Print method included in room event behavior to make sure interfaces are working as intended
 -Changed room from a class to struct to make modifying interfaces easier
 -Added set viewport to rendering
 -Tweaked/ added an actual viewport to make rendering interface viewports less painful
 -Tweaked cameras a little

12/12/18
--------------
 -Added camera updating (and bounds when moved)
 -Tweaked interface initiation for camera and full interface bounds
 -Added additional constructor for interface
 -Removed offset and element ID from camera
 -Media rendering tweaked to be based around camera
 -Tweaked test fill protocols for room rendering

12/12/18
--------------
 -Added move protocol to button bundle
 -Added hitbox checker to game interface
 -Readded hitboxes and managers to game interface
 -Added event cluster for multiple hitbox reading

12/15/18
--------------
 -Hitbox reading added

12/16/18
--------------
 -Added compare to behaviors for event rectangles and circles
 -Added event cluster manager to game interface
 -Tweaked game interface behaviors to find elements by index instead of searching element ID
 -Added an additional search method to game interface behaviors

1/18/19
--------------
 -Added is_active bool feature to sound class
 -Fixed naming issue when it came to object initiation
 -Modified image loading for color key to work
 -Modified parameters for rendering media clusters

1/19/19
--------------
 -Added parameters to changing button positions (so now buttons scroll in a viewport)
 -vp variables in game interface class is now used as an offset for camera (so images and so forth are positioned relative to their respective viewport)

1/20/19
--------------
 -Added move point functions to visual media (images, shapes, text)
 -Tweaked camera so now upper bounds of rendering in an interface works properly
 -Removed sorting behaviors from interface (since it does not have much purpose if accessing is done by element ID anyways)
 -Tweaked prints during steps
 -Added start of framework directions

 1/21/19
-------------
 -Moved variable scopes in main.cpp
 -Added string constant for window name (to make it easier to edit)
 -Tweaked camera values
 -Printing inactive for now
 -Separated key input queue conditions
 -Added room parameter to deactivating room (in case specific procedures for rooms have to be done)
 -Moved SDL libraries to a closer directory to the project

  1/22/19
-------------
 -Added a generic class to mechanics (it really doesn't do anything)
 -Added load text method to game interface (forgot to do so earlier xp)
 -Added scale parameter to loading text to make text bigger or smaller

 */
