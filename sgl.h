extern int sgl_init(int argc, char **argv);
extern int sgl_run(void);

extern void sgl_set_render_func(void (*func)(void));

extern void sgl_clear(void);
extern void sgl_set_background(float r, float g, float b);
extern void sgl_update_display(void);

extern int sgl_get_global_time_var(void);

extern void sgl_set_mouse_func(int button, void (*func)(int mouse_x, int mouse_y));
extern int sgl_mouse_right;
extern int sgl_mouse_left;
extern int sgl_get_mouse_pos_x();
extern int sgl_get_mouse_pos_y();

extern void sgl_set_color(float r, float g, float b);

extern void sgl_draw_circle(float x, float y, float r);
extern void sgl_draw_rectangle(float x, float y, float width, float height);
void sgl_draw_line(int lenght, int *data);
// extern void sgl_draw_heart(float x, float y, float r);
