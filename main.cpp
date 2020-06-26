#include "objects.h"

TObject* objects[20];
//viewing variables
float th = 0;
float ph = 0;
int gWidth;
int gHeight;
float look[3] = {0,0,-1}; //look vector

//lighting variables
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   15;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
float ambient   =  50;  // Ambient intensity (%)
float diffuse   =  80;  // Diffuse intensity (%)
float specular  =  20;  // Specular intensity (%)
float atn[3] = {1,.10,0};
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light angle
float ylight  =   0;  // Elevation of light

//timing variables
float lastTime;
static int targetFPS = 144;

//key and mouse variables
bool key_buffer[4]; //up, left, down, right
int mouse_pos[2];
bool mouse_visible = true;
bool rotate_light = true;

//game logic variables
float grace = .275; //grace area for target detection

//game logic forward declarations
void fire();
void light_four();

//returns delta, locking to FPS when able.
static float delta_()
{
  float delt = (glutGet(GLUT_ELAPSED_TIME)/1000.0) - lastTime;
  if(delt >= 1.0/(float)targetFPS) {
    lastTime = (glutGet(GLUT_ELAPSED_TIME)/1000.0);
    return delt;
  } else {
    return 0;
  }
}

//Process key buffer; currently not in use
void process_keys(float delta)
{
  if(key_buffer[0]) {
    ph -= 50 * delta;
  }
  if(key_buffer[1]) {
    th -= 50 * delta;
  }
  if(key_buffer[2]) {
    ph += 50 * delta;
  }
  if(key_buffer[3]) {
    th += 50 * delta;
  }
  //wrap rotation variables
  if(ph > 89) ph = 89;
  if(ph < -89) ph = -89;
  if(th > 360) th = 0;
  if(th < 0) th = 360;
}

//Process mouse movement
void process_mouse(float delta)
{
  int dx = mouse_pos[0] - (gWidth/2);
  int dy = mouse_pos[1] - (gHeight/2);
  th += dx * delta;
  ph += dy * delta;
  glutWarpPointer(gWidth/2, gHeight/2);
  //std::cout << mouse_pos[0] << ":" << mouse_pos[1] << std::endl;
}

void track_mouse(int x, int y)
{
  int dx = x - mouse_pos[0];
  int dy = y - mouse_pos[1];
  th += (float)dx*.17;
  ph += (float)dy*.17;
  mouse_pos[0] = x;
  mouse_pos[1] = y;
}

//Run lighting calculations
void runLighting()
{
  //  Translate intensity to color vectors
  float Ambient[]   = {(float)0.01*ambient ,(float)0.01*ambient ,(float)0.01*ambient ,1.0};
  float Diffuse[]   = {(float)0.01*diffuse ,(float)0.01*diffuse ,(float)0.01*diffuse ,1.0};
  float Specular[]  = {(float)0.01*specular,(float)0.01*specular,(float)0.01*specular,1.0};
  //  Light position
  //float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};

  //float Position[] = {2,0,2};
  float* lamp_pos = objects[15]->position_();
  float Position[] = {lamp_pos[0],0,lamp_pos[2]};
  //std::cout << Position[0] << ":" << Position[1] << ":" << Position[2] << std::endl;
  //float Position_1[] = {100,100,100};
  Position[0] = lamp_pos[0] -(1.5*Sin(objects[15]->rotation_()[1]));
  Position[1] = lamp_pos[1] - 4.0;
  Position[2] = lamp_pos[2] -(1.5*Cos(objects[15]->rotation_()[1]));
  //illustrate light
  glPointSize(10);
  glColor3f(1,1,0);
  glBegin(GL_POINTS);
  glVertex3f(Position[0],Position[1],Position[2]);
  glEnd();
  //  Set ambient, diffuse, specular components and position of light 0
  glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
  glLightfv(GL_LIGHT0,GL_POSITION,Position);
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION, atn[0]);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION, atn[1]);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION, atn[2]);
  //  Set ambient, diffuse, specular components and position of light 1
  /*
  glLightfv(GL_LIGHT1,GL_AMBIENT ,Ambient);
  glLightfv(GL_LIGHT1,GL_DIFFUSE ,Diffuse);
  glLightfv(GL_LIGHT1,GL_SPECULAR,Specular);
  glLightfv(GL_LIGHT1,GL_POSITION,Position_1);
  glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION, atn[0]);
  glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION, atn[1]);
  glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION, atn[2]);
  */
}

