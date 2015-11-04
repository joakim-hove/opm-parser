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


#ifndef _TABLE_COLUMN_HPP_
#define _TABLE_COLUMN_HPP_

#include <string>
#include <vector>


namespace Opm {

    class TableColumn {
    public:
        TableColumn(const std::string& name , bool ascending , bool strictlyMonotonic);
        size_t size( ) const;
        const std::string& name() const;
        void addValue(double);
        void addDefault();
        void updateValue(size_t index, double value);
        double operator[](size_t index) const;

    private:
        void assertOrder(double value1 , double value2) const;
        void assertUpdate(size_t index, double value) const;
        void assertPrevious(size_t index , double value) const;
        void assertNext(size_t index , double value) const;

        std::string m_name;
        bool m_ascending;
        bool m_strictlyMonotonic;
        std::vector<double> m_values;
        std::vector<bool> m_default;
    };
}


#endif