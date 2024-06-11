#ifndef FENETREDEROULANTE_H_INCLUDED
#define FENETREDEROULANTE_H_INCLUDED

typedef struct {
    GtkWidget *widget;    // The scrolled window widget
    GtkWidget *parent;    // The parent widget
    gint width;           // Width of the scrolled window
    gint height;          // Height of the scrolled window
    gchar *title;         // Title of the scrolled window
    gboolean visible;     // Visibility status
    gchar *bg_color;      // Background color
} ScrolledWindow;


ScrolledWindow* init_scrolled_window(GtkWidget *parent, const gchar *title, gint width, gint height, gboolean visible, const gchar *bg_color) {
    // Allocate memory for the ScrolledWindow structure
    ScrolledWindow *sw = (ScrolledWindow *)g_malloc(sizeof(ScrolledWindow));

    // Initialize the fields
    sw->widget = gtk_scrolled_window_new(NULL, NULL);
    sw->parent = parent;
    sw->width = width;
    sw->height = height;
    sw->title = g_strdup(title);  // Duplicate the title string
    sw->visible = visible;
    sw->bg_color = g_strdup(bg_color);  // Duplicate the background color string

    // Set properties
    gtk_widget_set_size_request(sw->widget, sw->width, sw->height);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw->widget), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Set title if specified
    if (sw->title) {
        gtk_widget_set_name(sw->widget, sw->title);
    }

    // Set background color if specified
    if (sw->bg_color) {
        GtkCssProvider *provider = gtk_css_provider_new();
        gchar *css = g_strdup_printf("scrolledwindow { background-color: %s; }", sw->bg_color);
        gtk_css_provider_load_from_data(provider, css, -1, NULL);
        GtkStyleContext *context = gtk_widget_get_style_context(sw->widget);
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        g_object_unref(provider);
        g_free(css);
    }

    // Set visibility
    if (sw->visible) {
        gtk_widget_show(sw->widget);
    }

    return sw;
}

void create_scrolled_window(ScrolledWindow *sw) {
    // Add the scrolled window to its parent container
    if (sw->parent) {
        gtk_container_add(GTK_CONTAINER(sw->parent), sw->widget);
    }
}

ScrolledWindow* add_scrolledWindow(GtkWidget *parent, const gchar *title, gint width, gint height, gboolean visible, const gchar *bg_color)
{
    ScrolledWindow *scrolledWindow = init_scrolled_window(parent,title, width, height, visible, bg_color);
    create_scrolled_window(scrolledWindow);
    return ((ScrolledWindow*)scrolledWindow);
}

void free_scrolled_window(ScrolledWindow *sw) {
    if (sw) {
        // Free the title string
        if (sw->title) {
            g_free(sw->title);
        }
        // Free the background color string
        if (sw->bg_color) {
            g_free(sw->bg_color);
        }
        // Destroy the widget
        gtk_widget_destroy(sw->widget);
        // Free the structure itself
        g_free(sw);
    }
}

#endif // FENETREDEROULANTE_H_INCLUDED