//glut idle func
void idle()
{
  float delta = delta_();
  if(delta) {
    process_keys(delta);
    //process_mouse(delta);
    if(rotate_light){
      zh += 90.0*delta;
      zh %= 360;
      //move lamp;
      float lamp_rot[3] = {10,(float)zh,0};
      objects[15]->set_rotation(lamp_rot);
    }
    if(mouse_visible){
      glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
    else {
      glutSetCursor(GLUT_CURSOR_NONE);
    }
  }
   glutPostRedisplay();
}

//transform the camera
void transform_camera()
{
  look[0] = Sin(th)*Cos(ph);
  look[1] = -Sin(ph);
  look[2] = -Cos(th)*Cos(ph);
  gluLookAt(0,0,4, look[0],look[1],look[2]+4, 0,1,0);
  glPointSize(10);
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  glVertex3f(look[0],look[1],look[2]+4);
  glEnd();

}

//glut display func
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  transform_camera();
  //gluLookAt(0,0,5, 0,0,0, 0,1,0);
  glPushMatrix();
  //glRotated(ph,1,0,0);
  //glRotated(th,0,1,0);
  runLighting();

  for(int n=0; n<15; n++) {
    objects[n]->draw();
  }
  objects[15]->draw();
  //objects[15]->draw();
  glPopMatrix();
  glutSwapBuffers();
}

//glut reshape func
void reshape(int width,int height)
{
  gWidth = width;
  gHeight = height;
  //set viewport
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  //projection mode
  glMatrixMode (GL_PROJECTION);
  //reset transform
  glLoadIdentity ();
  //set up perspective
  //glOrtho(0, 0, (GLsizei) width, (GLsizei) height, -1, 1);
  float asp = (float)width/height;
  gluPerspective(60,asp,1,128);
  //set back to modelview
  glMatrixMode (GL_MODELVIEW);
  //reset modelview too for good measure
  glLoadIdentity();
}

//OpenGL special key function
void special(int key,int x,int y)
{
  switch(key) {
    case GLUT_KEY_UP:
      key_buffer[0] = 1;
      break;
    case GLUT_KEY_LEFT:
      key_buffer[1] = 1;
      break;
    case GLUT_KEY_DOWN:
      key_buffer[2] = 1;
      break;
    case GLUT_KEY_RIGHT:
      key_buffer[3] = 1;
      break;
    default:
      break;
  }
}
void specialUp(int key, int x, int y)
{
  switch(key) {
    case GLUT_KEY_UP:
      key_buffer[0] = 0;
      break;
    case GLUT_KEY_LEFT:
      key_buffer[1] = 0;
      break;
    case GLUT_KEY_DOWN:
      key_buffer[2] = 0;
      break;
    case GLUT_KEY_RIGHT:
      key_buffer[3] = 0;
      break;
    default:
      break;
  }
}

void mouse(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
  {
    fire();
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 's':
      rotate_light = !rotate_light;
      break;
    case '0':
      th = 0;
      ph = 0;
      break;
    case '1':
      mouse_visible = !mouse_visible;
      break;
    case 27:
      exit(0);
    case 32: //spacebar
      fire();
      break;
    default:
      break;
  }
}

