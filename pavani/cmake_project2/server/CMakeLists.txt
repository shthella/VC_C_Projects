cmake_minimum_required(VERSION 3.22.1)
project(Restaurant_Billing_System)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Source files for the library
set(LIB_SOURCES
    debug.c
    display_menu.c
)

# Generate the static library
add_library(mylibrary STATIC ${LIB_SOURCES})

# Source files
set(SERVER_SOURCES
    main.c
    admin_s.c
    customer_s.c
    
)

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Add server and client executables
add_executable(server ${SERVER_SOURCES})

# Link the server executable with the library
target_link_libraries(server PRIVATE mylibrary)

# Link against SQLite3 library
target_link_libraries(server PRIVATE SQLite::SQLite3)


