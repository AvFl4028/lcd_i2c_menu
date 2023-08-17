#ifndef __LCD_I2C_MENU_H__
#define __LCD_I2C_MENU_H__
// SECTION - Librarys Section
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
//!SECTION

// NOTE - menu values
extern String menu_values[];

// NOTE - sub menu values array of arrays
extern String sub_menu_values[][10];

// NOTE - Functions array
extern void (*functions_array[][10])();

// NOTE - type of selection
enum change_selection
{
    UP,
    DOWN
};

// NOTE - Main class of this library
class lcd_i2c_menu
{
private:
    String _pointer;
    String main_string = "Main";

    int menu_columns, sub_menu_columns;
    int _menu_size, _submenu_size;
    int _pin_up, _pin_down, _pin_enter;
    int id;
    bool sub_menu = false;
    void default_function(){return;}
public:
    lcd_i2c_menu(int pin_up = 2, int pin_down = 3, int pin_enter = 4);
    ~lcd_i2c_menu();

    void init();
    void menu(int menu_size);
    void set_sub_menu(int submenu_size);
    void pointer(String pointer = ">");
    void change_option(change_selection type);
    void update_menu(bool auto_update_change_option = true);
};

extern void func_default();

#endif