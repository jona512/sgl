#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
// #include <stdio.h>

#include "sgl.h"

void sgl_intern_resize_func(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, h, 0);  // top-left(0,0) to bottom right(w,h) // x,y
  glMatrixMode(GL_MODELVIEW);
}

int sgl_mouse_left = 0;
int sgl_mouse_right = 1;

void sgl_inter_empty_func() {
  // printf("debug\n");
}

int sgl_intern_mouse_left_state = 0;  // 1 = down // 0 = up
int sgl_intern_mouse_right_state = 0;

int sgl_intern_mouse_pos_x = 0;
int sgl_intern_mouse_pos_y = 0;

int sgl_get_mouse_pos_x() {
  return sgl_intern_mouse_pos_x;
}

int sgl_get_mouse_pos_y() {
  return sgl_intern_mouse_pos_y;
}

void (*sgl_intern_mouse_left_func)(int mouse_x, int mouse_y) = &sgl_inter_empty_func;
void (*sgl_intern_mouse_right_func)(int mouse_x, int mouse_y) = &sgl_inter_empty_func;

void sgl_inter_handle_mouse(int glut_button, int glut_state, int mouse_x, int mouse_y) {
  sgl_intern_mouse_pos_x = mouse_x;
  sgl_intern_mouse_pos_y = mouse_y;

  if (glut_state == GLUT_DOWN) {
    if (glut_button == GLUT_LEFT_BUTTON) {
      sgl_intern_mouse_left_state = 1;
    } else if (glut_button == GLUT_RIGHT_BUTTON) {
      sgl_intern_mouse_right_state = 1;
    }
  } else if (glut_state == GLUT_UP) {
    if (glut_button == GLUT_LEFT_BUTTON) {
      sgl_intern_mouse_left_state = 0;
    } else if (glut_button == GLUT_RIGHT_BUTTON) {
      sgl_intern_mouse_right_state = 0;
    }
  }
}

void sgl_set_mouse_func(int button, void (*event_func)(int mouse_x, int mouse_y)) {
  if (button == 0) {
    sgl_intern_mouse_left_func = event_func;
  } else if (button == 1) {
    sgl_intern_mouse_right_func = event_func;
  }
}

void sgl_intern_mouse_func(int mouse_x, int mouse_y) {
  sgl_intern_mouse_pos_x = mouse_x;
  sgl_intern_mouse_pos_y = mouse_y;
}

int sgl_init(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("sgl");

  glutReshapeFunc(sgl_intern_resize_func);

  glutMouseFunc(sgl_inter_handle_mouse);
  glutMotionFunc(sgl_intern_mouse_func);
  glutPassiveMotionFunc(sgl_intern_mouse_func);

  return 0;
}

int sgl_global_time_var = 0;

int sgl_get_global_time_var() {
  return sgl_global_time_var;
}

void sgl_inter_update_func(int t) {
  sgl_global_time_var++;
  if (sgl_global_time_var > 100000) {
    sgl_global_time_var = 1;
  }
  glutPostRedisplay();
  glutTimerFunc(1000.0 / 60.0, sgl_inter_update_func, 0);

  if (sgl_intern_mouse_left_state == 1) {
    (*sgl_intern_mouse_left_func)(sgl_intern_mouse_pos_x, sgl_intern_mouse_pos_y);
  } else if (sgl_intern_mouse_right_state == 1) {
    (*sgl_intern_mouse_right_func)(sgl_intern_mouse_pos_x, sgl_intern_mouse_pos_y);
  }
}

int sgl_run() {
  glutTimerFunc(0, sgl_inter_update_func, 0);
  glutMainLoop();
  return 0;
}

void sgl_set_render_func(void (*render_func)(void)) {
  glutDisplayFunc(render_func);
}

void sgl_clear() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
}

void sgl_set_background(float r, float g, float b) {
  glClearColor(r, g, b, 1.0);
}

void sgl_update_display() {
  glutSwapBuffers();
}

void sgl_set_color(float r, float g, float b) {
  glColor3f(r, g, b);
}

void sgl_draw_circle(float x, float y, float r) {
  glBegin(GL_POLYGON);
  // for (float i = 0; i < M_PI * 2; i += 0.02) {
  // for (float i = 0; i < 3.14 * 2; i += 0.02) {
  // for (float i = 0; i < 3.14 * 2; i += 0.1) {
  for (float i = 0; i < 3.14 * 2; i += 3/(r+0.6)+0.01) {
    glVertex2f(x + r * sin(i), y + r * cos(i));
  }
  glEnd();
}

void sgl_draw_rectangle(float x, float y, float width, float height) {
  glBegin(GL_POLYGON);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}

void sgl_draw_line(int lenght, int *data) {
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < lenght; i++) {
    glVertex2f(data[i * 2], data[i * 2 + 1]);
  }
  glEnd();
}

// void sgl_draw_heart(float x, float y, float r) {
//   glBegin(GL_POLYGON);
//   float hx, hy;
//   // for (float i = 0; i < M_PI * 2; i += 0.02) {
//   for (float i = 0; i < 3.142 * 2; i += 0.02) {
//     hx = 16 * pow(sin(i), 3);
//     hy = 13 * cos(i) - 5 * cos(2 * i) - 2 * cos(3 * i) - cos(4 * i);
//     glVertex2f(x + r * hx, y + r * hy);
//   }
//   glEnd();
// }
