# 3DViewer
The 3DViewer v1.0 is a modern app written in C and C++. The application provides viewing 3D wireframe models, loaded from .obj files and be viewable on the screen with the ability to rotate, scale and translate.

## Features
- Load a wireframe model from an obj file.
- Translate the model by a given distance in relation to the X, Y, Z axes.

  ![Translation Screecast](./docs/Motion.gif)

- Rotate the model by a given angle relative to its X, Y, Z axes.
- Scale the model by a given value.

  ![Rotation Screecast](./docs/Rotation.gif)

- Customizing the type of projection (parallel and central).
- Setting up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices.
- Choosing the background color.

  ![Default Screeshot](./docs/Default.png)

- Saving settings between program restarts.

  ![Custom Screeshot](./docs/Custom.png)

- Display grid and axes.

  ![Grid Screecast](./docs/Grid_and_axis.gif)

- Saving the captured (rendered) images as bmp and jpeg files.
- Recording small screencasts by a special button - the current custom affine transformation of the loaded object into gif-animation.

## License
Copyright (c). All rights reserved.