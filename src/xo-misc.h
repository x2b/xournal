#ifndef XO_MISC_H
#define XO_MISC_H

// data manipulation misc functions

struct Page *new_page(struct Page *template);
struct Page *new_page_with_bg(struct Background *bg, double width, double height);
void realloc_cur_path(int n);
void realloc_cur_widths(int n);
void clear_redo_stack(void);
void clear_undo_stack(void);
void prepare_new_undo(void);
void delete_journal(struct Journal *j);
void delete_page(struct Page *pg);
void delete_layer(struct Layer *l);
void copy_page_background(struct Page *new, struct Page *orig);

// referenced strings

struct Refstring *new_refstring(const char *s);
struct Refstring *refstring_ref(struct Refstring *rs);
void refstring_unref(struct Refstring *rs);

// helper functions
void init_layer(struct Layer *l);
struct BBox make_bbox_from_lrtb(double l, double r, double t, double b);
struct BBox bbox_add_offset_lrtb(struct BBox a, double l, double r, double t, double b);
void make_bbox_copy(struct BBox *bbfrom, struct BBox *bbto, int padding);
void get_pointer_coords(GdkEvent *event, double *ret);
double get_pressure_multiplier(GdkEvent *event);
void fix_xinput_coords(GdkEvent *event);
void update_item_bbox(struct Item *item);
void make_page_clipbox(struct Page *pg);
GnomeCanvasItem* canvas_item_new_for_selection(int type);
void make_canvas_items(void);
void make_canvas_item_one_text(GnomeCanvasGroup *group, struct Item *item);
void make_canvas_item_one_image(GnomeCanvasGroup *group, struct Item *item);
void make_canvas_item_stroke(GnomeCanvasGroup *group, struct Item *item);
void make_canvas_item_one(GnomeCanvasGroup *group, struct Item *item);
void update_canvas_bg(struct Page *pg);
gboolean is_visible(struct Page *pg);
void rescale_bg_pixmaps(void);

int get_mapping(GdkEventButton *event);

gboolean have_intersect(struct BBox *a, struct BBox *b);
void lower_canvas_item_to(GnomeCanvasGroup *g, GnomeCanvasItem *item, GnomeCanvasItem *after);

void rgb_to_gdkcolor(guint rgba, GdkColor *color);
guint32 gdkcolor_to_rgba(GdkColor gdkcolor, guint16 alpha);

gboolean hittest_point(ArtSVP* lassosvp, double x, double y); 
gboolean hittest_item(ArtSVP* lassosvp, Item* item); 

double bbox_width(struct BBox b);
double bbox_height(struct BBox b);
void bbox_pad_symm(struct BBox *b, double xpadding, double ypadding);
gboolean items_overlap(struct Item *i1, struct Item *i2);
struct BBox bboxadd(struct BBox a, struct BBox b);  

// interface misc functions

void update_thickness_buttons(void);
void update_color_buttons(void);
void update_tool_buttons(void);
void update_tool_menu(void);
void update_ruler_indicator(void);
void update_color_menu(void);
void update_pen_props_menu(void);
void update_eraser_props_menu(void);
void update_highlighter_props_menu(void);
void update_mappings_menu_linkings(void);
void update_mappings_menu(void);
void update_page_stuff(void);
void update_toolbar_and_menu(void);
void update_file_name(char *filename);
void update_undo_redo_enabled(void);
void update_copy_paste_enabled(void);
void update_vbox_order(int *order);

gchar *make_cur_font_name(void);
void update_font_button(void);

void update_mapping_linkings(int toolno);
void do_switch_page(int pg, gboolean rescroll, gboolean refresh_all);
void set_cur_color(int color_no, guint color_rgba);
void recolor_temp_text(int color_no, guint color_rgba);
void process_color_activate(GtkMenuItem *menuitem, int color_no, guint color_rgba);
void process_thickness_activate(GtkMenuItem *menuitem, int tool, int val);
void process_papercolor_activate(GtkMenuItem *menuitem, int color, guint rgba);
void process_paperstyle_activate(GtkMenuItem *menuitem, int style);

gboolean ok_to_close(void);

void reset_focus(void);

// selection / clipboard stuff
void move_journal_items_by(GList *itemlist, double dx, double dy,
                           struct Layer *l1, struct Layer *l2, GList *depths);
void resize_journal_items_by(GList *itemlist, double scaling_x, double scaling_y,
                             double offset_x, double offset_y);

// functions to work around GTK path bugs
gboolean sp_bpath_good_check (ArtBpath * bpath); 
ArtBpath * sp_bpath_check_subpath_check (ArtBpath * bpath); 
GnomeCanvasPathDef * gnome_canvas_path_def_close_all_fixed (const GnomeCanvasPathDef * path);

// switch between mappings

void switch_mapping(int m);
void process_mapping_activate(GtkMenuItem *menuitem, int m, int tool);

// always allow accels
void allow_all_accels(void);
gboolean can_accel(GtkWidget *widget, guint id, gpointer data);
void add_scroll_bindings(void);

gboolean is_event_within_textview(GdkEventButton *event);

void hide_unimplemented(void);
void signal_canvas_changed(void);

void do_fullscreen(gboolean active);

// fix GTK+ 2.16/2.17 issues with XInput events
gboolean filter_extended_events(GtkWidget *widget, GdkEvent *event, gpointer user_data);
// gboolean fix_extended_events(GtkWidget *widget, GdkEvent *event, gpointer user_data);

// help with focus
gboolean handle_activate_signal(GtkWidget *widget, gpointer user_data);
gboolean intercept_activate_events(GtkWidget *w, GdkEvent *ev, gpointer data);
void install_focus_hooks(GtkWidget *w, gpointer data);

// wrapper for a function no longer provided by poppler 0.17+
void
wrapper_poppler_page_render_to_pixbuf (PopplerPage *page,
			       int src_x, int src_y,
			       int src_width, int src_height,
			       double scale,
			       int rotation,
			       GdkPixbuf *pixbuf);

// defines for paper rulings

#define RULING_MARGIN_COLOR 0xff0080ff
#define RULING_COLOR 0x40a0ffff
#define RULING_THICKNESS 0.5
#define RULING_LEFTMARGIN 72.0
#define RULING_TOPMARGIN 80.0
#define RULING_SPACING 24.0
#define RULING_BOTTOMMARGIN RULING_SPACING
#define RULING_GRAPHSPACING 14.17


void draw_rubberband (GtkWidget *widget, GdkWindow *window,
							      const GdkRectangle *rect, guchar alpha);

void encode_uri(gchar *encoded_uri, gint bufsize, const gchar *uri,int len);

void unset_flags(GtkWidget *w, gpointer flag);
void set_flags(GtkWidget *w, gpointer flag);

// this declaration is needed for gnome_canvas_path_def_close_all_fixed to compile
struct _GnomeCanvasPathDef {
	gint refcount;
	ArtBpath * bpath;
	gint end;		/* ART_END position */
	gint length;		/* Num allocated Bpaths */
	gint substart;		/* subpath start */
	gdouble x, y;		/* previous moveto position */
	guint sbpath : 1;	/* Bpath is static */
	guint hascpt : 1;	/* Currentpoint is defined */
	guint posset : 1;	/* Previous was moveto */
	guint moving : 1;	/* Bpath end is moving */
	guint allclosed : 1;	/* All subpaths are closed */
	guint allopen : 1;	/* All subpaths are open */
};


#endif  /* XO_MISC_H */
