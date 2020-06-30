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
                   float _size,float _at, GLubyte* _map)
{
  x = _x; y = _y; z = _z;
  dx = _dx; dy = _dy; dz = _dz;
  r = _r; g = _g; b = _b;
  active_time = _at;
  size = _size;
  map = _map;
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
  glPushMatrix();
  glColor3f(r,g,b);
  glRasterPos3f(x,y,z);
  glBitmap(8,8, 0,0, 0,0, map);
  glPopMatrix();
  active_time -= delta;
  if(active_time <= 0){
    return false;
  }
  return true;
}


/*
 * Initializes bitmaps into array
*/
void PartSys::initMaps() {
  maps[0] = new GLubyte[8] {0x48,0xd5,0x4a,0xdb,0xba,0xa9,0x4a,0x64}; //flake
  maps[1] = new GLubyte[8] {0x3c,0x7e,0xff,0xff,0xff,0xff,0x7e,0x3c};
}

/*
 * Adds a particle to the system.
*/
void PartSys::newParticle(float _x, float _y, float _z,
                          float _dx, float _dy, float _dz,
                          float _r, float _g, float _b,
                          float size, float _at, Map bmp)
{
  active_parts[next_index] = new Particle(_x,_y,_z, _dx,_dy,_dz, _r,_g,_b, size,_at, maps[bmp]);
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

/*
static float rand_dir() {
  int sign = (rand()%3)-1;
  float udir = (float)(rand()%200)+101.0;
  float dir = (udir*sign)/100.0;
  return dir;
}
*/

static float rand_col() {
  //float col = (float)((rand()%50)+26)/100.0;
  float col = rand()%2;
  if(col == 0) col += .1;
  if(col == 1) col -= .1;
  return col;
}

void PartSys::ef_confet(float _x, float _y, float _z) {
  float r=rand_col(), g=rand_col(), b=rand_col();
  for(int th = 0; th<360; th+=45) {
    float dx = Cos(th)*3;
    float dy = Sin(th)*3;
    float dz = 0; //in case I want to make an angle thing later
    float at = .5;
    newParticle(_x,_y,_z, dx,dy,dz, r,g,b, 5,at,MAP_CONFET);
  }
}
