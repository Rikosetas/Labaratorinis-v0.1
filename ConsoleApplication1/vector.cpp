#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

struct Studentas
{
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int n;
    int egzaminas;
};

double skaiciuotiVidurki( const std::vector<int>& nd, int n )
{
    if ( n == 0 )
        return 0.0;

    double suma = 0;
    for ( int i = 0; i < n; i++ )
        suma += nd [ i ];

    return suma / n;
}

double skaiciuotiMediana( const std::vector<int>& nd, int n )
{
    if ( n == 0 )
        return 0.0;

    std::vector<int> copy = nd;
    std::sort( copy.begin(), copy.end() );

    double rezultatas;
    if ( n % 2 == 0 )
        rezultatas = ( copy [ n / 2 - 1 ] + copy [ n / 2 ] ) / 2.0;
    else
        rezultatas = copy [ n / 2 ];

    return rezultatas;
}

double skaiciuotiGalutini( double nd_rezultatas, int egz )
{
    return 0.4 * nd_rezultatas + 0.6 * egz;
}

bool skaitytiSveika( int& reiksme, int min_val, int max_val )
{
    if ( !( std::cin >> reiksme ) )
    {
        std::cin.clear( );
        std::cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
        return false;
    }

    if ( reiksme < min_val || reiksme > max_val )
        return false;

    return true;
}


void generuotiPazymius( Studentas& s, int n )
{
    s.n = n;
    s.nd.resize( n );

    for ( int i = 0; i < n; i++ )
        s.nd [ i ] = rand( ) % 10 + 1;

    s.egzaminas = rand( ) % 10 + 1;
}

void generuotiVarda( Studentas& s, int indeksas )
{
    std::string vardai[ ] = { "Jonas", "Petras", "Ona", "Marta", "Lukas", "Egle", "Tomas", "Inga" };
    std::string pavardes[ ] = { "Jonaitis", "Petraitis", "Kazlauskas", "Stankevicious", "Vaitkus", "Lukosius" };


    s.vardas = vardai [ indeksas % 8 ];
    s.pavarde = pavardes [ indeksas % 6 ];
}

int pasirinktiRusiavima( ) 
{
    int pasirinkimas;

    std::cout << "\nRusiavimo pasirinkimas:\n";
    std::cout << "  1 - Pagal varda\n";
    std::cout << "  2 - Pagal pavarde\n";
    std::cout << "  3 - Pagal galutini (vidurkis)\n";
    std::cout << "  4 - Pagal galutini (mediana)\n";
    std::cout << "Pasirinkimas: ";

    while ( !skaitytiSveika( pasirinkimas, 1, 4 ) ) {
        std::cout << "Neteisinga reiksme. Pasirinkite 1-4: ";
    }

    return pasirinkimas;
}

void rusiuotiStudentus( std::vector<Studentas>& studentai, int rusiavimas ) 
{
    switch ( rusiavimas ) {
    case 1:
        std::sort( studentai.begin( ), studentai.end( ), [ ] ( const Studentas& a, const Studentas& b ) {
            return a.vardas < b.vardas;
            } );
        break;
    case 2:
        std::sort( studentai.begin( ), studentai.end( ), [ ] ( const Studentas& a, const Studentas& b ) {
            return a.pavarde < b.pavarde;
            } );
        break;
    case 3:
        std::sort( studentai.begin( ), studentai.end( ), [ ] ( const Studentas& a, const Studentas& b ) {
            double ga = skaiciuotiGalutini( skaiciuotiVidurki( a.nd, a.n ), a.egzaminas );
            double gb = skaiciuotiGalutini( skaiciuotiVidurki( b.nd, b.n ), b.egzaminas );
            return ga > gb;
            } );
        break;
    case 4:
        std::sort( studentai.begin( ), studentai.end( ), [ ] ( const Studentas& a, const Studentas& b ) {
            double ga = skaiciuotiGalutini( skaiciuotiMediana( a.nd, a.n ), a.egzaminas );
            double gb = skaiciuotiGalutini( skaiciuotiMediana( b.nd, b.n ), b.egzaminas );
            return ga > gb;
            } );
        break;
    }
}

