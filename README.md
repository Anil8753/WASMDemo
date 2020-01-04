Repository contains the working examples of web assembly using C++/emscripten.
Each example is a seperate working cmake project. Run the followings command to run the examples.

Setup environment

1. open bash
2. go to emsdk directorty and followings run command
    ./emsdk activate latest
    source ./emsdk_env.sh
    
Build setup

3. create directory 'build' 
    mkdir build
    cd build

4. configure cmake
    emconfigure cmake .. 

5. build the source to wasm
    emmake make
    
6. go to the web directory and start the python server by running server.py

7. open browser and launch url http://localhost:8000/
