/*
  Copyright (C) 2013 by Andreas Lauser

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

#define BOOST_TEST_MODULE MultiRecordTableTests

#include <opm/core/utility/platform_dependent/disable_warnings.h>
#include <boost/test/unit_test.hpp>
#include <opm/core/utility/platform_dependent/reenable_warnings.h>

#include <opm/parser/eclipse/Parser/ParserKeywords.hpp>
#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/Parser/ParseMode.hpp>
#include <opm/parser/eclipse/Deck/Deck.hpp>

// generic table classes
#include <opm/parser/eclipse/EclipseState/Tables/SimpleTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/MultiRecordTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/FullTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/TableManager.hpp>

// keyword specific table classes
#include <opm/parser/eclipse/EclipseState/Tables/PvtoTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/SwofTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/SgofTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/PlyadsTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/VFPProdTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/VFPInjTable.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>

#include <stdexcept>
#include <iostream>

using namespace Opm;


BOOST_AUTO_TEST_CASE( MultiRecordNumTables1 ) {
    ParserPtr parser(new Parser());
    boost::filesystem::path deckFile("testdata/integration_tests/TABLES/PVTO1.DATA");
    ParseMode parseMode;
    DeckPtr deck =  parser->parseFile(deckFile.string(), parseMode);
    BOOST_CHECK_EQUAL( MultiRecordTable::numTables( deck->getKeyword<ParserKeywords::PVTO>()) , 1);

    auto ranges = MultiRecordTable::recordRanges( deck->getKeyword<ParserKeywords::PVTO>() );
    auto range = ranges[0];
    BOOST_CHECK_EQUAL( range.first , 0 );
    BOOST_CHECK_EQUAL( range.second , 2 );
}


BOOST_AUTO_TEST_CASE( MultiRecordNumTables2 ) {
    ParserPtr parser(new Parser());
    boost::filesystem::path deckFile("testdata/integration_tests/TABLES/PVTO2.DATA");
    ParseMode parseMode;
    DeckPtr deck =  parser->parseFile(deckFile.string(), parseMode);
    BOOST_CHECK_EQUAL( MultiRecordTable::numTables( deck->getKeyword<ParserKeywords::PVTO>()) , 3);

    auto ranges = MultiRecordTable::recordRanges( deck->getKeyword<ParserKeywords::PVTO>() );
    auto range1 = ranges[0];
    BOOST_CHECK_EQUAL( range1.first , 0 );
    BOOST_CHECK_EQUAL( range1.second , 41 );

    auto range2 = ranges[1];
    BOOST_CHECK_EQUAL( range2.first , 42 );
    BOOST_CHECK_EQUAL( range2.second , 43 );

    auto range3 = ranges[2];
    BOOST_CHECK_EQUAL( range3.first , 44 );
    BOOST_CHECK_EQUAL( range3.second , 46 );
}


