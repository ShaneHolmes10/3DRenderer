.PHONY: lint format demo test docs

lint:
	find 3DRenderer -name "*.cpp" | xargs clang-tidy -p build/ --fix

format:
	find 3DRenderer -name "*.cpp" -o -name "*.h" | xargs clang-format -i

demo_%:
	cmake -B build && cmake --build build --target demo_$* && ./build/bin/examples/demo_$*

test:
	cmake --build build --target check

docs:
	cmake --build build --target docs
