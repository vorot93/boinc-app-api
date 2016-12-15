project(
    'boinc-app-api',
    'c',
)

lib = shared_library(
    'boinc-app-api',
    [
        'models.c',
        'shmem.c',
    ],
    install: true,
)

install_headers(
    [
        'api.h',
        'models.h',
        'shmem.h',
    ],
    subdir: 'boinc-app-api',
)

import('pkgconfig').generate(
    libraries: lib,
    version: '1.0',
    name: 'boinc-app-api',
    description: 'API library for communication with BOINC applications.',
)
