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
#ifndef OPM_PARSER_PVTO_TABLE_HPP
#define	OPM_PARSER_PVTO_TABLE_HPP

#include "FullTable.hpp"
#include "PvtoInnerTable.hpp"
#include "PvtoOuterTable.hpp"

namespace Opm {
    // forward declaration
    class TableManager;

    class PvtoTable : public Opm::FullTable<Opm::PvtoOuterTable, Opm::PvtoInnerTable>
    {
    public:
        typedef Opm::FullTable<Opm::PvtoOuterTable, Opm::PvtoInnerTable> ParentType;
        friend class TableManager;
        using ParentType::init;


#ifdef BOOST_TEST_MODULE
        // DO NOT TRY TO CALL THIS METHOD! it is only for the unit tests!
        void initFORUNITTESTONLY(Opm::DeckKeywordConstPtr keyword, size_t tableIdx)
        { init(keyword, tableIdx); }
#endif

    };

    typedef std::shared_ptr<PvtoTable> PvtoTablePtr;
    typedef std::shared_ptr<const PvtoTable> PvtoConstTablePtr;
}

#endif
