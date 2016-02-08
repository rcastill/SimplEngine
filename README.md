# SimplEngine

SimplEngine is a minimal graphics engine built on top of SDL2 written in C++11, the objective is to develop a modern interface with some common utilities for game development and similars. Another important goal is to integrate a network system for both usability and testing based on UDP protocol.

## Test

This repo includes a (in-development) mini-game coded with SimplEngine, it is in fact a guide to test engine's usability.

## Build and development environment

This project is being developed in [CLion](https://www.jetbrains.com/clion/ "CLion by JetBrains"), that means that the underlying build method is *cmake*. For building you'll need SDL2, SDL2_image, SDL2_ttf devel and runtime libraries.

***To do:*** *Detail more*

## To do list

- [x] Fix resource disposal bug
- [ ] Remove object capabilities

    *Both items above may imply to partially redesign and improve the resource system*

- [ ] **Network**
- [ ] Document (may be doxygen?)
- [ ] Timer System
- [ ] Complete and improve Position class
