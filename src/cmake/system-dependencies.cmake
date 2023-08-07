find_package(Gpgmepp REQUIRED)

# transitive requirement of dacap-clip unfortuanely its recipe as of Thu Aug  3 11:33:53 PM EEST
# 2023 does not require it, as it should
find_library(xvmc XvMC REQUIRED)
