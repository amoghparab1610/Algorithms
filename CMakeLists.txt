include_directories(./include)

add_executable(graph_traversals graph/graph_traversal.cpp graph/graph.cpp)

set_target_properties(graph_traversals PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(graph_shortest_path graph/graph_shortest_paths.cpp graph/graph.cpp data_structures/heap.cpp)

set_target_properties(graph_shortest_path PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(graph_mst graph/graph_mst.cpp graph/graph.cpp data_structures/heap.cpp)

set_target_properties(graph_mst PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(graph_scc graph/graph_scc.cpp graph/graph.cpp data_structures/heap.cpp)

set_target_properties(graph_mst PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(graph_euler graph/graph_euler.cpp graph/graph.cpp
        graph/graph_euler.cpp)

set_target_properties(graph_euler PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(bin_tree_traversals tree/binary_tree_traversals.cpp
        include/binary_tree.hpp)

set_target_properties(bin_tree_traversals PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(tree_traversals tree/tree_traversals.cpp include/tree.hpp)

set_target_properties(tree_traversals PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(lca tree/least_common_ancestor.cpp include/tree.hpp)

set_target_properties(lca PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(tree_center_root tree/tree_center_root.cpp)

set_target_properties(tree_center_root PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(max_flow max_flow/max_flow_bfs_dfs.cpp include/max_flow_edge.hpp)

set_target_properties(max_flow PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(max_flow_dp max_flow/max_flow_dp.cpp include/max_flow_edge.hpp)

set_target_properties(max_flow_dp PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(max_flow_cap max_flow/max_flow_cap.cpp include/max_flow_edge.hpp)

set_target_properties(max_flow_cap PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(max_flow_dinic max_flow/max_flow_dinic.cpp include/max_flow_edge.hpp)

set_target_properties(max_flow_dinic PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(bipartite_matching graph/bipartite_matching.cpp include/max_flow_edge.hpp)

set_target_properties(bipartite_matching PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(mountain_scene leet_code/dynamic_programming/mountain_scene.cpp)

set_target_properties(mountain_scene PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(tower_of_hanoi recursion/tower_of_hanoi.cpp)

set_target_properties(tower_of_hanoi PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(narrow_art_gallery leet_code/dynamic_programming/narrow_art_gallery.cpp)

set_target_properties(narrow_art_gallery PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(bst tree/binary_search_tree.cpp)

set_target_properties(bst PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(bbst tree/balanced_binary_search_tree.cpp graph/graph.cpp)

set_target_properties(bbst PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(fenwick_tree tree/fenwick_tree.cpp)

set_target_properties(fenwick_tree PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(merge_sort sorting/merge_sort.cpp)

set_target_properties(merge_sort PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(quick_sort sorting/quick_sort.cpp)

set_target_properties(quick_sort PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(dominator graph/dominator.cpp)

set_target_properties(dominator PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(hamiltonian_cycle graph/hamiltonian_cycle.cpp)

set_target_properties(hamiltonian_cycle PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(graph_coloring graph/graph_coloring.cpp)

set_target_properties(graph_coloring PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(optimal_bst dynamic_programming/optimal_bst.cpp)

set_target_properties(optimal_bst PROPERTIES COMPILE_FLAGS "-std=c++17")

add_executable(control_flow graph/control_flow.cpp)

set_target_properties(control_flow PROPERTIES COMPILE_FLAGS "-std=c++17")
