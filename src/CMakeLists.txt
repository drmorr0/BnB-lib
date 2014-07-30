
set(bnb_core_src bnbtree.cpp)
set(bnb_search_src
	dfs.cpp
   )

add_library(bnb SHARED ${bnb_core_src} ${bnb_search_src})


