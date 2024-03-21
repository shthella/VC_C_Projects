cmake_minimum_required(VERSION 3.22.1)
project(Restaurant_Billing_System)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Source files for the library
set(LIBRARY_SOURCES
    admin.c
    customer.c
    debug.c
    header_file.c
    display_menu.c
    display_restaurants.c
)

# Generate the static library
add_library(mylibrary STATIC ${LIBRARY_SOURCES})

# Source files for the client
set(CLIENT_SOURCES
    main.c
    add_item.c
    display_order_history.c
    place_order.c
    remove_item.c
    update_item.c
    clear_input_buffer.c
)

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Add client executable
add_executable(client ${CLIENT_SOURCES})

# Link the client executable with the library
target_link_libraries(client PRIVATE mylibrary)

# Link against SQLite3 library
target_link_libraries(client PRIVATE SQLite::SQLite3)

