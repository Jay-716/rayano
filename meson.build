project(
    'rayano',
    'c',
    version: '0.1',
    license: 'MIT',
    default_options: [
        'c_std=c11',
        'warning_level=2',
        'werror=true',
    ],
)

add_project_arguments([
    '-Wno-unused-parameter',
    '-Wvla',
], language: 'c')

cc = meson.get_compiler('c')

if get_option('hot_reload')
  error('NOT IMPLEMENTED')
endif

if get_option('static_link')
  if not (host_machine.system() == 'linux' and host_machine.cpu_family() == 'x86_64')
    error('static_link only supports GNU/Linux x86_64 currently.')
  endif
  # Just download the prebuilt libraries from github releases.
  raylib_release = 'https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_linux_amd64.tar.gz'
  raylib_tarball = raylib_release.split('/')[-1]
  raylib_dir = raylib_tarball.substring(0, -7)
  fs = import('fs')
  if not fs.is_dir(raylib_dir)
    run_command('curl', '-L', '-O', raylib_release, check: true)
    run_command('tar', '-xf', raylib_tarball, check: true)
  endif
  raylib_inc = include_directories(raylib_dir / 'include')
  raylib_lib = cc.find_library('raylib', dirs: meson.current_source_dir() / raylib_dir / 'lib')
  raylib = declare_dependency(dependencies: raylib_lib, include_directories: raylib_inc)
else
  raylib = dependency('libraylib')
endif

srcs = ['main.c']

executable(
    'rayano',
    srcs,
    dependencies: [
      raylib
    ],
    install: true,
)

