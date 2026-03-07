#ifndef IO_H
#define IO_H

#include "studentas.h"
#include <vector>
#include <iostream>

bool skaitytiSveika( int& reiksme, int min_val, int max_val );

void spausdintiRezultatus( std::vector<Studentas>& studentai, int m, bool mediana );

std::vector<Studentas> ivestiRankiniu( int& m, int& n );
std::vector<Studentas> nuskaitytiStudentus( );

#endif
