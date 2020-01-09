
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


int ledPin = 12;
LiquidCrystal_I2C lcd(0x27,16,2);
  
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {1,2,3,10},
  {4,5,6,11},
  {7,8,9,12},
  {'*',0,'#',13}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 4, 3, 2}; 

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){

  pinMode(ledPin, OUTPUT);
  lcd.init();                    
  lcd.backlight();
  lcd.print("Projekt UCYF");
  lcd.setCursor(0,1);
  lcd.print("Zakres pra. 0-13");
  delay(2000);
}

// Zmienne globalne
uint32_t tab_H[38] = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};  //Globalna tablica, przewcjowuje Kod Hamminga
uint32_t szyfr[2] = {0,0}; //Tablica przechowujaca zaszyfrowana liczbe wybrana przez uzytkownika
int tab_dH[32]; //Tablica zawierajaca odebrana wiadomosc po zdekodowaniu
uint32_t zmienna = 0; //Wybrana liczba przez uzytkownika
int bin[32]= { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Globalna tablica uzywana przez fun. DectoBin, za kazdym razem na poczatku zerowana

  
void loop() {
  bool tryb = false;
  int wiadomosc[38]={8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};    //Odebrana wiadomosc

  char customKey = customKeypad.getKey();
  lcd.clear();
  lcd.print("Wybierz numer: ");
  delay(1000);
 
  if (customKey){
      zmienna = customKey;
      if(zmienna == 35 || zmienna == 42) 
      {tryb = true;}
      lcd.clear();
      lcd.print("Wybrano: ");
      lcd.print(zmienna);
      delay(2000);
          
      uint32_t klucz[4]={1,2,3,4}; //Klucz do szyfru TEA
      uint32_t v[2]={zmienna,0};   // 0 w drugiej kolumnie poniewaz TEA wymaga dwoch liczb (pracuje na dwoch 32 bit blokach)
      szyfrator (v,klucz);         //Szyfrowanie
      DectoBin(zmienna);           //Zamieniamy zaszyfrowana wiadomosc na sys. binarny (zosatje umieszczona w tab. globalnej bin)
      kod_hamminga(bin);           //Funkcja oblicza kod Hamminga
      lcd.clear();
      int sensorValue = 0;
      float swiatlo = 0;
      
      lcd.print("TRANSMISJA ");
      lcd.setCursor(0,1);
      lcd.print("Wys. wiad -> ");
      delay(1500);
      lcd.clear();
      
      for(int i=0; i<38; i++){
        if(i == 16 || i == 32) {delay(2000); lcd.clear();}
        
        lcd.print(tab_H[i]);
        
        if(tab_H[i]%2 == 0)
          {
            if(tryb){
              if(i == 37)
              {digitalWrite(ledPin, HIGH);}
              else {digitalWrite(ledPin, LOW);}
            }
            else{
                digitalWrite(ledPin, LOW);
                }
          }
          else {
              if(tryb){
              if(i == 37)
              {digitalWrite(ledPin, LOW);}
              else {digitalWrite(ledPin, HIGH);}
            }
            else{
                digitalWrite(ledPin, HIGH);
                }
          }
        delay(10);
        sensorValue = analogRead(A0);
        swiatlo = sensorValue * (100.0 / 1023.0);
       
        if(swiatlo > 45.00){
          wiadomosc[i]=1;
          }
          
        else{
         wiadomosc[i]=0;
        }
        
       delay(90);
       
      }
    delay(2000);
    lcd.clear(); 
    digitalWrite(ledPin, LOW);
    dekoder(wiadomosc);
    deszyfrator(szyfr, klucz);
  }
}


uint32_t pow2(uint32_t x, int z)
{
    uint32_t xd = 1;
    if (z == 0) { return 1; }
    else
    {
        for (int i = 0; i < z; i++)
        {
            xd = x * xd;
        }
        return xd;
    }
}


uint32_t BintoDec(int z[32])
{
    uint32_t liczba = 0;
    for (int i = 31; i >= 0; i--)
    {
        if (z[i] == 1) {
            liczba = liczba + pow2(2, -(i - 31));
        }
    }

    return liczba;
}

void DectoBin(uint32_t z)
{
    for (int g = 0; g < 32; g++) { bin[g] = 0; }

    for (int i = 31; i >= 0; i--)
    {
        if (z % 2 == 0)
        {
            bin[i] = 0;
        }
        if (z % 2 == 1)
        {
            bin[i] = 1;
        }
        z = z / 2;
      
    }


}


void kod_hamminga(int liczba[32])
{
    int tab_pos[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int tab_kt[6] = { 0,0,0,0,0,0};
    int suma[6] = { 0,0,0,0,0,0};
    int it = 0;
    int it2 = 0;
    int it3 = 0;

    for (int i = 1; i < 39; i++)
    {
        if (i == pow2(2, it2))
        {
            tab_H[i - 1] = 8;
            it2++;
        }
        else
        {

            tab_H[i - 1] = liczba[it];
            it++;
            if (tab_H[i - 1] == 1)
            {
               tab_pos[it3] = i;
               it3++;

             }
        }
    
    }

    for (int i = 0; i < 6; i++)
    {
        
        for (int j = 0; j < 32; j++)
        {
            if(tab_pos[j] != 0){
            DectoBin(tab_pos[j]);
            suma[i] = suma[i] + bin[i+26];
           
            }
            
        }
        
        tab_kt[5 - i] = suma[i];
    }
    
    for (int k = 0; k < 6; k++)
    {
        
        if (tab_kt[k] % 2 == 0)
        {
            tab_kt[k] = 0;
        }
        else
        {
            tab_kt[k] = 1;
        }
      
    }
    it = 0;
    
    for (int z = 0; z < 38; z++)
    {

        if (tab_H[z] == 8)
        {
            tab_H[z] = tab_kt[it];
            it++;

        }
        
    }

    lcd.clear();
    lcd.print("Kodowanie ");
    delay(1000);
    lcd.clear();
}


void dekoder(int tab[38])
{
    uint32_t liczba = 0;
    int tab_pos[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int tab_kt[6] = { 0,0,0,0,0,0 };
    uint32_t suma2[6] = { 0,0,0,0,0,0 };
    int it = 0;

    lcd.clear();
    lcd.print("Odebrana w.");
    delay(1500);
    lcd.clear(); 
    for (int j = 1; j < 39; j++)
    {   if(j-1 == 16 || j-1 == 32) {delay(2000); lcd.clear();}
        lcd.print(tab[j - 1]);
        if (tab[j - 1] == 1)
        {
            tab_pos[it] = j;
           
            it++;
        }
    }
    delay(2000);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if(tab_pos[j] != 0){  
            DectoBin(tab_pos[j]);
            suma2[i] = suma2[i] + bin[i+26];
            
            }

        }
 
    }
   
    for (int i = 0; i < 6; i++)
    {
        if (suma2[i] % 2 != 0)
        {
            liczba = liczba + pow2(2, 5-i);

        }
    }
  
    if (liczba != 0)
    {
        if (tab[liczba - 1] == 1) { tab[liczba - 1] = 0; }
        else
        {
            tab[liczba - 1] = 1;
        }
    }

    
    it = 0;
    lcd.clear();
    for (int j = 2; j < 39; j++)
    {
        if (j == 3 || j == 7 || j == 15 || j == 31) { continue; }
        else {
            tab_dH[it] = tab[j];
            it++;
        }
    }

  
    szyfr[0] = BintoDec(tab_dH);
    lcd.clear();
    lcd.print("Dekodowana w.: ");
    lcd.setCursor(0,1);
    lcd.print(szyfr[0]);
    delay(2000);
    

}



void szyfrator(uint32_t v[2], uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    uint32_t delta = 0x9E3779B9;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];

    for (int i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }
    szyfr[1] = v1;
    zmienna = v0;
    lcd.clear();
    lcd.print("Szyfrowanie: ");
    lcd.setCursor(0,1);
    lcd.print(zmienna);
    delay(2000);

}


void deszyfrator(uint32_t v[2], uint32_t k[4]) {
  
    uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720;
    uint32_t delta = 0x9E3779B9;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    uint32_t wynik2[2] = { 0,0 };
    
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum -= delta;
    }
    wynik2[0] = v0; wynik2[1] = v1;
    lcd.clear();
    lcd.print("Odszyfrowana w.: ");
    lcd.setCursor(0,1);
    lcd.print("W. w DEC: ");
    lcd.print(wynik2[0]);
    delay(2000);
}



