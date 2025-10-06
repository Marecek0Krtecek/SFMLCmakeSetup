# 🎯 Mesačný plán vývoja hry (Október 2025)

Tento plán je navrhnutý tak, aby si mohol postupovať po malých, ale dôležitých krokoch — približne **1 hodinu denne**.
Každý víkend máš priestor na väčšie úlohy alebo refaktorovanie.

---

## 🗓️ Týždeň 1 – Údržba, stabilita a vylepšenie editora
**Cieľ:** Doladiť workflow v editore a pripraviť pôdu pre prácu s nepriateľmi.

- [ ] 🧩 Zjednotiť ukladanie a načítanie (spawn pointy, platformy, pozadie)
- [ ] 🧰 Upratať kód v `EditorState` – presunúť opakujúce sa časti do funkcií
- [ ] 💾 Vyriešiť správne otváranie a ukladanie súborov cez ImGuiFileDialog (prípadne pridať fallback)
- [ ] 🧠 Pridať možnosť Undo/Redo pre nepriateľov
- [ ] 🔍 Otestovať všetky tri akcie (Add, Move, Delete) pre platformy aj nepriateľov

> 🎯 **Cieľ týždňa:** Editor je stabilný a dokáže spoľahlivo ukladať aj načítavať všetky entity bez chýb.

---

## 🗓️ Týždeň 2 – Nepriatelia a ich správanie
**Cieľ:** Zaviesť prvú verziu systému nepriateľov.

- [ ] 👾 Vytvoriť základnú triedu `Enemy` a systém `EnemyManager`
- [ ] 🔁 Prepojiť `EnemySpawnPoint` s `EnemyDef`
- [ ] 🧱 Implementovať jednoduché správanie (napr. chôdza tam a späť)
- [ ] 🎨 V editore pridať zmenu typu nepriateľa a farby/ikonky podľa typu
- [ ] 🧪 Otestovať spawnovanie počas gameplayu

> 🎯 **Cieľ týždňa:** Nepriatelia sa správne objavujú a hýbu podľa definície v levele.

---

## 🗓️ Týždeň 3 – Background a vizuálne prvky
**Cieľ:** Pridať vizuálne vrstvy, ktoré spravia hru živšou.

- [ ] 🌄 Implementovať dynamické pozadie (parallax)
- [ ] 🧮 Pridať možnosť meniť vrstvy v editore
- [ ] 📂 Vylepšiť načítanie/ukladanie pozadia do JSON
- [ ] 🎨 Otestovať kombináciu pozadia, platforiem a nepriateľov v levele
- [ ] 🪶 Optimalizovať renderovanie, ak sa začnú prejavovať framedropy

> 🎯 **Cieľ týždňa:** Level editor podporuje vrstvené pozadie a všetko sa správne renderuje.

---

## 🗓️ Týždeň 4 – Gameplay testovanie a polish
**Cieľ:** Všetko, čo si vytvoril, prepojiť do hrateľného základu.

- [ ] 🎮 Spustiť level z editora a otestovať gameplay loop
- [ ] ⚙️ Doladiť pohyb hráča (kolízie, rýchlosť, skok)
- [ ] 💥 Implementovať základný systém kolízie s nepriateľmi
- [ ] 💡 Začať pripravovať základ pre UI (HP, skóre, level name)
- [ ] 🧹 Refaktor: vyčistiť redundantné include-y a premenovať funkcie pre čitateľnosť

> 🎯 **Cieľ mesiaca:** Hrateľný základ – môžeš otvoriť level, hrať ho, uložiť a vrátiť sa do editora bez crashu.

---

## 💬 Poznámky
- 📅 Ak nestíhaš denne, stačí si urobiť *2–3 väčšie bloky počas víkendu*.
- ⚡ Každý týždeň si poznač, čo fungovalo a čo nie – môžeš to zapísať pod plán.
- 🎯 Ak po mesiaci bude všetko hotové, v novembri sa môžeme zamerať na **bojový systém** alebo **animácie**.

---

> **Tento plán si môžeš priebežne meniť.**  
> Dôležité je, aby si mal stále *jedno jasné “čo dnes spravím”* – aj malý krok denne znamená veľký posun.
