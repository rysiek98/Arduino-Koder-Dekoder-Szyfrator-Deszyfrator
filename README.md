# Arduino-Koder-Dekoder-Szyfrator-Deszyfrator

Projekt: Koder/Dekoder kodu Hamminga & Szyfrator/Deszyfrator TEA zrealizowany na Arduino UNO, pozwalający na wprowadzanie cyfr z zakresu 1-13, (liczby 35 i 42 wprowadzane poprzez wciśniecie # lub * służą testowemu przekłamaniu jednego bitu (ustawiona jest zmiana 38 bita na przeciwny bit) by pokazać prawidłowe działanie kodu Hamminga).

Do projektu wykorzystałem: 
-Arduino UNO 
-Fotorezystor (służy do odbierania wiadomości) 
-Dioda (nadanie wiadomości) -Klawiatura (wprowadzanie cyfry) -
przewody
-rezystory 220 Ohm 
-płytka stykowa -panel LCD 16,2

Krótki opis działania:
Program po wybraniu na klawiaturze cyfry rozpoczyna działanie:
1) Szyfruje szyfrem TEA nasza wiadomosc i wpisuje szyfr w postaci uint32_t do zmiennej globalnej
2) Nastepuje zamiana szyfru z int na tablice intów (reprezentacja binarna) i kodowanie kodem Hamminga
3) Przysłanie zakodowanej i zaszyfrowanej wiadomości za pomocą Diody i Fororezystroa 
4) Dekodowanie
5) Deszyfowanie

Gdy wprowadzimy # lub * program dla odpowidajacym znaką wartoscia DEC według kodu ASCII wykona operacje, lecz dokonane zostanie przekłamanie ostatniego bitu (zamiana na przwciwny) celem pokazania możliwosci kodu Hamminga


Wykonanie  Michał Ryszka Styczneń 2020 
