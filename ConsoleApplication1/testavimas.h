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

// ---------------------------------------------------------------------------
// Template: nuskaityti faila i bet kuri konteinerio tipa (vector, list, deque)
// ---------------------------------------------------------------------------
template<typename Container>
Container nuskaitytiIsFailoT( const std::string& failoVardas )
{
    std::ifstream stream( failoVardas );
    if ( !stream.is_open( ) )
        throw FailoKlaida( "Nepavyko atidaryti failo: " + failoVardas );

    Container out;
    std::string line;

    if ( !std::getline( stream, line ) )
        return out;

    std::stringstream header_stream( line );
    std::string column;
    std::vector<std::string> cols;

    while ( header_stream >> column )
        cols.push_back( column );

    size_t nd_count = cols.size( ) >= 3 ? cols.size( ) - 3 : 0;

    while ( std::getline( stream, line ) )
    {
        if ( line.empty( ) )
            continue;

        std::stringstream ss( line );
        Studentas s;
        s.n = static_cast<int>( nd_count );
        s.nd.resize( nd_count );

        if ( !( ss >> s.vardas >> s.pavarde ) )
            throw DuomenuKlaida( "Nepavyko nuskaityti: " + line );

        for ( size_t j = 0; j < nd_count; j++ )
        {
            if ( !( ss >> s.nd[j] ) )
                throw DuomenuKlaida( "Nepavyko nuskaityti ND: " + line );
        }

        if ( !( ss >> s.egzaminas ) )
            throw DuomenuKlaida( "Nepavyko nuskaityti egzamino: " + line );

        out.push_back( s );
    }

    return out;
}

// ---------------------------------------------------------------------------
// Apskaiciuoti galutini bala
// ---------------------------------------------------------------------------
inline double apskaiciuotiGalutiniBala( const Studentas& s, bool mediana )
{
    if ( mediana )
        return skaiciuotiGalutini( skaiciuotiMediana( s.nd, s.n ), s.egzaminas );
    else
        return skaiciuotiGalutini( skaiciuotiVidurki( s.nd, s.n ), s.egzaminas );
}

// ---------------------------------------------------------------------------
// Rusiuoti konteinerio elementus pagal galutini bala (didejimo tvarka).
// std::list naudoja savo .sort(), vector/deque naudoja std::sort.
// ---------------------------------------------------------------------------
template<typename Container>
void rusiuotiPagalGalutini( Container& c, bool mediana )
{
    auto comp = [mediana]( const Studentas& a, const Studentas& b ) {
        return apskaiciuotiGalutiniBala( a, mediana ) < apskaiciuotiGalutiniBala( b, mediana );
    };

    if constexpr ( std::is_same_v<Container, std::list<Studentas>> )
        c.sort( comp );
    else
        std::sort( c.begin( ), c.end( ), comp );
}

// ---------------------------------------------------------------------------
// 1 strategija: bendras konteineris lieka nepakeistas,
// studentai kopijuojami i du naujus konteinerius (kietiakiai ir vargsiukai).
// Neefektyvu atminties atzvilgiu - studentas egzistuoja dviejuose konteineriuose.
// ---------------------------------------------------------------------------
template<typename Container>
void strategija1( const Container& studentai, Container& kietiakiai,
    Container& vargsiukai, bool mediana )
{
    for ( const auto& s : studentai )
    {
        if ( apskaiciuotiGalutiniBala( s, mediana ) >= 5.0 )
            kietiakiai.push_back( s );
        else
            vargsiukai.push_back( s );
    }
}

#endif
