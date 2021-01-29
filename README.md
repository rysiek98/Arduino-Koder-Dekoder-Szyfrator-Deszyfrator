# Arduino Koder-Dekoder-Szyfrator-Deszyfrator

[PL] (English version below)

Projekt: Koder/Dekoder kodu Hamminga & Szyfrator/Deszyfrator TEA zrealizowany na Arduino UNO, pozwalający na wprowadzanie cyfr z zakresu 1-13, (liczby 35 i 42 wprowadzane poprzez wciśniecie # lub * służą testowemu przekłamaniu jednego bitu (ustawiona jest zmiana 38 bita na przeciwny bit) by pokazać prawidłowe działanie kodu Hamminga).

Do projektu wykorzystałem: 
-Arduino UNO 
-Fotorezystor (służy do odbierania wiadomości) 
-Dioda (nadanie wiadomości) -Klawiatura (wprowadzanie cyfry) 
-przewody
-rezystory 220 Ohm 
-płytka stykowa -panel LCD (16,2)

Krótki opis działania:
Program po wybraniu na klawiaturze cyfry rozpoczyna działanie:
1) Szyfruje szyfrem TEA nasza wiadomosc i wpisuje szyfr w postaci uint32_t do zmiennej globalnej
2) Nastepuje zamiana szyfru z liczby w systemmie dziesiętnym na reprezentacja binarna (tablice intów) i kodowanie kodem Hamminga
3) Przysłanie zakodowanej i zaszyfrowanej wiadomości za pomocą Diody i Fororezystroa 
4) Dekodowanie
5) Deszyfowanie

Gdy wprowadzimy # lub * program dla odpowidajacym znaką wartoscia DEC według kodu ASCII wykona operacje, lecz dokonane zostanie przekłamanie ostatniego bitu (zamiana na przwciwny) celem pokazania możliwosci kodu Hamminga

# Prezentacja działania https://youtu.be/YpyHDQIto3s 
Wykonanie  Michał Ryszka Styczneń 2020

[ENG]

Project: Coder/Decoder Hamming code & Cipher/Decipher TEA realized on Arduino UNO.

Items used in project:
-Arduino UNO 
-Photoresistor (message reciver) 
-Diode (message sender) 
-Keyboard (to inupt numbers) 
-Wires
-Resistor 220 Ohm 
-Breadboard
-LCD screen (16,2)

How it works:
1) User input one digits from 1-13 using keyboard (* and # are using to show that Hamming code can reapair one false bit, 
which is intentionally distorted after pressing * or #)
2) Inputed digit is encrypted using TEA 
3) Encrypted date is converted to binary represenatation and code using Hamming code
4) Code and encrypted message is send using diode and photoresistor
5) Message after reciving is decoded and decypred. 

# Work presentation https://youtu.be/YpyHDQIto3s 

Created by Michał Ryszka January 2020 
