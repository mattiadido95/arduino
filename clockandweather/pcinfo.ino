// Software Clock: set to compile/upload time
// with power cycle, reset, or new serial monitor goes to original compile time
// AVR Macro Strings converted to tmElements_t using functions
// getDate() and getTime() functions taken from ds1307 library

// weather : https://create.arduino.cc/projecthub/user5511362020/get-current-weather-data-from-openweathermap-org-c19b08

#include <TimeLib.h>
#include <LiquidCrystal.h>

tmElements_t tm;
const char *monthName[12] = {
    "Gen", "Feb", "Mar", "Apr", "Mag", "Giu",
    "Lug", "Ago", "Set", "Ott", "Nov", "Dic"};

int Contrast = 75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
    analogWrite(6, Contrast);
    lcd.begin(16, 2);

    if (getDate(__DATE__) && getTime(__TIME__))
    {
        //....
    }
    else
    {
        lcd.print("Error...");
    }
    setTime(makeTime(tm)); // set Ardino system clock to compiled time
}
void loop()
{
    lcdClockDisplay();
    delay(2000);
}

bool getTime(const char *str)
{
    int Hour, Min, Sec;

    if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3)
        return false;
    tm.Hour = Hour;
    tm.Minute = Min;
    tm.Second = Sec;
    return true;
}

bool getDate(const char *str)
{
    char Month[12];
    int Day, Year;
    uint8_t monthIndex;

    if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3)
        return false;
    for (monthIndex = 0; monthIndex < 12; monthIndex++)
    {
        if (strcmp(Month, monthName[monthIndex]) == 0)
            break;
    }
    if (monthIndex >= 12)
        return false;
    tm.Day = Day;
    tm.Month = monthIndex + 1;
    tm.Year = CalendarYrToTm(Year);
    return true;
}

void lcdClockDisplay()
{
    // lcd clock display of the time
    lcd.setCursor(0, 0);
    lcd.print(hour());
    printDigits(minute());
    // printDigits(second());
    //  lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.print(day());
    lcd.print(' ');
    lcd.print(monthName[month() - 1]);
    lcd.print(' ');
    lcd.print("'");
    lcd.print(year() - 2000);
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    lcd.print(":");
    if (digits < 10)
        lcd.print('0');
    lcd.print(digits);
}