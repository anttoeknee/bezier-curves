## Bezier Curves (Technical Demo / Playground)

### Background / Backstory

This project is my first foray into C++ development, my background as a developer started in 
Visual Basic 6 where I made a rudamentry clone of Space Invaders (sadly I don't have the source
code for this anymore as it was in 2002, so before GitHub or any meaningful VCS).

In 2007 I then progressed into web development, both back-end and front-end at the same time. The tight
feedback loops of front-end development which looked like JavaScript/jQuery and Flash (ActionScript 2/3)
combined with a basic back-end in PHP became the entry point for a career in web development.

Over time, Flash died a death and jQuery started to become under stimulating and frustrating as the common
design patterns employed at the time weren't very scalable. I then turned my focus to back-end web
development exclusively, focusing on software architecture from a scalability and maintenance point of view
leading towards layered architecture and SOLID principles in everyday development practices (Credit to Robert C Martin & Martin Fowler).

I'm now looking to return to UI development, combining design patterns and understanding of developing
larger applications from my back-end developer experience with the nuances of rendering, i.e. Bezier Curves
, the maths behind it (Linear Interpolation, Quadratic and Cubic implementations), collisions detection (Ray Casting)
as a starting point.

This application aims to demonstrate this convergence.

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

