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
#include <utility>
#include <iostream>

#include <opm/parser/eclipse/EclipseState/Tables/SimpleTable.hpp>

namespace Opm {

    SimpleTable::SimpleTable()
    {

    }



    void SimpleTable::addColumns() {
        for (size_t colIdx = 0; colIdx < m_schema->size(); ++colIdx) {
            const auto& schemaColumn = m_schema->getColumn( colIdx );
            TableColumn column(schemaColumn); // Some move trickery here ...
            m_columns.insert( schemaColumn.name() , column );
        }
    }


// create table from single record
void SimpleTable::init(Opm::DeckItemConstPtr deckItem)
{
    addColumns();
    if ( (deckItem->size() % numColumns()) != 0)
        throw std::runtime_error("Number of columns in the data file is"
                                 "inconsistent with the ones specified");
    {
        size_t rows = deckItem->size() / numColumns();
        for (size_t colIdx = 0; colIdx < numColumns(); ++colIdx) {
            auto& column = getColumn( colIdx );
            for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {
                size_t deckItemIdx = rowIdx*numColumns() + colIdx;
                if (deckItem->defaultApplied(deckItemIdx))
                    column.addDefault( );
                else
                    column.addValue( deckItem->getSIDouble(deckItemIdx) );
            }
            if (colIdx > 0)
                column.applyDefaults(getColumn( 0 ));
        }
    }
}

size_t SimpleTable::numColumns() const {
    return m_schema->size();
}

size_t SimpleTable::numRows() const {
    const auto column0 = getColumn(0);
    return column0.size();
}


    const TableColumn& SimpleTable::getColumn( const std::string& name) const {
        return std::forward<const TableColumn &>(m_columns.get_const( name ));
    }

    const TableColumn& SimpleTable::getColumn( size_t columnIndex )  const {
        return std::forward<const TableColumn &>(m_columns.get_const( columnIndex ));
    }


    TableColumn& SimpleTable::getColumn( const std::string& name) {
        return std::forward<TableColumn &>(m_columns.get( name ));
    }

    TableColumn& SimpleTable::getColumn( size_t columnIndex ) {
        return std::forward<TableColumn &>(m_columns.get( columnIndex ));
    }



double SimpleTable::evaluate(const std::string& columnName, double xPos) const
{
    const auto& argColumn = getColumn( 0 );
    const auto& valueColumn = getColumn( columnName );

    const auto index = argColumn.lookup( xPos );
    return valueColumn.eval( index );
}






}
