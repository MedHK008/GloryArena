#ifndef FIXED_H_INCLUDED
#define FIXED_H_INCLUDED

typedef struct {
    GtkWidget* fixed;  // Pointer to the GtkFixed container
} Fixed;

// Function to initialize a GtkFixed container
Fixed* init_gtk_fixed() {
    Fixed* info =(Fixed*)malloc(sizeof(Fixed));  // Allocate memory for Fixed
    if (!info) {
        g_print("Error: Failed to allocate memory for Fixed\n");
        return NULL;
    }

    // Create a new GtkFixed container
    info->fixed = gtk_fixed_new();

    return info;
}

// Function to add a widget to a GtkFixed container
void add_widget_to_fixed(Fixed* fixedInfo, GtkWidget* widget, gint x, gint y) {
    // Add the widget to the GtkFixed container at the specified position
    gtk_fixed_put(GTK_FIXED(fixedInfo->fixed), widget, x, y);
}

// Function to remove a widget from a GtkFixed container
void remove_widget_from_fixed(Fixed* fixedInfo, GtkWidget* widget) {
    // Remove the widget from the GtkFixed container
    gtk_container_remove(GTK_CONTAINER(fixedInfo->fixed), widget);
}

// Function to free memory allocated for Fixed
void free_gtk_fixed_info(Fixed* fixedInfo) {
    if (fixedInfo) {
        g_object_unref(fixedInfo->fixed);  // Release resources associated with GtkFixed
        g_free(fixedInfo);  // Free the Fixed structure
    }
}

#endif // FIXED_H_INCLUDED
