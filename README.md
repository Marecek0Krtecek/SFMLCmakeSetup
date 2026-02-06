# Hansov paradox

Hansov paradox je 2D hra vytvorená ako vlastný projekt pre praktickú časť odbornej zložky maturitnej skúšky.
Projekt obsahuje samotnú hru aj editor úrovní, ktorý umožňuje vytvárať a upravovať levely bez zásahu do zdrojového kódu.

---

## 🎮 Základné informácie

- **Žáner:** 2D platformová hra
- **Platforma:** Windows
- **Jazyk:** C++
- **Grafická knižnica:** SFML
- **UI:** ImGui
- **Build:** Release verzia (spustiteľný `.exe` súbor)

---

## 🧩 Funkcionalita

### Hra
- pohyb hráča po platformách
- základná fyzika a gravitácia
- nepriatelia so stavovým správaním (Idle, Patrol, Chase, Attack)
- kolízia hráča s nepriateľmi
- checkpointy
- pause menu počas hry

### Level editor
- tvorba a úprava platforiem
- umiestňovanie nepriateľov a spawn pointov
- úprava pozadia (vrstvy, parallax)
- ukladanie a načítavanie levelov zo súborov
- rýchle prepínanie medzi editorom a hrou

---

## 🕹️ Ovládanie

### Hra
- **Pohyb:** A / D
- **Skok:** Space alebo W
- **Pause menu:** ESC
- **Prepnutie do editora:** F5

### Editor
- **Prepnutie do hry:** F5
- **Zobrazenie/skrytie nápovedy:** F1
- Ovládanie prebieha pomocou myši a editorových nástrojov

---

## ▶️ Spustenie projektu

1. Stiahni alebo rozbaľ priečinok s projektom
2. Spusti súbor `mygame.exe`
3. Nie je potrebné mať nainštalované Visual Studio ani ďalšie nástroje

> Poznámka: Projekt je distribuovaný ako release verzia určená na spustenie, nie na ďalší vývoj.

---

## ⚠️ Známe obmedzenia

- hra zatiaľ obsahuje iba jeden demo level
- hráč nemá implementovaný útok
- niektoré debug nástroje (ImGui okná) sú stále aktívne
- file dialog knižnica môže byť nestabilná pri práci s priečinkami

Tieto obmedzenia sú známe a zodpovedajú rozsahu projektu.

---

## 🎓 Kontext projektu

Projekt bol vytvorený ako:
- vlastný maturitný projekt (forma b)
- vytvorenie potrebnej grafiky pre prostredie, postavy a iné potrebné elementy
- návrh, dizajnovanie a postavenie levelov, ktoré budú sa nejako líšiť
- napísať vhodný scénar pre príbeh hry

---

## 👤 Autor

**Tomáš Turčina**  
Technické lýceum, 4.C  
Školský rok 2025/2026
