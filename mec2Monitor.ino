
int inBytePrev = 0;
int inBytes[11]; //pole bajtov
int idx = 100; //index pri zapisovani do pola. inicializacia na 100

long lucka = 0;

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(1200);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial3.available()) {
    int inByte = Serial3.read();

    //ak je index rozny od 100, uz zapisujeme
    if(idx != 100 && idx < 11)
    {
      inBytes[idx] = inByte;
      idx++;
    }

    //ak mame koniec vety, tak vetu spracujeme
    if(inBytePrev == 175 && (inByte == 130 || inByte == 128 || 2))
    {
      //koncime dvojicou AF 82
      //alebo dvojicou AF 80
      //alebo dvojicou AF 02

      /*
      for(int i=0; i<11; i++)
      {
        Serial.print(inBytes[i] < 16 ? "0" : "");
        Serial.print(inBytes[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
      */

      ///*
      //if(inBytes[0] == 0x9E)
      //{
        //printRAW();
      //}
      
      //vypis pre poschodie
      if(inBytes[0] == 0x80 && inBytes[1] == 0x00)
      {
        printZone("POSCHODIE");
      }

      //vypis pre jedalen
      if(inBytes[0] == 0x81 && inBytes[1] == 0x00)
      {
        printZone("JEDALEN");
      }

      //vypis pre TUV
      if(inBytes[0] == 0x84 && inBytes[1] == 0x00)
      {
        printWater();
      }

      //vypis vonkajsej teploty
      if(inBytes[0] == 0x89 && inBytes[1] == 0x00)
      {
        printOutdoor();
      }

      //udaje o kotli
      if(inBytes[0] == 0x92 && inBytes[1] == 0x00)
      {
        printBoilerWorkingTime();
      }

      //udaje o solare
      if(inBytes[0] == 0x9E && inBytes[1] == 0x00)
      {
        printSolar();
      }
      if(inBytes[0] == 0x9E && inBytes[1] == 0x06)
      {
        printSolar11();
      }
      if(inBytes[0] == 0x9E && inBytes[1] == 0x18)
      {
        printSolar1WorTime();
      }
      //*/

      idx = 0;
    }

    inBytePrev = inByte;
  }
}

void printZone(String zona)
{
  Serial.print(zona);
  Serial.print(" Nastavena teplota ");
  Serial.print(inBytes[6] / 2);
  Serial.print(" stupnov.");
  Serial.print("Teplota vykurovacej vody: ");
  Serial.print(inBytes[4]);
  Serial.print(" stupnov. ");
  //Serial.print("Skutocna hodnota: ");
  //Serial.print(inBytes[5]);
  //Serial.print(" stupnov. ");
  //Serial.print("Pozadovana hodota: ");
  //Serial.print(inBytes[6]/2);
  //Serial.print(" stupnov. ");
  //Serial.print("Skutocna hodota: ");
  //Serial.print(inBytes[7]/2);
  //Serial.print(" stupnov. ");
  Serial.println();
}

void printWater()
{
  Serial.print("TUV nastavena teplota ");
  Serial.print(inBytes[4]);
  Serial.print(" stupnov.");

  Serial.print("Realna teplota ");
  Serial.print(inBytes[5]);
  Serial.print(" stupnov.");
  Serial.println();
}

void printOutdoor()
{
  Serial.print("Vonkajsia teplota ");
  int outTemp = (inBytes[2] <= 127 ? inBytes[2] : -(256 - inBytes[2]));
  Serial.print(outTemp);
  Serial.print(" stupnov.");
  Serial.println();
}

void printSolar()
{
  Serial.print("SOLAR teplota kolektora ");
  float collTemp = (inBytes[5] * 256L + inBytes[6])/10;
  Serial.print(collTemp);
  Serial.print(" stupnov.");
  Serial.print(" Modulacia ");
  Serial.print(inBytes[7]);
  Serial.print("%.");
}

void printSolar11()
{
  Serial.print(" Zasobnik1 ");
  Serial.print(inBytes[2]);
  Serial.print(" stupnov. ");
  Serial.print("Prietok: ");
  if(inBytes[3] & 0x01)
  {
    Serial.print("Off ");
  }
  if(inBytes[3] & 0x02)
  {
    Serial.print("Low solar ");
  }
  if(inBytes[3] & 0x04)
  {
    Serial.print("Low flow ");
  }
  if(inBytes[3] & 0x08)
  {
    Serial.print("High flow ");
  }
  if(inBytes[3] & 0x10)
  {
    Serial.print("Manual ");
  }
  Serial.print(".");
}

void printSolar1WorTime()
{
  long totalMins = 65536L*inBytes[2] + 256L*inBytes[3] + inBytes[4];
  long totalHours = totalMins/60;
  int mins = totalMins - (totalHours * 60);
  Serial.print("Prevadzkovy cas ");
  Serial.print(totalHours);
  Serial.print(" hodin, ");
  Serial.print(mins);
  Serial.print(" minut. ");
  Serial.print("Celkom ");
  Serial.print(totalMins);
  Serial.print(" minut.");
  Serial.println();
}

void printBoilerWorkingTime()
{
  long totalHours = 65536L*inBytes[4] + 256L*inBytes[5] + inBytes[6];
  long totalMins = (totalHours * 60L) + inBytes[7];
  Serial.print("KOTOL: Modulacia ");
  Serial.print(inBytes[3]);
  Serial.print("%.");
  Serial.print(" Prevadzkovy cas kotla ");
  Serial.print(totalHours);
  Serial.print(" hodin, ");
  Serial.print(inBytes[7]);
  Serial.print(" minut. ");
  Serial.print("Celkom ");
  Serial.print(totalMins);
  Serial.print(" minut.");

  Serial.println();
}

void printRAW()
{
  for(int i=0; i<11; i++)
  {
    Serial.print(inBytes[i] < 16 ? "0" : "");
    Serial.print(inBytes[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

