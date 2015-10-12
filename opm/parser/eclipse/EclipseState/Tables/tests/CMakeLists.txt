foreach(tapp TableManagerTests TabdimsTests MultiRecordTableTests TableContainerTests
             PLYADSSTableTests TableColumnTests )

  opm_add_test(run${tapp} SOURCES ${tapp}.cpp
                          LIBRARIES opmparser ${Boost_LIBRARIES})

endforeach()
