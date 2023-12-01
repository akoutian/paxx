list(
    APPEND
    SYSTEM_DEPENDENCIES_REQUIRED
    Gpgmepp
    doctest
    expected-lite
    lyra
    qrcodegencpp
)

foreach(dep IN LISTS SYSTEM_DEPENDENCIES_REQUIRED)
    find_package(${dep} REQUIRED)
endforeach()
