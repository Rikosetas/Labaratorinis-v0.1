#ifndef TESTAVIMAS_H
#define TESTAVIMAS_H

#include "studentas.h"
#include "skaiciavimas.h"
#include "exceptions.h"

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <iterator>

void generuotiFaila( const std::string& failoVardas, int irasu_sk, int nd_kiekis );
void tyrimas1_failuKurimas( );
void tyrimasKonteineriu( bool mediana );
void tyrimasStrategiju( bool mediana );

std::vector<Studentas> nuskaitytiIsFailo( const std::string& failoVardas );

void isvestiKategorijaIFaila( const std::string& failoVardas,
    const std::vector<Studentas>& studentai, bool mediana );

#endif
