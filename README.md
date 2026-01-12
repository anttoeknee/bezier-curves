## Bezier Curves (Technical Demo / Playground)

### Description

In its current form this application demonstrates my learning journey from implementing simple LERP's, to then
drawing a Quadratic Curve and finally into a basic/crude/limited pen/shape tool.

It also aims to show specific C++ understanding (level of which is yet to be determined!) with separation
of concerns, interfaces/abstractions, usage of smart pointers and moving objects between classes, some light 
(but steadily increasing) usages of RAII principles, specifically in the ScopeWindowClipping class and understanding
of a build system such as CMake in this instance (not an exhaustive list).

Lastly it also demonstrates architectural design towards game/drawing apps development i.e. event handling, update, draw loop.

Disclaimer! It is a WIP and not what I'd call production ready code :sweat_smile: but I'm always looking for constructive feedback
and pointers (apologies for the pun).

### TODO's:

- ~~Replace hard coded geometry data in App.cpp with fed data from JSON demonstrating file I/O (coming soon)~~
- Update all Anchor Points in paths with an offset so they're centred on the line (also coming soon)
- Replace quadratic Bezier's with cubic Bezier's
- Allow resizing (and hence correct scaling) of window and UI
- Abstract SFML library behind shared objects and then substitute SFML with D2D for Windows and Core Graphics for MacOS (Will take some time)
- Introduce a Ray Casting implementation to visualise the drawn shapes in an interactive environment (for fun really, nice to have)

