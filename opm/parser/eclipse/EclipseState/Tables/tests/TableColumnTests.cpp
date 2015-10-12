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

#define BOOST_TEST_MODULE TableColumnTests

#include <opm/common/utility/platform_dependent/disable_warnings.h>
#include <boost/test/unit_test.hpp>
#include <opm/common/utility/platform_dependent/reenable_warnings.h>

#include <opm/parser/eclipse/EclipseState/Tables/TableColumn.hpp>

BOOST_AUTO_TEST_CASE( CreateColumn ) {
    Opm::TableColumn column("COLUMN");
    BOOST_CHECK_EQUAL("COLUMN" , column.name());
    BOOST_CHECK_EQUAL( 0 , column.size() );
}


BOOST_AUTO_TEST_CASE( AddData) {
    Opm::TableColumn column("COLUMN");
    column.pushBackData(100);
    column.pushBackData(200);

    BOOST_CHECK_EQUAL( 2U , column.size() );
    column.pushBackDefault();
    column.pushBackDefault();
    BOOST_CHECK_EQUAL( 4U , column.size() );
}


BOOST_AUTO_TEST_CASE( Get ) {
    Opm::TableColumn column("COLUMN");
    BOOST_CHECK_THROW( column[0] , std::range_error );
    column.pushBackData(100);
    column.pushBackData(200);

    BOOST_CHECK_EQUAL( column[0] , 100 );
    BOOST_CHECK_EQUAL( column[1] , 200 );
    column.pushBackDefault();
    column.pushBackDefault();
    BOOST_CHECK_EQUAL( 4U , column.size() );
    column.pushBackData(500);
    BOOST_CHECK_THROW( column[2] , std::invalid_argument );
    BOOST_CHECK_THROW( column[3] , std::invalid_argument );
    BOOST_CHECK_EQUAL( column[4] , 500 );

    column.updateValue(2 , 250);
    column.updateValue(3 , 350);

    BOOST_CHECK_EQUAL( column[2] , 250 );
    BOOST_CHECK_EQUAL( column[3] , 350 );
}
