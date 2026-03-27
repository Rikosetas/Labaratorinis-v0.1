#include "testavimas.h"
#include "skaiciavimas.h"
#include "studentas_utils.h"
#include "exceptions.h"
#include "io.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>

// ---------------------------------------------------------------------------
// Failo generavimas
// ---------------------------------------------------------------------------
void generuotiFaila( const std::string& failoVardas, int irasu_sk, int nd_kiekis )
{
    std::ofstream out( failoVardas );
    if ( !out.is_open( ) )
        throw FailoKlaida( "Nepavyko sukurti failo: " + failoVardas );

    out << std::left
        << std::setw( 25 ) << "Vardas"
        << std::setw( 27 ) << "Pavarde";

    for ( int i = 1; i <= nd_kiekis; i++ )
        out << std::setw( 10 ) << ( "ND" + std::to_string( i ) );

    out << std::setw( 10 ) << "Egz." << "\n";

    for ( int i = 1; i <= irasu_sk; i++ )
    {
        out << std::left
            << std::setw( 25 ) << ( "Vardas" + std::to_string( i ) )
            << std::setw( 27 ) << ( "Pavarde" + std::to_string( i ) )
            << std::right;

        for ( int j = 0; j < nd_kiekis; j++ )
            out << std::setw( 10 ) << ( rand( ) % 10 + 1 );

        out << std::setw( 10 ) << ( rand( ) % 10 + 1 ) << "\n";
    }

    out.close( );
}

// ---------------------------------------------------------------------------
// Backward-compatible vector nuskaitymas
// ---------------------------------------------------------------------------
std::vector<Studentas> nuskaitytiIsFailo( const std::string& failoVardas )
{
    return nuskaitytiIsFailoT<std::vector<Studentas>>( failoVardas );
}

// ---------------------------------------------------------------------------
// Kategorijos isvedimas i faila
// ---------------------------------------------------------------------------
void isvestiKategorijaIFaila( const std::string& failoVardas,
    const std::vector<Studentas>& studentai, bool mediana )
{
    std::ofstream out( failoVardas );
    if ( !out.is_open( ) )
        throw FailoKlaida( "Nepavyko sukurti failo: " + failoVardas );

    out << std::left
        << std::setw( 20 ) << "Pavarde"
        << std::setw( 20 ) << "Vardas"
        << std::setw( 20 ) << "Galutinis" << "\n";
    out << std::string( 60, '-' ) << "\n";

    for ( const auto& s : studentai )
    {
        double galutinis;

        if ( mediana )
            galutinis = skaiciuotiGalutini( skaiciuotiMediana( s.nd, s.n ), s.egzaminas );
        else
            galutinis = skaiciuotiGalutini( skaiciuotiVidurki( s.nd, s.n ), s.egzaminas );

        out << std::left
            << std::setw( 20 ) << s.pavarde
            << std::setw( 20 ) << s.vardas
            << std::fixed << std::setprecision( 2 )
            << std::setw( 20 ) << galutinis << "\n";
    }

    out.close( );
}

// ---------------------------------------------------------------------------
// 1 tyrimas: failu generavimas ir kurimo spartos matavimas
// ---------------------------------------------------------------------------
void tyrimas1_failuKurimas( )
{
    const int dydziai[] = { 1000, 10000, 100000, 1000000, 10000000 };
    const std::string pavadinimai[] = {
        "studentai_1000.txt",
        "studentai_10000.txt",
        "studentai_100000.txt",
        "studentai_1000000.txt",
        "studentai_10000000.txt"
    };
    const int nd_kiekis = 15;
    const int bandymu_sk = 3;

    std::cout << "\n================ 1 TYRIMAS: Failu kurimas ================\n\n";

    std::cout << std::left
        << std::setw( 18 ) << "Irasu sk."
        << std::setw( 18 ) << "1 bandymas (s)"
        << std::setw( 18 ) << "2 bandymas (s)"
        << std::setw( 18 ) << "3 bandymas (s)"
        << std::setw( 18 ) << "Vidurkis (s)" << "\n";
    std::cout << std::string( 90, '-' ) << "\n";

    for ( int i = 0; i < 5; i++ )
    {
        double laikai[bandymu_sk] = { };
        double suma = 0.0;

        for ( int b = 0; b < bandymu_sk; b++ )
        {
            std::remove( pavadinimai[i].c_str( ) );

            auto start = std::chrono::high_resolution_clock::now( );
            generuotiFaila( pavadinimai[i], dydziai[i], nd_kiekis );
            auto end = std::chrono::high_resolution_clock::now( );

            laikai[b] = std::chrono::duration<double>( end - start ).count( );
            suma += laikai[b];
        }

        std::cout << std::left << std::setw( 18 ) << dydziai[i]
            << std::fixed << std::setprecision( 5 )
            << std::setw( 18 ) << laikai[0]
            << std::setw( 18 ) << laikai[1]
            << std::setw( 18 ) << laikai[2]
            << std::setw( 18 ) << ( suma / bandymu_sk ) << "\n";
    }

    std::cout << "\nFailai sugeneruoti ir issaugoti.\n";
}
