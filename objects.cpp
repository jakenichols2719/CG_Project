#include "objects.h"

TObject::TObject()
{
  //but there was nothing there...
}
TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz)
{
  rot[0] = rx; rot[1] = ry; rot[2] = rz;
  sca[0] = sx; sca[1] = sy; sca[2] = sz;
  pos[0] = px; pos[1] = py; pos[2] = pz;
}
TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz,
                 float c0, float c1, float c2)
{
  rot[0] = rx; rot[1] = ry; rot[2] = rz;
  sca[0] = sx; sca[1] = sy; sca[2] = sz;
  pos[0] = px; pos[1] = py; pos[2] = pz;
  col[0] = c0; col[1] = c1; col[2] = c2;
}
TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz,
                 float c0, float c1, float c2,
                 char* file)
{
  rot[0] = rx; rot[1] = ry; rot[2] = rz;
  sca[0] = sx; sca[1] = sy; sca[2] = sz;
  pos[0] = px; pos[1] = py; pos[2] = pz;
  col[0] = c0; col[1] = c1; col[2] = c2;
  hasTexture = true;
  texture = LoadTexBMP(file);
}

TObject::~TObject()
{
  //irresponsible destructor definition
  //can override if an object needs it
}

int TObject::apply_transform()
{
  //apply texture
  if(hasTexture) {
    glBindTexture(GL_TEXTURE_2D, texture);
  }
  //translate
  glTranslatef(pos[0], pos[1], pos[2]);
  //scale
  //glScalef(sca[0],sca[1],sca[2]);
  //rotate
  glRotatef(rot[2],0,0,1);
  glRotatef(rot[1],0,1,0);
  glRotatef(rot[0],1,0,0);
  glScalef(sca[0],sca[1],sca[2]);
  return 0;
}

void TObject::init()
{
  std::cout << "Didn't implement init for this shape" << std::endl;
}

void TObject::draw()
{
  std::cout << "Didn't implement draw for this shape" << std::endl;
}

void TObject::toggle_light()
{
  std::cout << "toggle light not implemented for this object." << std::endl;
}
void TObject::toggle_light_off()
{
  std::cout << "toggle light off not implemented for this object." << std::endl;
}
void TObject::toggle_light_at(int x, int y)
{
  std::cout << "toggle light at not implemented for this object." << std::endl;
}
void TObject::toggle_light_off_at(int x, int y)
{
  std::cout << "toggle light off at not implemented for this object." << std::endl;
}
int TObject::lit_target_count()
{
  std::cout << "Lit target count not implemented for this object" << std::endl;
  return 0;
}

