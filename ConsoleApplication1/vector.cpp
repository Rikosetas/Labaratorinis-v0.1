#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

struct Studentas
{
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int n;
    int egzaminas;
};

double skaiciuotiVidurki( const int* nd, int n )
{
    if ( n == 0 )
        return 0.0;

    double suma = 0;
    for ( int i = 0; i < n; i++ )
        suma += nd [ i ];

    return suma / n;
}

double skaiciuotiMediana( int* nd, int n )
{
    if ( n == 0 )
        return 0.0;

    int* laikinas = new int [ n ];
    for ( int i = 0; i < n; i++ )
        laikinas [ i ] = nd [ i ];

    std::sort( laikinas, laikinas + n );

    double rezultatas;
    if ( n % 2 == 0 )
        rezultatas = ( laikinas [ n / 2 - 1 ] + laikinas [ n / 2 ] ) / 2.0;
    else
        rezultatas = laikinas [ n / 2 ];

    delete[ ] laikinas;
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
    s.nd = new int [ n ];

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

void free_students( Studentas* studentai, int m )
{
    for ( int i = 0; i < m; i++ )
        delete[ ] studentai [ i ].nd;

    delete[ ] studentai;
}

void spausdintiRezultatus( const std::vector<Studentas>& studentai, int m, bool mediana )
{
    std::cout << "\n" << std::string( 70, '-' ) << "\n";

    std::cout << std::left << std::setw( 25 ) << "Pavarde Vardas"
        << std::setw( 20 ) << "Galutinis (Vid.)";

    if ( mediana )
        std::cout << std::setw( 20 ) << "Galutinis (Med.)";

    std::cout << "\n";
    std::cout << std::string( 70, '-' ) << "\n";

    for ( int i = 0; i < m; i++ )
    {
        double vid = skaiciuotiGalutini( skaiciuotiVidurki( studentai [ i ].nd, studentai [ i ].n ), studentai [ i ].egzaminas );

        std::cout << std::left << std::setw( 25 )
            << ( studentai [ i ].pavarde + " " + studentai [ i ].vardas )
            << std::fixed << std::setprecision( 2 )
            << std::setw( 20 ) << vid;

        if ( mediana )
        {
            double med = skaiciuotiGalutini( skaiciuotiMediana( studentai [ i ].nd, studentai [ i ].n ), studentai [ i ].egzaminas );
            std::cout << std::setw( 20 ) << med;
        }

        std::cout << "\n";
    }

    std::cout << std::string( 70, '-' ) << "\n";
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
        studentas.nd.reserve( n );

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
        std::cout << "  4 - Baigti darba\n";
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

            free_students( studentai, m );
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

            Studentas* studentai = new Studentas [ m ];

            for ( int i = 0; i < m; i++ )
            {
                std::cout << "  Studentas #" << ( i + 1 ) << " vardas: ";
                std::cin >> studentai [ i ].vardas;

                std::cout << "  Studentas #" << ( i + 1 ) << " pavarde: ";
                std::cin >> studentai [ i ].pavarde;

                generuotiPazymius( studentai [ i ], n );
            }

            spausdintiRezultatus( studentai, m, mediana );
            free_students( studentai, m );
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

            Studentas* studentai = new Studentas [ m ];

            for ( int i = 0; i < m; i++ )
            {
                generuotiVarda( studentai [ i ], i );
                generuotiPazymius( studentai [ i ], n );
            }

            spausdintiRezultatus( studentai, m, mediana );
            free_students( studentai, m );
            break;
        }

        case 4:
        {
            std::cout << "Programa baigta.\n";
            break;
        }
        }

    } while ( meniu != 4 );

    return 0;
}