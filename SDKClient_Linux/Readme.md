# MANUS SDK Client - Linux
Install [cppzmq](https://github.com/zeromq/cppzmq/tree/master), a dependency for the LEAP Hand MANUS SDK 
```bash
sudo apt-get install libzmq3-dev
download and unzip the lib, cd to directory
mkdir build
cd build
cmake ..
sudo make -j4 install
```
To build, in this directory, run:
```
make
```

To run the SDK Client, run:
```
./SDKClient_Linux.out
```

In the start menu, choose Core Integrated.
