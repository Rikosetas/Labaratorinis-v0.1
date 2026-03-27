# Laboratorinis darbas v1.0 - Studentu rezultatu valdymo sistema

## Aprasymas

Programa skirta studentu egzaminu ir namu darbu rezultatams apdoroti. Ji leidzia nuskaityti studentu duomenis is failu, skaiciuoti galutinius balus, rusiuoti studentus ir skirstyti juos i dvi kategorijas: **kietiakius** (galutinis >= 5.0) ir **vargsiukus** (galutinis < 5.0).

Versija v1.0 papildyta triju konteineriu tipu (`std::vector`, `std::list`, `std::deque`) palaikymu, triju skaidymo strategiju realizacija bei issamiu spartos tyrimu.

### Galutinio balo formule

```
Galutinis = 0.4 * (vidurkis arba mediana namu darbu) + 0.6 * egzamino balas
```

---

## Versiju istorija (Release History)

| Versija | Aprasymas |
|---------|-----------|
| v0.1 | Pradine versija: rankinis ivedimas, pazymiu generavimas, galutinio balo skaiciavimas |
| v0.2 | Failu skaitymas, duomenu apdorojimas is `kursiokai.txt` |
| v0.3 | Kodo refaktorizavimas: atskiri `.h/.cpp` failai, exception handling |
| v0.4 | Failu generatorius, studentu skirstymas i kategorijas, spartos tyrimai |
| **v1.0** | **Triju konteineriu palaikymas (vector, list, deque), 3 skaidymo strategijos, issamios spartos analizes, CMake palaikymas** |

### Pagrindiniai v1.0 pakeitimai

- **Konteineriu palaikymas** - programa testuojama su `std::vector`, `std::list` ir `std::deque` konteineriais naudojant C++ template funkcijas
- **3 skaidymo strategijos**:
  - **1 strategija** - kopijuoti studentus i du naujus konteinerius (originalas lieka nepakeistas)
  - **2 strategija** - vargsiukus perkelti i nauja konteinerio ir istrinti is originalo
  - **3 strategija** - optimizuota su `std::stable_partition` ir efektyviu range perkėlimu
- **Issamios spartos analizes** - konteineriu ir strategiju palyginimas su skirtingo dydzio duomenu rinkiniais
- **CMake palaikymas** - paruostas `CMakeLists.txt` kompiliavimui bet kurioje OS

---

## Testavimo sistemos parametrai

| Parametras | Reiksme |
|------------|---------|
| **CPU** | AMD Ryzen 9 9950X 16-Core Processor |
| **RAM** | 64 GB DDR5 4800 MHz |
| **Diskas** | Samsung SSD 990 PRO 2TB (NVMe SSD) |
| **OS** | Windows 10 x64 |
| **Kompiliatorius** | MSVC v143 (Visual Studio 2022) |
| **Konfiguracija** | Release x64, /O2 optimizacija |
