/*
  Copyright 2015 Statoil ASA.

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

#ifndef OPM_PLYADSS_TABLE_HPP
#define	OPM_PLYADSS_TABLE_HPP

#include <vector>

#include <opm/parser/eclipse/Deck/DeckKeyword.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/SimpleTable.hpp>

namespace Opm {


    /**
       This table interacts with the ADSALNOD table. Lookup goes as
       follows:

          1. Take the polymer concentration and look up the correct
             inner table in the PLYADSS multi table.

          2. Take the salinity and look up the right nodes in the
             ADSALNOD table.

          3. Use the node index from the ADSALNOD table to look up the
             right values in the correct inner table.

    */
    class PLYADSSTable {
    public:
        PLYADSSTable( std::shared_ptr<const DeckKeyword> keyword , size_t tableIndex);

    private:
        std::vector<std::pair<double , std::shared_ptr<const SimpleTable> > > m_tables;
    };
}

#endif
