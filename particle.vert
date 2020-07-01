// Point particles
// derived from advanced ex20

uniform float time; //Time (total) currently
attribute float End; //Time (total) that the particle stops
attribute float Start; //Time (total) that the particle started
attribute vec3 Vel; //Velocity

void main(void)
{
  //position
  vec4 vert = gl_Vertex;
  //remaining particle time
  float end_t = End - time;
  //current particle time
  float t = time-Start;

  // set color to zero when inactive and move away
  if(end_t<0.0) {
    gl_FrontColor = vec4(0,0,0,0);
    vert = vec4 (10,20,-10,1);
  }
  else
  {
    vert = gl_Vertex;
    // Get particle color
    gl_FrontColor = gl_Color;
    // trajectory
    vert += t*vec4(Vel,0);
    // Gravity?
    vert.y -= 9.81 * t * t;
  }

  //transform location
  gl_Position = gl_ModelViewProjectionMatrix*vert;
}
