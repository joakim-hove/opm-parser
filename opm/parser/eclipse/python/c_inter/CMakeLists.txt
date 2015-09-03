add_library(copmparser SHARED
cparser.cc
cdeck.cc cdeck_keyword.cc cdeck_record.cc cdeck_item.cc
cparse_mode.cc
ctable_manager.cc
)

target_link_libraries(copmparser opmparser)
install( TARGETS copmparser DESTINATION ${CMAKE_INSTALL_LIBDIR} )
