cmake_minimum_required(VERSION 3.16.3)

project (phone_book)
find_package(Protobuf REQUIRED) # Команда находит пути к компилятору protoc и библиотеке libprotobuf
include_directories(${Protobuf_INCLUDE_DIRS}) # Добавляем в include path пути к библиотеке protobuf
include_directories(${CMAKE_CURRENT_BINARY_DIR}) # В ${CMAKE_CURRENT_BINARY_DIR} будут файлы, сгенерированные компилятором protoс, путь к ним надо добавить в include path

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS contact.proto) # Здесь надо перечислить все ваши .proto-файлы
add_executable(test test.cpp phone_book.cpp ${PROTO_SRCS} ${PROTO_HDRS}) # Здесь надо перечислить все ваши .cpp-файлы, в том числе и сгенерированные protoc'ом
target_link_libraries(test ${Protobuf_LIBRARIES}) # компонуем наш исполняемый файл с библиотекой libprotobuf 
target_compile_features(test PUBLIC cxx_std_17 )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
