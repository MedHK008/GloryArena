#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

/// Structure pour repr senter un cadre (frame) avec des  l ments associ s
typedef struct
{
    GtkWidget *widget;          // Le widget GTK repr sentant le cadre
    GtkWidget *parent;          // Le parent du cadre
    gint xligne;                // Position horizontale de l' tiquette dans le cadre
    gint yligne;                // Position verticale de l' tiquette dans le cadre
    texte *text;                // Structure de texte associ e au cadre
    // Le conteneur associ  au cadre (peut  tre un label ou autre)
    GtkShadowType type;          // Type d'ombre du cadre
    gchar* name;
} frame;

frame *initialiser_frame(GtkWidget *pere, gchar *name, gint x, gint y, texte *t, GtkShadowType type) {
    // Allouer dynamiquement la mémoire pour la structure de cadre
    frame *fr = (frame *)g_malloc(sizeof(frame));

    // Initialiser les champs de la structure avec les valeurs spécifiées
    fr->widget = gtk_frame_new(NULL);
    fr->text = t;
    fr->parent = pere;
    fr->type = type;
    fr->xligne = x;
    fr->yligne = y;
    fr->name = NULL;

    if (name) {
        fr->name = g_strdup(name);
        gtk_widget_set_name(fr->widget, name);
    }

    // Retourner la structure de cadre initialisée
    return fr;
}

void creer_frame(frame *fr) {
    // Créer une chaîne de caractères formatée pour l'étiquette avec des propriétés de texte spécifiées
    gchar *lab = NULL;
    if (fr->text)
       lab = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ", fr->text->taille_text, fr->text->style, fr->text->couleur_text, fr->text->police, fr->text->underline, fr->text->text);

    // Créer un widget de label GTK et définir son contenu avec la chaîne formatée
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), lab);

    // Définir le label comme étiquette du cadre
    gtk_frame_set_label_widget(GTK_FRAME(fr->widget), label);


    // Si des positions spécifiées, les appliquer à l'étiquette du cadre
    if (fr->xligne || fr->yligne)
        gtk_frame_set_label_align(GTK_FRAME(fr->widget), fr->xligne, fr->yligne);

    // Si un type d'ombre spécifié, l'appliquer au cadre
        gtk_frame_set_shadow_type(GTK_FRAME(fr->widget), fr->type);
}

frame *add_frame(GtkWidget *pere, gchar *name, gfloat xligne, gfloat yligne, texte *tx, GtkShadowType type, gint x, gint y) {
    frame *fr = initialiser_frame(pere, name, xligne, yligne, tx, type);
    creer_frame(fr);
    gtk_fixed_put(GTK_FIXED(pere), fr->widget, x, y);
    return fr;
}

// Fonction pour libérer la mémoire allouée à une structure frame
void free_frame(frame *fr) {
    if (fr) {
        // Libérer la mémoire allouée pour le texte associé
        if (fr->text) {
            g_free(fr->text);
        }
        // Libérer le nom s'il a été dupliqué
        if (fr->name) {
            g_free(fr->name);
        }
        // Détruire le widget GTK associé
        if (fr->widget) {
            gtk_widget_destroy(fr->widget);
        }
        // Libérer la structure frame elle-même
        g_free(fr);
    }
}

#endif // FRAME_H_INCLUDED
