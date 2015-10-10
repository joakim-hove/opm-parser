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

#include <opm/parser/eclipse/Parser/ParserKeywords.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/MultiRecordTable.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/PLYADSSTable.hpp>


namespace Opm {

    PLYADSSTable::PLYADSSTable(std::shared_ptr<const DeckKeyword> keyword , size_t tableIndex) {
        auto  recordRange = MultiRecordTable::recordRanges(keyword)[ tableIndex ];

        for (size_t  rowIdx = recordRange.first; rowIdx < recordRange.second; rowIdx++) {
            Opm::DeckRecordConstPtr deckRecord = keyword->getRecord(rowIdx);
            Opm::DeckItemConstPtr indexItem = deckRecord->getItem<ParserKeywords::PLYADSS::POLYMER_C>();
            Opm::DeckItemConstPtr dataItem = deckRecord->getItem<ParserKeywords::PLYADSS::DATA>();

            double indexValue = indexItem->getSIDouble( 0 );
            std::shared_ptr<Opm::SimpleTable> innerTable = std::make_shared<SimpleTable>( );
            innerTable->init( dataItem , std::vector<std::string> {"ADS_C"} );

            m_tables.push_back( make_pair( indexValue , innerTable ) );
        }
    }

}
