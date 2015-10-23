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

#include <algorithm>
#include <stdexcept>

#include <opm/parser/eclipse/EclipseState/Tables/TableColumn.hpp>

namespace Opm {

    TableColumn::TableColumn(const std::string& name) {
        m_name = name;
    }

    const std::string& TableColumn::name() const {
        return m_name;
    }

    bool TableColumn::hasDefault() const {
        const auto find_true = std::find(m_defaulted.begin() , m_defaulted.end() , true);
        if (find_true == m_defaulted.end())
            return false;
        else
            return true;
    }

    double TableColumn::getMax() const {
        if (m_values.size() == 0)
            throw std::invalid_argument("Can not ask for maximum of empty column");

        if (hasDefault())
            throw std::invalid_argument("Can not search for min/max in a vector with defaults");

        return *std::max_element( m_values.begin() , m_values.end() );
    }

    double TableColumn::getMin() const {
        if (m_values.size() == 0)
            throw std::invalid_argument("Can not ask for minimum of empty column");

        if (hasDefault())
            throw std::invalid_argument("Can not search for min/max in a vector with defaults");

        return *std::min_element( m_values.begin() , m_values.end() );
    }

    size_t TableColumn::size() const {
        return m_values.size();
    }

    void TableColumn::pushBackData( double value ) {
        m_values.push_back( value );
        m_defaulted.push_back( false );
    }


    void TableColumn::pushBackDefault() {
        m_values.push_back( -1 );
        m_defaulted.push_back( true );
    }


    void TableColumn::updateValue(size_t index , double value) {
        if (index < m_values.size()) {
            m_values[index] = value;
            m_defaulted[index] = false;
        } else
            throw std::range_error("Index value: " + std::to_string( index ) + " out of range: [0.." + std::to_string( m_values.size() ) + ")");
    }


    const double& TableColumn::operator[](size_t index) const {
        if (index < m_values.size()) {
            if (m_defaulted[index])
                throw std::invalid_argument("No value has been assigned for index: " + std::to_string( index ));
            else
                return m_values[index];
        } else
            throw std::range_error("Index value: " + std::to_string( index ) + " out of range: [0.." + std::to_string( m_values.size() ) + ")");
    }
}


