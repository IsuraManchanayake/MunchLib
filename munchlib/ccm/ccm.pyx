# py_myfunction.pyx
from libcpp.vector cimport vector
from libcpp.utility cimport pair
from cpython cimport bool

# Importing Python objects for handling within Cython
from libc.stdint cimport uint64_t
cimport cython

cdef extern from "interface.h":
    pair[vector[double], vector[double]] cpp_ccm_coordination(
        const vector[double] &X1, const vector[double] &X2,
        uint64_t embed_size, uint64_t lag, const vector[uint64_t] &lib_lens
    ) nogil

cdef pair[vector[double], vector[double]] calculate_ccm_coordination_nogil(
        vector[double] &X1,
        vector[double] &X2,
        uint64_t embed_size,
        uint64_t lag,
        vector[uint64_t] &lib_lens
    ) nogil:
    return cpp_ccm_coordination(X1, X2, embed_size, lag, lib_lens)

# Public function callable from Python, handling GIL
def calculate_ccm_coordination(X1, X2, embed_size, lag, lib_lens):
    cdef vector[double] X1_vec = X1
    cdef vector[double] X2_vec = X2
    cdef uint64_t embed_size_c = embed_size
    cdef uint64_t lag_c = lag
    cdef vector[uint64_t] lib_lens_vec = lib_lens
    cdef pair[vector[double], vector[double]] result
    with nogil:  # Use a nogil block to call the nogil function
        result = calculate_ccm_coordination_nogil(X1_vec, X2_vec, embed_size_c, lag_c, lib_lens_vec)
    return result