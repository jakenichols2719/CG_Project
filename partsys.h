#include "CSCIx229.h"
#include <iostream>

/*
 * Particle class
 * These are just going to be drawn points for right now
*/
class Particle {
private:
  float  x, y, z; //position
  float dx,dy,dz; //change in position with time
  float r,g,b; //color
  float active_time; //time particle is active on screen
  int size; //particle size
public:
  Particle();
  Particle(float _x, float _y, float _z,
           float _dx, float _dy, float _dz,
           float _r, float _g, float _b,
           float size, float _at);
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
  int next_index = 0;
public:
  void newParticle(float _x, float _y, float _z,
                   float _dx, float _dy, float _dz,
                   float _r, float _g, float _b,
                   float _size,float _at);
  void process(float delta);
  //and some predefined particle effects
  void ef_boom(float _x, float _y, float _z);
};
