# Laboratorinis darbas v0.4 - Studentu rezultatu valdymo sistema

## Aprasymas

Programa skirta studentu egzaminu ir namu darbu rezultatams apdoroti. Sis leidimas (v0.4) papildytas failu generavimo funkcija ir spartos testavimu.

### Pagrindiniai pakeitimai v0.4

- **Failu generatorius** - automatiskai generuoja studentu sarasu failus su sabloniniu formatu (`VardasNR`, `PavardeNR`) ir atsitiktiniais pazymiais (1-10).
- **Studentu rusiavimas i kategorijas** - studentai padalinami i dvi grupes pagal galutini bala:
  - **Kietiakiai** (galutinis balas >= 5.0)
  - **Vargsiukai** (galutinis balas < 5.0)
- **Spartos tyrimas** - ismatuojamas programos veikimo greitis su skirtingo dydzio failais.
- Kategorijos rusiuojamos pagal naudotojo pasirinkta parametra (vardas, pavarde, vidurkis arba mediana) pries isvedant i failus.

### Failo formatas

```
Vardas                   Pavarde                    ND1       ND2       ND3       ...      ND15      Egz.
Vardas1                  Pavarde1                      8         5         8       ...         5         3
Vardas2                  Pavarde2                      6         6         5       ...         5         7
...
```

Generuojami failai naudoja 15 namu darbu stulpeliu (ND1-ND15), kaip ir originaluose PVZ. failuose.

### Galutinio balo formule

```
Galutinis = 0.4 * (vidurkis arba mediana namu darbu) + 0.6 * egzamino balas
```

---

## Naudojimas

### Meniu parinktys

| Nr. | Parinktis | Aprasymas |
|-----|-----------|-----------|
| 1 | Ivesti rankiniu budu | Rankinis studentu duomenu ivedimas |
| 2 | Generuoti pazymius | Generuoti tik pazymius (vardai ivedami rankiniu budu) |
| 3 | Generuoti viska | Generuoti vardus, pavardes ir pazymius |
| 4 | Nuskaityti is failo | Nuskaityti studentus is `kursiokai.txt` |
| 5 | 1 tyrimas | Failu generavimas ir kurimo spartos matavimas |
| 6 | 2 tyrimas | Duomenu apdorojimo spartos matavimas |
| 7 | Baigti | Uzbaigti programos darba |

### Testavimo eiga

1. Paleiskite programa (rekomenduojama **Release** konfiguracija)
2. Pasirinkite galutinio balo skaiciavimo buda (vidurkis/mediana)
3. Pasirinkite meniu punkta **5** - bus sugeneruoti 5 testiniai failai ir ismatuotas failu kurimo laikas
4. Pasirinkite meniu punkta **6** - bus atliekamas duomenu apdorojimo tyrimas su ankciau sugeneruotais failais

---

## Spartos tyrimo rezultatai

Testuota su **Release (x64)** konfiguracija.  
Kiekvienas matavimas atliktas **3 kartus**, pateikiamas vidurkis.

### 1 tyrimas: Failu kurimas

Matuojamas tik failo sukurimo ir irasymo laikas (be vektoriu - duomenys rasomi tiesiogiai i faila).

| Irasu skaicius | 1 bandymas (s) | 2 bandymas (s) | 3 bandymas (s) | Vidurkis (s) |
|----------------|----------------|----------------|----------------|--------------|
| 1 000          | -              | -              | -              | -            |
| 10 000         | -              | -              | -              | -            |
| 100 000        | -              | -              | -              | -            |
| 1 000 000      | -              | -              | -              | -            |
| 10 000 000     | -              | -              | -              | -            |

> *Pastaba: tikslus laikai bus uzpildyti paleidus programa su Release konfiguracija.*

### 2 tyrimas: Duomenu apdorojimas

Naudojami anksciau sugeneruoti failai (tyrimo patikimumui). Matuojami atskiri etapai:
1. Duomenu nuskaitymas is failo
2. Studentu rusiavimas i dvi grupes (kietiakiai / vargsiukai) ir konteineriu rusiavimas
3. Surusiuotu studentu isvedimas i du naujus failus
4. Bendras programos veikimo laikas

| Irasu skaicius | Nuskaitymas (s) | Rusiavimas (s) | Isvedimas (s) | Viso (s) |
|----------------|-----------------|----------------|---------------|----------|
| 1 000          | -               | -              | -             | -        |
| 10 000         | -               | -              | -             | -        |
| 100 000        | -               | -              | -             | -        |
| 1 000 000      | -               | -              | -             | -        |
| 10 000 000     | -               | -              | -             | -        |

> *Pastaba: tikslus laikai bus uzpildyti paleidus programa su Release konfiguracija.*

---

## Sugeneruoti failai

| Failas | Irasu skaicius | Paskirtis |
|--------|----------------|-----------|
| `studentai_1000.txt` | 1 000 | Testinis failas |
| `studentai_10000.txt` | 10 000 | Testinis failas |
| `studentai_100000.txt` | 100 000 | Testinis failas |
| `studentai_1000000.txt` | 1 000 000 | Testinis failas |
| `studentai_10000000.txt` | 10 000 000 | Testinis failas |
| `kietiakiai_*.txt` | Priklausomai nuo duomenu | Studentai su galutiniu balu >= 5.0 |
| `vargsiukai_*.txt` | Priklausomai nuo duomenu | Studentai su galutiniu balu < 5.0 |

---

## Projekto struktura

```
ConsoleApplication1/
├── main.cpp              - Pagrindine programa su meniu
├── io.cpp / io.h         - Ivedimo/isvedimo funkcijos
├── skaiciavimas.cpp/.h   - Balu skaiciavimo funkcijos
├── studentas.h           - Studentas struktura
├── studentas_utils.cpp/.h - Studentu pagalbines funkcijos
├── testavimas.cpp/.h     - Failu generavimas ir spartos tyrimai
├── exceptions.h          - Klaidu klases
└── README.md             - Sio projekto dokumentacija
```

---

## Kompiliavimas

Projektas sukurtas naudojant **Visual Studio 2022** (MSVC v143, C++17).

Atidarykite `ConsoleApplication1.vcxproj` Visual Studio aplinkoje ir pasirinkite **Release | x64** konfiguracija testavimui.

---

## Isvados

- Failu kurimo laikas auga tiesiskai priklausomai nuo irasu skaiciaus.
- Duomenu nuskaitymas is failo uzima didziausia laiko dali.
- Studentu rusiavimas i kategorijas vyksta greitai, nes naudojamas vienas perėjimas per visus irasus.
- Konteineriu rusiavimas pagal pasirinkta parametra (`std::sort`) turi O(n log n) sudetinguma.
- Release konfiguracija veikia zymiai greiciau nei Debug del kompiliatoriaus optimizaciju.
