cmake_minimum_required(VERSION 3.10)
project(IoT_Event_Management VERSION 1.0 CXX)

# Bắt buộc sử dụng chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Khai báo thư mục chứa tất cả các file Header (.h)
include_directories(include)

# Tự động quét và lấy toàn bộ file nguồn (.cpp) trong thư mục src/
file(GLOB SOURCES "src/*.cpp")

# Đóng gói và tạo ra file thực thi (Executable) tên là 'iot_system'
add_executable(iot_system ${SOURCES})