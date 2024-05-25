#include <LiquidCrystal.h>

// Definiowanie pinów wyświetlacza LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, ct = 9;
LiquidCrystal mylcd(rs, en, d4, d5, d6, d7);

void setup() {
    analogWrite(ct, 50); // Ustawienie kontrastu
    mylcd.begin(16, 2); // Inicjalizacja wyświetlacza 16x2
    Serial.begin(9600); // Inicjalizacja komunikacji szeregowej z prędkością 9600 bps
    
    // Testowanie wyświetlacza LCD
    mylcd.clear();
    mylcd.setCursor(0, 0);
    mylcd.print("Test LCD");
    delay(2000); // Poczekaj 2 sekundy, aby sprawdzić wyświetlacz
    mylcd.clear();
    
    Serial.println("Setup complete"); // Debugging: potwierdzenie zakończenia setupu
}

void loop() {
    String hexString = "";

    if (Serial.available() > 0) {
        // Odczyt całego ciągu danych
        while (Serial.available() > 0) {
            char receivedChar = Serial.read(); // Odczytanie pojedynczego bajtu
            if (isHexadecimalDigit(receivedChar)) { // Sprawdzenie, czy znak jest cyfrą heksadecymalną
                hexString += receivedChar;
            }
            delay(10); // Krótkie opóźnienie dla zapewnienia odczytu całego ciągu
        }

        Serial.print("Received Hex String: ");
        Serial.println(hexString); // Debugging: wyświetlenie odebranego ciągu hex

        // Czyszczenie wyświetlacza
        mylcd.clear();
        mylcd.setCursor(0, 0);

        // Konwersja ciągu heksadecymalnego na ASCII i wyświetlanie
        for (int i = 0; i < hexString.length(); i += 2) {
            if (i + 1 < hexString.length()) {
                String hexByte = hexString.substring(i, i + 2);
                char asciiChar = (char) strtol(hexByte.c_str(), NULL, 16);
                mylcd.print(asciiChar);
                Serial.print("Converted ASCII Char: ");
                Serial.println(asciiChar); // Debugging: wyświetlenie przekonwertowanego znaku ASCII
            }
        }

        // Czyszczenie ciągu po przetworzeniu
        hexString = "";
    }
}
