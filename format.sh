find ./solutions -type f \
	\( -name "*.h" -o -name "*.hh" -o -name "*.hpp" -o -name "*.hxx" \
		 -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" -o -name "*.ipp" -o -name "*.tpp" \) \
	-exec clang-format -i {} +

clang-format -i ./main.cpp
