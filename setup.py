from setuptools import setup, Extension, find_packages
from Cython.Build import cythonize


# Define the extension module
extensions = [
    Extension(
        "munchlib.fruchterman.calculate_fruchterman_reingold_layout",                      # Name of the module
        sources=["munchlib/fruchterman/fruchterman.pyx",         # Cython source file
                 "munchlib/fruchterman/src/fruchterman.cpp"],              # C++ source files
        include_dirs=["munchlib/fruchterman/src"],                        # Include directory for the C++ header
        language="c++",
        extra_compile_args=['-O3', '-std=c++2a'],
    ),
    Extension(
        "munchlib.ccm.calculate_ccm_coordination",                      # Name of the module
        sources=[
            "munchlib/ccm/ccm.pyx",
            "munchlib/ccm/src/ccm.cpp",
            "munchlib/ccm/src/embed.cpp",
            "munchlib/ccm/src/interface.cpp",
            "munchlib/ccm/src/knn.cpp",
            "munchlib/ccm/src/utils.cpp",
        ],
        include_dirs=["munchlib/ccm/src"],
        language="c++",
        extra_compile_args=['-O3', '-std=c++2a'],
    ),
]

# Use cythonize on the extension object
setup(
    name="MunchLib",
    version="0.1",
    author="Isura Manchanayaka",
    packages=find_packages(),
    ext_modules=cythonize(extensions, language_level="3"),
)
