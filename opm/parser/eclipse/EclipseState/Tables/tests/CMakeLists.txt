foreach(tapp TableTests TableManagerTests TabdimsTests MultiRecordTableTests)
  opm_add_test(run${tapp} SOURCES ${tapp}.cpp
                          LIBRARIES opmparser ${Boost_LIBRARIES})
endforeach()
