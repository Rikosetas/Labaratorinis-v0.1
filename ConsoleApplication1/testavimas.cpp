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

void generuotiFaila( const std::string& failoVardas, int irasu_sk, int nd_kiekis )
{
    std::ofstream out( failoVardas );
    if ( !out.is_open( ) )
        throw FailoKlaida( "Nepavyko sukurti failo: " + failoVardas );

    out << std::left
        << std::setw( 20 ) << "Vardas"
        << std::setw( 20 ) << "Pavarde";

    for ( int i = 1; i <= nd_kiekis; i++ )
        out << std::setw( 10 ) << ( "ND" + std::to_string( i ) );

    out << std::setw( 10 ) << "Egz" << "\n";

    for ( int i = 1; i <= irasu_sk; i++ )
    {
        out << std::left
            << std::setw( 20 ) << ( "Vardas" + std::to_string( i ) )
            << std::setw( 20 ) << ( "Pavarde" + std::to_string( i ) );

        for ( int j = 0; j < nd_kiekis; j++ )
            out << std::setw( 10 ) << ( rand( ) % 10 + 1 );

        out << std::setw( 10 ) << ( rand( ) % 10 + 1 ) << "\n";
    }

    out.close( );
}

std::vector<Studentas> nuskaitytiIsFailo( const std::string& failoVardas )
{
    std::ifstream stream( failoVardas );
    if ( !stream.is_open( ) )
        throw FailoKlaida( "Nepavyko atidaryti failo: " + failoVardas );

    std::vector<Studentas> out;
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
            if ( !( ss >> s.nd[ j ] ) )
                throw DuomenuKlaida( "Nepavyko nuskaityti ND: " + line );
        }

        if ( !( ss >> s.egzaminas ) )
            throw DuomenuKlaida( "Nepavyko nuskaityti egzamino: " + line );

        out.push_back( s );
    }

    return out;
}

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

void tyrimas1_failuKurimas( )
{
    const int dydziai[ ] = { 1000, 10000, 100000, 1000000, 10000000 };
    const std::string pavadinimai[ ] = {
        "studentai_1000.txt",
        "studentai_10000.txt",
        "studentai_100000.txt",
        "studentai_1000000.txt",
        "studentai_10000000.txt"
    };
    const int nd_kiekis = 5;
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
        double laikai[ bandymu_sk ] = { };
        double suma = 0.0;

        for ( int b = 0; b < bandymu_sk; b++ )
        {

            std::remove( pavadinimai[ i ].c_str( ) );

            auto start = std::chrono::high_resolution_clock::now( );
            generuotiFaila( pavadinimai[ i ], dydziai[ i ], nd_kiekis );
            auto end = std::chrono::high_resolution_clock::now( );


            laikai[ b ] = std::chrono::duration<double>( end - start ).count( );
            suma += laikai[ b ];
        }

        std::cout << std::left << std::setw( 18 ) << dydziai[ i ]
            << std::fixed << std::setprecision( 5 )
            << std::setw( 18 ) << laikai[ 0 ]
            << std::setw( 18 ) << laikai[ 1 ]
            << std::setw( 18 ) << laikai[ 2 ]
            << std::setw( 18 ) << ( suma / bandymu_sk ) << "\n";
    }

    std::cout << "\nFailai sugeneruoti ir issaugoti.\n";
}

