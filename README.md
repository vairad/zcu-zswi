# Informace o projektu
Projekt týmu Šejdrem k předmětům KIV/ZSWI a KIV/UIR na ZČU v Plzni

## Zadání
Návrh aplikace pro záznam, zobrazení a uložení biosignálů získaných z e-Health senzor platform pro Arduino.

Komunikační program pro Arduino, které přenáší naměřená data z vybraných biosenzorů na PC. Aplikace na PC bude řídit záznam dat z biosenzorů, naměřená data zobrazí, uloží, popř. umožní doplnění dalších metadat. Uložená data bude možno dále zpracovávat v aplikacích MS Office.

Zadavatel: Pavel Mautner, e-mail: mautner@kiv.zcu.cz  

#Spuštění programu Šejdrem Sensor

## Požadavky:
1.  Zařízení Arduino UNO + eHealth kit 2 s nahraným programem rel_2smycka je připojené pomocí kabelu USB
 1. Doporučujeme zapojit zařízení, ve kterém jsou již připojeny senzory, které budou použity. Senzory připojené po zapojení zařízení můžou způsobovat chybná měření i na ostatních senzorech.

## Samotné kroky spuštění měření
1. Spuštění aplikace
2. Výběr uživatele slouží pro ukládání dat (bez přihlášení: naměřené údaje nebudou ukládány)
3. Zjištění připojených zařízení pomocí tlačítka 'obnovit' na nástrojové liště
4. Výběr zařízení (nejčastěji bude název vypadat následovně: "COM4 [Arduino Uno]"
5. Zahájení snímání pomocí tlačítka 'spustit' na nástrojové liště

## Poznámky
 - Různé senzory mají různé doby odezvy, některé senzory (např. puls nebo okysličení krve) mohou mít odezvu až 5 vteřin
