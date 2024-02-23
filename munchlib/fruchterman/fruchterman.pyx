# py_myfunction.pyx
from libcpp.vector cimport vector
from libcpp.utility cimport pair
from cpython cimport bool

# Importing Python objects for handling within Cython
from libc.stdint cimport uint64_t
cimport cython

cdef extern from "fruchterman.h":
    vector[pair[double, double]] cpp_calculate_fruchterman_reingold_layout(const vector[uint64_t]& nodes, const vector[pair[uint64_t, uint64_t]]& edges, double speed, double area, double gravity, uint64_t iter)


# Function to extract nodes and edges from a NetworkX graph
@cython.boundscheck(False)  # Deactivate bounds checking for performance
@cython.wraparound(False)  # Deactivate negative indexing.
def calculate_fruchterman_reingold_layout(graph, speed, area, gravity, iter):
    # Extracting nodes
    cdef vector[uint64_t] vec_nodes = [node for node in graph.nodes()]

    # Extracting edges
    cdef vector[pair[uint64_t, uint64_t]] vec_edges = [(int(u), int(v)) for u, v in graph.edges()]

    # Call the C++ function
    cdef vector[pair[double, double]] result = cpp_calculate_fruchterman_reingold_layout(vec_nodes, vec_edges, speed, area, gravity, iter)

    # Convert result back to Python list of tuples
    return [(item.first, item.second) for item in result]