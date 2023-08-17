#include <lcd_i2c_menu.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcd_i2c_menu::init()
{
    lcd.init();
    lcd.backlight();
    menu_columns = 0;

    pinMode(_pin_down, INPUT);
    pinMode(_pin_enter, INPUT);
    pinMode(_pin_up, INPUT);
}

void lcd_i2c_menu::menu(int menu_size)
{
    if (!sub_menu)
    {
        lcd.clear();
        _menu_size = menu_size;
        if (menu_columns + 1 > _menu_size)
        {
            menu_values[menu_columns + 1] = "";
        }

        lcd.setCursor(1, 0);
        lcd.print(menu_values[menu_columns]);
        lcd.setCursor(1, 1);
        lcd.print(menu_values[menu_columns + 1]);
    }
}

void lcd_i2c_menu::set_sub_menu(int submenu_size)
{
    _submenu_size = submenu_size;
    if (sub_menu)
    {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print(sub_menu_values[id][sub_menu_columns]);
        lcd.setCursor(1, 1);
        lcd.print(sub_menu_values[id][sub_menu_columns + 1]);
    }
}

void lcd_i2c_menu::pointer(String pointer)
{
    _pointer = pointer;
}

void lcd_i2c_menu::change_option(change_selection type)
{
    switch (type)
    {
    case UP:
        if (sub_menu)
        {
            if (_submenu_size - 1 > sub_menu_columns && sub_menu_values[id][sub_menu_columns + 1] != "")
                sub_menu_columns++;
        }
        else if (_menu_size - 2 > menu_columns)
            menu_columns++;

        break;
    case DOWN:

        if (sub_menu)
        {
            if (sub_menu_columns > 0)
                sub_menu_columns--;
        }
        else if (menu_columns > 0)
            menu_columns--;

        break;
    default:
        break;
    }

    if (!sub_menu)
        id = menu_columns;
}

void lcd_i2c_menu::update_menu(bool auto_update)
{
    lcd.setCursor(0, 0);
    lcd.print(_pointer);

    if (auto_update)
    {
        if (digitalRead(_pin_down))
            lcd_i2c_menu::change_option(DOWN);

        if (digitalRead(_pin_up))
            lcd_i2c_menu::change_option(UP);
    }

    if (digitalRead(_pin_enter))
    {
        menu_columns = 0;
        if (sub_menu_values[id][0] != main_string)
        {
            sub_menu_values[id][0] = main_string;
        }

        if (sub_menu_values[id][sub_menu_columns] == main_string && sub_menu)
        {
            sub_menu = false;
            return;
        }
        sub_menu = true;

        if(sub_menu)
            functions_array[id][sub_menu_columns ]();
    }

    while (digitalRead(_pin_enter) || digitalRead(_pin_down) || digitalRead(_pin_up))
        ;
}

lcd_i2c_menu::lcd_i2c_menu(int pin_up, int pin_down, int pin_enter)
{
    _pin_down = pin_down;
    _pin_up = pin_up;
    _pin_enter = pin_enter;
}

lcd_i2c_menu::~lcd_i2c_menu()
{
    return;
}