void program_init()
{
  //initialize random
  srand(time(NULL));
  //initialize scene objects
  //targetrack
  objects[0] = new TargetRack(0,0,0, 1,1,1, 0,0,-10); objects[0]->init();
  light_four();
  //walls; target.bmp is a temp for a carnival tent texture. Work on it.
  //floor
  objects[1] = new SurfaceRect(0,0,0, 20,1,25, 5,-3,-4, 1,1,1, (char*)"hay.bmp"); objects[1]->init();
  objects[1]->set_texture_scale(10,12.5);
  //left
  objects[2] = new SurfaceRect(0,-90,-90, 25,1,10, -5,2,-4, 1,1,1, (char*)"cloth.bmp"); objects[2]->init();
  objects[2]->set_texture_scale(2.5,1);
  //right
  objects[3] = new SurfaceRect(0,-90,90, 25,1,10, 15,2,-4, 1,1,1, (char*)"cloth.bmp"); objects[3]->init();
  objects[3]->set_texture_scale(2.5,1);
  //ceiling
  objects[4] = new SurfaceRect(0,0,180, 20,1,25, 5,7,-4, 1,1,1, (char*)"darkwood.bmp"); objects[4]->init();
  objects[4]->set_texture_scale(10,12.5);
  //front wall (from start view)
  objects[5] = new SurfaceRect(90,0,0, 20,1,10, 5,2,-16, 1,1,1, (char*)"cloth.bmp"); objects[5]->init();
  objects[5]->set_texture_scale(2,1);
  //back wall (from start view)
  objects[6] = new SurfaceRect(90,180,0, 20,1,10, 5,2,8.5, 1,1,1, (char*)"cloth.bmp"); objects[6]->init();
  objects[6]->set_texture_scale(2,1);
  //decorative objects
  objects[7] = new Cuboid(0,20,0, 2,2,2, -3.5,-2,-14, 1,1,1, (char*)"crate.bmp"); objects[7]->init();
  objects[8] = new Cuboid(0,30,0, 1,1,1, -3.5,-.5,-14, 1,1,1, (char*)"crate.bmp"); objects[8]->init();
  objects[9] = new Cuboid(0,30,0, 2,2,2,  3,-2,2, 1,1,1, (char*)"crate.bmp"); objects[9]->init();
  objects[10] = new Cuboid(0,-10,0, 1.6,1.6,1.6,  1.0,-2.2,.2, 1,1,1, (char*)"crate.bmp"); objects[10]->init();
  objects[11] = new Cuboid(0,45,0, 1.4,1.4,1.4,  -.7,-2.2,-.1, 1,1,1, (char*)"crate.bmp"); objects[11]->init();
  objects[12] = new Cuboid(0,10,0, 1.9,1.9,1.9,  -3,-2,-.1, 1,1,1, (char*)"crate.bmp"); objects[12]->init();
  objects[13] = new HayBale(0,0,0, 2,2,2, 3.5,-2,-14, 1,1,1); objects[13]->init();
  objects[14] = new Table(0,-45,0, 3,3,3, 11,-2,-11.5); objects[14]->init();
  objects[15] = new Lamp(0,0,0, 1.5,1.5,1.5, 5,7,-3, 1,1,1); objects[15]->init();
}

//game logic: shoot
void fire()
{
  float x = +14 * Sin(th);
  float y = -14 * Sin(ph);
  //std::cout << x << " " << y << std::endl;
  float x_mod = (x+2.25) / 1.5;
  float y_mod = (y-4.2) / -2;
  //std::cout << x_mod << " " << y_mod << std::endl;
  int x_pos = -1;
  int y_pos = -1;
  for(int n=0; n<4; n++) {
    if(n-grace <= x_mod && n+grace >= x_mod) x_pos = n;
    if(n-grace <= y_mod && n+grace >= y_mod) y_pos = n;
  }
  //std::cout << x_pos << " " << y_pos << std::endl;
  if(x_pos != -1 && y_pos != -1) {
    objects[0]->toggle_light_off_at(x_pos, y_pos);
  }
  if(objects[0]->lit_target_count() == 0) {
    light_four();
  }
}
//game logic: light random
void light_four()
{
  bool unique = false;
  int picked_indices[4];
  int x;
  int y;
  //select 4 unique targets
  for(int n=0; n<4; n++) {
    while(!unique) {
      int index = rand()%16;
      //iterate through picked array, assume unique
      unique = true;
      for(int i=0; i<n; i++) {
        if(picked_indices[i] == index) {
          unique = false;
          break;
        }
      }
      x = index/4;
      y = index%4;
      picked_indices[n] = index;
    }
    objects[0]->toggle_light_at(x,y);
    unique = false;
  }
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv); //initialize glut
  //init with rgb, double buffer, depth test
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600,600); //600x600 window
  glutCreateWindow("James Nichols"); //create window
  glutIdleFunc(idle);
  glutDisplayFunc(display); //display function
  glutReshapeFunc(reshape); //reshape function
  glutSpecialFunc(special); //arrow keys, esc
  glutSpecialUpFunc(specialUp);
  glutKeyboardFunc(keyboard); //keyboard controls
  //glutMouseFunc(mouse); //mouse controls; disabled
  //glutPassiveMotionFunc(track_mouse); //mouse controls; disabled
  //face culling/depth test
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  //lighting
  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);
  program_init();
  glutMainLoop();
  return 0;
}
