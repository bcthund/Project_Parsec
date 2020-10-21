# Project_Parsec
This is a personal project with the goal of being a general purpose game engine. I created this just as a way of better understanding programming in C++ and how to program with OpenGL. It has only ever been tested on an Nvidia graphics card and likely wont work on ATI due to differences in shader programming.<br>
<br>
The project is written in C++ in the Eclipse IDE. You should be able to go into the Debug folder and use: ```make clean && make all``` which should produce the binary ```Project_Parsec``` which is the current name of this project.<br>
<br>
# History
See the [History](HISTORY.md) file for the complete history of this project.<br>
<br>
# Current Status (2020-10-18)
The world now uses multiple noise layers that load and unload as needed as you move around. The system implements brownian fractal noise (simplex), perlin, ridged perlin, billow and voronoi which can all be mixed as desired and modified useing a list of functions that can be added and then executed in the order they are given. These functions include things like remapping the noise range, scaling, power, clamping values, fading and more. The noise layers also have a mode for how they are applied such as the default add mode where noise is simply added together, but there is also multiply, divide, subtract, and modulus which can allow some creative applications of the noise layers.<br>
The terrain is currently textured with 3D textures which doesn't allow mipmapping easily so it is currently disabled. 2D Array textures are going to be tested as a replacement for automatic mipmapping. Texturing is based on 3 items; the actual altitude, a moisture noise layer, and an altitude offset noise layer. These layers are combined together with 5 3D textures that each have 6 layers for a total of 30 different textures for the terrain, although some areas use the same texture. The extreme ends of the moisture make up desert and tropical types. No special texturing it set up for underwater yet but would just be an additional 3D texture. Slope also does not affect texturing yet but also will be a simple additional 3D texture.<br>
<img src="./screens/2020-10-18/Screenshot_20201018_143530.png" alt="High Altitude" width="500"/><br>
*Terrain from up high at maximum view distance*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_143735.png" alt="Low Altitude" width="500"/><br>
*Terrain from down low at approximate player height showing trees*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_143753.png" alt="Tree Grid" width="500"/><br>
*Trees are currently spawned on a grid, staggering will be implemented using a random seed*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_143921.png" alt="Water Cliff" width="500"/><br>
*Underwater is tuned to have dropoffs and then flatten back out*<br>
<br>
<br>
The GUI has also been completely rewritten using a much more complex parent-child format that allows all objects to be positioned relative to other objects. This allows much more complex and dynamic GUIs to be created. It also includes many common GUI elements such as text boxes, buttons with multiple modes, sliders, fields, tooltips, color swatches, line drawing, pie charts, combo boxes, radio/check boxes, scrolling windows and more.<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144236.png" alt="GUI - Check, text, sliders" width="500"/><br>
*Window showing checkboxes, text boxes, and sliders*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144303.png" alt="GUI - Text Area" width="500"/><br>
*Editable text area, currently not in edit mode*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144318.png" alt="GUI - Edit Text" width="500"/><br>
*Editable text area in edit mode*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144336.png" alt="GUI - Swatches" width="500"/><br>
*Color swatches allow easy color manipulation*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144348.png" alt="GUI - Icons" width="500"/><br>
*Icons which are just a special form of button*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144404.png" alt="GUI - Stipple" width="500"/><br>
*Stipple patterns can be added to window backgrounds*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144426.png" alt="GUI - Combo Box" width="500"/><br>
*Combo box allows a list of items to be created with complex data attached*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144447.png" alt="GUI - Pie Chart" width="500"/><br>
*Pie Charts which can automatically fill unspecified area and show legend with wedge highlighting*<br>
<br>
<img src="./screens/2020-10-18/Screenshot_20201018_144515.png" alt="GUI - Skill Tree Example" width="500"/><br>
*Example skill tree created with just buttons and internal logic*<br>
<br>
<br>
There are some current flaws in the code however and some incomplete classes tied to the current world. Texturing with 3D textures is using a modified binary file that is incomplete and 3D textures can currently only be used with terrain. The terrain textures are alos all loaded through the system textures, there is no 'tileset' loader yet. Trees are drawn by loading a single tree texture int o the system as well as the old sprite system no longer loads textures since trees are added dynamically through noise. A tree tileset needs to be created as well as a flora tileset which will likely be loaded through the same system instead of the old incomplete particle system.<br>
<br>
The GUI uses a special array of enable pointers that can be set to point to internal states or external objects. This is how the example skill tree works, however the system currently results in a massive amount of memory leaks from the pointers not being handled properly. The system needs to be redesigned but is fairly complex to do so and keep the same functionality and therefore might be abandoned. This currently causes a segfault or invalid free every time the game is exited but that is all.<br>
Currently the world is being stored in an unordered map which became an issue when trying to use distance sorting. This was an early mistake and one solution may be to create a separate ordered array of pointers to the maps.<br>
<br>
# Update (2020-10-19)
3D objects have been added into the loader for the map. These are files labeled by their chunk coordinates which therefore requires the chunk size to remain the same. In the end this shouldn't be an issue as the chunk size shouldn't change anyway. Bounding Volumes were fixed so they draw in the correct locations and detect in the correct locations. The sample particle system showing the cabin on fire with smoke has been adjusted to be on top of the cabin loaded by the binary file but currently particles are manually placed.<br>
<img src="./screens/2020-10-19/Screenshot_20201019_231502.png" alt="O3D - Large Castle" width="500"/><br>
*Distant Castle on the Shore*<br>
<br>
<img src="./screens/2020-10-19/Screenshot_20201019_232151.png" alt="O3D - Cabin Up Close" width="500"/><br>
*Small Cabin in the Forest*<br>
<br>
<img src="./screens/2020-10-19/Screenshot_20201020_000034.png" alt="O3D - Bounding Volume Detection Small" width="500"/><br>
*Bounding Volume Detection with Ray on Small Object*<br>
<br>
<img src="./screens/2020-10-19/Screenshot_20201020_000123.png" alt="O3D - Bounding Volume Detection Large" width="500"/><br>
*Bounding Volume Detection on Large Object*<br>
<br>
<img src="./screens/2020-10-19/Screenshot_20201020_000727.png" alt="O3D - Bounding Volume Cylinder" width="500"/><br>
*Bounding Volume Detection with Cylinder*<br>
<br>
<img src="./screens/2020-10-19/Screenshot_20201020_000803.png" alt="O3D - Bounding Volume Sphere" width="500"/><br>
*Bounding Volume Detection with Sphere*<br>
<br>
<img src="./screens/2020-10-19/Screenshot_20201020_002829.png" alt="O3D - Particle Example" width="500"/><br>
*Example Particle System showing Fire and Smoke*<br>
# Update (2020-10-21)
Trees have randomization applied to their size and position although some trees seem to be far too close together still. However the following screenshot shows a very high density forest and looks pretty good considering all trees use the same texture at the moment.<br>
<img src="./screens/2020-10-21/Screenshot_20201021_003458.png" alt="Tree Randomization" width="500"/><br>
*High Density Forest with Random Size and Position*<br>












