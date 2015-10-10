foreach(tapp TableManagerTests TabdimsTests MultiRecordTableTests TableContainerTests
             PLYADSSTableTests)

  opm_add_test(run${tapp} SOURCES ${tapp}.cpp
                          LIBRARIES opmparser ${Boost_LIBRARIES})

endforeach()
