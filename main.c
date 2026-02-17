#include <gtk/gtk.h>
#include "shutdown.h"

static void print_hello (GtkWidget *widget, gpointer   data)
{
    g_print ("Hello World\n");
}

static void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(provider, "../style.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}

void on_shutdown_clicked(GtkWidget *widget, gpointer data)
{
    GtkWidget *entry = GTK_WIDGET(data);

    const char *text =
        gtk_editable_get_text(GTK_EDITABLE(entry));

    int minutes = atoi(text);

    shutdown_system(minutes);
}

static void activate(GtkApplication *app, gpointer user_data) {
    load_css();

    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *shutdown_btn;
    GtkWidget *reboot_btn;
    GtkWidget *undo_btn;
    GtkWidget *button_box;
    GtkWidget *label;
    GtkWidget *entry;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Shutty utility v1.2.5 by vadii");
    gtk_window_set_default_size(GTK_WINDOW(window), 450, 360);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), box);

    button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_widget_set_halign(button_box, GTK_ALIGN_CENTER);

    /* Label */
    label = gtk_label_new("Enter the time (minutes)");
    gtk_widget_add_css_class(label, "label1");
    gtk_box_append(GTK_BOX(box), label);

    //TEXT BOX
    entry = gtk_entry_new();
    gtk_widget_add_css_class(entry, "time-entry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Minutes");
    //gtk_widget_set_size_request(entry, 100, 30);


    gtk_box_append(GTK_BOX(box), entry);

    /* shutdown button */

    shutdown_btn = gtk_button_new();

    GtkWidget *shutdown_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 51);
    GtkWidget *shutdown_icon = gtk_image_new_from_file("../icons/shutdown_button.jpg");

    if (g_file_test("../icons/shutdown_button.jpg", G_FILE_TEST_EXISTS)) {
        g_print("Файл найден(shutdown img)\n");
    } else {
        g_print("Файл НЕ найден\n");
    }

    gtk_image_set_pixel_size(GTK_IMAGE(shutdown_icon), 51); // размер картинки

    gtk_box_append(GTK_BOX(shutdown_box), shutdown_icon);
    gtk_button_set_child(GTK_BUTTON(shutdown_btn), shutdown_box);
    gtk_widget_add_css_class(shutdown_btn, "shutdown-btn");
    //g_signal_connect(shutdown_btn, "clicked", G_CALLBACK(shutdown_system), entry);

    g_signal_connect(shutdown_btn, "clicked", G_CALLBACK(on_shutdown_clicked), entry);
    /* CSS */


    /* reboot button */
    reboot_btn = gtk_button_new();

    //gtk_widget_set_size_request(reboot_btn, 30, 30);

    GtkWidget *reboot_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 51);
    GtkWidget *reboot_icon = gtk_image_new_from_file("../icons/reboot_button.jpg");

    if (g_file_test("../icons/reboot_button.jpg", G_FILE_TEST_EXISTS)) {
        g_print("Файл найден(reboot img)\n");
    } else {
        g_print("Файл НЕ найден(reboot img)\n");
    }

    gtk_image_set_pixel_size(GTK_IMAGE(reboot_icon), 51); // размер картинки

    gtk_box_append(GTK_BOX(reboot_box), reboot_icon);
    gtk_button_set_child(GTK_BUTTON(reboot_btn), reboot_box);
    gtk_widget_add_css_class(reboot_btn, "reboot-btn");

    g_signal_connect(reboot_btn, "clicked", G_CALLBACK(on_shutdown_clicked), entry);

    //g_signal_connect(reboot_btn, "clicked", G_CALLBACK(reboot_system), entry);




    /*undo button*/

    undo_btn = gtk_button_new();

    //gtk_widget_set_size_request(reboot_btn, 30, 30);

    GtkWidget *undo_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 51);
    GtkWidget *undo_icon = gtk_image_new_from_file("../icons/undo_button.jpg");

    if (g_file_test("../icons/undo_button.jpg", G_FILE_TEST_EXISTS)) {
        g_print("Файл найден(undo img)\n");
    } else {
        g_print("Файл НЕ найден(undo img)\n");
    }
    gtk_image_set_pixel_size(GTK_IMAGE(reboot_icon), 51);
    gtk_box_append(GTK_BOX(undo_box), undo_icon);
    gtk_button_set_child(GTK_BUTTON(undo_btn), undo_box);
    gtk_widget_add_css_class(undo_btn, "undo-btn");



    gtk_box_append(GTK_BOX(button_box), shutdown_btn);
    gtk_box_append(GTK_BOX(button_box), reboot_btn);
    gtk_box_append(GTK_BOX(button_box), undo_btn);

    gtk_box_append(GTK_BOX(box), button_box);

    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_window_present(GTK_WINDOW(window));

    void on_undo_clicked(GtkWidget *widget, gpointer data)
    {
        undo_operation();
    }
    g_signal_connect(undo_btn, "clicked", G_CALLBACK(on_undo_clicked), entry);
}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}


