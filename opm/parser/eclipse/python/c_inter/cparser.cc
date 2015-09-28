#include <opm/parser/eclipse/Deck/Deck.hpp>
#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/Parser/ParseMode.hpp>


extern "C" {

    Opm::Deck * parser_parse_file(const Opm::Parser * parser , const char * file) {
        Opm::ParseMode parseMode;
        return parser->newDeckFromFile( file , parseMode );
    }


    void * parser_alloc() {
        Opm::Parser * parser = new Opm::Parser( true );
        return parser;
    }

    bool parser_has_keyword(const Opm::Parser * parser , const char * keyword) {
        return parser->hasInternalKeyword( keyword );
    }


    void parser_free(Opm::Parser * parser) {
        delete parser;
    }

}
