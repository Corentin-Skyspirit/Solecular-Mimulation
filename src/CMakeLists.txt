target_sources(main PRIVATE  
    simulation.cpp
    reader.cpp
)

include_directories(../include)
target_compile_features(main PRIVATE cxx_std_23)