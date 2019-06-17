#include <math.h>
#include "sgl.h"

#define MXSTR 500

int stroke[MXSTR * 2];
int sc = 0;

void render() {
  sgl_clear();
  sgl_set_background(0, 0.1, 0.3);

  float s = (sin(sgl_get_global_time_var() * 0.03) + 1) / 2;
  sgl_set_color(0.1, 0.6, 0.03);

  for (int i = 0; i < sc / 2; i++) {
    int x = stroke[i * 2];
    int y = stroke[i * 2 + 1];
    // sgl_draw_circle(x, y, s * 100.0 + 3.0);
    sgl_draw_rectangle(x, y, s * 100.0 + 3.0, s * 100.0 + 3.0);
  }

  sgl_update_display();
}

float mod(float v, float m) {
  return v - (m * (int)((int)v / (int)m));
}

int c = 0;

void left_click(int mouse_x, int mouse_y) {
  stroke[sc] = mouse_x;
  stroke[sc + 1] = mouse_y;
  sc += 2;
  if (sc > MXSTR * 2) {
    sc = 0;
  }
}

int main(int argc, char** argv) {
  sgl_init(argc, argv);
  sgl_set_render_func(render);
  sgl_set_mouse_func(sgl_mouse_left, left_click);
  sgl_run();
  return 0;
}
