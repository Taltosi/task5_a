# CXX = g++
# # CC = clang++-14
# CFLAGS = -std=c++17 -Wall -Wextra
# LDFLAGS = -std=c++17

# TARGET = st_pipeline

# $(TARGET): st_pipeline.o threadSafeQueue.o activeObject.o
# 	$(CC) $(LDFLAGS) -o $@ $^

# st_pipeline.o: st_pipeline.cpp
# 	$(CC) $(CFLAGS) -c $<

# threadSafeQueue.o: threadSafeQueue.cpp threadSafeQueue.hpp
# 	$(CC) $(CFLAGS) -c $<

# activeObject.o: activeObject.cpp activeObject.hpp threadSafeQueue.hpp
# 	$(CC) $(CFLAGS) -c $<

# clean:
# 	rm -f $(TARGET) *.o

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lm -lstdc++ -pthread

st_pipeline: st_pipeline.o threadSafeQueue.o activeObject.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

st_pipeline.o: st_pipeline.cpp activeObject.hpp threadSafeQueue.hpp
	$(CXX) $(CXXFLAGS) -c $<

threadSafeQueue.o: threadSafeQueue.cpp threadSafeQueue.hpp
	$(CXX) $(CXXFLAGS) -c $<

activeObject.o: activeObject.cpp activeObject.hpp threadSafeQueue.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f st_pipeline *.o