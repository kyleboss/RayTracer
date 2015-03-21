Assignment 2: Ray Tracer

Kyle Boss (cs184-ck)
Declan Jones (cs184-ef)
Jingyi Li (cs184-ec)

Our code runs and compiles on Mac OS X. It requires openCV be installed.

Jingyi Li will submit the code. Kyle Boss & Declan Jones will submit READMEs.

In addition to the required features:
- Support for directional, point and ambient lights
- Phong shading model for spheres and polygons
- Reading and rendering .obj files (with normal interpolation if specified)
- Shadows and reflections
- Translations, scales and rotations (linear transformations)
- Using openCV to save to a .PNG

We have also implemented, for extra credit:
- Anti-aliasing (random/jittered model) 
- Multithreading
- Acceleration with AABB Trees
- Shearing
- Using AABB Boxing with assistance from Utah's Williams Lab: http://www.cs.utah.edu/~awilliam/box/

Input to our ray tracer is a .scene file with each line containing information as specified in the README. For our extra features, "alias" (as a seperate line) turns on anti-aliasing, "thread [# of threads]" turns on multithreading, and "xfh rx ry rz" denotes a shear transformation. AABB Trees are always used so there's no line parsing.
