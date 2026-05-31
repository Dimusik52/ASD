# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# название проекта
project(Algorithms-and-Data-Structures)

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)         # подхватываем функции, реализованные в файле function.cmake
                                      # для простоты мы объединили наборы команд для создания статической библиотеки
								      # и для создания исполняемого проекта в отдельные функции

add_subdirectory(lib_easy_example)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_easy_example
add_subdirectory(lib_point)
add_subdirectory(lib_circle)
add_subdirectory(lib_matrix)
add_subdirectory(lib_TVector)
add_subdirectory(lib_trianglematrix)
add_subdirectory(lib_mathvector)
add_subdirectory(lib_stack)
add_subdirectory(lib_stacklist)
add_subdirectory(lib_queue)
add_subdirectory(lib_queuelist)
add_subdirectory(lib_list)
add_subdirectory(lib_doublylinkedlist)
add_subdirectory(lib_dsu)
add_subdirectory(lib_itable)
add_subdirectory(lib_unsortedtablem)
add_subdirectory(lib_unsortedtablel)
add_subdirectory(lib_sortedtablem)
add_subdirectory(lib_skiplist)
add_subdirectory(lib_monom)
add_subdirectory(lib_polynom)
add_subdirectory(lib_binarytree)
add_subdirectory(lib_heap)
add_subdirectory(lib_prqueue)
add_subdirectory(lib_hashtablec)
add_subdirectory(lib_graphveclist)
add_subdirectory(lib_graphedgelist)
add_subdirectory(lib_hashtablehh)
add_subdirectory(lib_algorithms)
add_subdirectory(lib_tree)
add_subdirectory(lib_treetable)
add_subdirectory(lib_bsttable)
add_subdirectory(lib_avltree)
add_subdirectory(lib_avltreetable)
add_subdirectory(lib_rbtree)
add_subdirectory(lib_rbtreetable)



add_subdirectory(main)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем main

option(BTEST "build test?" ON)        # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                             # если тесты подключены         
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()