void tyrimas2_duomenuApdorojimas( bool mediana )
{
    const int dydziai[ ] = { 1000, 10000, 100000, 1000000, 10000000 };
    const std::string pavadinimai[ ] = {
        "studentai_1000.txt",
        "studentai_10000.txt",
        "studentai_100000.txt",
        "studentai_1000000.txt",
        "studentai_10000000.txt"
    };
    const int bandymu_sk = 3;

    int rusiavimas = pasirinktiRusiavima( );

    std::cout << "\n================ 2 TYRIMAS: Duomenu apdorojimas ================\n\n";

    std::cout << std::left
        << std::setw( 15 ) << "Irasu sk."
        << std::setw( 18 ) << "Nuskaitymas(s)"
        << std::setw( 18 ) << "Rusiavimas(s)"
        << std::setw( 18 ) << "Isvedimas(s)"
        << std::setw( 18 ) << "Viso(s)" << "\n";
    std::cout << std::string( 87, '-' ) << "\n";

    for ( int i = 0; i < 5; i++ )
    {
        {
            std::ifstream test( pavadinimai[ i ] );
            if ( !test.is_open( ) )
            {
                std::cout << std::left << std::setw( 15 ) << dydziai[ i ]
                    << "Failas nerastas! Pirma paleiskite 1 tyrima.\n";
                continue;
            }
        }

        double nuskaitymo_suma = 0.0;
        double rusiavimo_suma = 0.0;
        double isvedimo_suma = 0.0;
        double viso_suma = 0.0;

        for ( int b = 0; b < bandymu_sk; b++ )
        {
            auto viso_start = std::chrono::high_resolution_clock::now( );

            auto start = std::chrono::high_resolution_clock::now( );
            std::vector<Studentas> studentai = nuskaitytiIsFailo( pavadinimai[ i ] );
            auto end = std::chrono::high_resolution_clock::now( );
            double nuskaitymo_laikas = std::chrono::duration<double>( end - start ).count( );

            start = std::chrono::high_resolution_clock::now( );

            std::vector<Studentas> kietiakiai;
            std::vector<Studentas> vargsiukai;

            for ( const auto& s : studentai )
            {
                double galutinis;

                if ( mediana )
                    galutinis = skaiciuotiGalutini( skaiciuotiMediana( s.nd, s.n ), s.egzaminas );
                else
                    galutinis = skaiciuotiGalutini( skaiciuotiVidurki( s.nd, s.n ), s.egzaminas );

                if ( galutinis >= 5.0 )
                    kietiakiai.push_back( s );
                else
                    vargsiukai.push_back( s );
            }

            rusiuotiStudentus( kietiakiai, rusiavimas );
            rusiuotiStudentus( vargsiukai, rusiavimas );

            end = std::chrono::high_resolution_clock::now( );

            double rusiavimo_laikas = std::chrono::duration<double>( end - start ).count( );

            start = std::chrono::high_resolution_clock::now( );

            std::string kietiakiu_failas = "kietiakiai_" + std::to_string( dydziai[ i ] ) + ".txt";
            std::string vargsiuku_failas = "vargsiukai_" + std::to_string( dydziai[ i ] ) + ".txt";

            isvestiKategorijaIFaila( kietiakiu_failas, kietiakiai, mediana );
            isvestiKategorijaIFaila( vargsiuku_failas, vargsiukai, mediana );

            end = std::chrono::high_resolution_clock::now( );
            double isvedimo_laikas = std::chrono::duration<double>( end - start ).count( );

            auto viso_end = std::chrono::high_resolution_clock::now( );
            double viso_laikas = std::chrono::duration<double>( viso_end - viso_start ).count( );

            nuskaitymo_suma += nuskaitymo_laikas;
            rusiavimo_suma += rusiavimo_laikas;
            isvedimo_suma += isvedimo_laikas;
            viso_suma += viso_laikas;
        }

        std::cout << std::left << std::setw( 15 ) << dydziai[ i ]
            << std::fixed << std::setprecision( 5 )
            << std::setw( 18 ) << ( nuskaitymo_suma / bandymu_sk )
            << std::setw( 18 ) << ( rusiavimo_suma / bandymu_sk )
            << std::setw( 18 ) << ( isvedimo_suma / bandymu_sk )
            << std::setw( 18 ) << ( viso_suma / bandymu_sk ) << "\n";
    }

    std::cout << "\nRezultatai - vidurkiniai laikai is " << bandymu_sk << " bandymu.\n";
}
