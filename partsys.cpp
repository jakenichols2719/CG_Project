#include "partsys.h"

Particle::Particle()
{
   x = 0; y = 0; z = 0;
  dx = 0;dy = 0;dz = 0;
  r = 1; g = 1; b = 1;
  active_time = 5;
  size = 5;
}

//parameterized constructor
Particle::Particle(float _x, float _y, float _z,
                   float _dx, float _dy, float _dz,
                   float _r, float _g, float _b,
                   float _size,float _at)
{
  x = _x; y = _y; z = _z;
  dx = _dx; dy = _dy; dz = _dz;
  r = _r; g = _g; b = _b;
  active_time = _at;
  size = _size;
}

/*
 * Processes the particle for the given delta
 * Returns false if the active time of the particle is up
*/
bool Particle::process(float delta)
{
  x += dx * delta;
  y += dy * delta;
  z += dz * delta;
  glPointSize(size);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
  //std::cout << x << " " << y << " " << z << std::endl;
  glVertex3f(x,y,z);
  glEnd();
  active_time -= delta;
  if(active_time <= 0){
    return false;
  }
  return true;
}

/*
 * Adds a particle to the system.
*/
void PartSys::newParticle(float _x, float _y, float _z,
                          float _dx, float _dy, float _dz,
                          float _r, float _g, float _b,
                          float size, float _at)
{
  active_parts[next_index] = new Particle(_x,_y,_z, _dx,_dy,_dz, _r,_g,_b, size,_at);
  next_index++;
  next_index %= 80;
}

void PartSys::process(float delta)
{
  for(int n=0; n<80; n++) {
    if(active_parts[n]) {
      bool check = active_parts[n]->process(delta);
      if(!check) {
        delete active_parts[n];
        active_parts[n] = NULL;
      }
    }
  }
}

static float rand_dir() {
  int sign = (rand()%3)-1;
  float dir = (float)((rand()%600)*sign)/100.0;
  return dir;
}

static float rand_col() {
  //float col = (float)((rand()%50)+26)/100.0;
  float col = rand()%2;
  if(col == 0) col += .1;
  if(col == 1) col -= .1;
  return col;
}

void PartSys::ef_boom(float _x, float _y, float _z) {
  for(int n=0; n<20; n++) {
    float dx = rand_dir();
    float dy = rand_dir();
    float dz = rand_dir();
    float at = (float)(rand()%50)/100.0;
    newParticle(_x, _y, _z, dx,dy,dz, rand_col(),rand_col(),rand_col(), (rand()%5)+3,at);
  }
}
