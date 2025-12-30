# 🎯 Mesačný plán vývoja hry (Október 2025)

Tento plán je navrhnutý tak, aby si mohol postupovať po malých, ale dôležitých krokoch — približne **1 hodinu denne**.
Každý víkend máš priestor na väčšie úlohy alebo refaktorovanie.

---

## 🗓️ Týždeň 1 – Údržba, stabilita a vylepšenie editora
**Cieľ:** Doladiť workflow v editore a pripraviť pôdu pre prácu s nepriateľmi.

- [x] 🧩 Zjednotiť ukladanie a načítanie (spawn pointy, platformy, pozadie)
- [x] 🧰 Upratať kód v `EditorState` – presunúť opakujúce sa časti do funkcií
- [x] 💾 Vyriešiť správne otváranie a ukladanie súborov cez ImGuiFileDialog (prípadne pridať fallback)
- [x] 🧠 Pridať možnosť Undo/Redo pre nepriateľov
- [x] 🔍 Otestovať všetky tri akcie (Add, Move, Delete) pre platformy aj nepriateľov

> 🎯 **Cieľ týždňa:** Editor je stabilný a dokáže spoľahlivo ukladať aj načítavať všetky entity bez chýb.

---

## 🗓️ Týždeň 2 – Nepriatelia a ich správanie
**Cieľ:** Zaviesť prvú verziu systému nepriateľov.

- [x] 👾 Vytvoriť základnú triedu `Enemy` a systém `EnemyManager`
- [x] 🔁 Prepojiť `EnemySpawnPoint` s `EnemyDef`
- [x] 🧱 Implementovať jednoduché správanie (napr. chôdza tam a späť)
- [x] 🎨 V editore pridať zmenu typu nepriateľa a farby/ikonky podľa typu
- [x] 🧪 Otestovať spawnovanie počas gameplayu

> 🎯 **Cieľ týždňa:** Nepriatelia sa správne objavujú a hýbu podľa definície v levele.

---

## 🗓️ Týždeň 3 – Background a vizuálne prvky
**Cieľ:** Pridať vizuálne vrstvy, ktoré spravia hru živšou.

- [x] 🌄 Implementovať dynamické pozadie (parallax)
- [x] 🧮 Pridať možnosť meniť vrstvy v editore
- [x] 📂 Vylepšiť načítanie/ukladanie pozadia do JSON
- [x] 🎨 Otestovať kombináciu pozadia, platforiem a nepriateľov v levele
- [ ] 🪶 Optimalizovať renderovanie, ak sa začnú prejavovať framedropy

> 🎯 **Cieľ týždňa:** Level editor podporuje vrstvené pozadie a všetko sa správne renderuje.

---

## 🗓️ Týždeň 4 – Gameplay testovanie a polish
**Cieľ:** Všetko, čo si vytvoril, prepojiť do hrateľného základu.

- [x] 🎮 Spustiť level z editora a otestovať gameplay loop
- [x] ⚙️ Doladiť pohyb hráča (kolízie, rýchlosť, skok)
- [x] 💥 Implementovať základný systém kolízie s nepriateľmi
- [x] 💡 Začať pripravovať základ pre UI (HP, skóre, level name)
- [x] 🧹 Refaktor: vyčistiť redundantné include-y a premenovať funkcie pre čitateľnosť

> 🎯 **Cieľ mesiaca:** Hrateľný základ – môžeš otvoriť level, hrať ho, uložiť a vrátiť sa do editora bez crashu.

---

## 💬 Poznámky
- 📅 Ak nestíhaš denne, stačí si urobiť *2–3 väčšie bloky počas víkendu*.
- ⚡ Každý týždeň si poznač, čo fungovalo a čo nie – môžeš to zapísať pod plán.
- 🎯 Ak po mesiaci bude všetko hotové, v novembri sa môžeme zamerať na **bojový systém** alebo **animácie**.

---

> **Tento plán si môžeš priebežne meniť.**  
> Dôležité je, aby si mal stále *jedno jasné “čo dnes spravím”* – aj malý krok denne znamená veľký posun.

# ----------------------------------------------------------------------

# 🗓️ November 2025 – Gameplay, interakcie a polish

Tento mesiac je zameraný na to, aby hra začala pôsobiť živšie a hrateľne.
Väčšina systémov už existuje, teraz ide o ich prepojenie, testovanie a doladenie pocitu z hrania.

---

## 🕹️ Týždeň 5 – Život v hre

**Cieľ:** Zaviesť základnú hernú logiku a interakciu medzi hráčom a nepriateľmi.

- [ ] 👣 Zjednotiť pohyb hráča (vyhladený pohyb, lepší skok)
- [x] 💥 Implementovať systém poškodenia (hráč stratí HP pri kontakte s nepriateľom)
- [x] ❤️ Pridať HP bar alebo jednoduchý indikátor zdravia
- [x] ⚙️ Rozšíriť EnemyManager o update logiku (napr. patrolovanie, sledovanie hráča)
- [x] 💀 Implementovať respawn alebo restart levelu po smrti hráča
> 🎯 **Cieľ týždňa:** Nepriatelia a hráč majú základnú interakciu – dá sa „zomrieť“ a znova hrať.

---

## 🧭 Týždeň 6 – Editor ↔ Gameplay loop

**Cieľ:** Spraviť gameplay testovanie rýchlejším a plynulejším.

