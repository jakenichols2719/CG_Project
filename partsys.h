#pragma once
#include "CSCIx229.h"
#include <iostream>

enum Map {MAP_FLAKE,MAP_CONFET};

/*
 * Particle class
 * These are just going to be drawn points for right now
*/
class Particle {
private:
  //GLubyte map_flake[8] = {0x48,0xd5,0x4a,0xdb,0xba,0xa9,0x4a,0x64};
  float  x, y, z; //position
  float dx,dy,dz; //change in position with time
  float r,g,b; //color
  float active_time; //time particle is active on screen
  int size; //particle size
  GLubyte* map;
public:
  Particle();
  Particle(float _x, float _y, float _z,
           float _dx, float _dy, float _dz,
           float _r, float _g, float _b,
           float size, float _at, GLubyte* map);
  bool process(float delta);
};

/*
 * Particle system
 * Manages particles and can call effects
*/
class PartSys
{
private:
  Particle* active_parts[80];
  GLubyte* maps[2];
  int next_index = 0;
public:
  void initMaps();
  void newParticle(float _x, float _y, float _z,
                   float _dx, float _dy, float _dz,
                   float _r, float _g, float _b,
                   float _size,float _at, Map bmp);
  void process(float delta);
  //and some predefined particle effects
  void ef_confet(float _x, float _y, float _z);
};