//===CUBOID===
void Cuboid::init()
{
  draw_list = glGenLists(1);
  glNewList(draw_list,GL_COMPILE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glNormal3f( 0, 0, .5);
    glTexCoord2f(0.0,     0.0); glVertex3f(-.5,-.5, .5);
    glTexCoord2f(tex_sca_x, 0.0); glVertex3f(+.5,-.5, .5);
    glTexCoord2f(tex_sca_x, tex_sca_y); glVertex3f(+.5,+.5, .5);
    glTexCoord2f(0.0,     tex_sca_y); glVertex3f(-.5,+.5, .5);
    //  Back
    glNormal3f( 0, 0,-.5);
    glTexCoord2f(0.0,     0.0); glVertex3f(+.5,-.5,-.5);
    glTexCoord2f(tex_sca_x, 0.0); glVertex3f(-.5,-.5,-.5);
    glTexCoord2f(tex_sca_x, tex_sca_y); glVertex3f(-.5,+.5,-.5);
    glTexCoord2f(0.0,     tex_sca_y); glVertex3f(+.5,+.5,-.5);
    //  Right
    glNormal3f(+.5, 0, 0);
    glTexCoord2f(0.0,     0.0); glVertex3f(+.5,-.5,+.5);
    glTexCoord2f(tex_sca_x,     0.0); glVertex3f(+.5,-.5,-.5);
    glTexCoord2f(tex_sca_x, tex_sca_y); glVertex3f(+.5,+.5,-.5);
    glTexCoord2f(0.0,     tex_sca_y); glVertex3f(+.5,+.5,+.5);
    //  Left
    glNormal3f(-.5, 0, 0);
    glTexCoord2f(0.0,     0.0); glVertex3f(-.5,-.5,-.5);
    glTexCoord2f(tex_sca_x,     0.0); glVertex3f(-.5,-.5,+.5);
    glTexCoord2f(tex_sca_x, tex_sca_y); glVertex3f(-.5,+.5,+.5);
    glTexCoord2f(0.0,     tex_sca_y); glVertex3f(-.5,+.5,-.5);
    //  Top
    glNormal3f( 0,+.5, 0);
    glTexCoord2f(0.0,     0.0); glVertex3f(-.5,+.5,+.5);
    glTexCoord2f(tex_sca_x,     0.0); glVertex3f(+.5,+.5,+.5);
    glTexCoord2f(tex_sca_x, tex_sca_y); glVertex3f(+.5,+.5,-.5);
    glTexCoord2f(0.0,     tex_sca_y); glVertex3f(-.5,+.5,-.5);
    //  Bottom
    glNormal3f( 0,-.5, 0);
    glTexCoord2f(0.0,     0.0); glVertex3f(-.5,-.5,-.5);
    glTexCoord2f(tex_sca_x,     0.0); glVertex3f(+.5,-.5,-.5);
    glTexCoord2f(tex_sca_x, tex_sca_y); glVertex3f(+.5,-.5,+.5);
    glTexCoord2f(0.0,     tex_sca_y); glVertex3f(-.5,-.5,+.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void Cuboid::draw()
{
  glPushMatrix();
  apply_transform();
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
  //draw with texture
  if(hasTexture) {
    glCallList(draw_list);
  }
  //draw without texture
  else {
    glBegin(GL_QUADS);
      glColor3f(col[0],col[1],col[2]);
      glNormal3f( 0, 0, .5);
      glVertex3f(-.5,-.5, .5);
      glVertex3f(+.5,-.5, .5);
      glVertex3f(+.5,+.5, .5);
      glVertex3f(-.5,+.5, .5);
      //  Back
      glNormal3f( 0, 0,-.5);
      glVertex3f(+.5,-.5,-.5);
      glVertex3f(-.5,-.5,-.5);
      glVertex3f(-.5,+.5,-.5);
      glVertex3f(+.5,+.5,-.5);
      //  Right
      glNormal3f(+.5, 0, 0);
      glVertex3f(+.5,-.5,+.5);
      glVertex3f(+.5,-.5,-.5);
      glVertex3f(+.5,+.5,-.5);
      glVertex3f(+.5,+.5,+.5);
      //  Left
      glNormal3f(-.5, 0, 0);
      glVertex3f(-.5,-.5,-.5);
      glVertex3f(-.5,-.5,+.5);
      glVertex3f(-.5,+.5,+.5);
      glVertex3f(-.5,+.5,-.5);
      //  Top
      glNormal3f( 0,+.5, 0);
      glVertex3f(-.5,+.5,+.5);
      glVertex3f(+.5,+.5,+.5);
      glVertex3f(+.5,+.5,-.5);
      glVertex3f(-.5,+.5,-.5);
      //  Bottom
      glNormal3f( 0,-.5, 0);
      glVertex3f(-.5,-.5,-.5);
      glVertex3f(+.5,-.5,-.5);
      glVertex3f(+.5,-.5,+.5);
      glVertex3f(-.5,-.5,+.5);
    glEnd();
  }
  glPopMatrix();
}

//===RECTANGLE===
void SurfaceRect::init()
{
  draw_list = glGenLists(1);
  glNewList(draw_list, GL_COMPILE);
  //enable textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glEnable(GL_TEXTURE_2D);
  //enable lighting materials
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
  glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0,    0.0); glVertex3f(-.5,0,.5);
    glTexCoord2f(tex_sca_x,0.0); glVertex3f(.5,0,.5);
    glTexCoord2f(tex_sca_x,tex_sca_y); glVertex3f(.5,0,-.5);
    glTexCoord2f(0.0,    tex_sca_y); glVertex3f(-.5,0,-.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void SurfaceRect::draw()
{
  glPushMatrix();
  apply_transform();
  //draw with texture
  if(hasTexture) {
    glCallList(draw_list);
  }
  //draw without texture
  else {
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    //draw
    glBegin(GL_QUADS);
      glNormal3f(0,1,0);
      glVertex3f(-.5,0,.5);
      glVertex3f(.5,0,.5);
      glVertex3f(.5,0,-.5);
      glVertex3f(-.5,0,-.5);
    glEnd();
  }
  glPopMatrix();
}

//===CURVEDRECT===
void CurvedRect::init()
{
  draw_list = glGenLists(1);
  glNewList(draw_list,GL_COMPILE);
    //enable textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glBegin(GL_QUAD_STRIP);
      //first vertices
      glNormal3f(0,1,0);
      glTexCoord2f(tex_sca_x,0.0); glVertex3f(.5,0,-.5);
      glTexCoord2f(0.0,      0.0); glVertex3f(-.5,0,-.5);
      //halfway
      glTexCoord2f(tex_sca_x,tex_sca_y/2); glVertex3f(.5,0,0);
      glTexCoord2f(0.0,      tex_sca_y/2); glVertex3f(-.5,0,0);
      //curved part
      for(int ph=0; ph<90; ph+=10){
        float dist = (float)ph/180.0;
        float height = (-Cos(ph+180.0)*2)-2;
        float ty = (tex_sca_y/2)+dist; // y texture for these vertices
        glTexCoord2f(tex_sca_x, ty); glVertex3f(.5,height,dist);
        glTexCoord2f(0.0      , ty); glVertex3f(-.5,height,dist);
      }
    glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void CurvedRect::draw()
{
  glPushMatrix();
  apply_transform();
  glCallList(draw_list);
  glPopMatrix();
}


//===CIRCLE===
void Circle::init()
{
  draw_list = glGenLists(1);
  glNewList(draw_list, GL_COMPILE);
  //enable lighting materials
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glColor3f(1,1,1);
  //draw
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUAD_STRIP);
  for(int th = 0; th <= 360; th+=10) {
    int texth = th%90;
    float t0 = (float)(texth+5)/90;
    float t1 = (float)(texth-5)/90;
    glNormal3f(0,1,0);
    //top points
    glTexCoord2f(0,1); glVertex3f(0,0,0);
    glTexCoord2f(t1,1); glVertex3f(0,0,0);
    glTexCoord2f(t0,0); glVertex3f(-Sin(th+5),0,Cos(th+5));
    glTexCoord2f(t1,0); glVertex3f(-Sin(th-5),0,Cos(th-5));
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void Circle::draw()
{
  glPushMatrix();
  apply_transform();
  if(hasTexture) {
    glCallList(draw_list);
  }
  else {
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glColor3f(col[0], col[1], col[2]);
    //draw
    glBegin(GL_QUADS);
    for(int th = 0; th < 360; th+=10) {
      glNormal3f(0,1,0);
      glVertex3f(0,0,0);
      glVertex3f(-Sin(th+5),0,Cos(th+5));
      glVertex3f(-Sin(th-5),0,Cos(th-5));
      glVertex3f(0,0,0);
    }
    glEnd();
  }
  glPopMatrix();
}

//===CONE===
void Cone::init()
{
  base.init();
  draw_list = glGenLists(1);
  glNewList(draw_list, GL_COMPILE);
  //enable lighting materials
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glColor3f(col[0], col[1], col[2]);
  //draw
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  for(int th = 0; th < 360; th+=10) {
    float t0 = th/180;
    float t1 = (th+10)/180;
    glNormal3f(-Sin(th),1,Cos(th)); glTexCoord2f(0,1); glVertex3f(0,.5,0);
    glNormal3f(-Sin(th+5),1,Cos(th+5)); glTexCoord2f(t0,0); glVertex3f(-Sin(th+5),-.5,Cos(th+5));
    glNormal3f(-Sin(th-5),1,Cos(th-5)); glTexCoord2f(t1,0); glVertex3f(-Sin(th-5),-.5,Cos(th-5));
    glNormal3f(-Sin(th),1,Cos(th)); glTexCoord2f(1,1); glVertex3f(0,.5,0);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void Cone::draw()
{
  glPushMatrix();
  apply_transform();
  if(hasTexture) {
    glCallList(draw_list);
  }
  else {
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glColor3f(col[0], col[1], col[2]);
    //draw
    glBegin(GL_QUADS);
    for(int th = 0; th < 360; th+=10) {
      glNormal3f(-Sin(th),1,Cos(th)); glVertex3f(0,.5,0);
      glNormal3f(-Sin(th+5),1,Cos(th+5)); glVertex3f(-Sin(th+5),-.5,Cos(th+5));
      glNormal3f(-Sin(th-5),1,Cos(th-5)); glVertex3f(-Sin(th-5),-.5,Cos(th-5));
      glNormal3f(-Sin(th),1,Cos(th)); glVertex3f(0,.5,0);
    }
    glEnd();
  }
  base.draw();
  glPopMatrix();
}

//===SPHERE===
void Sphere::init()
{
  draw_list = glGenLists(1);
  glNewList(draw_list, GL_COMPILE);
  //enable lighting and tex materials
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glScalef(.5,.5,.5); //I don't feel like typing .5 a bunch
  //iterate rotation around y axis
  glEnable(GL_TEXTURE_2D);
  for(int th=0; th<360; th+=10) {
    //draw quad strip
    glBegin(GL_QUAD_STRIP);
    for(int ph = 0; ph<=180; ph += 10) {
      //find left/right tex coords for x
      float tx_r = ((float)th+5)/180.0, tx_l = ((float)th-5)/180.0;
      //tex coord in y direction for both vertices
      float ty = (float)ph/180.0;
      //find right and left points and draw
      float right[3] = {Sin(th+5)*Sin(ph),Cos(ph),Sin(ph)*Cos(th+5)};
      float left[3] = {Sin(th-5)*Sin(ph),Cos(ph),Sin(ph)*Cos(th-5)};
      glTexCoord2f(tx_r, ty); glNormal3fv(right); glVertex3fv(right);
      glTexCoord2f(tx_l, ty); glNormal3fv(left); glVertex3fv(left);
    }
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void Sphere::draw()
{
  //apply transformations
  glPushMatrix();
  apply_transform();
  glCallList(draw_list);
  glPopMatrix();
}

//===BARREL===
void Barrel::init()
{
  bottom.set_texture(texture); bottom.init();
  top.set_texture(texture); top.init();
  draw_list = glGenLists(1);
  glNewList(draw_list, GL_COMPILE);
    //enable lighting and tex materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glScalef(.5,.5,.5); //I don't feel like typing .5 a bunch
    //iterate rotation around y axis
    glEnable(GL_TEXTURE_2D);
    for(int th=0; th<360; th+=10) {
      //draw quad strip
      glBegin(GL_QUAD_STRIP);
        for(int ph = 50; ph<=130; ph += 10) {
          //find left/right tex coords for x
          float tx_r = ((float)th+5)/180.0, tx_l = ((float)th-5)/180.0;
          //tex coord in y direction for both vertices
          float ty = (float)ph/180.0;
          //find right and left points and draw
          float right[3] = {Sin(th+5)*Sin(ph)*(float).7,Cos(ph),Sin(ph)*Cos(th+5)*(float).7};
          float left[3] = {Sin(th-5)*Sin(ph)*(float).7,Cos(ph),Sin(ph)*Cos(th-5)*(float).7};
          glTexCoord2f(tx_r, ty); glNormal3fv(right); glVertex3fv(right);
          glTexCoord2f(tx_l, ty); glNormal3fv(left); glVertex3fv(left);
        }
      glEnd();
    }
    bottom.draw();
    top.draw();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void Barrel::draw()
{
  //apply transformations
  glPushMatrix();
  apply_transform();
  glCallList(draw_list);
  glPopMatrix();
}

//===TARGETFACE===
void TargetFace::init()
{
  //glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
  front.init();
  back.init();
}
void TargetFace::draw()
{
  glPushMatrix();
  apply_transform();
  //draw target faces
  front.draw();
  back.draw();
  glPopMatrix();
  //need to reset so that texture gets applied
  glPushMatrix();
  apply_transform();
  //draw wooden frame
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
    for(int th = 0; th < 360; th+=10) {
      glNormal3f(-Sin(th),0,Cos(th));
      glTexCoord2f(0,1); glVertex3f(-Sin(th+5),-.2,Cos(th+5));
      glTexCoord2f(0,0); glVertex3f(-Sin(th-5),-.2,Cos(th-5));
      glTexCoord2f(1,0); glVertex3f(-Sin(th-5),+.2,Cos(th-5));
      glTexCoord2f(1,1); glVertex3f(-Sin(th+5),+.2,Cos(th+5));
    }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}
void TargetFace::toggle_light()
{
  lit = !lit;
  if(lit) front.set_texture(lit_texture);
  if(!lit) front.set_texture(unlit_texture);
}
void TargetFace::toggle_light_off()
{
  if(lit) {
    front.set_texture(unlit_texture);
    lit = false;
  }
}

//===FULLTARGET
void FullTarget::init()
{
  prop1.init();
  prop2.init();
  prop3.init();
  targ.init();
}
void FullTarget::draw()
{
  glPushMatrix();
  apply_transform();
  targ.draw();
  prop1.draw();
  prop2.draw();
  prop3.draw();
  glPopMatrix();
}
void FullTarget::toggle_light()
{
  targ.toggle_light();
}
void FullTarget::toggle_light_off()
{
  targ.toggle_light_off();
}

//===TARGETRACK===
//targets at x = -2.25, -.75, .75, 2.25
//           y = 4, 2, 0, -2
void TargetRack::init()
{
  for(int y=0; y<4; y++) {
    float height = 3.3 - 2*y;
    shelves[y] = Cuboid(0,0,0, 6,.2,.5, 0,height,0, 1,1,1, (char*)"medwood.bmp"); shelves[y].init();
    for(int x=0; x<4; x++) {
      float posx = -2.25 + 1.5*x;
      float posy = 4 - 2*y;
      targets[x + y*4] = FullTarget(0,0,0, .75,.75,1, posx,posy,0, 1,1,1, (char*)"darkwood.bmp"); targets[x+y*4].init();
    }
  }
  leftside.init();
  rightside.init();
  topside.init();
}

void TargetRack::draw()
{
  glPushMatrix();
  apply_transform();
  for(int n=0; n<4; n++) {
    shelves[n].draw();
  }
  for(int n=0; n<16; n++) {
    targets[n].draw();
  }
  leftside.draw();
  rightside.draw();
  topside.draw();
  glPopMatrix();
}

void TargetRack::toggle_light_at(int x, int y)
{
  targets[x+y*4].toggle_light();
}

void TargetRack::toggle_light_off_at(int x, int y)
{
  targets[x+y*4].toggle_light_off();
}

int TargetRack::lit_target_count()
{
  int num = 0;
  for(int n=0; n<16; n++) {
    if(targets[n].targ.lit) {
      num++;
    }
  }
  return num;
}

//===HAYBALE===
void HayBale::init()
{
  top.init();
  bottom.init();
  texture = LoadTexBMP("hay.bmp");
}
void HayBale::draw()
{

  glPushMatrix();
  apply_transform();
  //draw target faces
  top.draw();
  bottom.draw();
  glPopMatrix();
  //need to reset so that texture gets applied
  glPushMatrix();
  apply_transform();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
    for(int th = 0; th < 360; th+=10) {
      int texth = th%180;
      float t0 = (float)(texth+5)/180;
      float t1 = (float)(texth-5)/180;
      glNormal3f(-Sin(th+5),0,Cos(th+5));
      glTexCoord2f(t0,0); glVertex3f(-Sin(th+5),-.5,Cos(th+5));
      glNormal3f(-Sin(th-5),0,Cos(th-5));
      glTexCoord2f(t1,0); glVertex3f(-Sin(th-5),-.5,Cos(th-5));
      glTexCoord2f(t1,1); glVertex3f(-Sin(th-5),+.5,Cos(th-5));
      glNormal3f(-Sin(th+5),0,Cos(th+5));
      glTexCoord2f(t0,1); glVertex3f(-Sin(th+5),+.5,Cos(th+5));
    }
  glEnd();

  /*
  glBegin(GL_QUAD_STRIP);
    //iterate circle
    for(int th=0; th<360; th+=10) {
      float texr = (th+5)/360;
      float texl = (th-5)/360;
      //draw cosine wave to simulate pile of hay
      for(int ph=0; ph<180; ph++) {
        float texy=ph/180;
        float dist = (float)ph/180;
        float right[3] = {Sin(th+5)*dist, Cos(ph)*(float).5, Cos(th+5)*dist};
        float left[3] = {Sin(th-5)*dist, Cos(ph)*(float).5, Cos(th-5)*dist};
        glTexCoord2f(texr,texy); glNormal3f(1,0,0); glVertex3fv(right);
        glTexCoord2f(texl,texy); glNormal3f(1,0,0); glVertex3fv(left);
      }
    }
  glEnd();
  */
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

//===HAYPILE===
void HayPile::init()
{
  draw_list = glGenLists(1);
  glNewList(draw_list, GL_COMPILE);
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glColor3f(1,1,1);
    //draw
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUAD_STRIP);
    for(int th = 0; th <= 360; th+=10) {
      int texth = th%90;
      float t0 = (float)(texth+5)/90;
      float t1 = (float)(texth-5)/90;
      glNormal3f(0,1,0);
      //top points
      glTexCoord2f(0,1); glVertex3f(0,.5,0);
      glTexCoord2f(t1,1); glVertex3f(0,.5,0);
      for(int ph=0; ph<=180; ph+=10) {
        float dist = (float)(ph)/180.0;
        //std::cout << -Sin(th+5)*dist << "," << Cos(ph)*.5 << "," << Cos(th+5)*dist << std::endl;
        glTexCoord2f(t0,0); glVertex3f(-Sin(th+5)*dist,Cos(ph)*.5,Cos(th+5)*dist);
        glTexCoord2f(t1,0); glVertex3f(-Sin(th-5)*dist,Cos(ph)*.5,Cos(th-5)*dist);
      }
    }
    glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
void HayPile::draw()
{
  glPushMatrix();
  apply_transform();
  glCallList(draw_list);
  glPopMatrix();
}

//===TABLE===
void Table::init()
{
  legs[0] = Cuboid(0,0,0, .1,.8,.1, -.9,-.1,+.4, 1,1,1, (char*)"medwood.bmp"); legs[0].init();
  legs[1] = Cuboid(0,0,0, .1,.8,.1, -.9,-.1,-.4, 1,1,1, (char*)"medwood.bmp"); legs[1].init();
  legs[2] = Cuboid(0,0,0, .1,.8,.1, +.9,-.1,+.4, 1,1,1, (char*)"medwood.bmp"); legs[2].init();
  legs[3] = Cuboid(0,0,0, .1,.8,.1, +.9,-.1,-.4, 1,1,1, (char*)"medwood.bmp"); legs[3].init();
  top =     Cuboid(0,0,0, 2,.2,1,   0.0,.4,0.0,  1,1,1, (char*)"medwood.bmp"); top.init();
}
void Table::draw()
{
  glPushMatrix();
  apply_transform();
  for(int n=0; n<4; n++) {
    legs[n].draw();
  }
  top.draw();
  glPopMatrix();
}

//===LAMP===
void Lamp::init()
{
  pole.init();
  lamp.init();
  bulb.init();
}
void Lamp::draw()
{
  glPushMatrix();
  apply_transform();
  pole.draw();
  lamp.draw();
  bulb.draw();
  glPopMatrix();
}

//===TEDDYBEAR===
void TeddyBear::init()
{
  head.init();
  snout.init();
  body.init();
  lear.init(); rear.init();
  lfoot.init(); rfoot.init();
  larm.init(); rarm.init();
}
void TeddyBear::draw()
{
  glPushMatrix();
  apply_transform();
  head.draw();
  snout.draw();
  body.draw();
  //draw legs
  lfoot.draw();
  rfoot.draw();
  //draw arms
  larm.draw();
  rarm.draw();
  //draw ears
  lear.draw();
  rear.draw();
  //draw snout
  glPopMatrix();
}
