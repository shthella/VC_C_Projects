cmake_minimum_required(VERSION 3.22.1)
project(Restaurant_Billing_System)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Source files for the library
set(LIBRARY_SOURCES
    
    debug.c
    helper_func.c
    display_menu.c
)

# Generate the static library
add_library(mylibrary STATIC ${LIBRARY_SOURCES})

# Source files for the client
set(CLIENT_SOURCES
    main.c
    admin.c
    customer.c
)

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Add client executable
add_executable(client ${CLIENT_SOURCES})

# Link the client executable with the library
target_link_libraries(client PRIVATE mylibrary)

# Link against SQLite3 library
target_link_libraries(client PRIVATE SQLite::SQLite3)

