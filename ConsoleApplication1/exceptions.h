#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

struct FailoKlaida : public std::runtime_error
{
    explicit FailoKlaida( const std::string& msg ) : std::runtime_error( msg ) {}
};

struct DuomenuKlaida : public std::runtime_error
{
    explicit DuomenuKlaida( const std::string& msg ) : std::runtime_error( msg ) {}
};

#endif
