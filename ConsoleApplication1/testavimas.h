#ifndef TESTAVIMAS_H
#define TESTAVIMAS_H

#include "studentas.h"
#include <string>
#include <vector>

void generuotiFaila( const std::string& failoVardas, int irasu_sk, int nd_kiekis );

std::vector<Studentas> nuskaitytiIsFailo( const std::string& failoVardas );

void isvestiKategorijaIFaila( const std::string& failoVardas,
    const std::vector<Studentas>& studentai, bool mediana );

void tyrimas1_failuKurimas( );

void tyrimas2_duomenuApdorojimas( bool mediana );

#endif
