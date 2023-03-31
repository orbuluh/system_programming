add_library(util SHARED error_handling.cpp network_handling.cpp
                        robust_io.cpp signal_handling.cpp process_ctrl.cpp
                        memory_handling.cpp io_handling.cpp
                        )
# need to install libfmt-dev
find_package(fmt REQUIRED)
target_link_libraries(util PRIVATE fmt::fmt)