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
    // Allouer dynamiquement la m�moire pour la structure de cadre
    frame *fr = (frame *)g_malloc(sizeof(frame));

    // Initialiser les champs de la structure avec les valeurs sp�cifi�es
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

    // Retourner la structure de cadre initialis�e
    return fr;
}

void creer_frame(frame *fr) {
    // Cr�er une cha�ne de caract�res format�e pour l'�tiquette avec des propri�t�s de texte sp�cifi�es
    gchar *lab = NULL;
    if (fr->text)
       lab = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ", fr->text->taille_text, fr->text->style, fr->text->couleur_text, fr->text->police, fr->text->underline, fr->text->text);

    // Cr�er un widget de label GTK et d�finir son contenu avec la cha�ne format�e
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), lab);

    // D�finir le label comme �tiquette du cadre
    gtk_frame_set_label_widget(GTK_FRAME(fr->widget), label);


    // Si des positions sp�cifi�es, les appliquer � l'�tiquette du cadre
    if (fr->xligne || fr->yligne)
        gtk_frame_set_label_align(GTK_FRAME(fr->widget), fr->xligne, fr->yligne);

    // Si un type d'ombre sp�cifi�, l'appliquer au cadre
        gtk_frame_set_shadow_type(GTK_FRAME(fr->widget), fr->type);
}

frame *add_frame(GtkWidget *pere, gchar *name, gfloat xligne, gfloat yligne, texte *tx, GtkShadowType type, gint x, gint y) {
    frame *fr = initialiser_frame(pere, name, xligne, yligne, tx, type);
    creer_frame(fr);
    gtk_fixed_put(GTK_FIXED(pere), fr->widget, x, y);
    return fr;
}

// Fonction pour lib�rer la m�moire allou�e � une structure frame
void free_frame(frame *fr) {
    if (fr) {
        // Lib�rer la m�moire allou�e pour le texte associ�
        if (fr->text) {
            g_free(fr->text);
        }
        // Lib�rer le nom s'il a �t� dupliqu�
        if (fr->name) {
            g_free(fr->name);
        }
        // D�truire le widget GTK associ�
        if (fr->widget) {
            gtk_widget_destroy(fr->widget);
        }
        // Lib�rer la structure frame elle-m�me
        g_free(fr);
    }
}

#endif // FRAME_H_INCLUDED