template <typename Stream>
void spausdintiIStream( Stream& out, const std::vector<Studentas>& studentai, bool mediana ) 
{
    out << "\n" << std::string( 70, '-' ) << "\n";

    out << std::left << std::setw( 15 ) << "Pavarde"
        << std::setw( 15 ) << "Vardas"
        << std::setw( 20 ) << "Galutinis (Vid.)";

    if ( mediana ) out << std::setw( 20 ) << "Galutinis (Med.)";

    out << "\n" << std::string( 70, '-' ) << "\n";

    for ( const auto& s : studentai ) 
    {
        double vid = skaiciuotiGalutini( skaiciuotiVidurki( s.nd, s.n ), s.egzaminas );

        out << std::left << std::setw( 15 ) << s.pavarde
            << std::setw( 15 ) << s.vardas
            << std::fixed << std::setprecision( 2 )
            << std::setw( 20 ) << vid;

        if ( mediana ) 
        {
            double med = skaiciuotiGalutini( skaiciuotiMediana( s.nd, s.n ), s.egzaminas );
            out << std::setw( 20 ) << med;
        }

        out << "\n";
    }

    out << std::string( 70, '-' ) << "\n";
}

void spausdintiRezultatus( std::vector<Studentas>& studentai, int m, bool mediana )
{
    int rusiavimas = pasirinktiRusiavima( );
    rusiuotiStudentus( studentai, rusiavimas );

    int outputPasirinkimas;
    std::cout << "\nIsvedimo vieta:\n  1 - Ekranas\n  2 - Failas\nPasirinkimas: ";

    while ( !skaitytiSveika( outputPasirinkimas, 1, 2 ) ) {
        std::cout << "Neteisinga reiksme. Pasirinkite 1 arba 2: ";
    }

    if ( outputPasirinkimas == 1 ) 
    {
        spausdintiIStream( std::cout, studentai, mediana );
    }
    else 
    {
        std::ofstream stream( "rezultatai.txt" );
        if ( !stream.is_open( ) ) 
        {
            std::cout << "Nepavyko atidaryti failo rasymui!\n";
            return;
        }

        spausdintiIStream( stream, studentai, mediana );
        std::cout << "Rezultatai issaugoti faile: rezultatai.txt\n";
    }
}

std::vector<Studentas> ivestiRankiniu( int& m, int& n )
{
    std::cout << "Kiek namu darbu? ";

    while ( !skaitytiSveika( n, 1, 100 ) ) {
        std::cout << "Neteisinga reiksme. Iveskite 1-100: ";
    }

    m = 0;
    int capacity = 2;
    std::vector<Studentas> studentai;

    while ( true )
    {
        Studentas studentas;

        std::cout << "\n--- Studentas #" << ( m + 1 ) << " (arba iveskite 'baigti') ---\n";
        std::cout << "Vardas: ";

        std::cin >> studentas.vardas;

        if ( studentas.vardas == "baigti" )
            break;



        std::cout << "Pavarde: ";
        std::cin >> studentas.pavarde;

        studentas.n = n;
        studentas.nd.resize( n );

        for ( int j = 0; j < n; j++ )
        {
            std::cout << "  ND" << ( j + 1 ) << " balas (1-10): ";
            while ( !skaitytiSveika( studentas.nd [ n ], 1, 10 ) ) {
                std::cout << "  Neteisinga reiksme (1-10): ";
            }
        }

        std::cout << "Egzamino balas (1-10): ";

        while ( !skaitytiSveika( studentas.egzaminas, 1, 10 ) ) {
            std::cout << "  Neteisinga reiksme (1-10): ";
        }

        studentai.push_back( studentas );

        m++;
    }

    return studentai;
}

