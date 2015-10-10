/*
  Copyright (C) 2015 by Statoil ASA

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE PLYADSSTests

#include <opm/common/utility/platform_dependent/disable_warnings.h>
#include <boost/test/unit_test.hpp>
#include <opm/common/utility/platform_dependent/reenable_warnings.h>

#include <opm/parser/eclipse/Deck/Deck.hpp>
#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/Parser/ParseMode.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/PLYADSSTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/MultiRecordTable.hpp>



BOOST_AUTO_TEST_CASE(create) {
    Opm::ParserPtr parser(new Opm::Parser());
    const std::string deck_input =
        "TABDIMS \n"
        "-- NTSFUN  NTPVT   NSSFUN   NPPVT   NTFIP   NRPVT \n"
        "    3       1        100     50       1           / \n"
        " \n"
        "PLYADSS \n"
        "0.00    0.0 \n"
        "        0 \n"
        "        1 \n"
        "        2 \n"
        "        3 / \n"
        "1.00    1.0 \n"
        "        0 \n"
        "        10 \n"
        "        20 \n"
        "        30  / \n"
        "2.00    2.0 \n"
        "        0 \n"
        "        100 \n"
        "        200 \n"
        "        300 / \n"
        "/ \n"
        "6.00    6.0 \n"
        "        0 \n"
        "        1 \n"
        "        2 \n"
        "        3   / \n"
        "7.00    7.0 \n"
        "        0 \n"
        "        10 \n"
        "        20 \n"
        "        30  / \n"
        "8.00    8.0 \n"
        "        0 \n"
        "        100 \n"
        "        200 \n"
        "        300 / \n"
        "/ \n"
        "3.00    4.0 \n"
        "        0 \n"
        "        1 \n"
        "        2 \n"
        "        3   / \n"
        "4.00    4.0 \n"
        "        0 \n"
        "        10 \n"
        "        20 \n"
        "        30  / \n"
        "5.00    5.0 \n"
        "        0 \n"
        "        100 \n"
        "        200 \n"
        "        300 / \n"
        "/ \n";

    Opm::DeckPtr deck =  parser->parseString(deck_input , Opm::ParseMode());
    Opm::DeckKeywordConstPtr kw = deck->getKeyword("PLYADSS");
    BOOST_CHECK_EQUAL( 3U , Opm::MultiRecordTable::numTables( kw ));

    Opm::PLYADSSTable table0( kw , 0);
    Opm::PLYADSSTable table1( kw , 1);
    Opm::PLYADSSTable table2( kw , 2);
}