- [x] 🔄 Umožni rýchle prepnutie medzi EditorState a GameState (napr. F5 = spustiť level, ESC = návrat)
- [x] 🗂️ Uistite sa, že všetky entity (platformy, spawn pointy, pozadie) sa správne prenášajú medzi stavmi
- [ ] 🖋️ Zobraz názov levelu počas hrania (z JSON súboru)
- [ ] 💾 Pridaj autosave/autoload pre rýchle testovanie (voliteľné)
- [x] 🧹 Refaktor: vyčisti include-y, odstráň nepoužívané premenné, zjednoť naming konvencie
> 🎯 **Cieľ týždňa:** Levely sa dajú hrať priamo z editora bez reštartu hry.

---

## 🎨 Týždeň 7 – UI & Vizuálny polish

**Cieľ:** Pridať základy užívateľského rozhrania a prvé vizuálne efekty.

- [ ] 🧱 Pridaj základné UI (HP, skóre, level name)
- [x] 🕶️ Pridaj jednoduché animácie – napr. pohyb nepriateľa, bliknutie pri poškodení
- [ ] 🌫️ Pridaj vizuálne efekty (napr. fade-in/out medzi levelmi)
- [ ] 🎧 Voliteľné: základný sound system (SFX pri skoku, zásahu, respawne)
> 🎯 **Cieľ týždňa:** Hra pôsobí živšie, hráč má spätnú väzbu na svoje akcie.

---

## 🧪 Týždeň 8 – Testovanie & Stabilita

**Cieľ:** Otestovať celé flow – editor → uloženie → gameplay → návrat do editora.

- [ ] 🧩 Prejsť všetky testovacie levely a zistiť, či sa správne načítavajú
- [x] 🐛 Odchytiť a zapísať najčastejšie chyby (napr. neplatné spawn pointy, chýbajúce textúry)
- [x] 📊 Pridať logovanie (napr. **std::cout** alebo debug overlay cez ImGui)
- [x] 🧠 Pripraviť si poznámky pre decembrový cieľ – bojový systém alebo animácie
> 🎯 **Cieľ mesiaca:** Stabilná hrateľná verzia, ktorú môžeš ukázať alebo zdieľať so spolužiakom na testovanie.

---

## 💬 Poznámky

- 🎯 Ak zvládneš polovicu úloh, budeš mať do decembra hotový kompletný gameplay základ.
- 🧠 Hlavné je testovať často – aj malé chyby v dátach (napr. spawn bez typu) sa dajú ľahko zachytiť.
- 🧩 V decembri sa môžeme zamerať na bojový systém, animácie alebo HUD polish – podľa toho, čo budeš chcieť prioritizovať.

# ----------------------------------------------------------------------

# 🗓️ December 2025 – AI, boj a polish

## 🧠 Týždeň 9 – AI základ: stavový stroj pre nepriateľa
**Cieľ:** Zaviesť prvú verziu AI, ktorá je jednoduchá, ale rozšíriteľná.

- [x] 🔄 Navrhnúť jednoduchý state machine pre nepriateľa (Idle → Patrol → Chase → Attack)
- [x] 👣 Dokončiť patrolovanie (chôdza tam a späť, obracanie sa, limity pohybu)
- [x] 👀 Pridať základné „vnímanie hráča“ (rádius alebo raycast dopredu)
- [x] 📏 Nastaviť parametre pre každý typ nepriateľa (speed, vision range, damage)

---

## ⚔️ Týždeň 10 – Základy boja
**Cieľ:** Zaviesť jednoduché útočenie a spätnú väzbu.

- [x] 💥 Implementovať „attack“ fázu nepriateľa (dotyk/kolízia alebo animovaný útok)
- [x] 🛡️ Uistiť sa, že hráč dostáva damage len raz, nie kontinuálne
- [x] ✨ Pridať vizuálnu spätnú väzbu (bliknutie hráča alebo efekt)
- [ ] 🔊 Voliteľné: pridať základné zvuky (attack, hit, krok)

---

## 🎮 Týždeň 11 – Prepojenie AI s gameplayom
**Cieľ:** AI sa správa konzistentne v každom levele.

- [x] 🧩 Pri respawne hráča resetovať aj správanie nepriateľov
- [x] 🔁 Otestovať AI vo viacerých leveloch s rôznymi platformami
- [ ] 🧭 Uistiť sa, že EnemySpawnPoint a EnemyDef sa prenášajú správne
- [ ] 🧹 Refaktor: odstrániť magic numbers a spraviť z nich parametre (speed, ranges, damage)

---

## ✨ Týždeň 12 – Polish, efekty a stabilita
**Cieľ:** Spraviť gameplay hladší a čitateľnejší.

- [ ] 🩹 Pridať krátke „invincibility frames“ po zásahu hráča
- [ ] 🚶 Pridať jednoduché animácie nepriateľov (otáčanie, idle animácia)
- [ ] 🌫️ Pridať efekt pri smrti nepriateľa
- [ ] 📈 Doladiť hodnoty AI (spravodlivý a čitateľný gameplay)
- [ ] 🧪 Otestovať celý flow: editor → hra → smrť → respawn → späť do editora

---

## Poznámky
- December má menej dní, plán je modulárny a môžeš ho presúvať do januára.
- Najťažšia časť bude návrh AI a samotný state machine.