std::vector<Studentas> nuskaitytiStudentus( )
{
    std::ifstream stream( "kursiokai.txt" );
    if ( !stream.is_open( ) )
        return { };

    auto start = std::chrono::high_resolution_clock::now( );

    std::vector<Studentas> out;

    std::string line;
    std::getline( stream, line );

    std::stringstream header_stream( line );

    std::string column;
    std::vector<std::string> cols;

    while ( header_stream >> column )
        cols.push_back( column );

    while ( std::getline( stream, line ) )
    {
        std::stringstream ss( line );

        Studentas studentas;
        studentas.n = cols.size( ) - 3;
        studentas.nd.resize( cols.size( ) - 3 );

        ss >> studentas.vardas >> studentas.pavarde;

        for ( int i = 0; i < cols.size( ) - 3; i++ )
        {
            ss >> studentas.nd [ i ];
        }

        ss >> studentas.egzaminas;

        out.push_back( studentas );
    }

    auto end = std::chrono::high_resolution_clock::now( );

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( end - start );
    std::cout << "Nuskaityti " << out.size( ) << " studentu is per " << std::fixed << std::setprecision( 3 ) << elapsed.count() << " ms\n";

    return out;
}

int main( )
{
    std::srand( std::time( nullptr ) );

    int skaiciavimas = { };
    std::cout << "Galutinio balo skaiciavimas:\n  1 - Vidurkis\n  2 - Mediana\nPasirinkimas: ";

    while ( !skaitytiSveika( skaiciavimas, 1, 2 ) ) {
        std::cout << "Neteisinga reiksme. Pasirinkite 1 arba 2: ";
    }

    bool mediana = ( skaiciavimas == 2 );

    int m { };
    int n { };

    int meniu;

    do {
        std::cout << "\n========== MENIU ==========\n";
        std::cout << "  1 - Ivesti duomenis rankiniu budu\n";
        std::cout << "  2 - Generuoti tik pazymius\n";
        std::cout << "  3 - Generuoti vardus, pavardes ir pazymius\n";
        std::cout << "  4 - Nuskaityti studentus is failo\n";
        std::cout << "  5 - Baigti darba\n";
        std::cout << "Pasirinkimas: ";

        if ( !skaitytiSveika( meniu, 1, 4 ) )
        {
            std::cout << "Neteisinga reiksme.\n";
            continue;
        }

        switch ( meniu )
        {
        case 1:
        {
            std::vector<Studentas> studentai = ivestiRankiniu( m, n );

            if ( m > 0 )
                spausdintiRezultatus( studentai, m, mediana );
            else
                std::cout << "Nera studentu duomenu.\n";
            break;
        }

        case 2:
        {
            std::cout << "Studentu skaicius: ";
            while ( !skaitytiSveika( m, 1, 10000 ) ) {
                std::cout << "Neteisinga reiksme: ";
            }

            std::cout << "Namu darbu skaicius: ";
            while ( !skaitytiSveika( n, 1, 100 ) ) {
                std::cout << "Neteisinga reiksme: ";
            }

            std::vector<Studentas> studentai( m );

            for ( int i = 0; i < m; i++ )
            {
                std::cout << "  Studentas #" << ( i + 1 ) << " vardas: ";
                std::cin >> studentai [ i ].vardas;

                std::cout << "  Studentas #" << ( i + 1 ) << " pavarde: ";
                std::cin >> studentai [ i ].pavarde;

                generuotiPazymius( studentai [ i ], n );
            }

            spausdintiRezultatus( studentai, m, mediana );
            break;
        }

        case 3:
        {
            std::cout << "Studentu skaicius: ";
            while ( !skaitytiSveika( m, 1, 10000 ) ) {
                std::cout << "Neteisinga reiksme: ";
            }

            std::cout << "Namu darbu skaicius: ";
            while ( !skaitytiSveika( n, 1, 100 ) ) {
                std::cout << "Neteisinga reiksme: ";
            }

            std::vector<Studentas> studentai( m );
            //studentai.resize( m );

            for ( int i = 0; i < m; i++ )
            {
                generuotiVarda( studentai [ i ], i );
                generuotiPazymius( studentai [ i ], n );
            }

            spausdintiRezultatus( studentai, m, mediana );
            break;
        }

        case 4:
        { 
            std::vector<Studentas> studentai = nuskaitytiStudentus();

            if ( studentai.size( ) > 0 )
                spausdintiRezultatus( studentai, studentai.size(), mediana );
            else
                std::cout << "Nera studentu duomenu.\n";

            break;
        }

        case 5:
        {
            std::cout << "Programa baigta.\n";
            break;
        }
        }

    } while ( meniu != 4 );

    return 0;
}